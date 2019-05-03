
# STM32 USB官方标准库
`2019.05.03 by jianfeng`

### USB应用API
- usb_conf.h
    > USB 相关配置的头文件
    - 对于USB-FS外设
        - 定义BTABLE和PMA端点地址
        - 根据实际需求，进行中断屏蔽
    - 对于OTG-FS外设
        - 定义端点号
        - 根据实际需求，进行中断屏蔽
- usb_pwr
    > USB 上电和连接管理
    - Power_on
        > 在usb_prop.c 中的xxx_init函数中被调用
    - Power_off
    - Suspend
    - Resume
        > 用于处理唤醒操作
- usb_desc
    > 设备描述符
- usb_istr
    > USB中断处理函数
    - USB_Istr在USB中断服务子程序中stm32f10x_it.c中的USB_LP_CAN1_RX0_IRQHandler()函数中调用
- usb_prop
    > USB应用协议命令实现(将core命令和desc实际数据关联)
    - 用于实现Device_Property, Device_Table, USER_STANDARD_REQUEST
- usb_endp
    > 非控制端点0 的中断处理
    - (^.^) CTR 解释一下：correct transfer 



### USB内核结构
- usb_core
    > USB 整个库的核心，主要实现了USB协议规范中所规定的第九章所有内容
    1. 设备级（device level）信息
        - Device_Table 
            > DEVICE 结构体
    2. 标准协议
        - USB协议标准命令结构，就不再此处提及了。若有不会的，建议参考USB标准协议第九章
        - ControlState
            > 内核状态，参考enum类型CONTROL_STATE
        - Current_Feature 
            > 影响SetFeature和GetFeature请求
        - Current_Configuration
            > SET_CONFIGURATION 和 GET_CONFIGURATION 相关的参数
        - Current_Interface
        - Current_Alternatesetting
            > alternate ??这个是用来作什么的？
        - Ctrl_Info
            > Endpoint Infomation、
    3. 设备属性结构 （Device property structure）
    4. 用户标准请求结构

    - 实际应用中，用户需要实现以下几个方面
        - DEVICE_PROP
        - DEVICE_TABLE
        - USER_STANDARD_REQUEST

- usb_init
    > 配置在整个库中用到的usb初始化函数和全局变量
    - 例如DEVICE_PROP和DEVICE_INFO 结构体指针的初始化
- usb_sil
    > USB外设额外的抽象层，方便用户直接调用
    0. USB_SIL_Init()
        > 已经在usb_prop.c中xxx_init函数中调用了
    1. USB_SIL_Write()
    2. USB_SIL_Read()
        > 读写USB端点中的数据
- usb_int
    > 正确传输中断服务线程 Correct transfer interrupt service routine
    - CTR_LP
    - CTR_HP
- usb_mem
    > 数据传输管理 Data transfer management (from/to packet memory area)
- usb_regs
    > 硬件抽象层 Hardware abstraction layer
