# QML常用操作

[TOC]

## 准备常用组件

MyRectangel.qml

```js
import QtQuick 2.15

Rectangle{
    id:borderRect
    property int myTopMargin:0
    property int myBottomMargin:0
    width:100
    height:100
    color:"black"
    Rectangle{
        id:innerRect
        color:"blue"
        anchors.fill: parent
        anchors.topMargin: myTopMargin
        anchors.bottomMargin: myBottomMargin
        anchors.leftMargin: 0
        anchors.rightMargin:0
    }
} 
```

## 组件与Loader

```js
//自定义组件并加载  
Component{
            id:com
            Rectangle{
                width:200
                height:100
                color:"black"
        	}
    	 } 
Loader{
        sourceComponent: com
      }
```

加载其他qml

```js
Loader{
        source:"/MyRectangle.qml" 
	    asynchronous: true		//异步加载 加载大资源使用
      }
```

动态加载组件

```js
//组件定义
Component{
        id:com
        Rectangle{
            width:200
            height:100
            color:"black"
            Component.onCompleted: {
                console.log("onCompleted",width,height,color)
            }
            Component.onDestruction: {
                console.log("onDestruction")
            }
        }
    }
//加载组件
Loader{
        id:loader 
        sourceComponent: com
        onStatusChanged: { console.log("status",status)  }
     }
//点击后可断链并让loader销毁组件
 Button{
        width:50
        height:50
        x:300
        onClicked: {  loader.sourceComponent = null  }
    }
//点击后修改组件内属性
 Button{
        width:50
        height:50
        x:600
        onClicked: { 
        	loader.item.width=50
            loader.item.color="red"
        }
    }
```



 

## 组件文件互相调用

MyComponent.qml

```js
import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.5

Rectangle{
    width:400
    height:300

    property Component com1
    property Component com2
    border.color: "black"

    Loader{
        id:loader1
        sourceComponent: com1
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 20

        Connections{
            target:loader1.item
             //无视未知信号  尤其发送者可能已经删除了信号栏
            ignoreUnknownSignals: ture
            function onBtnSig(value){ console.log("loader1",value) }
        }
    }

    Loader{
        id:loader2
        sourceComponent: com2
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 20
        anchors.right: parent.right
        anchors.rightMargin: 150

        Connections{
            target:loader2.item
            ignoreUnknownSignals: ture 
            function onBtnSig(value){ console.log("loader2",value) }
        }
    }

}
//定义组件时很多对信号相应的槽函数都可以当作组件的动作方法
```



main.qml

```js
import QtQuick 2.15
import QtQuick.Window 2.15 
import QtQuick.Controls 2.5

Window {
    id:window
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World") 
    //透明度
    opacity: 0.9 
	//-------------------------------
    Component{
        id:com
        Button{
            signal btnSig(int value)
            onClicked: {
                console.log ("clicked")
                btnSig(1002)
            }
        }
    } 
    MyComponent{
        com1:com
        com2:com
    } 
}
```

 

## QML的信号与槽

```js
Window {
    id:window
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World") 
    //-------------------------------
    //透明度
    opacity: 0.9 
    //-------------------------------
	//自定义信号槽
    signal testSig(string s ,int value ) 
	//按钮
    Button{
        width: 50
        height: 80
        y:40
        onClicked: testSig("go",495)
    } 
	//信号槽链接
    Connections {
        target:window
        //接收反应函数
        function onTestSig(sss,iii){
            console.log(sss,iii)
        } 
    } 
	//-------------------------------
} 
```



## QML 和 C++交互

### 属性关联

#### 旧版做法

前端main.qml

```js
import QtQuick 2.15
import QtQuick.Window 2.15 
import QtQuick.Controls 2.5

Window {
    id:window
    width: SCREEN_WIDTH
    height: 480
    visible: true
    title: qsTr("Hello World")  
}
```

后端main.cpp关键代码

```c++
QQmlApplicationEngine engine;
QQmlContext*  context= engine.rootContext();
//上下文操作作用于全局，可能影响性能，且前端重复定义会被重名隐藏
context->setContextProperty("SCREEN_WIDTH",200); 
```



#### 新版做法

新建一个类MyObject    ，  myobject.h

```c++
#ifndef MYOBJECT_H
#define MYOBJECT_H

#include <QObject>

class MyObject : public QObject
{
    Q_OBJECT
public:
    explicit MyObject(QObject *parent = nullptr);

    int iValue() const;
    void setIValue(int newIValue);

    const QString &sString() const;
    void setSString(const QString &newSString);

signals:
    void iValueChanged();

    void sStringChanged();

private:
    int m_iValue;		//针对变量 alt+enter 会自动创建一系列相关方法和宏定义
    QString m_sString;
  
    //这里的notify是值改变的通知
    Q_PROPERTY(int iValue READ iValue WRITE setIValue NOTIFY iValueChanged)
    //Q_PROPERTY(int iValue MEMBER m_iValue NOTIFY iValueChanged)//类内部值简写
    Q_PROPERTY(QString sString READ sString WRITE setSString NOTIFY sStringChanged)
	//Q_PROPERTY(QString sString MEMBER m_sString NOTIFY sStringChanged)
};

#endif // MYOBJECT_H

```



