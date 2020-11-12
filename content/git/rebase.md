## git rebase

- 이론: 추후에 정리 예정


- 커밋 합치고 싶을때
```
// 헤드에서부터 몇개를 가져올것인지
 git rebase -i HEAD~브랜치갯수

* vi 가 나오면 아래의 명령어들에따라 동작

- squash: 이것을 지정하여 여러개의commit을 합침
- reword(r) : 특정 commit의 message 변경
- drop(d) : 특정 commit 제거

// 강제로 푸시함
 git push origin -f HEAD:refs/heads/branchName
```