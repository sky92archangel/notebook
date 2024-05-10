# QML+VTK构建实现

[TOC]

 

### 1 创建QT QUICK项目

采用QT5.15+VTK9.2.0

这次我们不在主程中加载VTK的几何；

在qml建立的控件，创建MyVtkObject类的单例，main中将指针和单例挂钩；

在MyVtkObject实例中操作 QQuickVTKRenderItem 类即可；

由于VTK的opengl显示是状态机，所以无需进行MVVM的通知动作（类MVVM模式）；

这里再次采用按钮触发修改动作； 

### 2 构建类 MyVtkObject

myvtkobject.h

```c++
#ifndef MYVTKOBJECT_H
#define MYVTKOBJECT_H
 
#include <QObject>
 
#include <QQuickVTKRenderWindow.h>
#include <QQuickVTKRenderItem.h>
#include <vtkPolyDataMapper.h>
#include <vtkCylinderSource.h>
#include <vtkCubeSource.h>
 
class MyVtkObject : public QObject
{
    Q_OBJECT
public:
    explicit MyVtkObject(QObject *parent = nullptr);
 
    Q_INVOKABLE void initVtkView();
    Q_INVOKABLE QString addMsg(QString str);
    Q_INVOKABLE QString changeVtkItem( );
 
    void setRenderItem( QQuickVTKRenderItem* _item){
        this->m_vRenItem=_item ;
    };
    void setRenderWin(QQuickVTKRenderWindow* _win){
        this->m_vRenWin=_win ;
    }
 
    //单例
    static MyVtkObject* getInstance( ){
        static MyVtkObject* myobj = new MyVtkObject() ;
        return myobj;
    };
 
    const QString &sString() const;
    void setSString(const QString &newSString);
 
private:
    QString m_sString="init";
 
    QQuickVTKRenderItem* m_vRenItem;
    QQuickVTKRenderWindow* m_vRenWin;
 
    Q_PROPERTY(QString sString READ sString WRITE setSString NOTIFY sStringChanged)
 
signals:
 
    void sStringChanged();
};
 
#endif // MYVTKOBJECT_H
```

myvtkobject.cpp

```c++
#include "myvtkobject.h"
 
MyVtkObject::MyVtkObject(QObject *parent)
    : QObject{parent}
{
 
}
 
void MyVtkObject::initVtkView()
{
    vtkNew<vtkCylinderSource> cylinder;
    cylinder->SetResolution(8);
 
    // The mapper is responsible for pushing the geometry into the graphics
    // library. It may also do color mapping, if scalars or other attributes are
    // defined.
    vtkNew<vtkPolyDataMapper> cylinderMapper;
    cylinderMapper->SetInputConnection(cylinder->GetOutputPort());
 
    // The actor is a grouping mechanism: besides the geometry (mapper), it
    // also has a property, transformation matrix, and/or texture map.
    // Here we set its color and rotate it around the X and Y axes.
    vtkSmartPointer<vtkActor> cylinderActor=vtkSmartPointer<vtkActor>::New();
    cylinderActor->SetMapper(cylinderMapper);
    //    cylinderActor->GetProperty()->SetColor( colors->GetColor4d("Tomato").GetData());
    cylinderActor->RotateX(30.0);
    cylinderActor->RotateY(-45.0);
 
      auto main_render_3d = m_vRenItem->renderer();
 
    main_render_3d->AddActor(cylinderActor);
    main_render_3d->ResetCamera();
 
//    QQuickVTKRenderWindow* ren_win_3d = engine.rootObjects().first()
//            ->findChild< QQuickVTKRenderWindow* >( "vtkRenWin" );
    m_vRenWin->render();
 
}
 
QString MyVtkObject::addMsg(QString str)
{
    setSString(sString()+ str + '#' ) ;
    // m_sString = str+"@";
    qDebug()<< __FUNCTION__ <<" === "<<str;
    return sString();
}
 
QString MyVtkObject::changeVtkItem()
{
    vtkNew<vtkCylinderSource> cylinder;
    cylinder->SetResolution(8);
 
    vtkNew<vtkPolyDataMapper> cylinderMapper;
    cylinderMapper->SetInputConnection(cylinder->GetOutputPort());
 
    vtkSmartPointer<vtkActor> cylinderActor=vtkSmartPointer<vtkActor>::New();
    cylinderActor->SetMapper(cylinderMapper);
    cylinderActor->RotateX(-30.0);
    cylinderActor->RotateY(-95.0);
 
    //    auto qquickvtkItem =m_vRenItem;  // vtkSmartPointer<QQuickVTKRenderItem> ::New()   ;
    auto main_render_3d = m_vRenItem->renderer();
 
    //    main_render_3d->Clear();
    main_render_3d->AddActor(cylinderActor);
    main_render_3d->ResetCamera();
 
 
    vtkActorCollection* actors =main_render_3d->GetActors();
    qDebug()<< __FUNCTION__ <<" actors count: "<< actors->GetReferenceCount();
 
    return "OK";
}
 
 
const QString &MyVtkObject::sString() const
{
    return m_sString;
}
 
void MyVtkObject::setSString(const QString &newSString)
{
    if (m_sString == newSString)
        return;
    m_sString = newSString;
    emit sStringChanged();
}
 
```

