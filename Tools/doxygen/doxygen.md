# **Doxygen使用笔记**
![apaki](../../apaki.jpg)
`2018.04.16 by jianfeng`

## doxygen配置文件说明
- 一些简单易懂的就不做笔记了，比如：
    - 编码（工程，源码，输出chm等）
    - 源文件地址，文档输出地址，hhc地址
    - graphviz 工具 DOT的配置
    - ...
- SOURCE_BROWSER
    > 让源代码可以像头文件一样单独显示，比如.c中的文件。这个功能适合提供源文件的。比如stm32库
- INLINE_SOURCES
    > 表示直接在文档中就体现函数等的源码（注意和SOURCE_BROWSER的区别）
- STRIP_CODE_COMMENTS
    > 一般配置为NO，这样查看原文件的时候，所有的注释都能显示出来。默认是YES，表示文档摘出去的注释将不再源文件提示中显示
- REFERENCED_BY_RELATION
    > 被谁引用
- REFERENCES_RELATION
    > 引用了谁
- REFERENCES_LINK_SOURCE
    > 如果SOURCE_BROWSER配置YES，那么该项表明引用的文件可以直接跳转到相应源码处

## 预处理
- ENABLE_PREPROCESSING
    > 开启预处理，开启之后对于#define可以识别，在c文件中也能创建链接
- PREDEFINED
    > 声明某个宏定义，对于通过#ifdef来条件判断的，很有效
```
PREDEFINED             = "DEBUG"
```

## GRAPH
- HAVE_DOT
    > DOT是Graphviz工具的一部分，若YES，则采用该工具绘图。其他同类工具选项无效
- DOT_PATH
    > 工具路径，若默认路径能找到该工具（似乎环境变量中添加路径有效），则该项可不填
- INCLUDE_GRAPH
    > 文档包含关系图，但占用时间大。主要针对头文件
- INCLUDED_BY_GRAPH
    > 文档被包含关系图，但占用时间大。主要针对头文件
- CALL_GRAPH
    > 函数调用关系图，但占用时间大
    - 注意：不一定会把所有的调用关系都链接好，之前出现过明明函数调用没问题，但是关系图不显示的问题
- CALLER_GRAPH
    > 函数被调用关系图，但占用时间大
```
HAVE                   = YES
DOT_PATH               = "D:\Program Files\graphviz\bin"
INCLUDE_GRAPH          = NO
INCLUDED_BY_GRAPH      = NO
CALL_GRAPH             = YES
CALLER_GRAPH           = NO
```

## 注释风格
- 
