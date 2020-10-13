---
title: "Basic"
metaTitle: "Basic"
metaDescription: "This is the meta description"
---

## list comprehension

- `list([append에 넣을값 for i in range(반복횟수)])`

```py
## 
hash_table = list([0 for i in range(10)])
print(hash_table) # [0, 0, 0, 0, 0, 0, 0, 0, 0, 0] <-- 해시 테이블에서 슬롯을 만든것 0번 1번 2번 등 해시 주소를 가지고 있고 0이라는 해시 값이 있는 해시 테이블을 만든것

# 위의 내용은 아래와 같다
hash_table2 = []
for i in range(10):
    hash_table2.append(0)

print(hash_table2)
```

- ord(): ASC||(아스키 코드)를 리턴함
```py
data1 = 'Jack'

print(ord(data1[1])) # 97
```