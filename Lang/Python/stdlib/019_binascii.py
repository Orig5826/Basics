
import binascii
data = '31323334353637383931c3'
bb = bytes.fromhex(data)
r = binascii.crc_hqx(bb, 0)

res = hex(r)
print(res)
