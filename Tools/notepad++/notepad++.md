# **Notepad++使用记录**
![apaki](../../apaki.jpg)
`2018.11.13 by jianfeng`

### 自定义运行命令
- python
	> cmd /C cd /d "$(CURRENT_DIRECTORY)" & python "$(FULL_CURRENT_PATH)" & cd "$(CURRENT_DIRECTORY)" & pause


### 宏定义命令相关
- [shortcuts.xml](./shortcuts.xml)
	> 将该文件覆盖到路径  %HOMEPATH%\AppData\Roaming\Notepad++ 下即可。若是本地非安装版，则覆盖掉notepad++主目录下的shortcuts.xml即可