新建一个类MyObject，  myobject.cpp

```c++
#include "myobject.h"

MyObject::MyObject(QObject *parent)
    : QObject{parent}
{

}

int MyObject::iValue() const
{
    return m_iValue;
}

void MyObject::setIValue(int newIValue)
{
    if (m_iValue == newIValue)
        return;
    m_iValue = newIValue;
    emit iValueChanged();
}

const QString &MyObject::sString() const
{
    return m_sString;
}

void MyObject::setSString(const QString &newSString)
{
    if (m_sString == newSString)
        return;
    m_sString = newSString;
    emit sStringChanged();
}
```

 

后端main.cpp关键代码

```c++
QQmlApplicationEngine engine; 
qmlRegisterType<MyObject>("MyObj",1,0,"MyObject");//关键
```

前端main.qml 

```js
import QtQuick 2.15
import QtQuick.Window 2.15

import QtQuick.Controls 2.5

import MyObj 1.0

Window {
    id:window
    width: SCREEN_WIDTH
    height: 480
    visible: true
    title: qsTr("Hello World")

    //透明度
    opacity: 0.9
    //-------------------------------
    property int ivalue: myobj.iValue //ref动态绑定 由于iValue定义了通知动作；一个改变 会通知另一个改变 
    
    MyObject{
        id:myobj
        iValue:10
        sString: "ggs"
        Component.onCompleted: {
            console .log(iValue,sString);
        }
    }
    Button{
        width: 200
        height:200
        onClicked: {
            console.log(ivalue)
            myobj.iValue = 50   		//修改实例中的值 触发时就发出通知
            myobj.sString = "ecet"
            console.log(ivalue)
        }
    } 
}

```



### QML发送信号调用C++函数 

#### 类准备

myobject.h

```c++
#ifndef MYOBJECT_H
#define MYOBJECT_H

#include <QObject>

class MyObject : public QObject
{
    Q_OBJECT
public:
    explicit MyObject(QObject *parent = nullptr);
 
    Q_INVOKABLE void func();//需要调用的函数
  
#endif // MYOBJECT_H

```



myobject.cpp

```c++
#include "myobject.h" 
#include <QDebug>

MyObject::MyObject(QObject *parent)
    : QObject{parent}
{ }  
//需要调用的函数
void MyObject::func(){
    qDebug()<< __FUNCTION__ ; 
} 
```



main.cpp关键代码

```c++
qmlRegisterType<MyObject>("MyObj",1,0,"MyObject"); //关键前后关联
```

#### 控件内置动作直接调用

main.qml

```js
import QtQuick 2.15
import QtQuick.Window 2.15 
import QtQuick.Controls 2.5 
import MyObj 1.0

Window {
    id:window
    width: SCREEN_WIDTH
    height: 480
    visible: true
    title: qsTr("Hello World") 
    //-------------------------------  
    MyObject{
        id:myobj
        iValue:10
        sString: "ggs"
        Component.onCompleted: {
            console .log(iValue,sString);
        }
    } 
    //------------------------------- 
    //控件内置动作直接调用
    Button{
        width: 200
        height:200
        x:200
        onClicked: {
            myobj.func()
        }
    } 
} 
```

#### 通过Connections绑定qml内信号槽

main.qml

```js
import QtQuick 2.15
import QtQuick.Window 2.15 
import QtQuick.Controls 2.5 
import MyObj 1.0

Window {
    id:window
    width: SCREEN_WIDTH
    height: 480
    visible: true
    title: qsTr("Hello World") 
    //-------------------------------  
    MyObject{
        id:myobj
        iValue:10
        sString: "ggs"
     	Component.onCompleted: {
            console .log("INIT:",iValue,sString);
        }	//初始化完成时打印信息
    } 
    //-------------------------------  
    signal qmlSig(int i,string s)
    Button{
        width: 200
        height:200
        x:200
        onClicked: {
           qmlSig(10,"zgs")
        }
    }
    Connections{
        target: window
        function onQmlSig(i,s){
            myobj.cppSlot(i,s)
       }
     }
} 
```



#### 通过前端初始化完成时 将信号槽与方法绑定

main.qml

```js
import QtQuick 2.15
import QtQuick.Window 2.15 
import QtQuick.Controls 2.5 
import MyObj 1.0

Window {
    id:window
    width: SCREEN_WIDTH
    height: 480
    visible: true
    title: qsTr("Hello World") 
    //-------------------------------  
    MyObject{
        id:myobj
        iValue:10
        sString: "ggs"
     	Component.onCompleted: {
            console .log("INIT:",iValue,sString);
        }	//初始化完成时打印信息
    } 
    //-------------------------------  
    signal qmlSig(int i,string s)
    Button{
        width: 200
        height:200
        x:200
        onClicked: {
           qmlSig(10,"zgs")
        }
    }
   	Component.onCompleted: {
       qmlSig.connect(myobj.cppSlot)
    }
} 
```



