# **USB笔记**
![apaki](../../apaki.jpg)
`2018.05.30 by jianfeng`

### USB 枚举
- [USB_Setup](.\USB_Standard.docx)


### USB_SCSI 命令简介
> 没有特殊标注的的，均为从设备需要实现的命令
##### 基础常用命令
- INQUIRY (0x12)
	> 该命令询问Mass Storage设备的基本信息，如生产厂家，产品名称，产品版本等等。
- READ_FORMAT_CAPACITIES (0x23)
	> 该命令获取Mass Storage设备存储大小，Block长度（一般为一个扇区大小，默认为512）等信息。(大端模式)
	- @RET: 容量列表头{00000008}(4B) | 块个数(4B) | 格式化介质：当前介质容量{02}(1B) | 块大小(4B)
- READ_CAPACITY (0x25)
	> 该命令可以看成是READ_FORMAT_CAPACITIES命令的一个子集。
	- @RET: 逻辑块末地址(4B) | 逻辑块的大小(4B)
- READ_10 (0x28)
	> 该命令由PC端发出，请求Mass Storage设备发送指定扇区索引、扇区个数的数据。
	- @PARAM: {28}(1B) |Logic_Unit_Num(1B:bit5-7) |Logical_Block_Address(4B) |Reserved(1B) |Transfer_Length(2B) | Reserved(3B)
	- @RET: 1块数据
- WRITE_10 (0x2A)
	> 该命令由PC端发出，CBW命令块后面紧跟的就是相应扇区的数据。
- REQUEST_SENSE (0x70)
	> PC机每发送一个命令后，都会检测设备返回的CSW的状态值是否为0(Good Status),如果不为0，则PC机马上发送REQUEST_SENSE命令，询问出错的进一步信息。
- TEST_UNIT_READY (0x00)
	> 在没有其它命令进行操作时，PC端会每隔一定时间，就会发送该命令，主要是为了探测Mass Storage设备是否存在（类似心跳信号）。


##### U盘用到的命令
- Mode Sense(1A)
	- @RET：{03000000}
	> 暂时不知道这个具体时用来做什么的，但是win10系统会要这条命令（其他系统还未测试过）
- PREVENT-ALLOW MEDIUM REMOVAL Command (1e) >> [主]
	> 请求一个可移除媒体设备来加载或卸载其介质(启用或者禁用逻辑单元中介质的移除)
- START-STOP Unit Command (1b) >> [主]
	> 允许或者禁止从可移除设备中移除其介质


### USB_HID 
- 报告描述符详解
	- [博客：小脸龙的老巢](https://blog.csdn.net/cazicaquw/article/details/6724951)
	- [HID鼠标和键盘描述符](.\HID_Report_Descriptor.docx)

	- Logic Minimum / Maximum
		> 逻辑最大最小，表示该字段的取值范围
	- Usage Minimum / Maximum
		> 用于作为数组或者bit位，相对应的作用，比如键盘HID报告描述符中的[E0,E7]。若按下左侧ctrl,发送的第一个字节为0x01,他的含义是E0。关于E0表示左侧的Ctrl，可以参见《HID usage table1.pdf》
- 相关概念解释
	- Report 主要有3种：Input,Output,Feature类型的报表
	- 一般的情况
		- Feature 通过端点0进行传输：
			> 特征报告只能用控制型管线以get report(feature)和set report(feature)指令分别来取得和设定设备的特征值。
		- IN/OUT 我们通常用中断控制进行传输
	- Report ID
		> 一般用Report ID来表明该Report的数据结构。若Report Descriptor中没有Report ID，则可以认为仅仅有一种IN,OUT,Feature类型的报表存在。
		
- Windows HID设备
	1. SetFeature/GetFeature是由特定命令的，通过端点0进行发送和接收
	2. 在使用ReadFile等接口时，若涉及到ID，则需要根据HID报告描述符进行判断，若有ID项，则根据ID项配置（且发送的数据的第一个字节必须时ID？）。若报告描述符中没有ID项，则需要将ReadFile传递的参数的第一个字节配置为0。
