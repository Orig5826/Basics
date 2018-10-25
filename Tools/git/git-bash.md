# Windows git工具相关操作
`2018.10.25 by jianfeng`

### 该工具命令行参数说明(有些命令是直接从注册表抄袭来的 >^.^< )
> 说一下我的目的，我想要在Source Insight直接快捷打开git-bash或者git-gui
- "D:\Program Files (x86)\Git\cmd\git-gui.exe" "--working-dir" %d
    > %d 是当前文件的路径，若是非SI工具，其他工具则需要找到其路劲相关的命令参数
- "D:\Program Files (x86)\Git\git-bash.exe" --cd=%d
    > 该命令在Source Insight下不知道为什么会出现 “在git-bash窗口存在的时候，SI是不能操作的，否则会卡死”
