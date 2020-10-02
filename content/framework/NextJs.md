# NextJs

## Next.js란?

리액트 어플리케이션의 서버 사이드 렌더링(Server Side Rendering)을 쉽게 구현할 수 있도록 도와주는 간단한 프레임워크입니다.  

## SSR(Server Side Rendering)

서버사이트 렌더링이란 말그대로 서버에서 렌더링 작업을 한다는 뜻입니다.  
기존에 존재하던 방식으로 사용자가 웹페이지에 접근할 때,  
서버에 페이지에 대한 요청을 하며 서버에는 html, view와 같은 리소스를 어떻게 보여질지 해석하고 렌더링하여 사용자에게 반환합니다.  

한마디로 서버측에서 HTML과 View를 생성하여 응답하는 방식입니다.  

### SSR의 장점?

1. SSR의 경우 View를 서버에서 렌더링하여 가져오므로 첫 로딩이 매우 짧습니다.

2. SEO(Search Engine Optimization) 검색엔진 최적화에 유리합니다.  
JS 라이브러리/프레임워크를 사용하면서 고질적인 문제가 SEO인데,  
SSR은 서버에서부터 페이지를 제공할 때 컨텐츠가 담겨있기 때문에 SEO에 대한 걱정을 덜을 수 있습니다.  

## Next.js가 제공해주는 유용한 기능

- 다이나믹 라우트를 이용한 직관적인 페이지 기반의 라우팅 시스템
- 자동으로 페이지를 최적화
- 데이터 요구사항 차단과 함께 서버에서 랜더링
- 빠른 페이지 로딩을 위해 자동으로 코드 스플릿팅
- 최적화된 페이지 프리페치를 사용한 클라이언트 라우팅
- HMR(Hot Module Replacement)을 지원하는 Webpack 기반의 개발 환경
- 페이지에 사용되는 것과 동일한 간단한 라우터를 사용하여 서버리스 기능으로 API를 구축하기 위한 API 라우트
- 커뮤니티 플러그인과 고유한 Babel 및 Webpack 구성으로 사용자 지정 가능

## 설치하기

Next.js 어플리케이션 빌드를 하기위해서는 Node.js가 설치되어 있어야합니다.  
````
$ mkdir hello-next
$ cd hello-next
$ npm init -y// 질문 없이 바로 시작하고 싶다면 -f(--force), -y(--yes) 중 하나의 플래그를 추가하는 것을 추천합니다.
$ npm install --save react react-dom next
$ mkdir pages
````

그런 다음 `package.json` 파일에 아래의 스크립트를 추가해주세요.
````
{
    "scripts":{
        "dev":"next"
    }
}
````

## 첫번째 페이지 생성하기 및 개발 서버 실행

pages/index.js를 생성하고 아래의 내용을 추가하세요.
````
const index = () => (
    <div>
        <p>Hello Next.js</p>
    </div>
)

export default index;
````

아까 위에서 `package.json`에 만든 스크립트로 next.js를 실행시킵니다.  
````
$ npm run dev
````

## 페이지 이동

이제 이 어플리케이션에 페이지를 추가해보도록 하겠습니다.  
'About'이라는 페이지를 만들겁니다. 먼저 pages/about.js를 생성하여 아래의 코드를 추가합니다.  
````
const about = () => (
    <div>
        <p>This is the about page</p>
    </div>
)

export default about;
````

만들고 나면 http://localhost:3000/about 이라는 경로를 통해서 About 페이지에 접근할 수 있습니다.  

이제 이 페이지들을 연결시켜야 합니다. 이를 위해 HTML의 `a`태그를 사용할 수 있습니다.  
그러나 `a` 태그를 사용하면 클라이언트 사이드를 통해 이동하지 않고 서버사이드를 통해 페이지가 이동합니다.  

### a 태그가 문제가 되는 이유?

