## linux下安装报错提示：

**Qt安装完成后，先别打开，因为还需要安装其他工具以及库文件：**

```
   1|sudo apt-get install gcc g++         //安装 linux 下编程的编译器
   2|sudo apt-get install libqt4-dev      //不然编译时会出现错误“cannot find -lgl”
   3|sudo apt-get install build-essential //这是一个编译工具，它可以使得我们的程序知道头文件和库函数放在哪个位置；
   4|sudo apt-get install gdb //调试工具;
```

 **构建项目就会出现:`-1: error: cannot find -lGL`**

***解决方法：***`sudo apt-get install libgl1-mesa-dev`



##### 1.设置Qss时，QWidget[IMLoginWidget=true]，key不加双引号，默认字符串形式。

##### 2.关于控件提升，控件提升中头文件包含注意，如果头文件在子目录下，需要引入当前路径下==文件夹/文件/头文件==路径；如：IMControls/IMPassWordLineEdit/IMPassWordLineEdit.h；moc生成的文件引入的是提升中头文件的路径名称。

##### 3.添加exe图标： 在pro中添加：RC_ICONS = myappico.ico（百度创建文件.rc在引入不是Qt5.0以上版本方法，注意查看文档）

##### 4.QT 关闭窗口是否销毁窗口及子部件

顶层窗口调用close：应用程序销毁该窗口部件及子部件。

非顶层窗口close：关闭时只是隐藏，不会被销毁。

##### 5.关于Qt窗口最大化后无法设置大小：

当窗体设置showMaximized()后，在setFixedSize(QSize&)窗体后，再次设置showMaximized()导致失效问题，解决办法：

先showNormal()，恢复初始界面大小后即可设置（最好解决办法，局部变量获取放大后窗口位置以及大小，由于showNormal（）后窗口可能位置不对，需要move()移动窗体）。

##### 6.错误:QMetaObject::connectSlotsByName: No matching signal for

1. 如果在一个QObject子类里定义了"on_"开头的槽的话，一定会被connectSlotsByName函数进行搜索匹配的操作的 。
2. 同名connectSlotsByName只能给其中一个建立缺省的信号和的连接。
3. 出现大量编码创建大量控件的情况，最好是自己去建立信号和槽的连接，而不是依赖connectSlotsByName来做到这个工作。
4. connectSlotsByName更适合的任务是与desinger配合完成缺省的信号和槽的连接。

##### 7.关于QLayout布局信息

如果QWidget::setLayout（），则布局new时候不需要指定parent，否则会提示重复布局问题。