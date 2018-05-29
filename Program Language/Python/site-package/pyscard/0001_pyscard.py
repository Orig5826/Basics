# 
# 本程序是测试了CCID设备例程，成功获取随机数
# 效果和PCSC工具相似
# 
from smartcard.System import readers

def scTransPrint(DATA):
    '''
        将发送APDU打印到屏幕上
    '''
    Len = len(DATA)
    if(Len != 0):
        print("<< ",end='')
        for i in range(0, Len):
            print("%02x" % DATA[i], end=' ')
    print()

def scPrint(DATA, SW1=None, SW2=None):
    '''
        将响应APDU打印到屏幕上
    '''
    Len = len(DATA)
    if(Len != 0):
        print(">> ",end='')
        for i in range(0, Len):
            print("%02x" % DATA[i], end=' ')
    if(SW1 != None or SW2 != None):
        print()
        print("   %02x %02x" % (SW1, SW2), end=' ')
    print()
    print()


# 读取当前的SmartCard设备
r = readers()
print("设备：",r)
# 连接设备
connection = r[0].createConnection()
connection.connect()

# APDU指令
ATR = connection.getATR()
scPrint(ATR)

# 1.0 获取随机数
for i in range(0,10):
    GET_CHALLENGE = [0x00, 0x84, 0x00, 0x00, 0x08]
    scTransPrint(GET_CHALLENGE)
    DATA, SW1, SW2 = connection.transmit(GET_CHALLENGE)
    scPrint(DATA, SW1, SW2)
