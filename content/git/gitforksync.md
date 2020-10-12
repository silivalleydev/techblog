---
title: "git fork & sync"
metaTitle: "git fork & sync"
metaDescription: "This is the meta description for this page"
---

## git fork란?

`fork`는 저장소의 복사본으로 저장소를 분기하여 원래 프로젝트에 영향을 주지않고 자유롭게 실험할 수 있는 공간을 만듭니다.

## git fork는 왜 사용하는가?

일반적으로는 다른 사람의 프로젝트에 대한 변경을 제안하거나 다른 사람의 프로젝트로 자신의 아이디어를 구현하고 싶을때 사용합니다.

### 다른 사람의 프로젝트에 대한 변경 제안

예를 들어 `fork`를 사용하여 버그 수정과 관련된 변경 사항을 제안할 수도 있습니다.  
발견 한 버그에 대한 문제를 기록하는 대신 다음을 수행 할 수 있습니다.

- 저장소를 `fork`합니다.
- 버그와 관련된 내용을 수정합니다.
- 프로젝트 소유자에게 `pull request` 요청을 합니다.

## 포크 하는법

1. 복사하고 싶은 원본 저장소에 들어가서 왼쪽 상단에 있는 `Fork` 버튼을 누르고 복사할 공간을 선택합니다.
2. `Fork`로 복사된 저장소에 들어간 후 `git clone`해줍니다.
3. `clone`한 코드를 에디터로 열어 `git remote -v`로 먼저 포크된 저장소와 연결된 원격 저장소를 확인합니다.
4. `git remote add upstream 원본 저장소 URL`하여 `upstream` 설정을 하고 `git remote -v`으로 원본 저장소에 `upstream`되어있는지 확인합니다.  
- **잠깐! upstream 이란?**

    처음 `fork`를 시도한 저장소를 `upstream`이라고 합니다.  
    - 내가 다른 사람의 `repository`를 `fork`해왔을 때에 `upstream`은  
    일반적으로 `original repository(다른 사람의 repository)`를 의미합니다.  
    즉 내가 `다른 repository`를 `fork`해왔다고 할 때에 이 `다른 repository`가  
    `original repository`이고 `upstream`은 이를 지칭하는 것입니다.

    - 한편 `origin`은 내 `fork`를 의미합니다.  
    레포가 `clone`될 때에 `default remote`는 `origin`이라고 불립니다.  
    그러니까 내 `fork`를 `myRepo`라고 할 때, 클론하면 `myRepo`가 `origin`이 됩니다.  
    내가 `original repository`의 변화를 추적하고 싶으면 `upstream`이라는 이름의 리모트를  
    추가해야 합니다.

## sync fork(포크 동기화)란?

`upstream repository`와 `fork repository`를 동기화하여 최신 상태를 유지하는 것을 포크 동기화 라고합니다.

## sync fork하는 방법

1. 업스트림 저장소에서 브랜치와 각각의 커밋을 `git fetch upstream` 커멘드로 가져옵니다.  
커밋 `master`은 로컬 `branch`에 저장됩니다 `upstream/master`.
2. `git branch -a`로 전체 브랜치를 확인합니다.
3. `git checkout master`로 `fork`의 마스터 브랜치를 확인합니다.
4. `upstream/master`에서 로컬 `master` 브랜치로 변경 사항을 `git merge upstream/master`로 `merge`합니다.  
이것은 `master` 로컬 변경 사항을 잃지 않고 `fork`의 `branch`를 `upstream repository`와 `동기화(sync)`합니다.