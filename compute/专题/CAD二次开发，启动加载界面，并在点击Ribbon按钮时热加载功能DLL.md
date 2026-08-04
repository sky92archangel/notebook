# CAD二次开发，启动加载界面，并在点击Ribbon按钮时热加载功能DLL，并提供打包的工程框架

整个思路为启动时运行lsp，lsp操作仅加载一个界面DLL，其中按钮绑定CAD内部任务，或者使用反射绑定到指定的DLL文件；

假设这里已经完成了一个功能，并编译为 CAD.Demo.dll

先写个lsp文件，很简单 就是加载Ribbon主程DLL

AutoLoad.lsp

```lisp
;;; AutoLoad.lsp 
;;; 用于启动自动加载 
#| 
该文件AutoLoad.lsp可以复制在任意位置，功能安装完毕后，首次打开CAD进行需要设置
设置方法如下：

	输入命令appload 
	弹窗
	启动组=>内容 选择当前AutoLoad.lsp文件所在的路径,此时就已经永久加载了 ；
	如要卸载 把这个文件路径删除就可以  ；
|#
 


(setq CadToolsPath "D:\\WORKSPACE\\CODE_CAD\\CAD.Demo\\bin\\Debug\\")		;; 设定工具集DLL目录	
(command "NETLOAD" (strcat CadToolsPath "CAD.Ribbon.Template.dll"))	;; 加载界面DLL文件，即为功能界面的入口
 


; (command "NETLOAD" (strcat CadToolsPath "其他功能界面的DLL.dll"))	 

```



此时，建立工程 CAD.Template.Ribbon



主程文件  AcadNetApp.cs

```c#
using Autodesk.AutoCAD.ApplicationServices;
using Autodesk.AutoCAD.Runtime;
using Autodesk.Windows;
using System;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;


[assembly: ExtensionApplication(typeof(CAD.Template.Ribbon.AcadNetApp))]
namespace  CAD.Template.Ribbon
{
    public class AcadNetApp : IExtensionApplication
    {
        public static string assemblyPath = Assembly.GetExecutingAssembly().Location;
        public static string assemblyDir = Path.GetDirectoryName(assemblyPath) + "\\";

        /// <summary>
        /// 启动动作
        /// </summary>
        public void Initialize()
        {
            Application.Idle += OnIdle;
            //需要添加事件，监听工作空间有没有变化，如果有变化，需要重新生成面板
            Application.SystemVariableChanged += new SystemVariableChangedEventHandler(Application_SystemVariableChanged);

        }

        /// <summary>
        /// 关闭动作
        /// </summary>
        public void Terminate()
        {
            // do somehing to cleanup resource 
            Application.Idle -= OnIdle;
            //卸载
            Application.SystemVariableChanged -= new SystemVariableChangedEventHandler(Application_SystemVariableChanged);

        }

        /// <summary>
        /// 启动时行为
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void OnIdle(object sender, EventArgs e)
        {
            //无论如何 刷新一下工作空间
            var wsCurrent = Application.GetSystemVariable("WSCURRENT");
            Application.SetSystemVariable("WSCURRENT", wsCurrent);

            Application.Idle -= OnIdle;
        }

        /// <summary>
        /// 监听动作
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        void Application_SystemVariableChanged(object sender, SystemVariableChangedEventArgs e)
        {
            //Editor ed = Application.DocumentManager.MdiActiveDocument.Editor;
            //ed.WriteMessage("\n-Sys Var Changed: " + e.Name);

            if (e.Name.ToLower() == "wscurrent")
            {
                Application.DocumentManager.MdiActiveDocument.Editor.WriteMessage("\n加载程序中...\n");
                AddRibbon();
                Application.DocumentManager.MdiActiveDocument.Editor.WriteMessage("\n加载程序完成\n");
            }
        }

        //==========================================================================================================

        /// <summary>
        /// 需要添加的界面内容
        /// </summary>
        public void AddRibbon()
        {
            RibbonControl ribbonControl = ComponentManager.Ribbon;
            //该步骤自动时可能加载卡住
            RibbonTab ribbonTab = ribbonControl.AddTab("ribbonTab", Guid.NewGuid().ToString(), true);
            RibbonPanelSource panelSource = ribbonTab.AddPanel("ribbonAutoPanel");

            //----- 
            //按下按钮时加载指定dll内功能
            var dllPath = Path.Combine(assemblyDir, "CAD.Demo.dll");
            RibbonButton ribbonButton =
                RibbonService.GenRibbonButton("TestLoadDll", "TestLoadDllText", " ",
                  new LoadDllCommandHandler(dllPath, "CAD.Demo.HelloCommand", "ShowWpfView"),
                               RibbonService.GenImageSource(Resource.ICON_ALL));
            panelSource.Items.Add(ribbonButton);
            //----- 
            //调用CAD内部命令 Line
            RibbonButton lineButton =
            RibbonService.GenRibbonButton("Test_Line", "TestLineText", "Line",
                new RibbonCommandHandler(),
                             RibbonService.GenImageSource(Resource.ICON_ALL));
            panelSource.Items.Add(lineButton);
            //----- 
        }



    }
}

```

