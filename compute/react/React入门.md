# React使用

[TOC]



## 环境搭建

安装nodejs

然后终端输入

```shell
npx create-reat-app my_react_app
#或者
npx create-next-app my_react_app
#打开
cd  my_react_app
#启动
npm start
```

###  另

npm 地址切换

```shell
#查看地址
npm config get registry
#设定地址
npm config set registry http://registry.npm.taobao.org/
#回复默认
npm config delete registry
```

 



## 核心语法

React组件：一个包含功能的显示区域控件；

有 类组件 和 函数组件 ，主推使用函数组件，较为简单；

jsx语法的一个组件

```typescript
function App() { 
    
    const divContent = '标签内容'
    const divTitle = '标签标题'
  return (
    <>
      <div title={divTitle}>
	      {divContent}
      </div>     
    </>
  )
}

export default App
```



### 列表

```javascript
import { Fragment } from "react/jsx-runtime";

function cmp_list() {

    const list = [
        { id: 1, name: 'wu' },
        { id: 2, name: 'wang' },
        { id: 3, name: 'hua' },
    ]

    //循环生成  多个根标签
    const listContent = list.map(item => ( 
        <Fragment key={item.id}>
            <li>{item.name}</li>
            <li>-----------</li>
        </Fragment>     
    ))

    ////一般生成  
    // const listContent = list.map(item => ( 
    //     <li key={item.id}>{item.name}</li>       
    // ))
 
    return (
        <>
            <ul>{listContent}</ul>
        </>
    )
 
}


export default cmp_list;
```

### 事件操作

点击事件

```javascript
 

function cmp_click() {
 
    function handleClick(e){
        console.log('click',e);
    }

    return (
        <>
           <button onClick={handleClick}></button>
        </>
    )
 
}
 
export default cmp_click;
```

### 状态

单一状态

```javascript
import { useState } from "react";
  
function cmp_state() {

    const [content, setContent] = useState('default content')

    function handleClick( ) {
        setContent('new content ')
    }
    return (
        <>
            <div>{content}</div>
            <button onClick={handleClick}></button>
        </>
    )
}

export default cmp_state;
```

对象状态

```javascript

import { useState } from "react";
 
function cmp_update() {

    const [data, setData] = useState({
        title:'def title',
        content:'def content'
    })

    // function handleClick( ) {
    //     setData({
    //         title:'new title',
    //         content:'new content'
    //     })
    // }

    function handleClick( ) {
        setData({
            ...data,//展开属性直接用原属性覆盖 该属性不做改变
            content:'new content'
        })
    }
 
    return (
        <>
            <div>{data.title}</div>
            <div>{data.content}</div>
            <button onClick={handleClick}></button>
        </>
    )
}

export default cmp_update;
```

列表状态

```javascript
import { useState } from "react";
 
function cmp_list_update() {

    const [data, setData] = useState(
        [
            { id: 1, name: 'wu' },
            { id: 2, name: 'wang' },
            { id: 3, name: 'hua' },
        ]
    )
 
    //一般生成  
    const listData = data.map(item => (
        <li key={item.id}>{item.name}</li>
    ))

    //向列表中添加一项
    let id = 3;
    function handleAddClick() {
        setData([
            ...data,
            { id: ++id, name: 'li' }
        ])
    }

    //删除列表中某项
    function handleDelClick() {
        setData(data.filter(item=>item.id!==2))
    }
 
    return (
        <>
            <ul>{listData}</ul>
            <button onClick={handleAddClick}></button>
            <button onClick={handleDelClick}></button>
        </>
    )

}
 
export default cmp_list_update;
```







## 通讯和插槽





## React Hooks 用法



### reducer hooks

