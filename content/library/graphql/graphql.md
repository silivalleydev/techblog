---
title: "GraphQL"
metaTitle: "GraphQL"
metaDescription: "This is the meta description"
---

# GraphQL

## GraphQL은 왜 필요한가?

### OverFetching과 UnderFetching

- OverFetching :
예를 들어 내가 1번 사용자의 username 이 필요하다고 가정해봅니다.  
예를 들자면 /users/1로 요청을 한다면, 이때 이 요청에 따른 응답은 username 뿐만 아니라,  
profile, age, address 등등 필요하지 않은 정보들까지 포함됩니다.  
즉 우리는 username 하나만 필요하지만 이렇게 모든 데이터들을 불러온 후 내가 필요한 것만  
솎아서 사용해야 하기 때문에 리소스 낭비가 발생하게됩니다.  

- UnderFetching :
예를 들어 사용자가 SNS 어플을 실행시켰다고 가정해봅니다.  
알림에 관한 부분, 사용자 정보, 타임라인 등을 불러오는 요청을 여러번 보내야 합니다.  
하지만 GraphQL를 이용하면 이러한 많은 정보를 한번의 요청으로 해결 할 수 있습니다.  

### qrery

graphQl의 쿼리는 데이터베이스에 내가 원하는 정보만 뽑아서 알려줄 수 있는 언어입니다.
`````
query {
    feed {
        comments
        likeNumber
    }
    notifications {
        isRead
    }
    user {
        username
        profilePic
    }
}
`````
위의 내용을 예로들자면  
만약 피드 정보를 원하는데 피드 정보(feed)중 댓글(comments)이랑 좋아요 수(likeNumber)만 원한다거나,  
알림 정보를 원하는데 알림 확인여부(Reads)를 원하고,  
사용자 정보중에 사용자 이름(username)과 프로필 사진(profilePic)을 원한다고한다면 위와 같이 쿼리를 작성하여 보내게되면  
Backend에서 아래와 같이 쿼리에서 요청한 정보만을 담은 JavaScript Object를 보내주게 됩니다.  

`````
{
    feed: [
        { 
            comments:1,
            likeNumber: 20
        }
    ],
    notifications: [
        {
            isRead: true
        },
        {
            isRead: false
        }
    ],
    user: [
        {
            username: "jack",
            profilePic: "http://~"
        }
    ]
}
`````

## GraphQL yoga 및 개발 환경 설정

GraphQL yoga는 `create-react-app`과 비슷한 것으로  
빠르게 GraphQL 프로젝트를 시작할 수 있도록 도와주는 것입니다.  
````
npm install graphql-yoga
````

- nodemon은 파일을 수정할 때마다 서버를 재시작 시켜줍니다.

````
npm install global nodemon
````

- 그리고 스크립트에 scripts에 "start": "nodemon"을 설정해주고, main에는 index.js로 설정해줍니다.  

````
{
  "name": "movieql",
  "version": "1.0.0",
  "description": "Movie API with Graph QL",
  "main": "index.js",
  "scripts": {
    "test": "echo \"Error: no test specified\" && exit 1",
    "start" : "nodemon"
  },
  "author": "",
  "license": "ISC",
  "dependencies": {
    "global": "^4.4.0",
    "graphql-yoga": "^1.18.3",
    "nodemon": "^2.0.4"
  }
}
````

만약 전부 설정이 끝났다면 스크립트를 실행시켜주면됩니다.  
````
npm run start
````

- index.js에 console.log를 찍어보고 그 다음에 그 값을 계속 변경했을때 바로 수정된 값이 콘솔로 찍힌다면  
nodemon이 정상적으로 적용된 것입니다.  

````
console.log('bbbb'); // 콘솔의 내용을 변경하고 저장할 때마다 그 값이 콘솔로 바로 찍힌다면 잘 적용된 것입니다.
````

graphQl yoga를 import해야하는데, 바벨 설정이되어있지 않으면 require을 사용해야합니다.  
바벨 설정을 위해서 아래와 같이 설치를 해줍니다.  
````
npm install babel-cli --ignore-engines
````

그리고 package.json의 scripts 설정을 아래와 같이 바꿔줍니다.  
````
{
  "scripts": {
    "start" : "nodemon --exec babel-node index.js"
  }
}
````