按钮加载的服务文档 RibbonService.cs

其中的图案需要建立资源文件，把图片拷贝进去；



```c#
using Autodesk.Windows;
using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
//using Autodesk.Internal.Windows;
//using System.Windows.Forms;

using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Interop;
using System.Windows.Media;
using System.Windows.Media.Imaging;

namespace  CAD.Template.Ribbon
{
    public static partial class RibbonService
    {

        //==========================================================

        public static RibbonTab AddTab(this RibbonControl ribbonControl, string title, string id, bool isActive)
        {
            //TODO
            RibbonTab tab = new RibbonTab();
            tab.Title = title;
            tab.Id = id;
            tab.IsActive = isActive;
            ribbonControl.Tabs.Add(tab);

            return tab;
        }

        public static RibbonPanelSource AddPanel(this RibbonTab ribbonTab, string title)
        {
            RibbonPanelSource panelSource = new RibbonPanelSource();
            panelSource.Title = title;

            RibbonPanel ribbonPanel = new RibbonPanel();
            ribbonPanel.Source = panelSource;

            ribbonTab.Panels.Add(ribbonPanel);

            return panelSource;
        }

        //==========================================================

        /// <summary>
        /// 图像生成
        /// </summary>
        /// <param name="bitmap">   Resource.ICON_ALL</param>
        /// <returns></returns>
        public static ImageSource GenImageSource(Bitmap image)
        {
            //Bitmap image = Resource.ICON_ALL;
            ImageSource imageSource = Imaging.CreateBitmapSourceFromHBitmap(
                image.GetHbitmap(),
                IntPtr.Zero,
                Int32Rect.Empty,
                BitmapSizeOptions.FromEmptyOptions());
            return imageSource;
        }

        /// <summary>
        /// 按钮提示生成
        /// </summary>
        /// <param name="title"></param>
        /// <param name="content"></param>
        /// <param name="command"></param>
        /// <param name="expandedContent"></param>
        /// <param name="imageSource"></param>
        /// <param name="video"></param>
        /// <returns></returns>
        public static RibbonToolTip GenRibbonToolTip(string title, string content, string command,
            string expandedContent,
            ImageSource imageSource = null, Uri video = null)
        {
            RibbonToolTip ribbonToolTip = new RibbonToolTip
            {
                Title = title,
                Content = content,
                Command = command,
                ExpandedContent = expandedContent,
                ExpandedImage = imageSource,
                ExpandedVideo = video
            };
            return ribbonToolTip;
        }


        /// <summary>
        /// 按钮生成
        /// </summary>
        /// <param name="name"></param>
        /// <param name="text"></param>
        /// <param name="commandParam">可以为文字 或 空</param>
        /// <param name="commandHandler"></param>
        /// <param name="imageSource"></param>
        /// <param name="showText"></param>
        /// <param name="showImage"></param>
        /// <param name="toolTip"></param>
        /// <param name="ribbonItemSize"></param>
        /// <param name="orientation"></param>
        /// <param name="mouseEnterEvents">鼠标进入事件</param>
        /// <param name="mouseLeftEvents">鼠标移出事件</param>
        /// <returns></returns>
        public static RibbonButton GenRibbonButton(string name, string text,
            object commandParam,
            ICommand commandHandler,
            ImageSource imageSource = null,
            bool showText = true,
            bool showImage = true,
            ToolTip toolTip = null,
            RibbonItemSize ribbonItemSize = RibbonItemSize.Large,
            Orientation orientation = Orientation.Vertical,
            IEnumerable<EventHandler<EventArgs>> mouseEnterEvents = null,
            IEnumerable<EventHandler<EventArgs>> mouseLeftEvents = null
            )
        {

            RibbonButton ribbonButton = new RibbonButton();
            ribbonButton.Id = Guid.NewGuid().ToString();

            ribbonButton.Name = name;
            //设置文本
            ribbonButton.Text = text;
            //设置命令名称
            if (commandParam != null) ribbonButton.CommandParameter = commandParam;
            //
            if (commandHandler != null) ribbonButton.CommandHandler = commandHandler;

            //显示文本
            ribbonButton.ShowText = showText;
            //显示图案
            ribbonButton.ShowImage = showImage;
            //小图
            ribbonButton.Image = imageSource;
            //大图
            ribbonButton.LargeImage = imageSource;
            //按钮大小
            ribbonButton.Size = RibbonItemSize.Large;
            //要添加这个，这样才能让图片和文字上下，不然就是左右
            ribbonButton.Orientation = Orientation.Vertical;

            //设置提示
            if (toolTip != null) ribbonButton.ToolTip = toolTip;

            //鼠标进入和出去事件
            if (mouseEnterEvents != null && mouseEnterEvents.Count() > 0)
            {
                foreach (var mouseEnterEvent in mouseEnterEvents)
                {
                    ribbonButton.MouseEntered += mouseEnterEvent;
                }
            }
            if (mouseLeftEvents != null && mouseLeftEvents.Count() > 0)
            {
                foreach (var mouseLeftEvent in mouseLeftEvents)
                {
                    ribbonButton.MouseLeft += mouseLeftEvent;
                }
            }

            return ribbonButton;
        }


    }
}

```



