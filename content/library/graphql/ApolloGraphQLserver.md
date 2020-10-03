---
title: "ApolloGraphQLserver"
metaTitle: "ApolloGraphQLserver"
metaDescription: "This is the meta description"
---

# Apollo Server 및 Sequelize를 사용하여 Node.js에서 GraphQL 서버를 설정하는 방법

## 1단계 데이터베이스 설정

데이터베이스 설정부터 시작하겠습니다.  
데이터베이스에 SQLite를 사용할 것입니다.  
또한 Node.js 용 ORM 인 Sequelize를 사용하여 데이터베이스와 상호 작용합니다.  

#### ORM은 무엇인가요?

ORM이란 Object Relational Mapping(객체-관계-매핑)으로  
객체와 관계형 데이터베이스의 데이터를 자동으로 매핑(연결)해주는 것을 의미합니다.  
객체 지향 프로그래밍은 클래스를 사용하고, 관계형 데이터베이스는 테이블을 사용합니다.  
객체 모델과 관계형 모델 간에 불일치가 존재하는데,  
ORM을 통해 객체 간의 관계를 바탕으로 SQL을 자동으로 생성하여 불일치를 해결할 수 있습니다.  

- 먼저 새 프로젝트를 만들어봅시다.  

````
$ mkdir graphql-recipe-server
$ cd graphql-recipe-server
$ npm init -y
````

- 다음으로 Sequelize를 설치하겠습니다.  

````
npm install sequelize sequelize-cli sqlite3
````

Sequelize를 설치하는 것 외에도 sqlite3 Node.js용 패키지도 설치합니다.  

- 이제 cli를 이용하여 프로젝트를 만듭니다.  

````
node_modules/.bin/sequelize init
````

cli를 사용하면 다음과 같은 폴더가 생성됩니다.  

- config: Sequelize에게 데이터베이스 연결 방법을 알려주는 설정 파일이 들어 있습니다.
- models: 프로젝트의 모든 모델을 포함하고 모든 모델을 index.js통합 하는 파일 도 포함합니다 .
- migrations: 모든 마이그레이션 파일을 포함합니다.
- seeders: 모든 시드 파일을 포함합니다.

`config/config.json`에 아래의 내용을 설정해주세요.  
````
// config/config.json

{
  "development": {
    "dialect": "sqlite",
    "storage": "./database.sqlite"
  }
}
````

config.json에 방금 설정한 것은 dialect를 sqlite로 설정해주고 storage설정으로 sqlite의 데이터베이스를 가리키도록 하였습니다.  

#### Dialect가 뭔가요?

dialect는 Database의 방언을 의미하며 Database간의 SQL문법 차이를 말합니다.  
만약 database간의 문법 차이로 인해 다양한 종류의 데이터베이스에 맞게 코드를 구현해야한다면 엄청나게 힘든 일 일 수 있습니다.  
ORM은 그럴 필요 없이 위와 같이 dialect 설정을 하면, SQL dialect로부터 애플리케이션을 추상화하여  
어플리케이션의 일정 수준의 이식성을 확보할 수 있어 코드 변경없이 문제를 해결 할 수 있게 도와줍니다.  

- 이제 프로젝트의 루트 디렉토리 내에서 데이터베이스 파일을 만들어 봅시다.  

````
touch database.sqlite
````

## 2 단계 — 모델 및 마이그레이션 작성

이제 프로젝트 모델을 만들어볼 겁니다. 우리의 프로그램에서는 두가지 모델이 있는데, `User`와 `Recipe`입니다.  
Sequelize CLI를 사용해봅시다.  
````
node_modules/.bin/sequelize model:create --name User --attributes name:string,email:string,password:string
````

우리는 model 폴더에 `user.js`를 만들고 `migration` 파일을 migrations 폴더에 만들었습니다.  

User 모델의 어떤 필드도 Null입력이 안되도록 하기위해 명시적으로 정의해줘야합니다.  
`migrations/XXXXXXXXXXXXXX-create-user.js`에 아래와 같이 코드를 수정해주세요.  
````
// migrations/XXXXXXXXXXXXXX-create-user.js

name: {
    allowNull: false,
    type: Sequelize.STRING
},
email: {
    allowNull: false,
    type: Sequelize.STRING
},
password: {
    allowNull: false,
    type: Sequelize.STRING
}
````

