# **Notepad++使用记录**
![apaki](../../apaki.jpg)
`2018.11.13 by jianfeng`

### 自定义运行命令
- python
	> cmd /C cd /d "$(CURRENT_DIRECTORY)" & python "$(FULL_CURRENT_PATH)" & cd "$(CURRENT_DIRECTORY)" & pause


### 宏定义命令相关
- [shortcuts.xml](./shortcuts.xml)
	> 将该文件覆盖到路径  %HOMEPATH%\AppData\Roaming\Notepad++ 下即可。若是本地非安装版，则覆盖掉notepad++主目录下的shortcuts.xml即可

### 右键的“在线搜索”，将搜索引擎配置为Baidu
- 关键字$(CURRENT_WORD)表示在notepad++中选中的待搜索的词汇

```
https://www.baidu.com/s?ie=utf-8&f=8&rsv_bp=0&rsv_idx=1&tn=baidu&wd=$(CURRENT_WORD)&rsv_pq=fdeb207d0000adc0&rsv_t=28a1ZhT3yvSZEcu9ObzZ4WRpmEsU81pOmnRxW4%2FvE8tcZyuDDnuYlTrDhc8&rqlang=cn&rsv_enter=1&rsv_sug3=9&rsv_sug1=7&rsv_sug7=101&rsv_sug2=0&inputT=1969&rsv_sug4=2113&rsv_sug=1
```
