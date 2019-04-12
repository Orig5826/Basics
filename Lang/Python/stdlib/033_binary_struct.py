
import struct

"""
    # struct 模块说明：

    ###  大小端说明
    1. > 表示 big-endian
    2. < 表示 little-endian
    3. ! 表示 network(=big-endian)

    ### C Type说明
        > 仅列出常用的一些，其中，小写代表有符号，大小代表无符号
    1. b,B -> (unsigned) char
    2. h,H -> (unsigned) short
    3. i,I -> (unsigned) int
    4. l,L -> (unsigned) long (== 4 Bytes)
    5. q,Q -> (unsigned) long long (== 8 Bytes)
    6. f -> float
    7. d -> double
    8. s -> char []
    9. ? -> _Bool (C99)

    ### 注意点：
    有几个选项就得有几个对应的参数
"""

# ---------------------------------------
# 将4 Bytes 转化为 32bit整型 大端
data = bytes.fromhex('00 00 01 02')
print(data)
result = struct.unpack('>I', data)
print(result)
# 小端
data = b'\x02\x01\x00\x00'
print(data)
result = struct.unpack('<I', data)
print(result)

# 大端，直接将Bytes按照一定规则分割
data = bytes.fromhex('02 01 00 00')
print(data)
result = struct.unpack('>BHB', data)
print(result)


# ---------------------------------------
# 将数据转换为相应的 Bytes
data = 256
print(data)
result = struct.pack('H', data)    # 默认是小端
print(result)

# 将一组数据转换为相应的 BYtes
data = (256, 0)
print(data)
result = struct.pack('<HH', *data)
print(result)


# ---------------------------------
data = (256, 512)
print(data)
result = struct.pack('>2H', *data)    # 默认是小端
print(result)