그다음 User 모델에도 아래와 같이 수정해주세요.  
````
// models/user.js

name: {
    type: DataTypes.STRING,
    allowNull: false
},
email: {
    type: DataTypes.STRING,
    allowNull: false
},
password: {
    type: DataTypes.STRING,
    allowNull: false
}
````

그 다음으로 `Recipe` 모델을 만들어줍니다.  
````
node_modules/.bin/sequelize model:create --name Recipe --attributes title:string,ingredients:text,direction:text
````

`Recipe` 모델도 `User`모델과 똑같이 필드에 Null이 입력 안되도록 설정합니다.  
````
// migrations/XXXXXXXXXXXXXX-create-recipe.js

userId: {
    type: Sequelize.INTEGER.UNSIGNED,
    allowNull: false
},
title: {
    allowNull: false,
    type: Sequelize.STRING
},
ingredients: {
    allowNull: false,
    type: Sequelize.STRING
},
direction: {
    allowNull: false,
    type: Sequelize.STRING
},
````

````
// models/recipe.js

title: {
    type: DataTypes.STRING,
    allowNull: false
},
ingredients: {
    type: DataTypes.STRING,
    allowNull: false
},
direction: {
    type: DataTypes.STRING,
    allowNull: false
}
````

모델을 마무리하기 위해 모델 간의 관계를 정의해 봅시다.  
userId열을 recipes테이블에 포함시키는 것으로 추측했을 수 있습니다.  
레시피를 사용자에게 연결하거나 그 반대로 할 수 있기를 원합니다.  
따라서 우리는 모델간에 일대 다 관계를 원합니다.  

이제 `models/user.js`파일에서 `User.associate`를 수정해주세요.
````
  User.associate = function (models) {
    User.hasMany(models.Recipe)
  }
````

`Recipe` 모델에서 관계의 역을 정의해야합니다.  
````
// models/recipe.js

Recipe.associate = function (models) {
    Recipe.belongsTo(models.User, { foreignKey: 'userId' })
}
````

Sequelize는 기본적으로 해당 모델 이름과 해당 모델의 기본 키를 외래 키로 사용할 때 camelCase로 사용합니다.  
따라서 우리의 경우 외래 키가 될 것으로 예상됩니다 UserId.  
열의 이름을 다르게 지정 했으므로 foreignKey와의 관계를 명시적으로 정의해야합니다.

이제 마이그레이션을 실행할 수 있습니다.  
````
node_modules/.bin/sequelize db:migrate
````

#### 마이그레이션(migration)이 뭔가요?

CRUD(Create, Read, Update, Delete)를 잘 수행하려면, 
데이터 베이스 테이블 스키마가 잘 정의되어 있어야합니다.  

마이그레이션이란 한 운영환경으로부터 다른 운영환경으로 옮기는 작업을 뜻하는데,(예, 윈도우 --> 리눅스)  
하드웨어, 소프트웨어, 네트워크 등 넓은 범위에서 마이그레이션의 개념이 사용되고 있습니다.  

그렇다면 데이터베이스에서 데이터 마이그레이션이란 무엇일까요?  
데이터 베이스 스키마의 버전을 관리하기 위한 하나의 방법(데이터 전환)입니다.  

개발 시스템에는 데이터베이스 스키마가 변경되었지만,  
운영시스템의 데이터베이스 스키마가 변경되지 않았을 경우 마이그레이션을 수행합니다.  

작게는 프로젝트 상 테이블 생성 및 변경 작업부터,  
하나의 애플리케이션 또는 시스템을 옮기는 것까지 마이그레이션이라고 합니다.  

요구사항에 따라 애플리케이션과 스키마가 바뀌었고,  
개발 과정에는 적용됐지만 운영환경에는 적용되지 않아서 전환 시 애를 먹는 경우가 있는데,
데이터베이스 마이그레이션은 이러한 문제를 해결합니다.  

데이터베이스 마이그레이션은,  
개별 SQL 파일을 MySQL 콘솔 등에서 직접 실행하지 않고,  
프레임워크의 특정명령어를 통해 실행하고 이 결과를 별도의 테이블에 버전 관리를 하는 기법입니다.  

## 3 단계 — GraphQL 서버 생성

우리는 GraphQL 서버를 구축하기 위해 Apollo Server를 사용할 것입니다.  

- 설치