按钮中绑定命令事件的文档 AcadCommandHandler.cs 



```c#
using Autodesk.AutoCAD.ApplicationServices;
using Autodesk.Windows;

using System;
using System.CodeDom;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace CAD.Template.Ribbon
{
    /// <summary>
    /// 传统加载方法  通过按钮参数名称调动命令  
    /// 前提是 预先载入带有该命令的 DLL  但是这样会启动时锁定所有写入的功能DLL
    /// 参数必须是 DLL内功能的名称 CommandMethod
    /// </summary>
    public class AcadCommandHandler : System.Windows.Input.ICommand
    {
        public bool CanExecute(object parameter)
        {
            return true;
        }
#pragma warning disable 67
        public event EventHandler CanExecuteChanged;
#pragma warning restore 67
        public void Execute(object parameter)
        {
            //通过参数传达
            if (parameter is RibbonButton)
            {
                RibbonButton btn = (RibbonButton)parameter;
                if (btn.CommandParameter != null)
                {
                    Document doc = Application.DocumentManager.MdiActiveDocument;
                    doc.SendStringToExecute(btn.CommandParameter.ToString() + " ",
                        false, false, false);
                }
                return;
            }
        }
    }


    /// <summary>
    /// 本地DLL加载  即为热加载
    /// 可在按下按钮时加载DLL 并执行DLL内的命令
    /// 更加灵活
    /// 缺点是一个按钮只能绑定DLL的一个方法
    /// </summary>
    public class LoadDllCommandHandler : System.Windows.Input.ICommand
    {
        Action action;

        /// <summary>
        /// 本地DLL加载  即为热加载
        /// </summary>
        /// <param name="dllPath">dll所在目录</param>
        /// <param name="pathToClass">命名空间.类名称</param>
        /// <param name="methodName">方法名称</param>
        /// <param name="constuctParams">后续加入的参数</param>
        public LoadDllCommandHandler(string dllPath, string pathToClass, string methodName, object[] constuctParams = null)
        {
            action = CommandHotLoad.GenCommandAction(dllPath, pathToClass, methodName, constuctParams);
        }

        public bool CanExecute(object parameter)
        {
            return true;
        }
#pragma warning disable 67
        public event EventHandler CanExecuteChanged;
#pragma warning restore 67
        public void Execute(object parameter)
        {
            if (action != null)
            {
                action?.Invoke();
            }
        }
        
              /// <summary>
          /// 反射获得所需执行
          /// </summary>
          /// <param name="dllPath"> dll文件路径  C:\\CAD\\bin\\Debug\\ CadDemo.Space.dll</param>
          /// <param name="pathToClass">命名空间和类的全称  CadDemo.Space.Class</param>
          /// <param name="methodName"> 执行方法名  methodName</param>
          /// <returns></returns>
          public static Action GenCommandAction(string dllPath, string pathToClass, string methodName, object[] constuctParams = null)
          {
              var targetAssembly = Assembly.Load(File.ReadAllBytes(dllPath));
              var targetType = targetAssembly.GetType(pathToClass);
              var targetMethod = targetType.GetMethod(methodName);
              var targetObject = Activator.CreateInstance(targetType);

              if (constuctParams == null) { constuctParams = new object[] { }; }
              Action cmd = () => targetMethod.Invoke(targetObject, constuctParams);

              return cmd;

          }


    }
 


}

```

























