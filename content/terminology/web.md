---
title: "Web"
metaTitle: "Web"
metaDescription: "This is the meta description for this page"
---

## DOM이란 무엇인가?

DOM은 Document Object Model의 약자입니다. Document는 문서이고 Object는 객체로 Model은 모델로 번역이된다.

문서 객체 모델이란 것이 무엇일까? 문서 객체란 `<html>`이나 `<body>` 같은 html문서의 태그들을 JavaScript가 이용할 수 있는 객체  
(object)로 만들면 그것을 문서 객체라고 한다. (그럼 html문서의 태그들이 객체에 담긴 상태를 의미하는 것일까?)

여기에 Model을 붙였는데 Model이라는 영어 단어에는 모형, 주형이라는 의미도 있고 모듈이라는 의미도 있다.  
비슷하게 여기서는 문서 객체를 '인식하는 방식'이라고 해석할 수 있다.  

DOM은 넓은 의미로 웹 브라우저가 HTML 페이지를 인식하는 방식을 의미한다.  
조금 좁은 의미로 본다면 document 객체와 관련된 객체의 집합을 의미할 수도 있습니다.   

이제 DOM을 보게 되면 웹 브라우저가 html 페이지를 인식하는 방식을 이야기 하거나 문서 객체(document object)와  
관련된 객체의 집합에 관한 이야기라는 것을 쉽게 추측할 수 있다.  

DOM은 트리구조로 이어져 있으며, root Node에서 아래로 퍼져나가는 형태를 의미한다.

      root
        0
       /  \
      0     0
     / \   / \
    0   0 0   0

위와 같은 형태이다.

### JavaScript로 문서객체를 생성한다는 것은 어떤 의미인가?

문서 객체가 생성되는 방식은 두 가지로 나누어 볼 수 있다.  
우선 웹 브라우저가 HTML 페이지에 적혀 있는 태그를 읽으면 생성하는 것이다.  
이런 과정을 정적으로 문서 객체를 생성한다고 말한다.  
단순히 적혀져 있는 그대로 문서객체가 생성되는 것을 표현한 것이다.   

반대로 원래 HTML 페이지에 없던 문서객체를 JavaScript를 이용해서 생성할 수 있다.  
이런 과정을 동적으로 문서객체를 생성한다고 한다.  
따라서 JavaScript로 문서객체를 생성한다는 것은 처음에는 HTML 페이지에 없던 문서객체를 동적으로 생성하는 것이 된다. 

### 예제

```html
<!DOCTYPE html>
<html>
<head>
<meta charset="UTF-8">
<title> 문서객체 모델(DOM)</title >
<script type= "text/javascript">
    window.onload = function(){
       //1. 문서 객체 생성
       var header = document.createElement('h2'); //h2 태그를 생성해주는 것
       var textNode = document.createTextNode('Hello DOM');

       //2. 노드(요소/텍스트)를 연결.
       header.appendChild(textNode);

       //3. body 문서 객체에 header 문서 객체를 추가.
       document.body.appendChild(header);
    };
</script>
</head>
<body>
   <h1 id ="header_1" name= "" >HEADER-1 </h1 >
   <div >
      <h1 id = "header_2">HEADER-2</h1 >
   </div >
   <hr >
   <h1 id = "clock"></h1>
</body>
</html>
```