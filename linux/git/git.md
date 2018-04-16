# **Git的使用笔记**
`2018.04.16 by jianfeng`
#### 知识来源：[廖雪峰的官方网站](https://www.liaoxuefeng.com/wiki/0013739516305929606dd18361248578c67b8067c8c017b000)
- config --global user.name "Your Name" 
- config --global user.email "email@example.com"
    > --global表示本机器所有的仓库都使用该配置
- init
    > 仓库初始化（会在当前目录下创建.git目录，用来跟踪版本库）
--------------------------------------------------------------------
## 本地常用操作
    - 和svn本地管理类似
    - 相关概念
        - 版本库（Repository），即.git中所存放的内容，不可手动修改
        - 暂存区stage（或者叫index），add命令之后，则修改进入stage，而commit之后，才真正的提交到版本库中
        - 工作区，即我们认为操作的文件夹
        - master 自动创建的第一个分支
        - HEAD 是指向master的指针
- add
    > 提交修改/新文件
- status
    > 查看当前仓库的状态
- diff
    > (可以在提交前)查看当前修改的内容
    > git diff HEAD -- *.* 用来查看工作区和版本库里最新版的区别

- log
    > 查看历史提交信息(是从当前HEAD开始算起)
    - --pretty=oneline
        > 一行显示
- reflog
    > git reflog 查看命令历史，以便确定要回到未来的哪个版本
- reset 
    > 回退到上一个版本
    > 格式：git reset --hard HEAD^ 表示上一个版本，HEAD^^是上上个版本，HEAD~100是上100个版本 ？(我测试的时候，为什么会出现More？)

- checkout 
    - -- file
        > 其中--命令必须有，否则就会成为“切换另一个分支”了
        >
        >1.当工作区被乱改，想丢弃，则直接checkout -- file即可。
        >
        >2.若乱改后且已经添加到暂存区，reset HEAD file,可以回到场景1，然后按1操作
        >
        >3.若已经提交， 则可以考虑版本回退（当然了，你若已经提交到了远程库，则某些不合适的修改必然可以被大伙看到，且没法撤销了）
    - checkout恢复本地被删除的文件（前提库中没有删除，和svn中的checkout道理一样）
- rm
    > 从版本库中删除文件

--------------------------------------------------------------------
## 远程常用操作 --- GitHub为例
    - Git Bash
        > 利用Git Bash创建SSH Key
        > ssh-keygen -t rsa -C "Orig5826@163.com"
        > 随后在用户主目录下会出现.ssh文件，里面含有rsa的公钥和私钥
        > 登陆GitHub，在Setting中想办法将公钥数据添加到SSH key中，题目自己定
- clone
    > 从远程服务器中克隆一个本地库
    >
    > 例如 git clone git@github.com:Orig5826/Basics.git(从Github仓库找)
- remote
    > 将本地仓库和GitHub上新建的仓库关联
    - git remote add origin git@github.com:Orig5826/Basics.git
    > 





