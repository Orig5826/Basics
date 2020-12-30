CMAC算法实现

1. 密钥准备

    使用K=cmac_key对全0做ecb加密运算。得到密文C。

    若C的最高bit为1，则K1 = C<<1。否则K1 = (C1<<1) ^ const_Rb。
    
    若C的最高bit为1，则K2=K1<<1。否则K2 = ( K1<<1) ^ const_Rb。
    
    其中const_Rb为一个大数常量，和密钥K1和K2长度相关。
    
    例如：0x1B for 64-bit, 0x87 for 128-bit, and 0x425 for 256-bit blocks.
    
2. 计算流程：

    本质上是AES/3DES的IV为全0的CBC运算，只是针对message总长度是否为Block整数倍的做了不一样的处理。

    若message = Block_len * M(其中M为任意正整数)，则使用密钥K1，对message做cbc运算

    若message != Block_len * M，则需要使用b"10...0"做填充，使其为Block_len的整数倍，随后再使用密钥K2，对message做cbc运算。