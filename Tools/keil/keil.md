# KEIL经典使用法记录

### 调试阶段，保存内存中的数据
- SAVE filename startAddr,endAddr
	
	> 保存在文件filename中，格式为HEX386（若看不懂可以通过hex2bin工具进行转换）



### format命令使用

- fromelf --bin -o "$L@L".bin "#L"

  > 输出相应的bin文件

- fromelf -c -o "$L@L".dis "#L"

  > 将编译后的汇编代码输出到指定文件