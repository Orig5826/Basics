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


## EXTRACT 系列配置
- EXTRACT_ALL
- EXTRACT_PRIVATE
    > 类的私有成员
- EXTRACT_PACKAGE
- EXTRACT_STATIC
    > static 声明的变量和函数
- EXTRACT_LOCAL_CLASSES
    > 类的源文件也会被包含。"NO"仅仅包含头文件中的类定义
- EXTRACT_LOCAL_METHODS 
    > This flag is only useful for Objective-C code
- EXTRACT_ANON_NSPACES


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
    - 注意：不一定会把所有的调用关系都链接好，之前出现过明明函数调用没问题，但是关系图不显示的问题 (版本：1.8.14)
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

## 其他常用选项
- EXTENSION_MAPPING
    > 可以将md文件直接作为新的一页文档添加

## 分组
> 我暂时还用不到，先不详细学习了


## 注释风格
- 函数注释示例
    > 包括以下几个方面
    - 函数简述
    - 参数说明
    - 返回值说明
    - 函数调用示例（其中后面的{.c}表示这是c调用示例）。若你写的是python示例，则为{.py}
```
/**
 * @brief ftl 读操作
 * 
 * @param paddr 逻辑地址
 * @param data 读取的数据
 * @param len 读取的数据长度
 *
 * @retval true 读取成功
 * @retval false 读取失败
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.c}
 *	uint32_t addr = 0x0000;
 *	uint8_t data[64];
 *	// 注意地址指针的用法
 *	ftl_read((uint32_t *)addr,data,64);
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */
```

- 文件头注释
    > 包括以下几个方面
    - 函数简述
    - 文件名称
    - 作者信息
    - 创建时间
```
/**
 * @brief 文件简述
 * 
 * @file apdu.h
 * @author wenjf
 * @date 2019/4/26
 */
```

- MarkDown文件支持
    > 常用的基本都支持，此处不用详细说明

- Latex
    > 数学公式是其最大的亮点，暂用不到这么强大功能

- 内嵌HTML

