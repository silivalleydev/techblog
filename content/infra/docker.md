---
title: "docker"
metaTitle: "docker"
metaDescription: "This is the meta description"
---

## Docker

Docker는 개발자와 시스템 관리자가 build, run, container와 어플리케이션을 공유할 수 있도록 해주는 플랫폼입니다.  

컨테이너를 사용하여 어플리케이션을 배포하는 것을 containerization이라고합니다.  
컨테이너는 새로운 것은 아니지만 어플리케이션을 쉽게 배포하는데 사용됩니다.  

Conatinerization의 장점은 아래와 같습니다.  

- Flexible(유연성): 가장 복잡한 어플리케이션도 컨테이너화 할 수 있습니다.
- Lightweight(경량성): Container는 host kernel을 활용하고 공유하므로 시스템 리소스 측면에서 Virtual Machine보다 효율적입니다.  
- Portable(이식성): 로컬에서 빌드하고 클라우드에 배포하고 어디에서나 실행 가능합니다.
- Loosely coupled(느슨하게 결합): 컨테이너는 자체적으로 highly self sufficient하고 캡슐화 되어있으므로  
다른 컨테이너를 방해하지 않고 컨테이너를 교체하거나 업그레이드 할 수 있습니다.  
- Scalable(확장성): 데이터 센터에서 컨테이너 복제본을 늘리고 자동으로 배포할 수 있습니다.  
- Secure(보안성): 컨테이너는 사용자가 구성할 필요없이 프로세스에 constraint와 isolation을 적용합니다.  

### 이미지 및 컨테이너

컨테이너는 실행중인 프로세스에 지나지 않으며 호스트 및 다른 컨테이너와 격리된 상태를 유지하기 위해 일부 추가 캡슐화 기능이 적용됩니다.  
컨테이너 격리의 가장 중요한 측면 중 하나는 각 컨테이너가 자체 개인 파일 시스템과 상호작용한다는 것입니다.  
이 파일 시스템은 Docker Image에 의해 제공됩니다.  
이미지에는 어플리케이션을 실행하는데 필요한 모든 것이 포함됩니다.  

### 컨테이너 및 가상머신

컨테이너는 기본적으로 리눅스에서 실행되며 호스트 시스템의 커널을 다른 컨테이너와 공유합니다.  
별도의 프로세스를 실행하여 다른 실행 파일보다 더 많은 메모리를 사용하지 않으므로 가볍습니다.  

반대로 Virtual Machine은 호스트 리소스에 가상으로 접근할 수 있는 '게스트 운영체제'를 실행합니다.  

### 도커 받기