### 3 主程中连接qml中vtk控件的指针

main.cpp

```c++
#include <QGuiApplication>
#include <QQmlApplicationEngine>
 
#include "myvtkobject.h"
 
int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
 
    //定义app之前调用一次，别问我为啥，问就是官方文档上写的，我也不知道
    QQuickVTKRenderWindow::setupGraphicsBackend();
 
    QGuiApplication app(argc, argv);
 
    QQmlApplicationEngine engine;
 
    //=====注册给qml=======
    qmlRegisterSingletonInstance("VTKOBJ",9,2,"VtkObj",MyVtkObject::getInstance());
    qmlRegisterType<QQuickVTKRenderWindow>("VTK", 9, 2, "VTKRenderWindow");
    qmlRegisterType<QQuickVTKRenderItem>("VTK", 9, 2, "VTKRenderItem");
    //====================
 
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);
 
 
    //------------------------------------
    auto vtkItem = engine.rootObjects().first()->findChild< QQuickVTKRenderItem* >( "vtkRenItem" );
    auto vtkWin = engine.rootObjects().first()->findChild< QQuickVTKRenderWindow* >( "vtkRenWin" );
 
    MyVtkObject::getInstance()->setRenderItem(vtkItem);
    MyVtkObject::getInstance()->setRenderWin(vtkWin);
 
    MyVtkObject::getInstance()->initVtkView();
    //------------------------------------
 
    return app.exec();
}
```

main.qml

```javascript
import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.5
 
import VTKOBJ 9.2
import VTK 9.2
 
Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")
 
    onWidthChanged: { console.log(width) }
 
    //---------------------------------------
    //ref动态绑定 由于iValue定义了通知动作；
    //一个改变 会通知另一个改变
    property string sstring: VtkObj.sString
 
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
            VtkObj.addMsg("ee")
            VtkObj.changeVtkItem( )
            console.log ( VtkObj.sString)
            console.log (txt.text)
            console.log (sstring)
        }
    }
    //---------------------------------------
 
    VTKRenderWindow{
        id: vtkRenWindow
        z: 10
 
        //注意这个objectName， 等会要用到!!!!! x1
        objectName: "vtkRenWin"
 
        width: parent.width * 0.9
        height: width
        anchors.centerIn: parent
    }
 
    VTKRenderItem{
        id: vtkRenItem
        z: 10
 
        //注意这个objectName， 等会要用到!!!!! x2
        objectName: "vtkRenItem"
 
        anchors.fill: vtkRenWindow
        renderWindow: vtkRenWindow
        focus: true
    }
 
}
```



pro

```shell
QT += quick

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        myvtkobject.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


##VTK
INCLUDEPATH+=$$quote(D:/WORKSPACE/CODE_CPP/VTK/VTK920/runtime/include/vtk-9.2)

CONFIG(debug,debug|release){
    LIBS+=$$quote(D:/WORKSPACE/CODE_CPP/VTK/VTK920/runtime/lib/*.lib)
}else{
    LIBS+=$$quote(D:/WORKSPACE/CODE_CPP/VTK/VTK920/runtime/lib/*.lib)
}

HEADERS += \
    myvtkobject.h

```





