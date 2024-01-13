WPF 绑定

[TOC]



## 关于全局绑定

前台做法

```xaml
<Window.DataContext>
 	<local:MainViewModel/>
</Window.DataContext>
```

后台做法

```C#
this.DataContext = new MainViewModel();
```

-----

直接绑定，这样绑定会直接寻找最近datacontext的名称

```xaml
<TextBlock Text="{Binding}"/>
```

若后台具有属性 

```c#
public string message { get; set; } = "hello";
```

则可以如下输出属性

```xaml
<TextBlock Text="{Binding Path=message}"/>
<TextBlock Text="{Binding message}"/> 
```

-----

若后台重写了输出ToString

```
public override string ToString() => message;
```

如下也可显示属性message

```xaml
<TextBlock Text="{Binding }"/>
<TextBlock Text="{Binding .}"/>
<TextBlock Text="{Binding Path=.}"/>
<TextBlock>
	<TextBlock.Text>
        <Binding Path="message" />
	</TextBlock.Text>    
</TextBlock>
```

-----

后台控制绑定

```xaml
<TextBlock x:Name="tbl"/>
```

```C#
var binding = new Binding()
            {
                Path = new PropertyPath("MESSAGE"),
                Mode= BindingMode.TwoWay
            };
            BindingOperations.SetBinding(tbl, TextBlock.TextProperty, binding);
```

----

## source绑定

```XAML
<Window.Resources>
 	<system:String x:Key="str">Hello</system:String>
</Window.Resources>
<Grid>
    <TextBlock Text="{Binding Source={StaticResource str}}"/>
 	<TextBlock Text="{DynamicResource str}"/>
</Grid>
```

### 绑定类属性

```C#
class MyResource
{
    public string Message { get; } = "public proterty";
    public static string StaticStr  = "static string";
    public const string ConstString = "const string";
} 
```

```xaml
<Window.Resources>
    <system:String x:Key="str">Hello!!</system:String>
    <local:MyResource x:Key="myRes"/>
</Window.Resources>

<Grid>
 	<TextBlock Text="{Binding Source={StaticResource myRes},Path=Message}"/>
 	<TextBlock Text="{Binding Source={x:Static local:MyResource.StaticStr} }"/>
 	<TextBlock Text="{Binding Source={x:Static local:MyResource.ConstStr} }"/>
 	<TextBlock Text="{Binding Source={x:Static HorizontalAlignment.Stretch} }"/>
</Grid>
```

## ElementName

### 同步两者数据

```xaml
<TextBox Name="textbox"/>
<TextBlock Text="{Binding ElementName=textbox,Path=Text}"/> 
```

### 绑定树问题

失效

```xaml
<TextBlock Text="Tips">
    <TextBlock.ToolTip>
        <TextBlock Text="{Binding ElementName=textbox,Path=Text}"/>
    </TextBlock.ToolTip>
</TextBlock>

```

有效

```xaml
<TextBlock Text="Tips">
    <TextBlock.ToolTip>
        <TextBlock Text="{Binding  Source={x:Reference Name=textbox}, Path=Text}"/>
    </TextBlock.ToolTip>
</TextBlock> 
```

### 相对源

向上向外寻找首个Window控件，并绑定其Top属性

```xaml
<TextBlock  Text="{Binding RelativeSource={RelativeSource Mode=FindAncestor, AncestorType=Window}, Path=Top}"/>
<TextBlock  Text="{Binding RelativeSource={RelativeSource AncestorType=Window}, Path=Top}"/> 
```

 寻找绑定父级属性

```xaml
<Grid Tag ="Level1"> 
	<TextBlock  Text="{Binding RelativeSource={RelativeSource Mode=FindAncestor, AncestorType=Grid}, Path= Tag}"/>
</Grid>
```

多层情况下 AncestorLevel 表达能够找到的Grid控件集合列表中的第几个Grid

```xaml
<!--显示Level1-->
<Grid Tag ="Level2"> 
    <Grid Tag ="Level1">
        <TextBlock  Text="{Binding RelativeSource={RelativeSource Mode=FindAncestor,AncestorType=Grid,AncestorLevel=1},Path= Tag}"/>
    </Grid>
</Grid> 


<!--显示Level2-->
<Grid Tag ="Level2"> 
    <Grid Tag ="Level1">
        <TextBlock  Text="{Binding RelativeSource={RelativeSource Mode=FindAncestor,AncestorType=Grid,AncestorLevel=2},Path= Tag}"/>
    </Grid>
</Grid> 
 

<!--显示Level2-->
<Grid Tag ="Level2">
    <Border> 
        <Grid Tag ="Level1">
            <TextBlock  Text="{Binding RelativeSource={RelativeSource Mode=FindAncestor,AncestorType=Grid,AncestorLevel=1},Path= Tag}"/>
        </Grid>
    </Border>
</Grid> 
```

绑定父级下的子集某项目，即同级某项

```xaml
<StackPanel Name="panel" Margin="2">
    <TextBox/>
    <TextBlock Text="{Binding RelativeSource={RelativeSource AncestorType=StackPanel}, Path=Children[0].Text}"/>
</StackPanel> 
```

### 绑定自己

```xaml
<TextBlock Text="{Binding RelativeSource={ x:Static RelativeSource.Self },Path=ActualWidth}"/>
<TextBlock Text="{Binding RelativeSource={ x:Static RelativeSource 2 },Path=ActualWidth}"/> 
```

控件属性绑定 将内部的padding和模板所有者控件的padding绑定

```xaml
<Label Content="Hello" Padding ="10">
    <Label.Template>
        <ControlTemplate TargetType="Label">
            <Border Padding="{Binding RelativeSource={RelativeSource Mode=TemplatedParent},Path=Padding}">
                <ContentPresenter/>
            </Border>
        </ControlTemplate>
    </Label.Template>
</Label> 
```



## 其他技巧

format

```xaml
<TextBlock Text="{Binding  ElementName=window,Path=Top,StringFormat='Top:{0:F3}'}"/>
```

多重绑定中的format

```xaml
<TextBlock>
    <TextBlock.Text>
        <MultiBinding StringFormat="Pos:{0},{1}">
            <Binding ElementName="window" Path="Top"/>
            <Binding ElementName="window" Path="Left"/>
        </MultiBinding>
    </TextBlock.Text>
</TextBlock> 
```



```xaml
<Label Content="{Binding ElementName=window,Path=Left,StringFormat='Left:{0:F3}'}" ContentStringFormat="Left:{0:F3}"/>  
```

触发

```xaml
<!--失焦时更改-->
<TextBox Text="{Binding ElementName=tbl,Path=Text,UpdateSourceTrigger=LostFocus}"/>
<!--实时触发更改-->
<TextBox Text="{Binding ElementName=tbl,Path=Text,UpdateSourceTrigger=PropertyChanged}"/> 
```

 xpath 用于绑定xml对象













