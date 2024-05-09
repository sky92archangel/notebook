# QML+CPP类MVVM结构工程最小化实现



[toc]



## 一、采用QT对方法提供的宏进行结构MVVM的构建



### 1.打开QT ，并创建QT-QUICK 工程，建议QT5.15及以上

### 2.准备 类 MyObject 其实这个类就可以作为VM使用

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
 
    Q_INVOKABLE QString func(QString str);//需要调用的函数
 
    //单例
    static MyObject* getInstance(){
        static MyObject* myobj = new MyObject() ;
        return myobj;
    };
 
 
    int iValue() const;
    void setIValue(int newIValue);
 
    const QString &sString() const;
    void setSString(const QString &newSString);
 
signals:
    void iValueChanged();
 
    void sStringChanged();
 
private:
    int m_iValue;		//针对变量 alt+enter 会自动创建一系列相关方法和宏定义
    QString m_sString="init";
 
//signals:
 
 
    //这里的通知动作iValueChanged sStringChanged非常重要，是属性变化后 通知前端做同步的核心
    Q_PROPERTY(int iValue READ iValue WRITE setIValue NOTIFY iValueChanged)
    Q_PROPERTY(QString sString READ sString WRITE setSString NOTIFY sStringChanged)
};
 
#endif // MYOBJECT_H
```



myobject.cpp

```c++
#include "myobject.h"
#include <QDebug>
 
MyObject::MyObject(QObject *parent)
    : QObject{parent}
{  } 
//需要调用的函数 
//这里有个重点  必须采用setSString方法来设置sString的值，这样才能启动通知
// 等号赋值不会通知前端，重载复制运算符应该会有效，但是要从QString创建子类操作
QString MyObject::func(QString str)
{
    setSString(sString()+ str + '#' ) ;
    // m_sString = str+"@";
    qDebug()<< __FUNCTION__ <<" === "<<str;
    return sString();
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



### 3 main.cpp中连接创建的类

main.cpp 如果版本较新则采用注册单例qmlRegisterSingletonInstance方式进行 

```C++
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "myobject.h"
 
int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);
 
    QQmlApplicationEngine engine;
 
    //关键//
    qmlRegisterSingletonInstance( "MyObj",1,0,"MyObjectIns",MyObject::getInstance());
 
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);
 
    return app.exec();
}	
```



### 4 qml部分 作为view

main.qml

```C++
import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.5
import MyObj 1.0
 
Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")
 
    onWidthChanged: { console.log(width) }
 
    //ref动态绑定 由于iValue定义了通知动作；
    //一个改变 会通知另一个改变  建议用此承接前端属性
    property string sstring: MyObjectIns.sString
 
    Text {
        id: txt
        text: sstring
    }
 
    Button {
        objectName: "myButton"
        width:100
        height:100
        y:100
        onClicked: {
            MyObjectIns.func("ee")
            console.log ( MyObjectIns.sString)
            console.log (txt.text)
            console.log (sstring)
        }
    }
}
```



## 二、其他后续问题

可见目前只是通过按钮修改后台数据，并在view绑定了前端的属性进行同步变化；

那么如果我需要改变通知的是个表格呢？

我们可能需要采用更加复杂的数据结构和复杂的更新机制；

 