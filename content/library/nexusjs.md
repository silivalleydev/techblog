---
title: "Nexus.JS"
metaTitle: "Nexus.JS"
metaDescription: "This is the meta description for this page"
---

# Nexus Js

## NexusJs란?

Nexus.js는  Node.js TypeScript 중심의 code-first GraphQL framework입니다.  
Nexus는 3가지를 보완해줍니다.  

1. 모든 기능을 갖춘 GraphQL API를 빌드하기위한 API입니다.  
모든 기능에는 type-safety autocompletion 및 jsDoc에 중점을 둡니다.
2. 작업하는 동안 일상적인 워크 플로우를 지원하기위한 CLI가 있습니다.
3. A plugin system spaning API and CLI for rich end-to-end plugins that you can use (or write) to fill in your niche needs.  

## CLI

프로젝트 디렉토리를 작성하고를 초기화 package.json하고 nexus를 추가하여 시작하세요.  
````
mkdir nexus-tutorial && cd nexus-tutorial 
npm init -y 
npm install nexus
````

알아야 할 CLI 명령어가 2가지 있습니다.

- `nexus dev`:이 명령은 개발 서버를 watch 모드로 시작합니다. 파일을 변경할 때마다 앱이 다시 시작됩니다.
- `nexus build`:이 명령은 배포 할 준비가 된 "production-ready"서버를 작성합니다.

`package.json`에 스크립트를 세팅해주세요.
`````
"scripts": {
  "dev": "nexus dev",
  "build": "nexus build"
}
`````

### Conventional entrypoint

이제 첫 번째 모듈을 `api/app.ts`다음 에서 생성합니다.
````
mkdir api && touch api/app.ts
````

### Contextual feedback

entry point 설정을 통해 dev 모드를 부팅하고 어떻게되는지 봐야합니다.
````
npm run dev
````

당연히 nexus에서 경고 메세지가 표시될 겁니다.  
````
▲ nexus:schema Your GraphQL schema is empty. [...]
````
넥서스는 GraphQL에 스키마가 추가되어있지 않기 때문에 위의 메세지로 피드백을 해줍니다.

### Try it out

경고 외에도 서버가 실행 중이고 위치를 나타내는 메시지가 표시됩니다.
````
● nexus:server listening  --  url: 'http://localhost:4000/graphql'
````

localhost:4000에 들어가보면 GraphQL playground로 들어가집니다.  

## 첫 번째 스키마 작성

### Reflection?

Nexus에는 Reflection이라는 개념이 있습니다.  
`nexus dev` 또는 `nexus build` 실행중인 경우 응용 프로그램 코드가 실행될뿐만 아니라  
정보가 수집되고 아티팩트가 파생되고 있다는 사실을 나타냅니다.  
리플렉션에 사용되는 Nexus의 일부 기능은 다음과 같습니다.  

- 사용중인 플러그인과 설정이 무엇인지 파악
- 리졸버에게 완벽한 타입 안전성을 제공하는 TypeScript 타입 생성
- SDL 파일 생성

여기에 Nexus에 Declarative API가있는 이유가 부분적으로 설명되어 있습니다.  
빌드 타임에 앱을 안정적으로 실행할 수있는 방법이 필요합니다.  
Declarative API는 Nexus에게이를위한 높은 수준의 제어 기능을 제공합니다.  
Declarative API는 Nexus가 필요한 작업을 수행하기에 충분한 의미를 제공합니다.  

사용자는 자신의 프로젝트에서 작업을 하거나 사용자 자신의 의도하지 않은 서버를 사용할 때(예를들어 GraphQL Playground)  
`nexus dev`를 사용해야한다는 점을 인지하고 있어야합니다.  

### 도메인 모델링

도메인의 일부 핵심 엔티티를 모델링하여 블로그 스키마를 시작해 보겠습니다.  
`Post`라는 것을 만들건데, 이는 블로그의 게시물 페이지를 의미합니다.  
게시되지 않은 경우 draft라고 합니다.  

데이터베이스 계층이 아닌 API 계층에서 모델링 작업이 시작됩니다.  
이 API 우선 접근 방식은 프런트 엔드 팀과 협력하여 데이터를 조기에 형성하는 데 도움을주는 좋은 방법입니다.  

`api/graphql/Post.ts`에서 Post 객체에 대한 새 모듈을 만듭니다.  

우리는 전체 스키마를 api / app.ts 또는 api / graphql.ts에서 작성할 수 있지만  
그러나 GraphQL Type Definition을 모듈화하면 코드베이스를 확장하는 데 도움이 될 수 있습니다  
````
mkdir api/graphql && touch api/graphql/Post.ts
````

