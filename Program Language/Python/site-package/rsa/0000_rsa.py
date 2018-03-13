# -*- coding: utf_8 -*-

import rsa

# 经过查看rsa库源代码
# 加密接口符合pkcs规范 0002 填充
(pubkey, prikey) = rsa.newkeys(1024)
plain = b"Hello world!"
cipher = rsa.encrypt(plain, pubkey)
print(len(cipher))
for data in cipher:
    print("%02x " % data, end="")
print(" ")
outplain = rsa.decrypt(cipher, prikey)
print(outplain)


# 测试签名
message = plain
signature = rsa.sign(message, prikey, "SHA-1")
try:
    rsa.verify(message, signature, pubkey)
    print("验签成功")
except:
    print("验签失败！")


def pub_decode(message, pub_key):
    from rsa import common, transform, core
    keylength = common.byte_size(pub_key.n)
    encrypted = transform.bytes2int(message)
    decrypted = core.decrypt_int(encrypted, pub_key.e, pub_key.n)
    clearsig = transform.int2bytes(decrypted, keylength)
    return clearsig


def HashData(message):
    import hashlib
    m = hashlib.sha1()
    m.update(message)
    return m.digest()


print(len(signature))
# 此处对签名的数据做一下解密，看看内容
out = pub_decode(signature, pubkey)
for data in out:
    print("%02x " % data, end="")
print("")

# 计算Hash
for data in HashData(message):
    print("%02x " % data, end="")
print("")
