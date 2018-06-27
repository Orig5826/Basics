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

## 注释风格
- 