- .babelrc 설정  

.babelrc 파일을 생성하고 아래의 코드를 추가시켜줍니다.  
````
{
    "presets": ["env", "stage-3"]
}
````

아래의 패키지들을 설치합니다.
`````
npm install babel-cli babel-preset-env babel-preset-stage-3 --dev
`````

이제 index.js에 아래와 같은 코드를 추가합니다.  
````
import { GraphQLServer } from 'graphql-yoga';

const server = new GraphQLServer({

});

server.start(() => console.log('GraphQLServer Running'));
````

GraphQLServer를 import하고  server라는 변수에 GraphQLServer를 생성하여 담습니다.  
이때 생성한 GraphQLServer에 `new GraphQLServer({})` 안에 환경설정을 해주시면됩니다.  

현재 위의 코드만 사용하면 당연히 오류가 나게됩니다. 왜냐하면 정의된 schema가 없기 때문이죠.  

## Schema

Schema란 쉽게말하면 받거나 줄 정보가 담겨있는 내용이라 보면됩니다.  

스키마(Schema)를 먼저 정의하는 이유는 쿼리의 형태는 리턴되는 값과 거의 일치하는데,  
어떤 필드를 선택할지 어떤 종류의 객체를 반환할지, 하위 객체에서 필요한 사용할 수 있는 필드는 무엇인지 알기 위해선  
스키마의 존재가 필연적이기 때문입니다.  

- 먼저 graphql이라는 폴더를 만들고 `schema.graphql`이라는 파일을 생성해줍니다.  

`schema.graphql`이라는 파일에서는 사용자가 뭘 할지에 대해서 정의할 겁니다.  
그중 하나는 DB로부터 정보를 얻는 것을 할겁니다. 이것을 Query라고합니다.  
그 다음에는 정보를 DB로 보낼겁니다.  
Query는 정보를 받을때만 쓰이고, Mutation(변형)은 사용자가 정보를 변형할때,  
사용자가 서버에서 또는 DB에서, 메모리에서 정보를 바꾸는 작업을 할 때를 Mytation이라고 합니다.  

우리가 GraphQL 서버에서 할 것은 어떤 Mutation과 어떤 Query들을 우리가 가졌는지 알려주는 것을 할겁니다.  

## 쿼리의 선언, resolvers

이제 첫번째 쿼리를 선언해봅시다. 이곳에는 사용자에게 정보를 주는 모든 것들을 넣을 겁니다.  
````
type Query {
    name: String!
}
````

위의 내용을 해석해보면, 어떤 사용자가 쿼리에 name이라는 것을 보내면,  
서버에서 사용자에게String 형태의 내용을 Respond해주는 것입니다.  
!는 isRequired의 의미를 갖고 있습니다. 여기서 name은 쿼리에 대한 설명을 의미합니다.  

여기서 Query는 DB에게는 문제와 같은 것이기 때문에 이 쿼리를 해결해주는 resolver(해결)이 존재해야합니다.  
graphql 폴더에 resolver.js를 생성해봅니다.  

- resolvers.js

````
const resolvers = {
    Query: {
        name: () => "nicolas"
    }
}

export default resolvers;
````

쿼리에서 name이라는 질문을 던졌고 우리는 그것을 nicloas라는 String으로 답변한다는 내용으로 이해하면됩니다.  

- index.js

````
import { GraphQLServer } from 'graphql-yoga';
import resolvers from './graphql/resolvers'

const server = new GraphQLServer({
    typeDefs: "graphql/schema.graphql",
    resolvers
});

server.start(() => console.log('GraphQLServer Running'));
console.log('hello');
````

index.js에 GraphQLServer에 설정을 해줍니다. typeDefs 속성은 그래프ql schema의 경로를 넣어주면되고
그다음에 resolvers를 넣어주면 GraphQLServer가 제대로 동작하게됩니다.  

이제 http://localhost:4000/ 에 들어가면 graphql playground가 나옵니다.  
여기서 위에서 정의한 쿼리를 작성해주면 정상적으로 nicolas가 나오게됩니다.  
````
// 내가 보낸 쿼리
query{
  name
}

// 답변
{
  "data": {
    "name": "nicolas"
  }
}
````

