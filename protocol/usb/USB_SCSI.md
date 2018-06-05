# **USB笔记**
![apaki](../../apaki.jpg)
`2018.05.30 by jianfeng`

### USB 枚举
- [USB_Setup](.\USB_Standard.docx)

### USB_SCSI 命令简介
- INQUIRY (0x12)
	> 该命令询问Mass Storage设备的基本信息，如生产厂家，产品名称，产品版本等等。
- READ_FORMAT_CAPACITIES (0x23)
	> 该命令获取Mass Storage设备存储大小，Block长度（一般为一个扇区大小，默认为
512）等信息。(大端模式)
- READ_CAPACITY (0x25)
	> 该命令返回最后一个块的索引和块的长度，其实该命令可以看成是
READ_FORMAT_CAPACITIES命令的一个子集。
- READ_10 (0x28)
	> 该命令由PC端发出，请求Mass Storage设备发送指定扇区索引、扇区个数的数据。
- WRITE_10 (0x2A)
	> 该命令由PC端发出，CBW命令块后面紧跟的就是相应扇区的数据。
- REQUEST_SENSE (0x70)
	> PC机每发送一个命令后，都会检测设备返回的CSW的状态值是否为0(Good Status),
如果不为0，则PC机马上发送REQUEST_SENSE命令，询问出错的进一步信息。
- TEST_UNIT_READY (0x00)
	> 在没有其它命令进行操作时，PC端会每隔一定时间，就会发送该命令，主要是为了
探测Mass Storage设备是否存在（类似心跳信号）。

### USB_HID 
- 报告描述符详解
	- [博客：小脸龙的老巢](https://blog.csdn.net/cazicaquw/article/details/6724951)
	- [HID鼠标和键盘描述符](.\HID_Report_Descriptor.docx)