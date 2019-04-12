
"""
    小提示：
    python3 所有的字符串都默认为 Unicode编码

    而python2不一样，
    默认是已经编码（非Unicode）的字符串，若需要输入Unicode编码字符串，则需要在字符串引号前添加'u'标记

    以下示例都是在python3环境下的理解测试
"""


# 个人理解
# 编码的所谓加密和解密是针对Unicode而言的。
#  若 Unicode 转化为 utf-8 编码，则需要采用encode进行编码
code_src = '我的世界'
text = code_src.encode('utf-8')
print(text)

# 若 utf-8 转化为 Unicode 编码，则需要采用decode 进行解码
code_src = b'\xe6\x88\x91\xe7\x9a\x84\xe4\xb8\x96\xe7\x95\x8c'
text = code_src.decode('utf-8')
print(text)