위에서 일어난 일을 보자면 graphql이 사용자의 서버에서 쿼리에서 name을 찾고 그 쿼리에 맞는 Resolver를 찾아서  
맞는 값을 리턴해준 것입니다.  

만약 쿼리상에서 타입을 Int로 지정해준다면? 오류가 나게될 겁니다.  
왜냐하면 리턴값이 String이기 때문입니다.  

Graphql Playground는 GraphQL yoga에서 따라오는 것인데 이것의 역할은 자신의 DB를 테스트하게 도와주는 도구 같은 것입니다.  

graphql의 Query는 Json data와 비슷한 것으로 항상 POST로 보내게됩니다.  
왜냐하면 서버가 받아야하기 때문이지요.  

## 여러가지의 타입 리턴 받기

### Object 형

그렇다면 Object형태의 값을 반환 받을땐 쿼리에서 어떻게 처리해야될까요?  
resolvers에 nicolas라는 객체를 만들어봅시다.  
`````
const nicolas = {
    name: "Nicolas",
    age: 18,
    gender: "female"
}

const resolvers = {
    Query: {
        person: () => nicolas
    }
}

export default resolvers;
`````

nicolas 객체는 string형의 데이터도있고 integer형태의 데이터도 있습니다.  
이 데이터들의 정의는 schema.graphql에 Nicolas라는 타입의 쿼리를 새로 생성해주면됩니다.  
````
type Nicolas {
    name: String!
    age: Int!
    gender: String!
}

type Query {
    person: Nicolas!  
}
````

쿼리에선 person에서 Nicolas라는 객체 타입을 반환하도록 설정하였고 그것을 resolvers에서 해석해서 반환해줍니다.  
이제 graphql playground에서 테스트를 진행해보면 됩니다.  

다만 이전과는 다르게 객체에서 어떤 데이터를 받을지를 설정해줘야합니다. 아래처럼 말이죠.  
`````
// 보낸쿼리
query{
  person {
    age
  }
}

// 답변
{
  "data": {
    "person": {
      "age": 18
    }
  }
}
`````

만약 gender도 알고 싶다면 person 객체에 넣어서 쿼리를 날리면되겠습니다.  

### Array 형

이번엔 People이라는 객체를 받을 겁니다. People은 한명이 아니기 때문에 Array 형태로 반환 받습니다.  

- schema.graphql

````
type Person {
    id: Int!
    name: String!
    age: Int!
    gender: String!
}

type Query {
    people: [Person]!  
    person(id: Int!): Person
}
````

위의 코드를 `people`에 `[Person]`이라는 객체를 반환했습니다.  
여기서 중괄호의 의미는 Array를 의미하며, Person이 여러명모여 People이 되기 때문에 저렇게 표현하게됩니다.  

근데 여기서 오직 한명의 Person만 얻고 싶다면 아이디가 필요합니다.  
그러기위해서는 Person의 아이디를 쿼리에 정의해야 됩니다. 자유롭게 정해도되는데, id라고 하겠습니다.

`person(id: Int!): Person`이라는 문장이 들어가게됩니다.  
이것의 의미는 Integer형태의 아이디의 person id를 보내면 그 아이디에 맞는 : 오른쪽에 있는 Person객체를 반환한다는 의미입니다.  

이제 resolvers에 여러 사람을 주가해봅시다.  
````
const people = [
{
    id: 0,
    name: "Nicolas",
    age: 18,
    gender: "female"
},
{
    id: 1,
    name: "Jack",
    age: 23,
    gender: "male"
},
{
    id: 2,
    name: "Alison",
    age: 24,
    gender: "female"
},
{
    id: 3,
    name: "Ron",
    age: 12,
    gender: "male"
},
{
    id: 4,
    name: "Ben",
    age: 30,
    gender: "male"
}
]
const resolvers = {
    Query: {
        people: () => people
    }
}

export default resolvers;
````

이제 graphql playground에 가서 데이터를 요청해봅시다.  
만약 사람들의 이름만 알고 싶다고하면 이름만 요청하면 됩니다. 아래와 같이 말이죠.  
`````
// 쿼리 요청
query{
 	people{
    name
  }
}

// 답변
{
  "data": {
    "people": [
      {
        "name": "Nicolas"
      },
      {
        "name": "Jack"
      },
      {
        "name": "Alison"
      },
      {
        "name": "Ron"
      },
      {
        "name": "Ben"
      }
    ]
  }
}
`````

