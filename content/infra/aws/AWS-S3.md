---
title: "AWS-S3"
metaTitle: "AWS-S3"
metaDescription: "This is the meta description"
---

# AWS-ServerLessWebHosting

## CloudFront

`Region` 안 에는 `S3Bucket`이 존재합니다.  
이 버킷 안에html, img, 동영상 파일 등 컨텐츠를 업로드하여 호스팅을 하게되면 웹사이트 처럼 작동할 수 있게 구성할 수 있습니다.  

기본적으로 `S3`는 인터넷과 통신할 수 있는 대용량 객체 스토리지이고 웹사이트에서 어디서든지 원하는 양의 데이터를 저장하고 검색할 수 있기 때문에 `S3`만으로도 웹 호스팅이 가능합니다.  

근데 만약 웹브라우저에서 읽어들일 컨텐츠의 양이 방대하다면 로딩이 지연되는 현상이 발생하게되는데  
이를 보완해준 서비스가 `Amazon Colud Front` 입니다.  

`Colud Front` 컨텐츠를 빠르게 읽어들일 수 있도록 `Caching` 기능을 제공하기 때문에 `S3` 단독으로 구성한 웹보다 더 빠른 웹서비스를 만들 수 있게됩니다.  

보통 `S3` 단독으로 이용하면 `S3Bucket`에 있는 컨텐츠 들이 바로 유저나 개발자에게 전송되지만, `Cloud Front`를 이용하게되면 컨텐츠들이 캐싱이되어 더욱 빠르게 전송되게 됩니다.  

## 아키텍쳐 구현 순서

#### S3 정적 웹 호스팅 구성하기

1. S3 Bucket 생성
2. 정적 웹 사이트 호스팅 활성화
3. 웹 사이트 엔드포인트 테스트(정상적으로 호스팅 되는지 테스트)

#### Cloud Front를 이용해 웹사이트 속도 높이기

1. Clout Front 배포 만들기
2. 생성된 Cloud Front 도메인 확인

## S3 실습

1. `S3` 서비스를 찾아서 들어간 다음 `Create Bucket`을 합니다.  
2. `Bucket name`을 설정하고 `Region`을 `Seoul`로 설정해줍니다.  
3. `Bucket settings for Block Public Access`는 외부인터넷과 `S3`로의 접속의 보안 기능 설정 탭입니다.  
모든 인터넷에서의 접속을 차단하는것인데 일단은 전부 풀고 진행해봅니다. 나머지 설정값은 기본값으로 설정합니다.
4. 이제 아까 만든 버킷에 들어가보면 `Overview`가 보이게됩니다.
5. `Proerties` 탭에서 `Static Website hosting`을 누르면 설정 탭이 보이게됩니다.  
이 상태에서 `Use this bucket to host a website`를 선택합니다.  
`Index document` 박스에는 `index.html`을 넣어주면되는데, 이렇게하면 버킷에 웹 호스팅해서 접속할 때  
처음 읽어들이는 파일을 `index.html`로 명시하게된 것입니다.  
그 다음 `save`합니다.
6. 그 다음 `Permissions`에서 권한을 설정합니다.  
처음 탭은 버킷 생성시 설정한 보안 관련 내용입니다.  
세번째 탭은 `Bucket Policy`를 설정하면되는데, 이것은 외부 인터넷에서 `AWS S3` 내부로 접속을 차단, 허용하는것 뿐만 아니라 버킷과 버킷내의 컨텐츠에대한 보안을설정하는 공간입니다.  
먼저 `Bucket policy editor` 옆에 `ARN` 부분을 카피합니다.  
이 내용을 정책을 작성할 때 사용합니다.  
제일 밑에 `Policy generator`를 누릅니다. 이는 `Bucket policy`를 작성해주는 에디터입니다.  

첫번째 `Policy Type`은 `S3 Bucket Policy`를 선택합니다.  

두번째 `Add Statement`에서는 권한 부분을 설정해주는 겁니다.  

`Effect`는 `Allow`해주고, `Principal`은 모든 서비스에 대해 모든 서비스에 대해 허용하겠다는 의미에서 `*`를 넣습니다.  
`Action`에서는 어떤 권한을 줄것인지 선택하는 겁니다. `All Action`을 선택합니다.  
`Amazon Resource Name`에는 아까 복사한 `ARN` 코드를 붙여넣기 하시면됩니다.  
이렇게 `Add Statement`를 하면 정책이 생성됩니다.  
그 다음 작성된 Policy를 복사해서 에디터에 붙여넣기합니다.  
이렇게만 사용하면 컨텐츠에 버킷을 올리더라도 웹 호스팅이 되지 않게되기 때문에 `Resource` 부분에 문구를 추가해야하는데, `/*`를 추가하면됩니다.  
이 의미는 버킷아래에 있는 모든 컨텐츠가 외부로 나가는 것을 허용한다는 의미입니다. 이후 저장합니다.  
이렇게되면 웹사이트 호스팅이 설정된것입니다.  
7. 이제 호스팅할 `index.html` 파일을 업로드합니다.
8. 업로드한 `index.html`을 눌러보게되면 상세 내용이 나오게되는데, `Object URL`을 눌러보면 웹페이지가 보이게됩니다.

## CloudFront 실습

1. `CloudFront Distributions`에서 `Create Distribution`을 누름
2. `Web`의 `Get Started`를 누른다
3. `S3 Bucket`의 리스트가 `Origin Domain Name`을 클릭하면 나옵니다
4. `Distribution Settings`의 `Price Class`는 Edge Location에 Cashing하겠다는 부문인데 이를 All Location(전세계에서 캐싱)으로 설정합니다
5. `Create Distribution`을 눌러 배포를 생성합니다
6. Status가 Deployed가되면 배포가된 것입니다.
7. CloudFront Distribution의 `Domain Name/index.html`이런식으로 했을때 해당 페이지가 정상적으로 나온다면 성공한 것입니다.

