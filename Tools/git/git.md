# **Git的使用笔记**
![apaki](../../apaki.jpg)
`2018.04.16 by jianfeng`
#### 知识来源：[廖雪峰的官方网站](https://www.liaoxuefeng.com/wiki/0013739516305929606dd18361248578c67b8067c8c017b000)
- config --global user.name "Your Name" 
- config --global user.email "email@example.com"

	> --global表示本机器所有的仓库都使用该配置
- init

	> 仓库初始化（会在当前目录下创建.git目录，用来跟踪版本库）

----------------------------------------------------------------
## 本地常用操作
- 相关概念
	- 版本库（Repository），即.git中所存放的内容，不可手动修改
	- 暂存区stage（或者叫index），add命令之后，则修改进入stage，而commit之后，才真正的提交到版本库中
	- 工作区，即我们认为操作的文件夹
	- master 自动创建的第一个分支
	- HEAD 是指向master的指针
- add
	> 提交修改/新文件
	- git add . 
	>将文件的修改，文件的新建，添加到暂存区 
	- git add -u(git add --updata)
	>将文件的修改、文件的删除，添加到暂存区 
	- git add -A (git add --all)
	>将文件的修改，文件的删除，文件的新建，添加到暂存区 
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
	- git checkout -- file
		> 命令中 -- 必须有，否则可能实现预期之外的功能（如切换到分支等）
		>
		>1. 若文件已经添加到暂存区，则该命令是回到暂存区状态。
		>2. 若文件没有添加到暂存区，则该文件回到版本库状态
		
	- git checkout .
		
	> 放弃当前所有的本地修改
		
	- git checkout -b develop
	
	    > 创建develop分支，命令作用等同于git branch develop; git checkout develop
	
	- git checkout tag_name
	
	    > 此时，提示 detached HEAD是因为tag相当于快照，是不能直接修改的
	
	- git checkout -b branch_name tag_name
	
	    > 基于该tag创建一个分支，这样就和普通分支一样可以操作了
	
	- git checkout -f branch_name
	
	    > 强制新建branch_name（即便该分支名称已经存在），我之前用它来操作（移动）branch_name指针
	
	- git checkout -b dev origin/dev
	
	    > 新建分支dev，且关联到远程分支origin/dev上
- rm


> 从版本库中删除文件

- clean
	
	> git clean -xdf 清空：本地新增但没有add到暂存区的所有文件
- tag
	> 打标签 （下面的方括号表示可选项，若不手动添加，则自动进入提示操作）
	- git tag -a v1.0 [-m 'tag备注']
	- git tag -a v1.0 17b6b9a
	- git tag -d v1.0
	
- show
	
- git showv1.0
	
- commit

- git commit -m'提交备注'

- git commit --amend

	> 修改最后一次注释

- rebase
	> ? 
	- git rebase -i HEAD~3
	- git rebase -i 17b6b9a



----------------------------------------------------------------
## 远程常用操作 --- GitHub为例
- Git Bash
	> 利用Git Bash创建SSH Key
	> ssh-keygen -t rsa -C "Orig5826@163.com"
	> 随后在用户主目录下会出现.ssh文件，里面含有rsa的公钥和私钥
	> 登陆GitHub，在Setting中想办法将公钥数据添加到SSH key中，题目自己定
`其实除了Github之外，中国也有Git托管：诸如gitee.com，coding.net`
- clone
	> 从远程服务器中克隆一个本地库
	>
	> 例如 git clone git@github.com:Orig5826/Basics.git(从Github仓库找)
- remote
	> 将本地仓库和GitHub上新建的仓库关联
	- git remote add origin git@github.com:Orig5826/Basics.git
	
		> origin 远程库名称，可以修改
	- git push -u origin master
		> -u 的作用，推送+关联
		>
		> 此时就可以在GitHub页面看到远程库和本地库一致了
	- git push origin master
	
		> 以后就可以使用该命令将更新的代码提交到远程库中

