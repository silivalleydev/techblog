# Prisma 2

Prisma는 데이터베이스를 쉽게 사용할 수 있게 도와주는 데이터베이스 툴킷 입니다.  

## Prisma의 구성

- Prisma Client: Prisma server 와 상호작용을 하는 Prisma Client 입니다.
- Prisma Migrate: Django의 migration과 같이 데이터베이스 모델을 선언할 수 있습니다.
- Prisma Studio: 데이터베이스의 데이터를 수정할 수 있도록 Prisma에서 제공해주는 GUI 입니다.

## Prisma는 어떻게 동작할까?

### Prisma Schema

Prisma를 사용하는 모든 프로젝트는 Prisma schema file 을 거칩니다.  
Prisma schema file 은 기본적으로 schema.prisma 라는 네이밍을 가지고 Prisma CLI 가 자동으로 감지합니다.  
만약 다른 네이밍을 가질 경우, 명령어에 --schema 옵션과 주소를 같이 넣어주면 됩니다.  
````
prisma generate --schema ./database/myschema.prisma
````

````

datasource db {
  provider = "postgresql"
  url      = env("DATABASE_URL")
}
generator client {
  provider = "prisma-client-js"
}
model User {
  id    Int     @id @default(autoincrement())
  email String  @unique
}
````

`schema.prisma` 는 위처럼 작성할 수 있습니다.  
Prisma Schema에서는 3가지를 설정 할 수 있습니다.

- Data source: 데이터베이스를 연결합니다.
- Generator: Prisma Client를 생성합니다.
- Data model: 애플리케이션의 모델을 정의합니다.

### Prisma data model

data model은 모델의 집합입니다.  
이 모델은 두 가지의 중요한 함수를 가지고 있습니다.  

- 데이터베이스의 테이블을 나타냅니다.
- Prisma Client API의 쿼리에 대한 기반을 제공합니다.

또한 Prisma Schema에 모델을 입력하는 방법도 크게 두 가지가 있습니다.  
두 가지 방법 모두 아래 예제에서 해보겠습니다.  

- 데이터베이스를 검사해서 데이터 모델을 생성하는 방법
- 데이터 모델을 수동으로 작성하여 Migrate로 데이터베이스에 매핑하는 방법

## Prisma로 MySQL 세팅하기

### 필수 사항

Prisma와 MySQL을 사용하기 전에 Node.js 와 MySQL 설치가 되어있어야겠죠? 만약 없다면 설치해주세요.  

### 초기화

새 프로젝트를 만들고 필요한 의존성 패키지를 설치하겠습니다.  
````
$ mkdir hello-prisma
$ cd hello-prisma
$ npm init -y
$ npm i -D @prisma/cli typescript ts-node @types/node
````

그리고 `tsconfig.json` 를 만들어서 typescript 설정을 하겠습니다.  
````
// tsconfig.json
{
  "compilerOptions": {
    "sourceMap": true,
    "outDir": "dist",
    "strict": true,
    "lib": ["esnext"],
    "esModuleInterop": true
  }
}
````

Prisma CLI를 설치했다면 명령어로 `prisma schema` 파일을 만들 수 있습니다.

````
$ npx prisma init
````

## 데이터베이스 연결

위 명령어를 입력했다면 `schema.prisma` 라는 파일이 생성된 것을 확인할 수 있는데요,  
MySQL을 사용하기 위해선 `schema.prisma` 파일의 `datasource` 를 수정해야합니다.  
`datasource` 의 `provider` 를 `postgresql` 에서 `mysql` 로 바꿔주세요.  
그리고 자신의 데이터베이스 `connection URL` 을 알아야합니다. MySQL은 이런 형식을 가지고 있습니다.  

mysql://root:1234@localhost:3306/prismatest

- `.env` 에 세팅해줍니다

````
# Environment variables declared in this file are automatically made available to Prisma.
# See the documentation for more detail: https://pris.ly/d/prisma-schema#using-environment-variables

# Prisma supports the native connection string format for PostgreSQL, MySQL and SQLite.
# See the documentation for all the connection string options: https://pris.ly/d/connection-strings

DATABASE_URL="mysql://root:1234@localhost:3306/prismatest"
````

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