`a`태그가 문제가되는 이유는 a 태그의 기본적인 속성은 페이지를 이동시키면서, 페이지를 아예 새로 불러오게(refrash)됩니다.  
그렇게 되면서 우리 앱이 지니고있는 상태들도 초기화되고, 렌더링된 컴포넌트도 모두 사라지고 새로 렌더링을 하게됩니다.  

그렇기 때문에 클라이언트 사이드 이동을 지원하기 위해 `next/link`를 통해 export된 Next.js의 Link API를 사용해야 합니다.  

### Link 사용하기

두개의 페이지를 연결하기 위해 `next/link`를 사용할 예정입니다.  

pages/index.js에 아래의 코드를 추가하세요.  
````
import Link from 'next/link';

const index = () => (
    <div>
        <Link href="/about">
            <a>About Page</a>
        </Link>
        <p>Hello Next.js</p>
    </div>
)

export default index;
````

우리는 Link 컴포넌트를 이용하여 About 페이지로 이동하였습니다.  
동작을 보면 서버 요청없이 브라우저 안에서 수행되게 되며, refrash가 일어나지 않습니다.  
이것을 클라이언트 사이드 이동이라고합니다.  

### next/link의 클라이언트 사이드 히스토리 지원

뒤로가기 버튼을 클릭하면 클라이언트 사이드를 통해 인덱스 페이지로 이동합니다.  
`next/link`는 모든 location.history를 처리합니다.  

### Link 스타일링

링크에 스타일을 지정하는 방법이 있습니다.  
하지만 여기서 주의할 점은 `Link` 컴포넌트는 래퍼 컴포넌트이기 때문에 style을 줘도 아무런 효과가 없을 것입니다.  
왜냐하면 `next/link`는 단지 `href`와 다른 라우팅 관련 props만 받아들이는 래퍼 컴포넌트이기 때문입니다.  
스타일을 적용하려면 하위컴포넌트인 `a`태그에 적용해야합니다.  
````
import Link from 'next/link';

const index = () => (
    <div>
        <Link href="/about">
            <a style={{ fontSize: "30px" }}>About Page</a>
        </Link>
        <p>Hello Next.js</p>
    </div>
)

export default index;
````

### Link는 어떤 것과도 동작합니다.

`a` 태그 대신에 `button`을 사용해볼 겁니다. 아래와 같이 코드를 수정해주세요.  
````
import Link from 'next/link';

const index = () => (
    <div>
        <Link href="/about">
            <button>About Page</button>
        </Link>
        <p>Hello Next.js</p>
    </div>
)

export default index;
````

버튼과 같이 커스텀 React 컴포넌트나 div 등을 Link 안에 배치할 수 있습니다.  
Link 안에 있는 컴포넌트들의 유일한 요구사항은 onClick prop을 받을 수 있어야 한다는 것입니다.  

## 공유 컴포넌트

공유 컴포넌트는 한 컴포넌트를 여러 페이지들에서 사용하게되는 컴포넌트를 의미합니다.  
공유 컴포넌트를 통해 Layout 컴포넌트를 구현하고 이 컴포넌트가 여러페이지에서 어떻게 사용되는지 알아볼 겁니다.  

### Header 컴포넌트 구현하기

components/header.js를 생성하고 아래의 코드를 추가하세요.  
````
import Link from 'next/link';

const linkStyle = {
    marginRight: 15
}

const Header = () => (
    <div>
        <Link href="/">
            <a style={linkStyle}>Home</a>
        </Link>
        <Link href="/about">
            <a style={linkStyle}>About</a>
        </Link>
    </div>
)

export default Header;
````

### Header 컴포넌트 사용하기

페이지들 안에 Header 컴포넌트를 import하고 사용해봅시다. index.js 페이지를 아래와 같이 코드를 수정해주세요.  
````
import Header from '../components/header';

const index = () => (
    <div>
        <Header/>
        <p>Hello Next.js</p>
    </div>
)

export default index;
````

