---
title: "Docker AWS EC2 Deploy"
metaTitle: "Docker AWS EC2 Deploy"
metaDescription: "This is the meta description"
---

## Docker AWS EC2 Deploy

## 배포하는 법

#### AWS 인스턴스 docker 세팅
1. 만들어진 도커이미지를 도커 허브에 올립니다.
2. sudo yum update -y : 인스턴스에 설치한 패키지 및 패키지 캐시를 업데이트 합니다.
3. sudo yum install -y docker : 최신 Docker Community Edition 패키지를 설치합니다.
4. sudo service docker start : 도커 서비스를 시작합니다.
5. sudo usermod -a -G docker ec2-user : ec2-user가 도커 명령을 실행할 수 있도록 docker 그룹에 ec2-user를 추가합니다.
6. 로그아웃하고 다시 로그인해서 새 docker 그룹 권한을 선택합니다(커넥트한 창을 껏다가 다시 커넥트하면됨). 이를 위해 현재 SSH 터미널 창을 닫고 새 창에서 인스턴스를 다시 연결할 수 있습니다. 새 SSH 세션은 해당되는 docker 그룹 권한을 갖게 됩니다.
7. ec2-user 가 도커 명령을 실행할 수 있는지 확인합니다. `docker info`

## 도커 이미지 가져오기

1. `docker login` : 아이디/패스워드를 입력해서 로그인합니다.
2. `docker pull` <이미지 이름>:<태그> : 이미지 이름에 gunjuko/{image-name} 처럼 / 앞에 사용자명을 입력하면 Docker hub에서 해당 사용자가 올린 이미지를 받습니다. 공식 이미지는 사용자명이 붙지 않습니다.
3. `docker images` : 해당 명령어로 도커 허브에서 이미지를 성공적으로 다운받았는지 확인해봅니다.
4. `docker run -d -p 8080:8080 {image}` : 도커 이미지를 이용해서 컨테이너를 실행합니다.