`connection URL` 에 대한 다른 정보는 [여기](https://www.prisma.io/docs/reference/database-connectors/connection-urls) 에서 확인해주세요.  
참고로 MySQL의 기본 포트는 3306 입니다!  

## Prisma Migrate로 데이터베이스 테이블 생성

간단하게 Post, Profile, User Model을 작성해보겠습니다.  
````
// This is your Prisma schema file,
// learn more about it in the docs: https://pris.ly/d/prisma-schema

datasource db {
  provider = "mysql"
  url      = env("DATABASE_URL")
}

generator client {
  provider = "prisma-client-js"
}

model Post {
  id        Int       @default(autoincrement()) @id
  createdAt DateTime  @default(now())
  title     String
  content   String?
  published Boolean   @default(false)
  author    User      @relation(fields: [authorId], references: [id])
  authorId  Int
}

model Profile {
  id      Int   @default(autoincrement()) @id
  bio     String?
  user    User  @relation(fields: [userId], references: [id])
  userId  Int   @unique
}

model User {
  id      Int     @default(autoincrement()) @id
  email   String  @unique
  name    String?
  posts   Post[]
  profile Profile?
}
````

`schema.prisma` 에 위 처럼 모델을 작성하고 아래 명령어로 migrate를 해주세요.
````
$ npx prisma migrate save --name init --experimental
$ npx prisma migrate up --experimental
````

`migrate save` 로 migration 히스토리를 생성하고 `migrate up` 을 통해 실제 DB의 테이블을 생성합니다.  
데이터베이스에 접속하면 모델을 작성한대로 테이블과 _Migration 테이블이 생성된 것을 확인할 수 있습니다.  

## 데이터베이스 테이블 불러오기

명령어 `npx prisma migrate` 를 통해서 데이터베이스 테이블을 생성했다면,  
이번엔 반대로 Prisma에서 데이터베이스 테이블을 불러오는 방법을 알아보겠습니다.  
명령어 `npx prisma introspect` 로 불러올 수 있습니다.  
이 명령어로 Prisma CLI가 데이터베이스를 검사하고 다른 부분이 있다면 Prisma schema 를 업데이트 합니다.  

## 데이터베이스 제어하기

데이터베이스를 연결하고 테이블을 생성했으니 사용해봐야겠죠?  
Prisma로 데이터베이스를 제어하려면 제어할 client가 있어야합니다.  
````
npm install @prisma/client
````

### Prisma Client 생성하기

아래 명령어를 통해 Prisma CLI가 우리의 Prisma schema 를 읽고  
`node_modules/@prisma/client` 에 Prisma Client 를 생성합니다.  
````
npx prisma generate
````

## Prisma Client 사용하기

이제 client를 사용해봅시다. `index.ts` 를 생성하고 아래 코드를 작성해주세요.  
````
import { PrismaClient } from '@prisma/client'

const prisma = new PrismaClient()

async function main() {
  await prisma.user.create({
    data: {
      name: 'Alice',
      email: 'alice@prisma.io',
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

### Prisma Client를 사용하여 데이터베이스에 쿼리를 보냅니다.

````
import { PrismaClient } from '@prisma/client'
const prisma = new PrismaClient()
// use `prisma` in your application to read and write data in your DB
````

또는

````
const { PrismaClient } = require('@prisma/client')
const prisma = new PrismaClient()
// use `prisma` in your application to read and write data in your DB
````    

인스턴스화되면 `PrismaClient`코드에서 쿼리를 보낼 수 있습니다.

`ts-node`는 미리 컴파일 할 필요없이, 사용자가 직접 타입 스크립트 파일을 실행 할 수있는 NPM 패키지입니다
````
npx ts-node index.ts
````

# Prisma 공식 사이트 이론

## Prisma란?

Prisma는 오픈 소스 데이터베이스 툴킷입니다. 주로 다음과 같은 부분으로 구성됩니다.  

- Prisma Client : Node.js 및 TypeScript를위한 자동 생성 및 유형 안전 쿼리 빌더
- Prisma Migrate ( Experimental ) : 선언적 데이터 모델링 및 마이그레이션 시스템
- Prisma Studio ( Experimental ) : 데이터베이스에서 데이터를보고 편집하는 GUI

Prisma Client는 모든 Node.js 또는 TypeScript 백엔드 애플리케이션 (서버리스 애플리케이션 및 마이크로 서비스 포함) 에서 사용할 수 있습니다 .  

## Prisma의 작동방식

### The Prisma schema

Prisma 툴킷의 도구를 사용하는 모든 프로젝트는 Prisma 스키마 파일로 시작합니다 .  
Prisma 스키마를 통해 개발자는 직관적인 데이터 모델링 언어로 애플리케이션 모델을 정의 할 수 있습니다.  
또한 데이터베이스에 대한 연결을 포함하고 generator를 정의합니다.  

````
datasource db {
  provider = "postgresql"
  url      = env("DATABASE_URL")
}
generator client {
  provider = "prisma-client-js"
}
model Post {
  id        Int     @id @default(autoincrement())
  title     String
  content   String?
  published Boolean @default(false)
  author    User?   @relation(fields:  [authorId], references: [id])
  authorId  Int?
}
model User {
  id    Int     @id @default(autoincrement())
  email String  @unique
  name  String?
  posts Post[]
}
````

이 스키마에서는 다음 세 가지를 구성합니다.  

- Data source: 환경 변수를 통해 데이터베이스 연결을 지정합니다
- Generator: Prisma Client를 생성 할 것임을 나타냅니다.
- Data model: 애플리케이션 모델을 정의합니다

### 프리즈 마 데이터 모델

#### 프리즘 모델의 기능

모델에는 두 가지 주요 기능이 있습니다.  

- 기본 데이터베이스에서 테이블을 나타냅니다.
- Prisma Client API의 쿼리 기반을 제공합니다.  

#### 데이터 모델 얻기

Prisma 스키마에 데이터 모델을 "가져 오기"위한 두 가지 주요 워크 플로우가 있습니다.  

- 데이터베이스를 검사 하여 데이터 모델 생성
- Prisma Migrate 를 사용하여 데이터 모델을 수동으로 작성하고 데이터베이스에 매핑

데이터 모델이 정의되면 Prisma Client 를 생성 하여 정의 된 모델에 대한 CRUD 및 추가 쿼리를 표시 할 수 있습니다.  
TypeScript를 사용하는 경우 모델 필드의 하위 집합 만 검색하는 경우에도 모든 쿼리에 대해 완전한 형식 안전성을 얻을 수 있습니다.  

## Prisma Client로 데이터베이스에 액세스

### PrismaClient 생성

Prisma Client를 사용하는 첫 번째 단계는 @prisma/clientnpm 패키지를 설치하는 것입니다.  
````
npm install @prisma/client
````

@prisma/client 패키지를 설치하면 prisma generate 명령어를 호출되어 Prisma schema를 읽고 Prisma Client 코드를 생성합니다.  
코드는 node_modules/@prisma/client에 있습니다. 
 
데이터 모델을 변경 한 후 내부 코드 node_modules/@prisma/client가 업데이트 되도록  
Prisma Client를 수동으로 다시 생성해야합니다 .

````
prisma generate
````