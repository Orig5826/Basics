# pyOpenSSL

# 产生密钥对
> 利用PKey对象可以方便快速产生密钥对，然后dump_函数可以把PKey对象转成字节码方便写入文件，或者进行base64编码后进行网络传输。
```
from OpenSSL.crypto import PKey
from OpenSSL.crypto import TYPE_RSA, FILETYPE_PEM
from OpenSSL.crypto import dump_privatekey, dump_publickey

pk = PKey()
print(pk)
pk.generate_key(TYPE_RSA, 1)
dpub = dump_publickey(FILETYPE_PEM, pk)
print(dpub)
dpri = dump_privatekey(FILETYPE_PEM, pk)
print(dpri)
```
# 签名与验证
> 利用sign和verify可以进行签名和验证，但是verify需要用到X509对象作为参数
```
from OpenSSL.crypto import PKey
from OpenSSL.crypto import TYPE_RSA, FILETYPE_PEM
from OpenSSL.crypto import sign, verify
from OpenSSL.crypto import X509

pk = PKey()
pk.generate_key(TYPE_RSA, 1024)

signature = sign(pk, 'hello, world!', 'sha1')
print(signature)

x509 = X509()
x509.set_pubkey(pk)
verify(x509, signature, 'hello, world!', 'sha1')
```