### 本地分支和远程分支不一致的情况
```shell
# 先将远程分支更新到本地，但不合并
git fetch origin

# 然后查看下差异
git diff master origin/master

# 如需要，可以将远程分支合并到本地分支中
git merge origin/master 
# 如果提示错误：fatal: refusing to merge unrelated histories。那么
# 加上如下命令，可以让两个不相干的分支强行合并
git merge origin/master --allow-unrelated-histories

# 最后push即可
git push origin master

```

----------------------------------------------------------------
## 分支合并等操作
- branch

	> 分支操作
	
	- git branch
	
	> 查看当前所有分支
	
	- git branch feature-usb
	
	> 创建feature-usb分支
	
	- git branch -m [old_branch_name] new_branch_name
	
	> 修改当前分支名称 [修改旧分支名称为新分支名称]
	
- merge

	> 以合并两个git仓库为例子，在想整合的仓库(即本仓库)路径下执行以下命令
	>
	> 备注：注意第4-5操作指令，是谁合并到了谁。
	1. git remote add other repo_path 
	
		> other为别名,repo_path为被合并的仓库路径。该命令本质上，相当于是将被合并的仓库当作远程仓库
	2. git fetch other
	
		> 从repo_path中抓取数据到本仓库
	3. git checkout -b repo1 other/master
	
		> 将repo_path仓库抓取的master分支作为新分支checkout到本地，新分支名称设置为repo1
	4. git checkout master
	
		> 切换为本仓库的master分支
	5. git merge repo1
	
		> 将repo1合并到master
	
	- 注意事项：
		- 若merge的时候出现冲突，则需要先修改冲突。然后add,commit,push
		- 若merge出现unrelated history的警告，则需要在命令结尾添加--allow-unrelated-histories参数进行强行合并
	
- fetch

	> 相当于是从远程获取最新版到本地，不会自动merge。（当服务器被他人更改时）
	
- pull

	> 相当于fetch + merge。（当服务器被他人更改时）
----------------------------------------------------------------
## 搭建git服务器
- 在linux上搭建git服务器
	1. 安装git
	2. sudo adduser git
	
		> 新建一个git用户，用来运行git服务
	3. 创建证书登陆,即将客户端的id_rsa.pub导入进来，将公钥都放在/home/git/.ssh/authorized_keys文件中，一行一个(也可以后续在做该步骤)
	4. sudo git init --bare ubuntu.git
	
		> cd到你所选定的目录下，初始化git仓库
	5. sudo chown -R git:git ubuntu.git
	
		> 记得一定要修改所有者，要不然远程登陆肯定失败呀
	6. 同时，可以考虑禁用shell登陆，方法可以是：将/etc/passwd文件中的git用户的shell做如此修改 =>/bin/bash -->/usr/bin/git-shell
	
		> 此后，git用户可以正常通过ssh使用git，但无法登陆shell，因为我们为git用户指定的git-shell每一次登陆就自动推出
	7. [客户端]之后，就可以在各自的电脑上进行clone

----------------------------------------------------------------
## 其他操作
- 忽略特殊文件
	- 直接在.gitignore文件中添加所需要忽略的文件/文件夹即可
	- 当然了在..git/info/exclude中添加了文件，也可以。但是一般不去手动修改.git中的文件
		- .git/infor/exclude
		
		> 在exclude中添加 **/.vscode/,忽略本地仓库中所有的./vscode文件
	
- 配置别名
	1. git config --global alias.st status
	
		> 可以直接输入 git st
	2. git config --global alias.lg "log --color --graph --pretty=format:'%Cred%h%Creset -%C(yellow)%d%Creset %s %Cgreen(%cr) %C(bold blue)<%an>%Creset' --abbrev-commit"
	
		> 这个是真的好，之前还想git log --pretty=oneline 有点信息不全呢，哈哈



## 问题
```
Cloning into 'Basics'...
The authenticity of host 'github.com (20.205.243.166)' can't be established.
ED25519 key fingerprint is SHA256:+DiY3wvvV6TuJJhbpZisF/zLDA0zPMSvHdkr4UvCOqU.
This key is not known by any other names.
Are you sure you want to continue connecting (yes/no/[fingerprint])?
Host key verification failed.
fatal: Could not read from remote repository.
```
如果遇到以上问题，那么要注意，Are you sure ...的时候，。不要直接回车。
而是输入yes之后，再回车。
