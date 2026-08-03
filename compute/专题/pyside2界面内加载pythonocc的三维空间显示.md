# pyside2界面内加载pythonocc的三维空间显示

这个部分在gitee上有较为纯python的实现： [纯python实现（不带有QT的.ui文件）](https://gitee.com/openminds/pythonocc-demos/blob/master/examples/core_display_qt5_app.py)

其中 [实现的关键部分qtDisplay包](https://blog.csdn.net/weixin_42755384/article/details/87925748) 也有人写过，这里我们直接使用了；

这里介绍最为精简的一种方式 结合 qt的.ui文件以及pyocc的代码；



我假设你应该使用conda将pythonocc和 pyside2/pyqt5 环境都配置好了；

随后进行如下的操作；

首先使用qt-designer建立一个window.ui文件作为界面，和主程pyhton文件放在同目录下；

```
<!-- window.ui    注意这里面的两个关键字  button  hLayout  后台代码要用到  -->
<?xml version="1.0" encoding="UTF-8"?>
<ui version="4.0">
 <class>MainWindow</class>
 <widget class="QMainWindow" name="MainWindow">
  <property name="geometry">
   <rect>
    <x>0</x>
    <y>0</y>
    <width>526</width>
    <height>801</height>
   </rect>
  </property>
  <property name="windowTitle">
   <string>标题栏</string>
  </property>
  <widget class="QWidget" name="centralwidget">
   <widget class="QPlainTextEdit" name="textEdit">
    <property name="geometry">
     <rect>
      <x>60</x>
      <y>20</y>
      <width>401</width>
      <height>161</height>
     </rect>
    </property>
   </widget>
   <widget class="QPushButton" name="button">
    <property name="geometry">
     <rect>
      <x>60</x>
      <y>190</y>
      <width>191</width>
      <height>71</height>
     </rect>
    </property>
    <property name="text">
     <string>显示BOX</string>
    </property>
   </widget>
   <widget class="QWidget" name="horizontalLayoutWidget">
    <property name="geometry">
     <rect>
      <x>60</x>
      <y>280</y>
      <width>401</width>
      <height>201</height>
     </rect>
    </property>
    <layout class="QHBoxLayout" name="hLayout"/>
   </widget>
  <widget class="QMenuBar" name="menubar">
   <property name="geometry">
    <rect>
     <x>0</x>
     <y>0</y>
     <width>526</width>
     <height>23</height>
    </rect>
   </property>
  </widget>
  <widget class="QStatusBar" name="statusbar"/>
 </widget>
 <resources/>
 <connections/>
</ui>
```

运行部分的代码采用类将ui部分逻辑包起来

首先看在pyside2环境下的情况

```
#pyocc_pyside2_ui.py
from OCC.Core.BRepPrimAPI import BRepPrimAPI_MakeBox

from OCC.Display.backend import load_backend
load_backend("qt-pyside2")			#这里必须 填写关键字  qt-pyside2 qt-pyqt5  wx   根据环境选一个
from OCC.Display import qtDisplay

from PySide2.QtWidgets import QApplication, QMessageBox, QDialog, QMainWindow
from PySide2.QtUiTools import QUiLoader
from PySide2.QtCore import QFile
 
#记得继承 QMainWindow 或者 QDialog
class Stats(QMainWindow):

    def __init__(self):
        super().__init__()
        
        # 从文件中加载UI定义   这是加载的一种备用方式
        
        # qfile_stats = QFile("../ui/window_demo.ui")
        # qfile_stats.open(QFile.ReadOnly)
        # # qfile_stats.close()
        # self.ui = QUiLoader().load(qfile_stats)

        # 这里是直接加载的方式
        # 从 UI 定义中动态 创建一个相应的窗口对象
        # 注意：里面的控件对象也成为窗口对象的属性了
        # 比如 self.ui.button , self.ui.textEdit
        self.ui = QUiLoader().load('./window_demo.ui')
        
        #给按钮绑定建立BOX的动作
        self.ui.button.clicked.connect(self.displayBOX)

        self.canvas = qtDisplay.qtViewer3d(self)  	#这里初始化occ针对qt的显示
        self.ui.hLayout.addWidget(self.canvas)		#关键代码 将occ针对qt的显示 加载到控件
        self.canvas.resize(200, 200)
        self.canvas.InitDriver()		# canva的驱动,设置驱动后，才能成功display
        self.display = self.canvas._display

    #创建box模型
    def displayBOX(self):
        a_box = BRepPrimAPI_MakeBox(10.0, 20.0, 30.0).Shape()
        self.ais_box = self.display.DisplayShape(a_box)[0]
        self.display.FitAll()


app = QApplication([])
stats = Stats()
stats.ui.show() 
app.exec_()
```

再来看在pyqt5环境下的情况

```
#pyocc_pyqt5_ui.py
from OCC.Core.BRepPrimAPI import BRepPrimAPI_MakeBox

from PyQt5.QtWidgets import QApplication, QMessageBox, QDialog, QMainWindow
# from PyQt5.QtUiTools import QUiLoader
from PyQt5 import uic		#这里和pyside2不同  官方的pyside命名是比较正规的
from PyQt5.QtCore import QFile

from OCC.Display.backend import load_backend
load_backend("qt-pyqt5")	#这里必须 填写关键字  qt-pyside2 qt-pyqt5  wx   根据环境选一个
from OCC.Display import qtDisplay

# from pyocc_ui_demo import ShowShape

class Stats(QDialog):

    def __init__(self):
        super().__init__()
        
        # 从文件中加载UI定义 这是加载的一种备用方式
        # qfile_stats = QFile("./window_demo.ui")
        # qfile_stats.open(QFile.ReadOnly)
        # qfile_stats.close()
        # self.ui = QUiLoader().load(qfile_stats)

        # 这里是直接加载的方式
        # 从 UI 定义中动态 创建一个相应的窗口对象
        # 注意：里面的控件对象也成为窗口对象的属性了
        # 比如 self.ui.button , self.ui.textEdit
        self.ui = uic.loadUi('./window_demo.ui')
		
        #给按钮绑定建立BOX的动作
        self.ui.button.clicked.connect(self.displayBOX)

        self.canvas = qtDisplay.qtViewer3d(self)	#这里初始化occ针对qt的显示  qtviewer3d
        self.ui.hLayout.addWidget(self.canvas)		#关键代码 将occ针对qt的显示 加载到控件
        self.canvas.resize(200, 200)
        self.canvas.InitDriver()
        self.display = self.canvas._display

    #OCC创建box模型
    def displayBOX(self):
        a_box = BRepPrimAPI_MakeBox(10.0, 20.0, 30.0).Shape()
        self.ais_box = self.display.DisplayShape(a_box)[0]
        self.display.FitAll()
     
app = QApplication([])
stats = Stats()
stats.ui.show()
# ShowShape()
app.exec_()
```

上述的python文件运行即可；出现结果：

![img](https://i-blog.csdnimg.cn/blog_migrate/c0563ef844a2be5cab58f68fd15ec879.png)![点击并拖拽以移动](data:image/gif;base64,R0lGODlhAQABAPABAP///wAAACH5BAEKAAAALAAAAAABAAEAAAICRAEAOw==)编辑















