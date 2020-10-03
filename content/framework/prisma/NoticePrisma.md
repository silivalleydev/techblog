# 중요한 점

## DB 연결

### Mysql 연결

처음 `prisma init`으로 prisma 프로젝트를 생성하면 `schema.prisma` 파일에 아래과 같은 코드가 있습니다.  
`````
datasource db {
  provider = "mysql"
  url      = env("DATABASE_URL")
}
`````

여기서 provider는 사용자가 연결할 database의 이름이되고,  
url은 데이터베이스의 url을 의미합니다.  

mysql 데이터베이스 url의 경우 아래와 같은 형태입니다.  
````
mysql://USER:PASSWORD@HOST:PORT/DATABASE
````

|   name          | Placeholder |   description                                     |
|-----------------|-------------|---------------------------------------------------|
|   주최자        |   HOST      |   데이터베이스 서버의 IP 주소 / 도메인 localhost  |
|   포트          |   PORT      |   데이터베이스 서버가 실행중인 포트 (예 : 5432    |
|   사용자        |   USER      |   데이터베이스 사용자 이름 (예 : janedoe          |
|   암호          |   PASSWORD  |   데이터베이스 사용자의 비밀번호                  |
|   데이터베이스  |   DATABASE  |   사용하려는 데이터베이스 이름 ( 예 :mydb         |

- 이제 mysql db url을 `.env`파일 에 세팅해줍니다

````
# Environment variables declared in this file are automatically made available to Prisma.
# See the documentation for more detail: https://pris.ly/d/prisma-schema#using-environment-variables

# Prisma supports the native connection string format for PostgreSQL, MySQL and SQLite.
# See the documentation for all the connection string options: https://pris.ly/d/connection-strings

DATABASE_URL="mysql://root:1234@localhost:3306/prismatest"
````

## Prisma 스키마 업데이트와 클라이언트 코드 업데이트

### 데이터베이스 스키마 업데이트

Prisma schema에서 새로운 모델을 생성했다거나 모델을 변경시켰다면  
아래의 작업을 수행해야합니다.  
````
$ npx prisma migrate save --name init --experimental // migration 히스토리를 생성
$ npx prisma migrate up --experimental // 실제 DB의 테이블을 생성
````

반대로 데이터 베이스에서 모델을 생성했다면 아래의 작업을 하시면됩니다.  
````
npx prisma introspect
````

### 클라이언트 코드 업데이트

우리는 prisma로 index.ts를 만들어서 crud 작업을 할때 아래와 같이 사용합니다.
````
import { PrismaClient } from '@prisma/client'

const prisma = new PrismaClient()

async function main() {
  await prisma.user.create({
    data: {
      name: 'Jack',
      email: 'jack@prisma.io',
      posts: {
        create: { title: 'Hello World' },
      },
      profile: {
        create: { bio: 'I like turtles' },
      },
    },
  })
  
  const allUsers = await prisma.user.findMany({
    include: {
      posts: true,
      profile: true,
    },
  })

  console.dir(allUsers, { depth: null })
}

main()
  .catch((e) => {
    throw e
  })
  .finally(async () => {
    await prisma.disconnect()
  });
````

하지만 여기서 드는 의문점이 있습니다. PrismaClient를 사용하는 코드를 보면  
`await prisma.user.create({})` 이런 형태인데 저기있는 user 프로퍼티는 어디서 나온 것인지 알 수가 없습니다.  
우리가 생성하지도 않았는데 말이죠. 어떻게 생성된 것일까요?  

답은 Prisma Client generate에 있습니다.

아래 명령어를 통해 Prisma CLI가 우리의 Prisma schema를 읽고  
`node_modules/@prisma/client` 에 Prisma Client를 생성합니다.  
만약 데이터베이스 스키마에 새로운 모델을 정의했다거나 모델을 변경시켰다면  
아래의 명령어를 똑같이 해주시면 Prisma Client 코드가 업데이트 됩니다.  
````
npx prisma generate
````

그렇다면 예를 들어보겠습니다.  
Psts라는 모델을 새로 정의해봅니다.  
````
// schema.prisma

model Psts {
  id Int @default(autoincrement()) @id
  title String
  name String
  what String
}
````

이제 정의한 모델을 데이터베이스에 생성해줘야합니다.  
````
$ npx prisma migrate save --name init --experimental // migration 히스토리를 생성
$ npx prisma migrate up --experimental // 실제 DB의 테이블을 생성
````

db에 테이블이 생성되었다면 이제 PrismaClient code를 업데이트 해주세요.
````
npx prisma generate
````

위의 작업을해주면 `node_modules/.prisma/client/index.d.ts` 파일에 보시면 해당 모델에 맞는 코드가 업데이트 되었습니다.  
````
// index.d.ts


  /**
   * `prisma.psts`: Exposes CRUD operations for the **Psts** model.
    * Example usage:
    * ```ts
    * // Fetch zero or more Psts
    * const psts = await prisma.psts.findMany()
    * ```
    */
  get psts(): PstsDelegate;

````

이렇게되면 `index.ts`에서 crud 작업을 할 수 있게됩니다. 해당 테이블에 내용을 추가해보겠습니다.  
````
import { PrismaClient } from '@prisma/client'

const prisma = new PrismaClient()

async function main() {
  await prisma.psts.create({
      data: {
          title: 'blahblah',
          name: 'mack',
          what: 'what?'
      }
  })
}

main()
  .catch((e) => {
    throw e
  })
  .finally(async () => {
    await prisma.disconnect()
  });
````

ts-node를 이용하여 코드를 실행시켜줍니다.  
````
npx ts-node index.ts
````

정상적으로 db에 데이터가 들어가게됩니다.

## CRUD

### findOne

`findOne` 쿼리를 사용하면 ID 또는 다른 고유 속성으로 단일 데이터베이스 레코드를 검색 할 수 있습니다.  
select및 include옵션을 사용하여 반환 된 객체에 포함 할 속성을 결정할 수 있습니다.  
여기서 중요한건 고유한 속성인 값만 넣을 수 있다는 점입니다.  

- ex

id가 42인 user의 정보를 추출
````
const result = await prisma.user.findOne({
  where: {
    id: 42,
  },
})
````

예를들어 아까의 Psts의 레코드 하나를 출력해본다면?  
````
await prisma.psts.findOne({
      where: {
          id:1
      }
  })

// 결과
{ id: 1, title: 'blahblah', name: 'mack', what: 'what?' }
````

### findMany

findMany쿼리는 데이터베이스 레코드의 목록을 반환합니다.  
select및 include옵션을 사용하여 반환 된 객체에 포함 할 속성을 결정할 수 있습니다.  
목록을 페이지 네이션, 필터링 및 순서를 지정할 수도 있습니다.

- ex

아까 만든 Psts에 name이 mack인 데이터를 여러개 create한뒤에 findMany로 데이터를 추출해보겠습니다.  
````
await prisma.psts.findMany({
    where: {
        name: 'mack'
    }
})

// 결과
[
  { id: 1, title: 'blahblah', name: 'mack', what: 'what?' },
  { id: 2, title: 'walwal', name: 'mack', what: 'what the' },
  { id: 3, title: 'hey', name: 'mack', what: 'the' }
]
````

### create

create쿼리는 새로운 데이터베이스 레코드를 작성합니다.  
select및 include옵션을 사용 하여 반환 된 객체에 포함 할 속성을 결정할 수 있습니다.  

- ex

````
  await prisma.psts.create({
      data: {
          title: 'hey',
          name: 'mack',
          what: 'the'
      }
  })
````

### update

update쿼리는 기존 데이터베이스 레코드를 업데이트합니다.  
select및 include옵션을 사용 하여 반환 된 객체에 포함 할 속성을 결정할 수 있습니다.  

- ex

id가 1인 레코드의 title 값을 bowwow로 바꿔보겠습니다.  
````
await prisma.psts.update({
        where: { id:1 },
        data: { title: 'bowwow'}
    })

// 결과
{ id: 1, title: 'bowwow', name: 'mack', what: 'what?' }
````

### Upsert

upsert쿼리는 기존 데이터를 업데이트하거나 새 데이터베이스 레코드를 작성합니다.  
select및 include옵션을 사용 하여 반환 된 객체에 포함 할 속성을 결정할 수 있습니다.  

- ex

이번엔 id가 1인 레코드의 title값을 바꾸고  
이름이 laxy이고 title은 bobo, what에는 hello라는 데이터를 만들어보겠습니다.  
````
    await prisma.psts.upsert({
        where: {
            id:1
        },
        update: {
            title: 'id:1, changed'
        },
        create: {
            title: 'bobo',
            name: 'laxy',
            what: 'hello'
        },
    })
````

### delete

delete쿼리는 기존의 데이터베이스 레코드를 삭제합니다.  
레코드를 삭제하더라도 삭제 된 delete객체를 계속 반환합니다.  
select및 include옵션을 사용 하여 반환 된 객체에 포함 할 속성을 결정할 수 있습니다.  

- ex

이번엔 id가 1인 레코드를 지워보겠습니다.  
````
    await prisma.psts.delete({
        where: {
            id:1
        }
    })

//결과
null
[
  { id: 2, title: 'walwal', name: 'mack', what: 'what the' },
  { id: 3, title: 'hey', name: 'mack', what: 'the' }
]
````

### updateMany

updateMany쿼리는 대량의 기존 데이터베이스 레코드를 업데이트하고 삭제 된 레코드의 수를 반환합니다.  
업데이트 할 레코드 목록을 필터링 할 수 있습니다.

- ex

이번엔 이름이 mack인 데이터의 title을 바꿔보겠습니다.  
````
    await prisma.psts.updateMany({
        where:{
            name:'mack'
        },
        data:{
            title:'all title update'
        }
    })

// 결과
[
  { id: 2, title: 'all title update', name: 'mack', what: 'what the' },
  { id: 3, title: 'all title update', name: 'mack', what: 'the' }
]
````

### deleteMany

deleteMany쿼리는 대량의 기존 데이터베이스 레코드의 배치를 삭제하고 삭제 된 레코드의 수를 반환합니다.  
삭제할 레코드 목록을 필터링 할 수 있습니다.  

- ex

이번엔 이름이 mack인 데이터를 모두 삭제해보겠습니다.
````
    await prisma.psts.deleteMany({
        where: {
            name: 'mack'
        }
    })

// 결과
[]
````

### count

count()를 사용하면 사용 가능한 레코드 수가 반환됩니다. 계산할 레코드 목록을 필터링 할 수 있습니다.  

- ex

이번엔 Psts에 3개의 레코드를 생성하고 카운트 해보겠습니다.
````
await prisma.psts.count()

// 결과
3
````