db 관련 데이터는 resolvers.js에는 원래 들어있으면 안되기 때문에 graphql폴더에 db.js로 따로 빼주세요.  
- db.js

````
export const people = [
    {
        id: 0,
        name: "Nicolas",
        age: 18,
        gender: "female"
    },
    {
        id: 1,
        name: "Jack",
        age: 23,
        gender: "male"
    },
    {
        id: 2,
        name: "Alison",
        age: 24,
        gender: "female"
    },
    {
        id: 3,
        name: "Ron",
        age: 12,
        gender: "male"
    },
    {
        id: 4,
        name: "Ben",
        age: 30,
        gender: "male"
    }
    ]
````

### 조건에 맞는 아이디 찾기

먼저 db.js에 filter 조건을 걸어주는데, people중에 사용자가 넣어준 아이디에 맞는 person을 리턴하게 해줍니다.  
````
    export const getById = id => {
        const filteredPeople = people.filter(person => person.id === id);
        return filteredPeople[0]
    }
````

그 다음에 쿼리에 날릴 데이터와 받을 데이터를 설정해줍니다.  
````
type Person {
    id: Int!
    name: String!
    age: Int!
    gender: String!
}

type Query {
    people: [Person]!  
    person(id: Int!): Person
}
````

person에 Integer형태의 아이디를 보내주면 Person객체를 반환합니다. 이제 이것을 resolvers에서 처리해주겠습니다.
````
import { people, getById } from './db'

const resolvers = {
    Query: {
        people: () => people,
        person: (_,{ id }) => getById(id)
    }
}

export default resolvers;
````

person이라는 객체에 id를 넣어주면 getById(id)가 Person을 반환합니다.  
graphql playground에서 테스트 해보겠습니다.  
`````
// 쿼리 전송
query{
 	person(id:1){
    name
  }
}

// 답변
{
  "data": {
    "person": {
      "name": "Jack"
    }
  }
}
`````

### Mutation

먼저 영화 관련 내용을 쿼리로 받는 db를 만들겠습니다.  

- moviesdb.js 를 만들어주세요.

`````
let movies = [
    {
        id: 0,
        name: "Star Wars - The new one",
        score: 0.1
    },
    {
        id: 1,
        name: "Avengers - The new one",
        score: 8
    },
    {
        id: 2,
        name: "The Godfather",
        score: 99
    },
    {
        id: 3,
        name: "Rogan",
        score: 2
    },
]

export const getMovies = () => movies;

export const getById = id => {
    const fileteredMovies = movies.filter(movie => movie.id === id);
    return fileteredMovies[0];
}

// 만약 1번 영화를 넣었다면 0,2,3의 영화가 cleanedMovies에 들어가게되고(filtered) 현재 moives 배열보다 cleanedMoive의 길이가 작다면,
// movies에 cleanedMovies의 값을 넣고 true를 반환한다. 그렇게되면 1번 영화는 삭제된다.
export const deleteMovies = id => {
    const cleanedMovies = movies.filter(movie => movie.id !== id);
    if(movies.length > cleanedMovies.length) {
        movies = cleanedMovies;
        return true;
    }else{
        return false;
    }
}
`````

맨 마지막의 함수는 영화를 db에서 지우는 것인데 이따가 설명하겠습니다.  

다음 스키마(schema.graphql)를 변경시켜주세요.  
````
type Movie {
    id: Int!
    name: String!
    score: Int!
}

type Query {
    movies: [Movie]!
    movie(id: Int!): Movie
}
````

마지막으로 resolvers를 변경시켜줍니다.  
````
import { getMovies, getById } from './moviesdb'

const resolvers = {
    Query: {
        movies: () => getMovies(),
        movie: (_,{ id }) => getById(id)
    }
}

export default resolvers;
````

자 이제 세팅이 완료되었습니다.  
이제 Mutation에 대해서 설명하겠습니다.  
Mutation은 DB의 상태가 변할때 사용됩니다.  

#### 영화 추가

먼저 moviesdb에 영화를 추가하는 것을 만들어보겠습니다.  
````
export const addMovie = (name, score) => {
    const newMovie = {
        id: movies.length + 1,
        name,
        score
    }

    movies.push(newMovie);
    return newMovie;
}
````