#### 通过后端代码关联方法    利用传统connect  比比较麻烦

main.qml

```js
import QtQuick 2.15
import QtQuick.Window 2.15 
import QtQuick.Controls 2.5 
import MyObj 1.0

Window {
    id:window
    objectName: "window"//用于后台识别
    width: SCREEN_WIDTH
    height: 480
    visible: true
    title: qsTr("Hello World") 
    //-------------------------------  
    MyObject{
        id:myobj
        iValue:10
        sString: "ggs"
     	Component.onCompleted: {
            console .log("INIT:",iValue,sString);
        }	//初始化完成时打印信息
    } 
    //-------------------------------  
    signal qmlSig(int i,string s)
    Button{
        objectName: "myButton"//用于后台识别
        width: 200
        height:200
        x:200
        onClicked: {
           qmlSig(10,"zgs")
        }
    } 
} 
```

main.cpp 关键部分

```c++
engine.load(url);

    //LOAD后
    auto list = engine.rootObjects() ;
    auto objWin= list.first();
    qDebug()<<objWin->objectName();//qml 顶级对象 应该是window
    auto objButton = list.first()->findChild<QObject*>("myButton");
    qDebug()<<objButton->objectName();//qml 指名对象 应该是button
	//传统的链接模式
    QObject::connect(objWin,SIGNAL(qmlSig(int,QString)),
                     MyObject::getInstance(),SLOT(cppSlot(int,QString)));
```



###  C++发送信号调用QML函数 

类准备

myobject.h

```c++
#ifndef MYOBJECT_H
#define MYOBJECT_H

#include <QObject>

class MyObject : public QObject
{
    Q_OBJECT
public:
    explicit MyObject(QObject *parent = nullptr);
 
    Q_INVOKABLE void func();

    static MyObject* getInstance(){
        static MyObject* myobj = new MyObject() ;
        return myobj;
    };

public slots:
    void cppSlot (int i,QString s);
 
signals: 
    void cppSig(QVariant i,QVariant s); 
private:
 
};

#endif // MYOBJECT_H

```



myobject.cpp

```c++
#include "myobject.h" 
#include    <QDebug> 
MyObject::MyObject(QObject *parent)
    : QObject{parent}
{

} 
void MyObject::func(){
    emit cppSig(101,"saad");
    qDebug()<< __FUNCTION__ ;
}

void MyObject::cppSlot (int i,QString s){

    qDebug()<< __FUNCTION__<<" " <<i<<" "<<s;

}

```



main.cpp 关键代码

```c++
qmlRegisterSingletonInstance( "MyObj",1,0,"MyObjectInstance",MyObject::getInstance());
//直接采用cpp类的单例实例
```



main.qml

```js
import QtQuick 2.15
import QtQuick.Window 2.15 
import QtQuick.Controls 2.5 
import MyObj 1.0//main.cpp中qmlRegisterSingletonInstance定义一致

Window {
    id:window
    objectName: "window"
    width: SCREEN_WIDTH
    height: 480
    visible: true
    title: qsTr("Hello World")

    //透明度
    opacity: 0.9 
    //-------------------------------
    signal qmlSig(int i,string s)
    function qmlSlot(i,s){
        console.log("qml",i,s);
    }
    Button{
        objectName: "myButton"
        width: 200
        height:200 
        onClicked: {
           MyObjectInstance.func()
        }
    }

    Connections{
        target: MyObjectInstance
        function onCppSig(i,s){
           qmlSlot(i,s)
        }
    } 
}

```





### C++直接调用QML的函数

qml 

```js
import QtQuick 2.15
import QtQuick.Window 2.15 
import QtQuick.Controls 2.5 
import MyObj 1.0//main.cpp中qmlRegisterSingletonInstance定义一致

Window {
    id:window
    objectName: "window"
    width: SCREEN_WIDTH
    height: 480
    visible: true
    title: qsTr("Hello World")

    //透明度
    opacity: 0.9 
    //-------------------------------
    signal qmlSig(int i,string s)
    function qmlFunc(i,s){
        console.log(i,s,"-OK")
        return "success"
    }
    Button{
        objectName: "myButton"
        width: 200
        height:200 
        onClicked: {
           MyObjectInstance.func()
        }
    } 
}

```

main.cpp

```c++
engine.load(url);

//LOAD后 
auto list = engine.rootObjects() ;
auto objWin= list.first();
qDebug()<<objWin->objectName();//qml 顶级对象 应该是window 
//开始调用
QVariant res;
QVariant arg_1=123;
QVariant arg_2="zhangs";
QMetaObject::invokeMethod(objWin,"qmlFunc",
                          Q_RETURN_ARG(QVariant, res),//结果保存
                          Q_ARG(QVariant,arg_1),	//参数
                          Q_ARG(QVariant,arg_2)		//参数
                          );
```





## QML项目打包为DLL





