Header 컴포넌트는 about 페이지에서도 똑같이 import해줘서 사용할 수 있습니다.  

### 레이아웃 컴포넌트

Header 컴포넌트를 각 페이지에 import해줘서 공용 컴포넌트로 사용할 수 있습니다.  
그런데 만약 공용으로 쓰이는 컴포넌트가 여러개라면 어떨까요?  
각 페이지마다 전부 import해줘서 배치해줘야합니다.  

이러한 방법보단 공통의 스타일을 사용하여 공통 레이아웃 컴포넌트를 만들어 각페이지에서 사용하는 방법이 있습니다.  
그것이 레이아웃 컴포넌트입니다.  
components/MyLayout.js에 아래의 코드를 추가해주세요.  
````
import Header from './Header'

const layoutStyle = {
    margin: 20,
    padding: 20,
    border: "1px solid #DDD",
}

const Layout = (props) => (
    <div style={layoutStyle}>
        <Header/>
        {props.children}
    </div>
)

export default Layout;
````

#### props.children은 무엇인가요?

props.children이라는 것은 부모 컴포넌트의 데이터들을 자식 컴포넌트에게 넘겨주는 것을 의미합니다.  
여기서 부모 컴포넌트는 Layout 컴포넌트가 될 것이며, 데이터를 전달받은 자식 컴포넌트는  
index.js와 about.js들이 될 것입니다.  

이제 위에서 만든 Layout 컴포넌트를 index.js와 about.js에 적용해줄 것입니다.  

- index.js

`````
import Layout from '../components/MyLayout';

const index = () => (
        <Layout>
            <p>Hello Next.js</p>
        </Layout>
)

export default index;
`````

- about.js

````
import Layout from '../components/MyLayout';

const about = () => (
    <Layout>
        <p>This is the about page</p>
    </Layout>
)

export default about;
````

## 동적 페이지

보통 어플리케이션에는 동적 컨텐츠들을 표시하기 위해 동적으로 페이지를 생성해야합니다.  
이번에는 쿼리 문자열을 사용하여 동적으로 페이지를 생성해 볼 겁니다.  

이번에는 간단한 블로그 어플리케이션을 만들 예정입니다.  

### 포스트 목록 추가하기

먼저 home 페이지 안에 포스트 제목 목록을 추가할 겁니다.  
pages/index.js에 다음과 같은 내용을 추가해주세요.  
````
import Layout from '../components/MyLayout';
import Link from 'next/link';

const PostLink = (props) => (
    <li>
        <Link href={`/post?title=${props.title}`}>
            <a>{props.title}</a>
        </Link>        
    </li>
)

const index = () => (
        <Layout>
            <h1>My Blog</h1>
            <ul>
                <PostLink title="Hello Next.js"/>
                <PostLink title="Learn Next.js is awesome"/>
                <PostLink title="Deploy apps with Zeit"/>
            </ul>
        </Layout>
)

export default index;
````

### query string을 통해 데이터 전달하기

query string을 통해 데이터를 전달했습니다.  
위 예제의 경우 title이 query parameter입니다.  
위의 예제로 링크 목록으로 이동하게 되면 url에 `http://localhost:3000/post?title=Hello%20Next.js`  
이런식으로 표현되는데 여기서 `title=Hello%20Next.js`로 표현된 것이 query string을 이용해 데이터를 전달한 것입니다.  

### post 페이지 생성

이제 블로그 포스트를 보여줄 post 페이지를 생성할 겁니다.  
이를 구현하기 위해 위에서 배운 query string으로 제목을 가져올 겁니다.  

pages/post.js를 생성하고 아래의 코드를 추가해주세요.  
````
import Layout from '../components/MyLayout';

const post = (props) => (
    <Layout>
        <h1>{props.url.query.title}</h1>
        <p>This is the blog post contents</p>
    </Layout>
)

export default post;
````