[도커 받는 주소](https://docs.docker.com/get-docker/)  

### Docker 버전 테스트

`$ docker --version`  

### Docker 설치 테스트

````
$ docker run hello-world

dUnable to find image 'hello-world:latest' locally
latest: Pulling from library/hello-world
0e03bdcc26d7: Pull complete 
Digest: sha256:4cf9c47f86df71d48364001ede3a4fcd85ae80ce02ebad74156906caff5378bc
Status: Downloaded newer image for hello-world:latest

Hello from Docker!
This message shows that your installation appears to be working correctly.

To generate this message, Docker took the following steps:
 1. The Docker client contacted the Docker daemon.
 2. The Docker daemon pulled the "hello-world" image from the Docker Hub.
    (amd64)
 3. The Docker daemon created a new container from that image which runs the
    executable that produces the output you are currently reading.
 4. The Docker daemon streamed that output to the Docker client, which sent it
    to your terminal.

To try something more ambitious, you can run an Ubuntu container with:
 $ docker run -it ubuntu bash

Share images, automate workflows, and more with a free Docker ID:
 https://hub.docker.com/

For more examples and ideas, visit:
 https://docs.docker.com/get-started/
````

- `docker image ls`로 도커 이미지가 리스트에 있는 지 확인해보세요
- `docker ps`는 실행중인 컨테이너를 확인할 수 있으며 종료된 컨테이너까지 보고싶다면 `--all` 옵션을 사용합니다.

## 이미지 빌드 및 실행

### Development WorkFlow

1. 먼저 도커 이미지를 생성하여 어플리케이션의 각 구성 요소에 대한 개별 컨테이너를 생성하고 테스트합니다.  
2. 컨테이너와 지원 인프라를 완전한 어플리케이션으로 조립하세요.
3. 완전한 컨테이너 식 어플리케이션을 테스트, 공유 배포합니다.

### 예제를 통한 실습

````
git clone https://github.com/dockersamples/node-bulletin-board
````

#### 이미지 빌드 및 테스트

이제 소스코드와 Dockerfile이 있으므로 첫 번째 이미지를 빌드하고 여기에서 시작된 컨테이너가 예상대로 작동되는지 확인해야합니다.  
아래의 명령을 실행하면 이미지를 빌드합니다.
이미지 빌드할때  docker build --tag bulletinboard:1.0 .  <---마지막에 `.` 붙혀야 빌드가됩니다.

````
docker build --tag bulletinboard:1.0 .
````

Dockerfile의 각 지침을 통해 Docker 단계를 수행하여 이미지를 구축하는 것을 볼 수 있습니다.  
성공하면 빌드 프로세스가 `Successfully tagged bulletinboard:1.0` 메시지와 함께 종료됩니다.  

#### 이미지를 컨테이너로 실행

1. 다음 명령어를 실행하여 새 이미지를 기반으로 컨테이너를 시작합니다.  

````
docker run --publish 8000:8080 --detach --name bb bulletinboard:1.0
````

- common flag

* `--publish`: 도커는 호스트의 포트 8000에서 들어오는 트래픽을 컨테이너의 포트 8080으로 전달하도록 요청합니다.  
컨테이너에는 자체 전용 포트 집합이 있으므로 네트워크에서 하나에 도달하려면 이러한 방식으로 트래픽을 전달해야합니다.  
그렇지 않으면 방화벽 규칙이 기본 보안 상태로 모든 네트워크 트래픽이 컨테이너에 도달하지 못하도록 차단합니다.  
* `--detach`: 도커에게 백그라운드에서 이 컨테이너를 실행하도록 요청합니다.
* `--name`: 다음 명령에서 컨테이너를 참조할 수 있는 이름을 지정합니다.

2. 브라우저에서 어플리케이션에 접속해보면됩니다. `localhost:8000`
컨테이너가 정상적으로 작동하는 것을 확인할 수 있습니다.  

3. 게시판 컨테이너가 올바르게 작동하는 것을 확인했다면 중지시키거나 삭제하시면됩니다. 

```
// 컨테이너 중지
docker stop <컨테이너아이디>

// 컨테이너 중지 및 삭제
docker rm --force <컨테이너아>

// 도커 이미지 삭제하고 싶은경우
docker rmi <이미지아이디>
```

## 클라우드에 배포

### 샘플 Dockerfile 

Dockerfile 작성은 어플리케이션 컨테이너화의 첫번째 단계입니다. 이러한 Dockerfile 명령은 이미지를  
빌드하는 방법에 대한 단계별 레시피로 생각할 수 있습니다. 예제 어플리케이션의 Dockerfile은 다음과 같습니다.  

```python
FROM node:12

ENV PORT 3000

# app 디렉토리 생성
RUN mkdir -p usr/src/app

# Docker 이미지 내부에서 RUN, CMD, ENTRYPOINT의 명령이 실행될 디렉터리를 설정합니다.
WORKDIR /usr/src/app

# 현재 디렉터리에 있는 파일들을 이미지 내부 /app 디렉터리에 추가함
COPY package.json .
COPY . /usr/src/app

# npm 스크립트 코드를 실행
RUN npm install

RUN npm run build

# 하기 포트를 외부로 노출합니다.
EXPOSE 3000

# 컨테이너가 시작되었을 때 npm start 스크립트를 실행
CMD "npm" "start"
```

```python
# 공식이미지를 상위 이미지(node에서 제공하는 공식 이미지)로 사용합니다. (FROM)
FROM node:current-slim

# 작업 디렉토리를 설정합니다. (WORKDIR)
# app 디렉토리 생성
WORKDIR /usr/src/app

# 호스트에서 현재 위치로 파일을 복사합니다. (COPY)
COPY package.json .

# 이미지 파일 시스템 내에서 명령을 실행하세요 (RUN)
RUN npm install

# 이미지에 메타 데이터를 추가하여 런타임에 컨테이너가 수신하는 포트를 설명합니다. (EXPOSE)
EXPOSE 8080

# 컨테이너에 지정된 명령을 실행합니다. (CMD)
CMD [ "npm", "start" ]

# 나머지 앱 소스 코드를 호스트에서 이미지 파일 시스템으로 복사합니다. (COPY)
COPY . .
```

- 정의된 dockerfile은 다음 단계를 따릅니다.  

* `FROM`: 기존 `node:current-slim` 이미지를 시작합니다.  
이것은 node.js 공급 업체에서 빌드하고 Docker에서 고품질 이미지로 검증된 공식 이미지입니다.  
* `WORKDIR`: `WORKDIR`을 사용하여 모든 후속 작업이 이미지 파일 시스템의 `/ usr / src / app `에서 디렉토리에서 수행되도록 지정합니다.
* `COPY`: 호스트의 `package.json` 파일을 이미지의 현재 위치로 복사합니다.(이 경우에는 /usr/src/app/package.json)
* `RUN`: 이미지 파일 시스템 내에서 `npm install` 명령을 실행합니다.(앱의 노드 종속성을 확인하기 위해 package.json을 읽고 설치)
* `CMD`: CMD 지시문은이 이미지를 기반으로 컨테이너를 실행하는 방법을 설명하는 일부 메타 데이터를 이미지에 지정하는  
첫 번째 예입니다. 이 경우이 이미지가 지원하는 컨테이너화 된 프로세스는 `npm start`라는 의미입니다.
* `EXPOSE`: EXPOSE 8080은 컨테이너가 런타임에 포트 8080에서 수신 대기 중임을 Docker에 알립니다.

### Docker Hub에서 이미지 공유

1. 도커 허브에 가입 후 Docker 아이콘을 클릭하고 Repositories > Create로 이동하여 리포지토리를 생성합니다.
2. 도커 허브에서 이미지를 공유하려면 올바르게 네임 스페이스를 지정해야합니다. 양식은 `<Your Docker ID>/<Repository Name>:<tag>`입니다.  

````
docker tag bulletinboard:1.0 <Your Docker ID>/bulletinboard:1.0
````

3. 도커 허브에 푸시하기전, 도커 로그인을 해줘야합니다.

````
docker login
````

4. 마지막으로 이미지를 도커 허브에 푸시합니다.

````    
docker push <Your Docker ID>/bulletinboard:1.0
````

## Docker Compose

Compose는 다중 컨테이너 Docker 어플리케이션을 정의하고 실행하기 위한 도구입니다.  
Compose에는 YAML 파일을 사용하여 어플리케이션의 서비스를 구성합니다.  
그 다음 단일 명령으로 configuration으로 부터 모든 서비스를 만들고 시작합니다.  
  
Compose는 프로덕션, 스테이징, 개발, 테스트 및 CI 워크 플로우와 같은 모든 환경에서 작동합니다.  

- 작성 사용은 기본적으로 3단계 프로세스입니다.  

1. `Dockerfile`: 어디에서나 재현할 수 있도록 `Dockerfile`을 이용하여 앱의 환경을 정의합니다.  
2. `docker-compose.yml`: 격리된 환경에서 함께 실행할 수 있도록 앱을 구성하는 서비스를 정의합니다.  
3. `docker-compose up`: 실행 및 작성은 전체 앱을 시작하고 실행합니다.  

`docker-compose.yml`는 다음과 같습니다.

````
version: '2.0'
services:
  web:
    build: .
    ports:
    - "5000:5000"
    volumes:
    - .:/code
    - logvolume01:/var/log
    links:
    - redis
  redis:
    image: redis
volumes:
  logvolume01: {}

````

Compose에는 어플리케이션의 전체 생명 주기를 관리하는 명령이 있습니다.  

- 서비스 시작, 중지 및 재 구축
- 실행중인 서비스의 상태보기
- 실행중인 서비스의 로그 출력 스트리밍
- 서비스에서 일회성 명령 실행

### Docker Compose 시작하기

#### 설정

1. 먼저 폴더를 만드세요.

````
mkdir composetest
cd composetest
````

2. 프로젝트 디렉토리에`app.py`라는 파일을 만들고 다음 위치에 붙여 넣습니다.  

```python
import time

import redis
from flask import Flask

app = Flask(__name__)
cache = redis.Redis(host='redis', port=6379)


def get_hit_count():
    retries = 5
    while True:
        try:
            return cache.incr('hits')
        except redis.exceptions.ConnectionError as exc:
            if retries == 0:
                raise exc
            retries -= 1
            time.sleep(0.5)


@app.route('/')
def hello():
    count = get_hit_count()
    return 'Hello World! I have been seen {} times.\n'.format(count)
```

이 예에서는 redis애플리케이션 네트워크에있는 redis 컨테이너의 호스트 이름입니다. Redis에 6379 기본 포트를 사용합니다.  

3. 프로젝트 디렉토리에 `requirements.txt`라는 다른 파일을 만들고 다음 위치에 붙여 넣습니다.

```
flask
redis
```

#### Dockerfile 생성

이 단계에서는 Docker 이미지를 빌드하는 Dockerfile을 작성합니다.  
이미지에는 Python 어플리케이션에 대한 모든 dependencies가 포함되어 있습니다.  

프로젝트 디렉토리에 Dockerfile 다음 이름의 파일을 만들고 붙여 넣습니다.  
````
FROM python:3.7-alpine
WORKDIR /code
ENV FLASK_APP app.py
ENV FLASK_RUN_HOST 0.0.0.0
RUN apk add --no-cache gcc musl-dev linux-headers
COPY requirements.txt requirements.txt
RUN pip install -r requirements.txt
EXPOSE 5000
COPY . .
CMD ["flask", "run"]
````

위에 작성한 내용은 아래와 같은 의미를 가집니다.

- Python 3.7 이미지로 시작하는 이미지를 빌드합니다.
- 작업 디렉토리를 `/code`로 설정합니다.
- `flask` 명령에 사용되는 환경변수를 설정합니다.
- gcc 및 기타 dependencies를 설치합니다.
- `requirement.txt`를 복사하고 Python dependencies를 설치합니다.
- 이미지에 메타데이터를 추가하여 컨테이너가 포트 5000에서 수신중임을 설정합니다.
- workdir의 이미지를 현재 디렉토리에 복사합니다.
- 컨테이너의 기본명령을 `flask run`으로 설정합니다.

#### Compose 파일에서 서비스 정의

프로젝트 디렉토리에 `docekr-compose.yml`라는 파일을 만들고 다음을 붙여넣습니다.  

````
version: '3'
services:
  web:
    build: .
    ports:
      - "5000:5000"
  redis:
    image: "redis:alpine"
````

- 웹서비스

이 `web` 서비스는 `Dockerfile` 현재 디렉토리에서 빌드된 이미지를 사용합니다.  
그런 다음 컨테이너와 호스트 시스템을 노출된 5000 포트에 바인딩합니다. 예제 서비스는 Flask 웹 서버의 기본 포트인 5000을 사용합니다.  

- Radis 서비스

이 radis 서비스는 Docker Hub 레지스트리에서 가져온 공개 Radis 이미지를 사용합니다.  

#### Compose 앱 빌드 및 실행

1. 프로젝트 디렉토리에서 `docker-compose up` 명령어로 어플리케이션을 시작합니다.  
2. `http://localhost:5000/`을 통해서 실행중인 어플리케이션을 확인할 수 있습니다.
3. `docker image ls`를 사용하면 로컬의 이미지 리스트를 알 수 있습니다.
4. `docker-compose down`으로 실행중인 어플리케이션을 중단하거나 `CTRL + C`로 중단 할 수 있습니다.

#### Compose 파일을 편집하여 바인드 마운트 추가

프로젝트 디렉토리에서 `docker-compose.yml`을 편집하여 서비스에 대한 바인드 마운트를 추가하세요.

````
version: '3'
services:
  web:
    build: .
    ports:
      - "5000:5000"
    volumes:
      - .:/code
    environment:
      FLASK_ENV: development
  redis:
    image: "redis:alpine"
````

`volumns`는 호스트의 프로젝트 디렉토리(현재 디렉토리)를 `/code` 컨테이너 내부에 마운트하므로 이미지를 다시  
빌드하지 않고도 즉시 코드를 수정할 수 있습니다.  `enviroment`는 지시 환경변수(예제에서는 FLASK_ENV)를 설정하여, 개발모드에서  
실행하고 변화에 따라 코드를 다시 로드합니다. 이 모드는 개발에만 사용합니다.  

#### Compose 앱 다시 빌드 및 실행

프로젝트 디렉토리에서 `docker-compose up`을 입력하여 업데이트된 Compose 파일로 앱을 빌드하고 실행합니다.