`Post`객체를 생성하기 위해 `nexus` 패키지 에서 `schema` 컴포넌트를 가져옵니다.  
`schema.objectType` 방법은 GraphQL Object Type을 만드는 데 도움이됩니다 .

````
// api/graphql/Post.ts
import { schema } from 'nexus'
schema.objectType({
  name: 'Post',            // <- Name of your type
  definition(t) {
    t.int('id')            // <- Field named `id` of type `Int`
    t.string('title')      // <- Field named `title` of type `String`
    t.string('body')       // <- Field named `body` of type `String`
    t.boolean('published') // <- Field named `published` of type `Boolean`
  },
})
````  

### SDL?

이 파일 변경 사항을 디스크에 저장하면 앱이 다시 시작되고 비어있는 GraphQL 스키마에 대한 이전 경고가 사라져야합니다.  

api.graphql 프로젝트 루트에 새 파일 이 있음을 알 수 있습니다.  
여기에는 GraphQL 스키마 정의 언어 (SDL)라는 구문으로 스키마의 표현이 포함됩니다.  
개발자 모드에서 Nexus는 앱을 다시 시작할 때마다 이를 생성합니다. 그 안에 다음이 표시되어야합니다.  
````
type Post {
  id: Int
  title: String
  body: String
  published: Boolean
}
````

이 파일을 비활성화 할 수 있지만 (나중에 설명 할 설정) 파일의 존재는 두 가지 장점이 있습니다.  

SDL에 익숙한 사용자에게는 소스 코드와 해당 코드 간의 일치 성이 Nexus의 스키마 API를 더 빨리 배우는 데 도움이 될 수 있습니다.  
SDL 구문을 사용하면 다른 사람이 Nexus 또는 JavaScript에 대해 알 필요없이 들어오는  
API 변경 사항을 평가할 수있는 방법이됩니다.  

### Your first home-grown query

Post객체가 있지만 클라이언트가 그 데이터를 읽을 수있는 방법은 여전히 ​​없습니다.  
특수 Query객체를 사용 하여 Post 객체를 노출합니다.  

우선 API 클라이언트가 블로그 draft를 읽도록하겠습니다.  
````
// api/graphql/Post.ts      // 1
// ...
schema.extendType({
  type: 'Query',            // 2
  definition(t) {
    t.field('drafts', {     // 3
      nullable: false,      // 4
      type: 'Post',         // 5
      list: true,           // 6
    })
  },
})
````
````
type Query {
  drafts: [Post!]!
}
````

1. Query type은 많은 type들이 표시되는 스키마 중심위치입니다.  
GraphQL Definition을 모듈식으로 하듯이 여기서도 모듈식으로 Definition 할 수 있습니다.  
`api/graphql/Query.ts`로 모듈을 따로 빼거나 한곳에 모든 타입을 정의할수 있습니다.  

2. 프로젝트의 여러 위치에서 type을 "extend"하여 type을 빌드하는 방법을 정의합니다.

3. 첫 번째 매개 변수는 여기에서 필드 이름을 지정합니다. ex) `drafts`  

4. `nullable: false` 클라이언트가 항상이 필드의 값을 가져 오도록 지정합니다.  
기본적으로 Nexus에서는 모든 "output types"(필드에서 반환 된 type)은 null이 가능합니다.  

5. type: 필드의 type을 지정합니다. ex) `Post`  

6. `list: true` 필드의 type 스펙을 확장하여 목록 유형으로 랩핑합니다.  

여기에서, [Post]와 같이 여러개의 Post 배열을 받을때, Nexus는이 아래와 같은 것을 제공합니다.  
````
definition(t) {
  t.list.field('drafts', { ... })
}
````

IDE에서 resolve속성 이 누락되었다는 피드백이 표시 됩니다. 계속해서 자동 완성 기능을 사용하도록 구현하십시오.  
````
// api/graphql/Post.ts
import { schema } from 'nexus'
// ...
schema.extendType({
  type: 'Query',
  definition(t) {
    t.field('drafts', {
      type: 'Post',
      list: true,
      resolve() {
        return [{ id: 1, title: 'Nexus', body: '...', published: false }]
      },
    })
  },
})
````

### 사용해보기

이제 GraphQL Playground를 열고 다음 쿼리를 시도해보십시오 (위쪽).  
이에 대한 응답으로 다음과 같이 표시됩니다 (아래쪽).  

````
{
  drafts {
    id
    title
    body
    published
  }
}
````
````
{
  "data": {
    "posts": [
      {
        "id": 1,
        "title": "Nexus",
        "body": "...",
        "published": false
      }
    ]
  }
}
````

## Adding mutations to Your API

### Wire up the context

가장 먼저 할 일은 인 메모리 데이터베이스를 설정하고 GraphQL 컨텍스트를 사용하여 리졸버에 노출시키는 것 입니다.  

