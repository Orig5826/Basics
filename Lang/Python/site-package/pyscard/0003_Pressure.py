from smartcard.System import readers


class Card():
    '''
        Card 通讯
    '''
    __port = 0

    def __init__(self):
        # 连接设备
        try:
            '''
                _Private__Attr
            '''
            print(self.__port)
            self.__r = readers()
            self.__card = self.__r[self.__port].createConnection()
            self.__card.connect()
            print("# Connect Device ：", self.__r)

            # 若已经打开了一次该设备，则下次调用该类，打开下一设备
            # self.__port += 1
            # 注意理解和上面代码的含义
            Card.__port += 1

            # APDU指令
            ATR = self.__card.getATR()
            print("[ATR] " + bytes(ATR).hex())
        except:
            print("# Connect Device Failed!")

    def __Send(self, apdu):
        '''
            _Private__Method
        '''
        print("\n>> " + bytes(apdu).hex())
        res, sw1, sw2 = self.__card.transmit(apdu)
        if len(res) != 0:
            print("<< " + bytes(res).hex())
        print("<< {0:02x}{1:02x}".format(sw1, sw2))
        sw = (sw1 << 8) | sw2
        return res, sw

    def Pressure(self,cnt = 255):
        '''
            压力测试
			有一点需要注意的是，CCID设备有最大包长限制
			这个可能有一些问题。
        '''
        for i in range(255,cnt + 1):
            apdu = [0x00, 0x03, 0x00, 0x00]
            data = [x & 0xff for x in range(i)]
            if i < 256:
                apdu.append(i)
            else:
                apdu.append(0x00)
                apdu.append((i >> 8) & 0xff)
                apdu.append(i & 0xff)
            apdu.extend(data)
            self.__Send(apdu)


app = Card()
print(app._Card__port)
app2 = Card()
print(app2._Card__port)

app.Pressure(258)
