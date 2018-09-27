# Windows下USB通讯
`2018.9.27 by jianfeng`

### 工程示例说明
> 重点或者整理后的通讯接口，使用**加粗**标注
- libusb_demo
    > windows下使用libusb，hid设备正常读写，但scsi设备有问题。据上网查资料，libusb在windows上scsi设备不能正常识别
- **usb_demo**
    > windows API的调用，HID通讯，且封装为dll库，方便调用，同时添加python调用接口（但并不完善）
- USB_HID
    > windows API的调用，HID通讯最初版本
- **usbdisk**
    > 通过磁盘盘符，对USB Mass Storage设备进行SCSI命令的访问
- usbdrv
    > 最初想通过PID和VID对SCSI设备进行访问，但调试失败!