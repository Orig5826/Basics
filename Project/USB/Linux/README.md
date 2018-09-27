# Linux下USB通讯
`2018.9.27 by jianfeng`

### 工程示例说明
> 重点或者整理后的通讯接口，使用**加粗**标注
- libusb_demo
    > 最初版本，用来测试libusb相关接口使用，其中实现了hid和scsi的测试
- **usbdrv**
    > 主要版本，将SCSI相关的命令封为特定的函数接口，方便以后调用