````
touch api/db.ts
````

````
// api/db.ts
export const db = {
  posts: [{ id: 1, title: 'Nexus', body: '...', published: false }],
}
````

이제 GraphQL 컨텍스트에서이를 노출하기 위해 addToContext라는 새로운 스키마 메소드를 사용합니다.  
앱의 어느 곳에서나 할 수 있지만 api/app.ts에서 이미 만든 모듈입니다.  

````
// api/app.ts
import { schema } from 'nexus'
import { db } from './db'

schema.addToContext(() => {
  return {
    db,
  }
})
````

넥서스는 TypeScript 컴파일러 API를 사용하여 리턴 유형을 추출하여 컨텍스트가 액세스 가능한 앱의 일부로 전파합니다.
````
declare global {
  interface NexusContext {
    // type information here
  }
}
````

### Use the context

이제 Query.drafts 데이터를 사용하여 리졸버를 다시 구현해 보겠습니다.  
````
schema.queryType({
  definition(t) {
    t.list.field('drafts', {
      type: 'Post',
      resolve(_root, _args, ctx) {                             // 1
       return ctx.db.posts.filter(p => p.published === false)  // 2
      },
    })
  },
})
````

1. 컨텍스트(ctx)는 일반적으로 다음과 같이 식별되는 세 번째 매개 변수입니다.
2. 게시되지 않은 게시물 ( 일명 draft)로 필터링 된 데이터를 반환합니다 . Nexus는 type이 일치하는지 확인합니다.

### First Mutation

이제 상황에 맥락을 연결하는 방법을 알았으니 첫 번째 Mutation을 구현해 봅시다.  
API 클라이언트가 새 draft를 만들 수 있도록하겠습니다.  

Mutation은 이름이 필요한데 `createDraft`라고 하겠습니다.  

- Mutation 루트 type이며 해당 필드는 entry point입니다.
- Mutation 필드를 모든 Mutation 필드와 관련이 있거나 집중시키는 개체와 함께 위치시킬 수 있습니다.

이전과 마찬가지로 배열 방식을 사용합니다.

````
// api/graphql/Post.ts
// ...
schema.extendType({
  type: 'Mutation',
  definition(t) {
    t.field('createDraft', {
      type: 'Post',
      nullable: false,
      resolve(_root, args, ctx) {
        ctx.db.posts.push(/*...*/)
        return // ...
      },
    })
  },
})
````

````
Mutation {
  createDraft: Post!
}
````

리졸버를 완료하려면 클라이언트의 입력 데이터를 가져와야합니다.  
이를 통해 새로운 개념 인 GraphQL argrument를 얻을 수 있습니다.  
GraphQL의 모든 필드가 이를 승인 할 수 있습니다.  
효과적으로 GraphQL의 각 필드를 함수처럼 생각할 수 있습니다.  
입력을 받아들이고, 무언가를하고, 출력을 반환합니다.  
대부분의 경우 "무언가를하는 것"은 읽기와 유사한 작업의 문제이지만 Mutation,  
"무언가를하는 것"필드에는 일반적으로 부작용이있는 프로세스 (예 : 데이터베이스에 쓰는)가 수반됩니다.  

GraphQL argument로 구현을 수정 해 봅시다.
````
schema.extendType({
  type: 'Mutation',
  definition(t) {
    t.field('createDraft', {
      type: 'Post',
     args: {                                        // 1
       title: schema.stringArg({ required: true }), // 2
       body: schema.stringArg({ required: true }),  // 2
     },
      resolve(_root, args, ctx) {
       const draft = {
         id: ctx.db.posts.length + 1,
         title: args.title,                         // 3
         body: args.body,                           // 3
         published: false,
       }
       ctx.db.posts.push(draft)
       return draft
      },
    })
  },
})
````

````
Mutation {
  createDraft: Post
  createDraft(title: String!, body: String!): Post
}
````

1. 필드 정의에 args 특성을 추가하여 arg를 정의하십시오.  
키는 arg 이름이고 값은 type 사양입니다.
2. argument type을 정의하려면 Nexus 헬퍼를 사용하십시오.  
schema.booleanArg 또는 schema.intArgand와 같은 모든 GraphQL 스칼라마다 이러한 도우미가 있습니다.  
InputObject와 같은 type을 참조하려면 schema.arg({ type: "..." })을 사용하세요.
3. 리졸버에서 위에서 지정한 arg에 액세스하여 사용자 정의 로직으로 전달하십시오.  
args 매개 변수 위로 마우스를 가져 가면 정의 할 수 없다는 사실을 포함하여 Nexus에서 올바르게 입력 한 것을 볼 수 있습니다.

### 도메인 모델링 : 2 부

