---
title: "Basic git command"
metaTitle: "Basic git command"
metaDescription: "This is the meta description for this page"
---

## git branch

- `git branch` 로컬 브랜치 확인
- `git branch -a` 연결된 모든 브랜치 확인
- `git branch -avv` 연결된 모든 브랜치 연결된 상태까지 확인

## git checkout

- `git checkout -b 생성할 브랜치명` 새로운 브랜치 생성
- `git checkout 이동할 브랜치명` 브랜치 이동

## git remote

-  `git remote -v` 연결된 저장소 확인
-  `git remote add upstream 연결할 저장소주소` upstream으로 설정할 저장소 설정

## git merge

- `git merge 병합할 브랜치명` 현재 로컬 브랜치에 다른 브랜치를 병합. 병합후에는 `push`해줘야한다