위의 코드에서 일어난 상황을 해석해보자면,  
props로 url prop이 전달되는데,  
![propsurl](./img/propsurl.png)  
url prop에 있는 query 객체를 이용하여 제목을 가져오게되는 것입니다.  

주의할점은 url prop은 페이지의 메인 컴포넌트에만 전달된다는 것입니다.  

만약 자식 컴포넌트에서 url prop을 호출하게되면 어떻게될까요?  
````
import Layout from '../components/MyLayout';

const ChlidrenContent = (props) => {
    <div>
        {props.url.query.title}
    </div>
}

const post = (props) => (
    <Layout>
        <h1>{props.url.query.title}</h1>
        <p>This is the blog post contents</p>
        <ChlidrenContent/>
    </Layout>
)

export default post;
````

위의 코드처럼 하게되면 에러가 발생하게됩니다.  
만약 자식컴포넌트에 전달하고 싶다면 props로 url prop을 전달해줘야되는 것이죠.  
````
import Layout from '../components/MyLayout';

const ChlidrenContent = (props) => (
    <div>
        {props.url.query.title}
    </div>
)

const post = (props) => (
    <Layout>
        <h1>{props.url.query.title}</h1>
        <p>This is the blog post contents</p>
        <ChlidrenContent url={props.url}/>
    </Layout>
)

export default post;
````

## 라우트 마스킹

라우트 마스킹은 실제 url과 다른 url이 브라우저에 표시되게 합니다.  

블로그 포스트 url에 라우트 마스크를 추가해 봅시다.  

pages/index.js에 아래와 같이 코드를 수정해주세요.  
````
import Layout from '../components/MyLayout';
import Link from 'next/link';

const PostLink = (props) => (
    <li>
        <Link as={`/p/${props.id}`} href={`/post?title=${props.title}`}>
            <a>{props.title}</a>
        </Link>
    </li>
)

const index = () => (
        <Layout>
            <h1>My Blog</h1>
            <ul>
                <PostLink title="Hello Next.js"/>
                <PostLink title="Learn Next.js is awesome"/>
                <PostLink title="Deploy apps with Zeit"/>
            </ul>
        </Layout>
)

export default index;
````

`<Link>` 엘레먼트에 `as`라는 prop을 사용하였습니다.  
이는 브라우저에 보여질 url을 의미합니다.  
어플리케이션에 표시되는 url은 href에 지정되어있습니다.  

라우트 마스크를 사용하여 링크를 통해 들어가면 전혀 문제가 없어보입니다.  
하지만 해당 페이지에서 새로고침을 하면 404 에러가 발생하게됩니다.  
왜냐하면 서버에서 불러올페이지가 없기 때문입니다.  
이러한 문제를 해결하는 방법은 Next.js에 커스텀 서버 API가 있습니다.  

## 커스텀 서버 생성하기

Express를 사용하여 어플리케이션의 커스텀 서버를 생성할 겁니다.  

- Express 설치

````
npm install --save express
````

그 다음 server.js 파일을 생성하고 아래의 코드를 추가합니다.
````
const express = require('express');
const next = require('next');

const dev = process.env.NODE_ENV !== 'production';
const app = next({dev});
const handle = app.getRequestHandler();

app.prepare()
.then(() => {
    const server = express();

    server.get('*', (req,res) => {
        return handle(req, res);
    })

    server.listen(3000, (err) => {
        if(err) throw err;
        console.log('> Ready on http://localhost:3000')
    })
})
.catch((ex) => {
    console.log(ex.stack);
    process.exit(1);
})
````

npm dev 스크립트를 수정해주세요.
````
{
    "scripts": {
        "dev": "node server.js"
    }
}

````

이제 `npm run dev` 명령어로 어플리케이션을 실행해주세요.  

그러면 정상적으로 동작은 하지만 서버사이드의 깔끔한 URL 동작은 하지 않을 겁니다.  

### 커스텀 라우트 생성하기

