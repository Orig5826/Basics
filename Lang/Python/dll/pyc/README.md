# C 和 Python 相互调用的方法
`2018.10.13 by jianfeng`

[参考链接](https://www.zhihu.com/question/23003213/answer/56121859)

## C 调用 Python脚本模块
- [pyc](./pyc)
    > 遇到的编译和调试相关问题，我都已经备注在代码中了。请直接参考代码

# Python 调用 C接口
- [calc](./calc)
    - 通过Python.h编译C的dll库，然后修改名称为*.pyd
        > 注意：生成的dll必须为Release版本，修改名称为*.pyd才能正常调用。Debug下可能会有问题。(我测试的时候遇到的，调试了半天) --- ( @o@ )
- [calc_setup_py](./calc_setup_py)
    - 通过setuptools工具，写一个setup.py脚本，直接编译
    - 命令：setup.py build
- [calc_swig](./calc_swig)
    > 这个是我现在觉得最便捷的方式(2018.10.13)，很方便生成*.pyd
    - swig 工具在windows上需要自己下载，并添加环境变量