mutation은 db의 상태가 변화되는 것이기 때문에 스키마에 타입을 따로 나눠줍니다.  
````
type Movie {
    id: Int!
    name: String!
    score: Int!
}

type Query {
    movies: [Movie]!
    movie(id: Int!): Movie
}

type Mutation {
    addMovie(name: String!, score: Int!): Movie!
}
````

다음에는 resolvers를 바꿔줍니다. 
````
import { getMovies, getById, addMovie } from './moviesdb'

const resolvers = {
    Query: {
        movies: () => getMovies(),
        movie: (_,{ id }) => getById(id)
    },
    Mutation: {
        addMovie: (_, { name, score }) => addMovie(name, score)
    }
}

export default resolvers;
````

이제 graphql playground에서 테스트 해줍니다.  
영화를 추가해보는데 이번에 타입은 mutation이 되고 addmovie에 name과 score를 넣어줄겁니다.
````
// 쿼리 전송
mutation{
  addMovie(name: "Iron man", score:9){
    name
  }
}

// 답변
{
  "data": {
    "addMovie": {
      "name": "Iron man"
    }
  }
}
````

그리고 movies에 잘 추가가되었는지 확인해봅니다.  
````
// 쿼리 전송
query{
  movies{
    name
  }
}

//답변
{
  "data": {
    "movies": [
      {
        "name": "Star Wars - The new one"
      },
      {
        "name": "Avengers - The new one"
      },
      {
        "name": "The Godfather"
      },
      {
        "name": "Rogan"
      },
      {
        "name": "Iron man"
      }
    ]
  }
}
````

DB에 영화가 정상적으로 추가가 되었네요! 이렇게 DB의 상태가 변화되는 것을 Mutation이라고 합니다.

#### 영화 삭제

- moviesdb.js에 아까 아래와 같이 영화를 삭제하는 함수를 추가했었습니다.  

````
// 만약 id가 1인 영화를 인자에 넣었다면 id 0,2,3의 영화가 cleanedMovies에 들어가게되고(filtered) 현재 moives 배열보다 cleanedMoive의 길이가 작다면,
// movies에 cleanedMovies의 값을 넣고 true를 반환한다. 그렇게되면 1번 영화는 삭제된다.
export const deleteMovie = id => {
    const cleanedMovies = movies.filter(movie => movie.id !== id);
    if(movies.length > cleanedMovies.length) {
        movies = cleanedMovies;
        return true;
    }else{
        return false;
    }
}
````

이제 이 함수를 이용하여 db에 mutation을 줄겁니다.  

schema.graphql에 먼저 deleteMovie 함수의 스키마를 정해줍시다.
````
type Mutation {
    addMovie(name: String!, score: Int!): Movie!
    deleteMovie(id: Int!): Boolean!
}
````

위에서 deleteMovie 함수를 보면 id를 받고있고 true, false를 반환하기 때문에 반환 값의 자료형은 Boolean이 됩니다.  

이제 resolvers에서 처리를 해줍시다.  

````
import { getMovies, getById, addMovie, deleteMovie } from './moviesdb'

const resolvers = {
    Query: {
        movies: () => getMovies(),
        movie: (_,{ id }) => getById(id)
    },
    Mutation: {
        addMovie: (_, { name, score }) => addMovie(name, score),
        deleteMovie: (_, { id }) => deleteMovie(id)
    }
}

export default resolvers;
````

자 이제 playground에서 테스트를 해보면됩니다.  

우리가 아까 추가한 영화들 중에서 아이디가 1인 영화를 지워보겠습니다.

````
// 쿼리 전송
mutation{
  deleteMovie(id:1)
}

// 답변
{
  "data": {
    "deleteMovie": true
  }
}
````

- db 결과
````
{
  "data": {
    "movies": [
      {
        "id": 0,
        "name": "Star Wars - The new one"
      },
      {
        "id": 2,
        "name": "The Godfather"
      },
      {
        "id": 3,
        "name": "Rogan"
      }
    ]
  }
}
````

id가 1번인 영화가 정상적으로 지워졌습니다!

## yts API를 이용해 영화 리스트 받아오기

### 영화 리스트 받아오기

