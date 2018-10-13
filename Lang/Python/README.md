# python相关问题
`2018.10.03 by jianfeng`

## windows下python文档查看乱码问题
- \*.chm默认使用IE浏览器的编码，若 \*.chm使用的编码和IE编码不一样，则会出现乱码
    > 将IE浏览器【编码】修改为"自动选择"即可。

## VS2017 C 调用python37 脚本模块
- Debug模式下，python37_d找不到的问题
    > python37_d.lib 在Debug模式下，需要在安装python的时候安装相应的"python debug bin/library..."。
    > 有对应的选项，具体名称我记不住了。安装的时候如果忘记安装了，后续Modify也可以