````
npm install apollo-server graphql bcryptjs
````

`bcryptjs`를 설치하는 이유는 나중에 사용자 암호를 해시하는데 사용해야되기 때문입니다.  

이제 src 디렉토리를 하나 생성하고 index.js 파일을 만들어 아래의 코드를 추가해주세요.  
````
// src/index.js

const { ApolloServer } = require('apollo-server')
const typeDefs = require('./schema')
const resolvers = require('./resolvers')
const models = require('../models')

const server = new ApolloServer({
  typeDefs,
  resolvers,
  context: { models }
})

server
  .listen()
  .then(({ url }) => console.log('Server is running on localhost:4000'))
````

Apollo 서버의 새 인스턴스에 스키마와 리졸버를 넣어주고 모델을 컨텍스트로 서버에 전달합니다.  
이를 통해 리졸버의 모델에 접근할 수 있습니다.  

## 4 단계 — GraphQL 스키마 정의

이제 어플리케이션의 스키마를 만들어 보겠습니다. schema.js에 다음의 내용을 작성해주세요.  

````
const { gql } = require('apollo-server');

const typeDefs = gql`
    type User {
        id: Int!
        name: String!
        email: String!
        recipes: [Recipe]!
    }

    type Recipe {
        id: Int!
        title: String!
        ingredients: String!
        direction: String!
        user: User!
    }

    type Query {
        user(id: Int!): User
        allRecipes: [Recipe!]!
        recipe(id: Int!): Recipe
    }

    type Mutation {
        createUser(name: String!, email: String!, password: String!): User!
        createRecipe(userId: Int!, title: String!, ingredients: String!, direction: String!): Recipe!
    }
`

module.exports = typeDefs;
````

apollo-server에서 가져온 gql 패키지는 스키마를 정의하는데 사용합니다.  

## 5 단계 — 리졸버 만들기

resolver는 스키마의 필드가 실행되는 방법을 정의합니다. resolver.js에 아래의 내용을 추가해주세요.  
````
// src/resolvers.js

const resolvers = {
    Query: {
        async user (root, { id }, { models }) {
              return models.User.findById(id)
        },
        async allRecipes (root, args, { models }) {
              return models.Recipe.findAll()
        },
        async recipe (root, { id }, { models }) {
              return models.Recipe.findById(id)
        }
      },
}

module.exports = resolvers
````

먼저 쿼리에 대한 리졸버를 만드는 것부터 시작합니다.  
여기서는 데이터베이스에서 필요한 쿼리를 수행하고 결과를 반환하기위해서 모델을 사용하고 있습니다.  

bcryptjs를 import한 다음 Query 객체 뒤에 다음의 코드를 추가해주세요.  
````
const bcrypt = require('bcryptjs');

const resolvers = {
    Query: {
        async user (root, { id }, { models }){
            return models.User.findById(id)
        },
        async allRecipes (root, args, { models }){
            return models.Recipe.findAll()
        },
        async user (root, { id }, { models }){
            return models.Recipe.findById(id)
        },
    },
    Mutation: {
        async createUser (root, { name, email, password }, { models }) {
            return models.User.create({
                name,
                email,
                password: await bcrypt.hash(password, 10)
            })
        },
        async createRecipe (root, { userId, title, ingredients, direction }, { models }) {
            return models.Recipe.create({
                userId,
                title,
                ingredients,
                direction
            })
        }
    }
}

module.exports = resolvers;

````

Mutation에서 createUser는 사용자의 이름과 이메일, 비밀번호를 받고  
그 정보에 따라서 데이터베이스에 새 레코드를 생성합니다.  
그리고 비밀번호는 해싱 처리를 하여 넣어주고 이렇게 새로 생성된 사용자를 리턴하게됩니다.  

이제 User와 Recipe 정보를 얻기위해 아래의 내용을 추가해주세요.  
````
    User: {
        async recipes (user) {
            return user.getRecipes();
        }
    },
    Recipe: {
        async user (recipe) {
            return recipe.getUser();
        }
    }
````

## 6 단계 — GraphQL 서버 테스트

GraphQL 서버를 테스트 할 차례입니다. 먼저 다음과 같이 서버를 시작해야합니다.  
package.json에 script를 추가해주세요.  
````
{
    "script": {
        "start": "node src/index.js
    }
}
````
`npm run start`로 서버를 시작합니다.  
