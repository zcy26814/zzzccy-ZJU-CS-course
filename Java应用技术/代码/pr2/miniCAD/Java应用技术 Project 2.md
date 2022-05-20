# Java应用技术 Project 2

## Mini CAD   周承扬_3190102371   **Date: 2021-11-13**

### 第一节: 简介

在这个工程里，我们需要用java来完成一个小型CAD画图工具。以CAD的方式操作，能放置直线、矩形、圆和文字，能选中图形，修改参数，如颜色等，能拖动图形和调整大小，可以保存和恢复。

### 第二节: 核心程序介绍

为达到与参考视屏中的CAD绘图效果，需要不同模块代码来实现对应，具体如下：

```java
class ImageIcon implements Icon
```

ImageIcon类代表了图标内容的设计，定义了其对应长度、宽度、种类以及颜色，为后续按钮设计服务；

```java
class ImageButton extends JPanel
```

ImageButton类代表了该CAD小程序里需要用到的对应按钮栏，通过调用Icon图标类型来实现不同功能按钮的样式，再通过调用imageDatabase来handle起所需要的功能；

```java
class ImageMenu extends JPanel
```

ImageMenu类主要将上述所涉及到的图标按钮组合起来，整理规划成一个CAD绘图工具的菜单栏，同时与Button部分相似，再通过调用imageDatabase来展开所需要的功能；

```java
class ImagePlot extends JPanel
```

ImagePlot类构成一个画板，负责对于直线、圆、长方形和文本框的绘制调用工作，通过鼠标唤醒后续对应的绘制程序；

```java
class Image<T>
```

创建控制图形的相关属性的类；

```java
enum ImageEventHandle
```

此部分用来对于直线、圆、长方形和文本框的具体绘制语句的描述，整体结构类似，此部分以直线部分为例做进一步说明：

```java
public String getType( ) //获取绘制图样类型
public void paintImage(Graphics g, ImageDatabase idb) //绘制图形
public void mousePressed(MouseEvent e, ImageDatabase idb)
public void mouseReleased(MouseEvent e, ImageDatabase idb)
public void mouseClicked(MouseEvent e, ImageDatabase idb)
public void mouseDragged(MouseEvent e, ImageDatabase idb) //定义鼠标操作，包括按住绘制与松开停止绘制，点击选中、点击移动等
public void keyReleased(KeyEvent e, ImageDatabase idb) //按键松开，用于删除操作
public void changeColor(ImageDatabase idb) //改变画笔颜色
public void fillShape(ImageDatabase idb) //填充颜色
public void deleteShape(ImageDatabase idb) //删除图形
public void selectShape(ImageDatabase idb) //选中图形
public void resumeShape(ImageDatabase idb) //恢复图形
```

以此为基础实现对于核心绘制功能的实现；

```java
class ImageDatabase
```

管理整个画板上所有图形以及按钮的数据和状态，类似于一个数据库。

### 第三节: 成果展示

图形绘制：先按Plot键，然后选取对应图标进行绘制，并在文本框中输入字符；![1](C:\Users\clearlove-champion7\Desktop\1.png)

图形移动：以移动圆为例，先在左侧选取圆的图标，接着在菜单栏选择Select，点击圆，接着拖动；![2](C:\Users\clearlove-champion7\Desktop\2.png)

填充功能：选中圆，点击左侧红色，点击菜单栏的Fill；![3](C:\Users\clearlove-champion7\Desktop\3.png)

调整大小：选中长方形，滚动鼠标滚轮进行调整；![4](C:\Users\clearlove-champion7\Desktop\4.png)

颜色改变：点击圆进行绘制，选择不同颜色，画出不同颜色的圆

![7](C:\Users\clearlove-champion7\Desktop\7.png)

保存恢复： 选中长方形，点击Delete即可删除，再点击Resume便恢复；![6](C:\Users\clearlove-champion7\Desktop\6.png)

![5](C:\Users\clearlove-champion7\Desktop\5.png)

