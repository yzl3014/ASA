# ASA
Animations of Sorting Algorithms - 排序算法动画

![](https://img.shields.io/badge/version-1.0b-blue)
![](https://img.shields.io/badge/language-C%2B%2B-brightgreen)
![](https://img.shields.io/badge/Powered_By-EasyX-orange)

一款基于C++的算法动画演示程序，采用了 [Easyx](https://easyx.cn/) 免费VC++绘图库。参考灵感来源于 [一个有关排序算法声音的视频](https://b23.tv/BhAsS9X) 。

# 使用方法

## 运行
安装本项目内附带的Easyx安装包，自解压程序双击运行即可，注意安装到VS的版本要与运行程序的VS版本一致。它支持VC6到VC2022之间的所有正式版。

下载或fork仓库到本地，打开`main.cpp`文件，直接运行即可。

>本程序在`Microsoft Visual Studio Community 2019 (版本16.11.26)`环境下开发，运行正常。

## 运行和内置参数调整

运行程序，根据菜单指示按下键盘按键，程序将为你呈现完整算法过程。

> ![菜单](https://s2.loli.net/2023/05/10/h6cBVsydi4ZQHwp.png)
> 打开程序，菜单将在数据生成完后显示。

通过修改`configs.h`中的前几个`#define`值，程序可以显示不同的效果。注意按照注释修改，否则程序可能无法正常运行。

# 显示

**一个长方形方块（也可以当做柱子）就代表一个数值。**

## 颜色对应
本程序会对每个方块填充颜色，不同颜色意味着不同状态。

| **颜色** | **状态** | **备注**                   |
|:------:|:------:|:------------------------:|
| 白色     | 默认     | 目前未被读取，也不属于以下任一情况。       |
| 红色     | 读取     | 该数值正在被读取或移动。             |
| 黄色     | 参考中    | 该数值正在作为参考值，例如在快速排序中的基准值。 |
| 绿色     | 排序完成   | 该数值已经在正确位置上，无需再移动。       |

## 它是如何工作的？

代码的技术含量很低，而且有些地方写的不清晰，所以不建议参考。

开始运行，程序自动生成随机数据，再显示右上角的菜单，等待用户输入。用户指定算法后，程序开始进行排序。排序和显示是分开进行的，每次程序对数组中的数值进行操作（如读取、移动）后，都会调用`show()`以显示。排序的同时也会记录一些数据，可用于参考。

每个数值同时存储在整型数值数组和结构体数组。每次显示都是由`show()`遍历数组的同时读取`Nums`和`Blocks`，然后根据数值大小绘制到窗口中。

> ![ASAv1.0b-2.gif](https://s2.loli.net/2023/05/10/N1IzUMcD2OVv6Ri.gif)
> 程序运行过程：快速排序演示（30FPS）
