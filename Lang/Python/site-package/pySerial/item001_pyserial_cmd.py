
from pyserial_uart import Uart

class Demo():
    def __init__(self):
        self.com = Uart(1)
    def send(self, cmd, param, data):
        if isinstance(cmd, str):
            # cmd.replace(' ','',-1)    #fromhex内部已经做个去除空格处理
            cmd = bytes.fromhex(cmd)
        if isinstance(param, str):
            param = bytes.fromhex(param)
        if isinstance(data, str):
            data = bytes.fromhex(data)
        data_len = len(data)
        command = bytearray()
        # 总长度
        total_length = data_len + 4
        command.append((total_length >> 8) & 0xff)
        command.append(total_length & 0xff)
        # 命令整合
        command.extend(cmd)
        command.extend(param)
        command.append((data_len >> 8) & 0xff)
        command.append(data_len & 0xff)
        command.extend(data)
        # print("command: ",command)
        res = self.com.send(command)
        # print("response: ",res)
        if res == False:
            return False
        status = res[0]
        res_len = (res[1] << 8) + res[2]
        if res_len == 0:
            return (status, None)
        else:
            return (status, res[3:].hex())

    def sm1_enc_ecb(self, data):
        if len(data) % 16 != 0:
            print("数据长度错误")
            return False
        key = "40bb12dd6a8273867f3529d354b4a026 "
        # data = "ffeeddccbbaa99887766554433221100 "
        status,res = self.send("41","10",key+data)
        if status != 0x00:
            return False
        return res
    def sm1_dec_ecb(self,data):
        if len(data) % 16 != 0:
            print("数据长度错误")
            return False
        key = "40bb12dd6a8273867f3529d354b4a026  "
        # data = "ffeeddccbbaa99887766554433221100 "
        status,res = self.send("42","10",key+data)
        if status != 0x00:
            return False
        return res


demo = Demo()
while True:
    plain = "ffeeddccbbaa99887766554433221100"
    cipher = demo.sm1_enc_ecb(plain)
    result = demo.sm1_dec_ecb(cipher)
    if plain != result:
        print("--- 加解密失败！ ---")
        break