draft를 실제 게시된(publish) 게시물로 변환하기 위해 Mutation을 추가 한 다음  
API 클라이언트가 게시된 게시물을 읽도록 할 것입니다.  

````
// api/graphql/Post.ts
import { schema } from 'nexus'
schema.extendType({
  type: 'Mutation',
  definition(t) {
    // ...
    t.field('publish', {
      type: 'Post',
      args: {
        draftId: schema.intArg({ required: true }),
      },
      resolve(_root, args, ctx) {
        let draftToPublish = ctx.db.posts.find(p => p.id === args.draftId)
        if (!draftToPublish) {
          throw new Error('Could not find draft with id ' + args.draftId)
        }
        draftToPublish.published = true
        return draftToPublish
      },
    })
  },
})
````

````
type Mutation {
  createDraft(body: String!, title: String!): Post
  publish(draftId: Int!): Post
}
````

````
// api/graphql/Post.ts
import { schema } from 'nexus'
schema.extendType({
  type: 'Query',
  definition(t) {
    // ...
    t.list.field('posts', {
      type: 'Post',
      resolve(_root, _args, ctx) {
        return ctx.db.posts.filter(p => p.published === true)
      },
    })
  },
})
````

````
type Query {
  drafts: [Post!]
 posts: [Post!]
}
````

### 사용해보기

이제 GraphQL Playground로 가서이 쿼리를 실행하세요.

````
mutation {
  publish(draftId: 1) {
    id
    title
    body
    published
  }
}
````

````
{
  "data": {
    "publish": {
      "id": 1,
      "title": "Nexus",
      "body": "...",
      "published": true
    }
  }
}
````

이제 게시 된 draft를 posts쿼리 를 통해 볼 수 있습니다.  
````
query {
  posts {
    id
    title
    body
    published
  }
}
````

````
{
  "data": {
    "posts": [
      {
        "id": 1,
        "title": "Nexus",
        "body": "...",
        "published": true
      }
    ]
  }
}
````

## Persisting data (via Prisma)

### Nexus Plugin

Nexus Plugin은 Nexus에서 Prisma를 사용할 수 있도록 해줍니다.  
Nexus Plugin은 세가지 영역을 개선해줍니다.  

- worktime: 새로운 파일 형식을보고, 이벤트에 연결하고, 새로운 CLI 명령을 첨부합니다.
- runtime: 스키마 미들웨어 추가, 사전 설정 설정, 필드 빌더, 사용자 정의 스칼라 등 ...
- testtime: Nexus 테스트 컨텍스트에 데이터 첨부

플러그인 패키지는 일반적으로 `nexus-plugin-<name>`이라는 규칙으로 이름이 지정됩니다.  
이름 접미사 부분으로 참조합니다. 넥서스와 프리즈마를 의미하는 `nexus-plugin-prisma`로 이름을 지정해봅니다.  

````
npm add nexus-plugin-prisma
````

````
import prisma from 'nexus-plugin-prisma'
import { prisma } from 'nexus-plugin-prisma' // alternative, as you wish
import { use } from 'nexus'
use(prisma())
````

모든 플러그인은 기능입니다.  
플러그인 작성자가 원하는 경우 선택적 또는 필수 설정을 할 수 있습니다.  
플러그인을 가져 와서 호출하면 반환 값이 Nexus의 `use` 메소드로 전달됩니다.  

### 데이터베이스에 연결

- Prisma 플러그인 설치
- `api/app.ts` 모듈에서 사용하십시오
- 프리즈마 스키마 생성
- `.env` 데이터베이스 정보를 저장할 파일 작성
- 데이터베이스에 연결

````
npm add nexus-plugin-prisma
````

plugin을 설치한후 아래와 같이 `app.ts` 파일에서 prisma plugin을 사용할 수 있도록 선언해주세요
````
// api/app.ts

import { use } from 'nexus'
import { prisma } from 'nexus-plugin-prisma'

use(prisma())
````

prisma init으로 prisma 관련 파일들을 생성해줍니다.
````
npx prisma init
````

prisma init으로 생성된 schema.prisma에서 연결할 db를 설정해줄 수 있습니다.  
provider는 사용할 db의 종류를 설정해주시면되고 url은 database url을 설정해주는데 이것은 `.env`파일에서 설정해줄겁니다.  
````
// prisma/schema.prisma
datasource postgres {
  provider = "postgresql"
  url      = env("DATABASE_URL")
}
````

아까 schema.prisma 파일에 있던 DATABASE_URL은 이파일로 맵핑되어 여기서 URL을 가져갑니다.  
`<postgres_connection_url>` 쪽에다가 자신이 결정한 database의 url을 넣어주시면됩니다. 

````
# prisma/.env
DATABASE_URL="<postgres_connection_url>"
````

### makeSchema


### 데이터베이스 스키마 생성

우리는 이미 