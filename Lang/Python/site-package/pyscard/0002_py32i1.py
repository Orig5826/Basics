from smartcard.System import readers


def Connect():
    r = readers()
    # 连接设备
    try:
        connection = r[0].createConnection()
        connection.connect()
        print("# Connect Device ：", r)
    except:
        print("# Connect Device Failed!")
        return False
    # APDU指令
    ATR = connection.getATR()
    print("ATR = " + bytes(ATR).hex())
    return connection


# -------------------------------------------------
# 全局card变量
card = Connect()
if card == False:
    exit

# -------------------------------------------------


def SendData(apdu):
    print("\n>> " + bytes(apdu).hex())
    res, sw1, sw2 = card.transmit(apdu)
    if len(res) != 0:
        print("<< " + bytes(res).hex())
    print("<< {0:02x}{1:02x}".format(sw1, sw2))
    sw = (sw1 << 8) | sw2
    return res, sw


# -------------------------------------------------
def GetChallenge(rLen):
    if rLen >= 256 or rLen <= 0:
        print("Get Challenge -> the length must less than 256")
        return
    return SendData([0x00, 0x84, 0x00, 0x00, rLen])


def HashData(data=None, Alg='sha256'):
    HashLen = 0
    apdu = [0x00, 0x2A, 0x00, 0x00]
    if Alg == 'sha1':
        apdu[3] = 0x01
        HashLen = 0x14
    elif Alg == 'sha224':
        apdu[3] = 0x02
        HashLen = 0x1C
    elif Alg == 'sha256':
        apdu[3] = 0x03
        HashLen = 0x20
    elif Alg == 'sm3':
        HashLen = 0x20
    else:
        print("[Warning] You should choose the right Algorithm!")
    apdu.append(len(data))
    apdu.extend(data)
    apdu.append(HashLen)
    return SendData(apdu)


# -------------------------------------------------
GetChallenge(8)

data = []
for i in range(0, 3):
    data.append(i)
HashData(data)
