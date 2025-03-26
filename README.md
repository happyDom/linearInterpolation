# linearInterpolation

## 介绍

本 [linearInterpolation](git@gitee.com:DyyYq/linearInterpolation.git) 模块是基于C语言提供的一维/二维线性插值算法。表格值是为float类型，适合在单片机中使用。

## 软件架构

序号 | 文档 | 说明
-|:-|:-
1|linearInterpolation.h|线性查表头文件
2|linearInterpolation.c|线性查表实现
3|main.c|演示程序

## 引入模块

```bash
git submodule add git@gitee.com:DyyYq/linearInterpolation.git submodules/linearInterpolation
```

## 引入头文件

以下代码引入了<font color=Green>linearInterpolation.h</font>头文件，定定义了演示用的表变量 <font color=Green>demoTable</font>。 表 <font color=Green>demoTable</font>可以当一维表用，也可以当二维表用。

```C
#include "linearInterpolation.h"

linearInterpolation_t demoTable;
```

## 填充表格内容（一维表）

以下代码对表<font color=Green>demoTable</font>进行了一维内容填充👇

```C
/*
* Y
* ↑
* | 
* 20-------------*
* ｜
* 15--------*
* ｜
* 10---* 
* ｜
* *----2----4----8-------------> X
*/
//static的约束保障了这些变量的空间不会被收回
static float xValues[] = {2, 4, 8};
static float yValues[] = {10.0f, 15.0f, 20.0f};
tableInitXY_withValues(&demoTable, 3, xValues,yValues);
```

## 填充表格内容（二维表）

以下代码对表<font color=Green>demoTable</font>进行了二维内容填充👇

```C
/*
* *----1----2-----------------> X
* |
* 1    2    3
* |
* 2    3    4
* |
* 3    4    8
* |
* ↓
* Y
*/
//static的约束保障了这些变量的空间不会被收回
static float xValues[] = {1,2};
static float yValues[] = {1,2,3};

static float zValues[][2] = {   {2,3},
                                {3,4},
                                {4,8}};
tableInitXYZ_withValues(&demoTable, 2, 3, xValues, yValues, zValues);
```

## 一维查表

如果你对表格进行了一维填充，则可以对这个表格进行一维查表。如下是对表<font color=Green>demoTable</font>进行一维查表👇

```C
float userX=0;
while (1)
{
    printf("please input X value:"); scanf("%f", &userX);
    printf("the x is: %f, then the y should be: %f\n", userX, demoTable.getY(&demoTable, userX));
}
```

方法 <font color=Green>getY</font> 可以根据指定的<font color=Green>x</font>值查表获取对应的 <font color=Green>y</font> 值。

## 二维查表

如果你对表格进行了二维填充，则可以对这个表格进行二维查表。如下是对表<font color=Green>demoTable</font>进行二维查表👇

```C
float userX=0, userY=0;
while (1)
{
    printf("please input X value:"); scanf("%f", &userX);
    printf("please input Y value:"); scanf("%f", &userY);
    printf("the coord is: (%f, %f), then the z should be: %f\n", userX, userY, demoTable.getZ(&demoTable, userX, userY));
}
```

方法 <font color=Green>getZ</font> 可以根据指定的 <font color=Green>x</font>、<font color=Green>y</font> 值，查表获取对应的 <font color=Green>z</font>值。

## 小结

以上就是本模块所提供的线性查表方法了。