먼저 server.js를 아래와 같이 코드를 수정해주세요.  
````
const express = require('express');
const next = require('next');

const dev = process.env.NODE_ENV !== 'production';
const app = next({dev});
const handle = app.getRequestHandler();

app.prepare()
.then(() => {
    const server = express();

    server.get('/p/:id', (req, res) => {
        const actualPage = '/post';
        const queryParams = {title:req.params.ids};
        app.render(req, res, actualPage, queryParams)
    })

    server.get('*', (req,res) => {
        return handle(req, res);
    })

    server.listen(3000, (err) => {
        if(err) throw err;
        console.log('> Ready on http://localhost:3000')
    })
})
.catch((ex) => {
    console.log(ex.stack);
    process.exit(1);
})
````

## 데이터 가져오기

데이터 소스를 가져오기 위해서는 원격으로 데이터를 가져와야하는데,  
Next.js는 페이지에 데이터를 가져오기위한 표준 API를 제공합니다.  
그것이 `getInitialProps`라 불리는 비동기 함수입니다.  

주어진 페이지에서 원격 데이터 소스를 통해 데이터를 가져오고 원하는 페이지에 props를  통해 전달할 수 있습니다.  

서버와 클라이언트 사이드 둘 다 동작하도록 getInitialProps를 작성할 수 있습니다.  