먼저 graphql 폴더에 ytsdb.js를 생성해주고 아래의 코드를 작성해주세요.  
````
const API_URL = "https://yts.mx/api/v2/list_movies.json";

const getMovies = (limit, rating) => {
    
}
```` 

다음은 node.js에서 fetch할 때 필요한 `node-fetch`를 설치합니다.  
````
npm install node-fetch
````

그 다음 `node-fetch`를 import하여 사용해줍니다.  
````
import fetch from 'node-fetch'

const API_URL = "https://yts.mx/api/v2/list_movies.json";

export const getYtsMovies = (limit, rating) => {
    return fetch(`${API_URL}`)
        .then(res => res.json())
        .then(json => json.data.movies)
}
````

schema.graphql에서 스키마를 정의해줍니다.  
````
type YtsMovie {
    id: Int!
    title: String!
    rating: Float!
    summary: String!
    language: String!
    medium_cover_image: String!
}

type Query {
    ytsMovies: [YtsMovie]!
}
````

그다음 resolvers에서 처리해줍니다.  
````
const resolvers = {
    Query: {
        ytsmovies: () => getYtsMovies(),
    }
}
````

이제 playground에서 쿼리를 날려봅시다.  
````
// 쿼리 전송
query{
	ytsmovies{
    id
    title
    rating
    summary
    language
    medium_cover_image
  }
}

// 답변
{
  "data": {
    "ytsmovies": [
      {
        "id": 19506,
        "title": "Haole",
        "rating": 0,
        "summary": "Thirteen-year-old DAVID KEALOHA dreams of escaping rural Hawaii. But when JONAH MORRIS (13), a white kid from Phoenix, Arizona moves into the neighborhood, tragedy strikes, irrevocably changing the trajectory of David's life and those closest to him.",
        "language": "English",
        "medium_cover_image": "https://yts.mx/assets/images/movies/haole_2019/medium-cover.jpg"
      },
      {
        "id": 19499,
        
        ...
````

데이터가 잘 받아져왔습니다.  

### 영화 리스트를 받아올 때 조건 걸어주기

ytsdb.js에 있는 getMovies함수에서 limit와 rating을 받는 이유는  
`https://yts.mx/api/v2/list_movies.json?limit=50&minimum_rating=9`  
위와 같이 limit 수로 가져올 정보의 갯수를 정하고 rating 수로 평점에 따라 가져올 것이기 때문입니다.  

그렇다면 이번엔 그것을 적용시켜보겠습니다.  
먼저 함수의 형태를 변경 시켜줄 겁니다.  
````
import fetch from 'node-fetch'

const API_URL = "https://yts.mx/api/v2/list_movies.json";

export const getYtsMovies = (limit, rating) => {
    let REQUEST_URL = API_URL;
    if (limit > 0) {
        REQUEST_URL += `?limit=${limit}`
    }
    if (rating > 0) {
        REQUEST_URL += `&minimum_rating=${rating}`
    }
    return fetch(`${REQUEST_URL}`)
        .then(res => res.json())
        .then(json => json.data.movies)
}
````

limit 또는 rating이 0보다 클때 URL에 추가해주는 구조입니다.  
이제 getYtsMovies에는 argument가 필요하니 schema.graphql에서 스키마를 정의 해줘야합니다.  
````
type Query {
    ytsmovies(limit: Int!, rating: Float!): [YtsMovie]!
}
````

이제 resolvers에서 처리해주겠습니다.  
````
const resolvers = {
    Query: {
        ytsmovies: (_, { limit, rating }) => getYtsMovies(limit, rating)
    }
}
````

playground에서 쿼리를 날려보겠습니다.  
````
// 쿼리 전송
query{
	ytsmovies(limit:3, rating: 8.5){
    id
    title
    rating
  }
}

// 답변
{
  "data": {
    "ytsmovies": [
      {
        "id": 19416,
        "title": "Every Brilliant Thing",
        "rating": 8.5
      },
      {
        "id": 18877,
        "title": "Hamilton",
        "rating": 8.9
      },
      {
        "id": 18169,
        "title": "Stewart Lee: Carpet Remnant World",
        "rating": 8.6
      }
    ]
  }
}
````

정상적으로 rating이 8.5이상인 영화 리스트 3개가 나왔습니다.  