```javascript
import { useReducer  } from "react";


function countReducer(state: number, action: { type: any; }) {
    switch (action.type) {
        case "increment":
            return state + 1;
        case "decrement":
            return state - 1;
        default:
            throw new Error()
    }
}

export default function HookUseReducer() {
    const [state, dispatch] = useReducer(countReducer, 0)
    const handleIncrement = () => dispatch({ type: "increment" })
    const handleDecrement = () => dispatch({ type: "decrement" })

    return(
        <div>
            <button onClick={handleDecrement}>-</button>
            <span>{state}</span>
            <button onClick={handleIncrement}>+</button>
        </div>
    )

}
 
// export default function
```

### ref hooks

```javascript
import { useState, useRef } from "react";

export default function HookUseRef() {
    const [count, setCount] = useState(0)
    const prevCount = useRef<number|undefined>(undefined)

    function handleClick() {
        if (count !== undefined) {
            prevCount.current = count
            setCount(count + 1)
        }
    }

    return (
        <div>
            <p> last count : {prevCount.current}  </p>
            <p> new count : {count}  </p>
            <button onClick={handleClick}>increment</button>
        </div>
    )

}
```

### effect hooks

```javascript
import { useEffect, useState } from "react";


//useEffect用于数据副作用  即为 trigger 触发
export default function HookUseEffect() {
    const [count, setCount] = useState(0)
    const handleIncrement = () => setCount(count + 1)
    const handleDecrement = () => setCount(count - 1)

    //#开始创建一个副作用函数
    useEffect(()=>{
        console.log("useEffect")
    },[count])  
    //[ ]   为    就第一次变化执行useEffect  然后不再执行useEffect
    //[count]   为    count渲染变化导致effect执行useEffect
    

    return (
        <div>
            <button onClick={handleDecrement}>-</button>
            <span>{count}</span>
            <button onClick={handleIncrement}>+</button>
        </div>
    ) 
} 
```



### memo hooks

```javascript
import { useState, useMemo } from "react";


function DoSomeMathX({ value }) {
    console.log("re-calculated")
    let result = 0;
    for (let i = 0; i < 1000000; i++) {
        result += value * 2;
    }
    return (
        <div>
            <p>input:{value}</p>
            <p>cal:{result}</p>
        </div>
    );
}

// useMemo内部的内容在value不改变时不再进行计算 相当于 将首次得到的结果缓存了起来 
function DoSomeMath({ value }) {

    const result = useMemo(() => {
        console.log("re-calculated")
        let result = 0;
        for (let i = 0; i < 1000000; i++) {
            result += value * 2;
        }
        return result;
    }, value)

    return (
        <div>
            <p>input:{value}</p>
            <p>cal:{result}</p>
        </div>
    );
}

export default function HookUseMemo() {

    const [inputValue, setInputValue] = useState(5);
    const [count, setCount] = useState(0);

    return (
        <div>
            <p>count:{count}</p>
            <button onClick={() => setCount(count + 1)}>update</button>
            <br />
            <br />
            <input
                type="number"
                value={inputValue}
                onChange={(e) => setInputValue(parseInt(e.target.value))}
            />
            <DoSomeMath value={inputValue} />
        </div>
    );
 
} 
```





### callback hooks

```javascript
import { useState, memo, useCallback } from "react";

//
const Button = memo(
    function Button({ onClick }) {
        console.log('button rendered');
        return <button onClick={onClick}>sub components</button>;
    })
 
function ButtonX({ onClick }) {
    console.log('button rendered')
    return <button onClick={onClick}>sub components</button>
}

export default function HookUseCallback() {
    const [count, setCount] = useState(0)

    // const handleClick =()=>{
    //     console.log('click button')        
    // };
    //直接将函数缓存   主组件渲染时不再进行子组件渲染
    const handleClick = useCallback(
        () => { console.log('click button'); },
        []
    )
 
    const handleUpdate = () => {
        setCount(count + 1)
    };
 
    return (
        <div>
            <p>count:{count}</p>
            <button onClick={handleUpdate}>click</button>
            <br />
            <Button onClick={handleClick} />
        </div>
    )

}
```



