이번에는 getInitialProps를 사용하여 공개된 [TVmaze API](http://www.tvmaze.com/api)에서 가져온 배트맨 TV쇼에 대한 정보를 보여주는 어플리케이션을 구현할 겁니다.  

### 배트맨 TV쇼 데이터 가져오기

먼저 `isomorphic-unfetch`를 설치해야합니다.  
데이터를 가져올 떄 사용할 라이브러리로 브라우저 fetch API 구현을 간단하게 할 수 있도록 만들어진 것입니다.  
````
npm install --save isomorphic-unfetch
````

pages/index.js 코드를 아래의 코드로 수정해주세요.
````
import Layout from '../components/MyLayout';
import Link from 'next/link';
import fetch from 'isomorphic-unfetch';

const Index = (props) => (
        <Layout>
            <h1>Betman TV Shows</h1>
            <ul>
                {props.shows.map(({show}) => (
                    <li key={show.id}>
                        <Link as={`/p/${show.id}`} href={`/post?id=${show.id}`}>
                            <a>{show.name}</a>
                        </Link>
                    </li>
                ))}
            </ul>
        </Layout>
)

Index.getInitialProps = async function(){
    const res = await fetch('https://api.tvmaze.com/search/shows?q=batman');
    const data = await res.json();

    console.log(`Show data fetched. Count: ${data.length}`);
    console.log(data)
    return {
        shows: data
    }
}

export default Index;
````

위에서보면 `getInitialProps`은 어떤 페이지든 추가할 수 있는 정적 비동기 함수입니다.  

getInitialProps 함수에서 가져온 데이터를 콘솔에 출력해보면,  
서버에서만 출력되게됩니다.  
왜냐하면 처음에 시작할때 페이지는 서버에서 페이지가 랜더링 되기 때문입니다.  
이미 데이터를 가지고 있어서 클라이언트에서 다시 정보를 가져올 필요가 없습니다.  

### post 페이지 구현하기

TV 쇼에 대한 자세한 정보를 보여주는 '/post' 페이지를 구현해봅니다.  

먼저 server.js를 열고 /p/:id 라우트를 다음과 같이 바꿔주세요.  
````
    server.get('/p/:id', (req, res) => {
        const actualPage = '/post';
        const queryParams = {id: req.params.id};
        app.render(req, res, actualPage, queryParams);
    })
````

아래와 같이 pages/post.js를 변경해주세요.
````
import Layout from '../components/MyLayout';

const post = (props) => (
    <Layout>
        <h1>{props.show.name}</h1>
        <p>{props.show.summary.replace(/<[/]?p>/g, '')}</p>
        <img src={props.show.image.medium}/>
    </Layout>
)

post.getInitialProps = async function(context) {
    const {id} = context.query;
    const res = await fetch(`https://api.tvmaze.com/shows/${id}`);
    const show = await res.json();

    console.log(`Fetched show: ${show.name}`);

    return {show}
}

export default post;
````

여기에서 함수의 첫번째 파라미터는 context 객체입니다.  
정보를 가져올 때 사용할 수 있는 쿼리 필드를 가지고 있습니다.  

예제에서 쿼리 파라미터로 보여지는 ID를 선택하고 TV Maze API로부터 데이터를 가져옵니다.  

getInitialProps 함수에서 표시할 제목을 출력하는 console.log를 추가했습니다. 이제 어디에서 출력되는지 볼 수 있습니다.  

배트맨 쇼 제목을 클릭하면 브라우저 콘솔에서 출력됩니다.  

### 클라이언트 사이드에서 데이터 가져오기

브라우저 콘솔에서 출력되는 이유는 클라이언트 사이드를 통해 포스트 페이지로 이동했기 때문입니다.  
만약 http://localhost:3000/p/975 라는 주소에 직접 이동한다면 서버에서 메세지가 출력될 겁니다.  

## 컴포넌트 스타일링

Next.js에는 styled-jsx라는 CSS in JS 프레임워크가 있습니다.  
이 CSS는 해당 컴포넌트에만 적용되며 하위 컴포넌트에는 적용되지 않습니다.  

### home 페이지 스타일링하기

home 페이지(pages/index.js)에 스타일링을 추가해봅시다.  
````
import Layout from '../components/MyLayout';
import Link from 'next/link';

function getPosts() {
    return [
        { id: 'hello-nextjs', title: 'Hello Next.js'},
        { id: 'learn-nextjs', title: 'Learn Next.js is awesome'},
        { id: 'deploy-nextjs', title: 'Deploy apps with Next.js'},
    ]
}


const Index = () => (
        <Layout>
            <h1>My Blog</h1>
            <ul>
                {getPosts().map((post) => (
                    <li key={post.id}>
                        <Link as={`/p/${post.id}`} href={`/post?title=${post.title}`}>
                            <a>{post.title}s</a>
                        </Link>
                    </li>
                ))}
            </ul>
            <style jsx>
            {`
                h1, a {
                    font-family:"Arial";
                }

                ul {
                    padding: 0;
                }

                li {
                    list-style: none;
                    margin: 5px 0;
                }

                a {
                    text-decoration:none;
                    color: blue;
                }

                a:hover {
                    opacity: 0.6;
                }
            `}
            </style>
        </Layout>
)

export default Index;
````

위에서 주의할점은 `<style jsx>`사이에 CSS를 작성할때는 `{``}` 템플릿 문자열 안에 작성해야한다는 것입니다.  

### 스타일과 중첩된 컴포넌트

만약 링크 컴포넌트를 따로 분리시킨다면 스타일이 어떻게 적용될까요?
````
import Layout from '../components/MyLayout';
import Link from 'next/link';

function getPosts() {
    return [
        { id: 'hello-nextjs', title: 'Hello Next.js'},
        { id: 'learn-nextjs', title: 'Learn Next.js is awesome'},
        { id: 'deploy-nextjs', title: 'Deploy apps with Next.js'},
    ]
}

const PostLink = ({ post }) => (
    <li>
        <Link as={`/p/${post.id}`} href={`/post?title=${post.title}`}>
            <a>{post.title}</a>
        </Link>
    </li>
)


const Index = () => (
        <Layout>
            <h1>My Blog</h1>
            <ul>
                {getPosts().map((post) => (
                    <PostLink keu={post.id} post={post}/>
                ))}
            </ul>
            <style jsx>
            {`
                h1, a {
                    font-family:"Arial";
                }

                ul {
                    padding: 0;
                }

                li {
                    list-style: none;
                    margin: 5px 0;
                }

                a {
                    text-decoration:none;
                    color: blue;
                }

                a:hover {
                    opacity: 0.6;
                }
            `}
            </style>
        </Layout>
)

export default Index;
````

링크에는 적용이 안되고 해당 컴포넌트안에 있는 h1태그에만 스타일이 적용되게됩니다.  
즉, 중첩된 컴포넌트에는 적용되지 않습니다.  

만약 적용하고싶다면 직접 링크 컴포넌트 안에 스타일을 적용 시켜주는 방법이 있고,  
````
const PostLink = ({ post }) => (
    <li>
        <Link as={`/p/${post.id}`} href={`/post?title=${post.title}`}>
            <a>{post.title}</a>
        </Link>
        <style jsx>
            {`
                h1, a {
                    font-family:"Arial";
                }

                ul {
                    padding: 0;
                }

                li {
                    list-style: none;
                    margin: 5px 0;
                }

                a {
                    text-decoration:none;
                    color: blue;
                }

                a:hover {
                    opacity: 0.6;
                }
            `}
            </style>
    </li>
)
````

아니면은 전역 스타일을 적용시켜주는 방법이 있습니다.  

### 전역 스타일

때때로 하위 컴포넌트 안의 스타일을 바꿔야하는데, 예시로 리액트에서 마크다운을 사용하는 경우가 있습니다.  
이것을 post페이지에다 적용시켜보겠습니다.  
pages/post.js에 내용을 수정해주세요.  

- 리액트 마크다운 설치

````
npm install --save react-markdown
````
````
import Layout from '../components/MyLayout';
import Markdown from 'react-markdown';

const post = (props) => (
    <Layout>
        <h1>{props.url.query.title}</h1>
        <div className="markdown">
            <Markdown source={`
            This is our blog post.
            Yes. We can hava a [link](/link).
            And we can have a title as well.

            ### This is a title

            And here's the content.
            `}/>
        </div>
        <style jsx global>{`
            .markdown {
                font-family: 'Arial';
            }

            .markdown a{
                text-decoration: none;
                color: blue;
            }

            .markdown a:hover {
                opacity: 0.6;
            }

            .markdown h3 {
                margin: 0;
                padding: 0;
                text-transform: uppercases
            }
        `}
        </style>
    </Layout>
)

export default post;
````

## 배포하기

이번엔 Next.js 어플리케이션을 배포해 볼건데, ZEIT now로 배포를 할 것입니다.  

### Build와 Start

처음으로 프로덕션 우리의 Next.js 어플리케이션을 빌드할 것입니다.  
빌드는 최적화된 프로덕션 세트를 생산합니다.  

다음의 코드를 package.json의 스크립트에 추가해주세요
````
{
    "script": {
        "build": "next build"
    }
}
````

그런 다음 하나의 포트에서 Next.js를 시작해야합니다. 사이드 렌더링을 수행하고 페이지를 제공합니다.  

npm 스크립트를 하나 추가할 겁니다.  
````
{
    "script": {
        "start": "next start"
    }
}
````

이러면 3000 포트에 어플리케이션이 시작됩니다.  

이제 프로덕션에서 어플리케이션을 동작시키기위해 다음의 명령어를 실행할 수 있습니다.  
````
npm run build
npm run start
````

### 두개의 인스턴스 실행하기

애플리케이션의 인스턴스 두개를 실행시켜 봅시다.  
start npm 스크립트를 아래와 같이 변경해주세요.  
````
{
    "script": {
        "start": "next start -p $PORT"
    }
}
````

만약 윈도우라면 next start -p %PORT% 로 스크립트를 변경해야합니다.  

이제 어플리케이션을 처음으로 빌드해봅시다.  
````
npm run build
````

그러면 터미널에서 명령어로 실행시켜봅시다.  
PORT=8000 npm run start
PORT=9000 npm run start

