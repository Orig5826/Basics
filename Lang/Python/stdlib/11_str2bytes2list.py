#!/usr/bin/python
# -*- coding: utf-8 -*-
'''
    渐渐用多了，才发现，整理的这些东西，并非是用来提供直接调用的。
    主要是方便对于python各种数据类型的理解，方便用到什么的时候，
    可以直接拿来作为参考
'''



# -------------- python3.6 ----------------------
'''
1-3 主要涉及Hex,Bytes,List之间的相互转换
    这里的Hex指的是诸如 str("313233414234") (即相当于是2个字符表示一位十六进制数据)
    则可定Hex不能有[^0-9A-Fa-f]数据
4-6 涉及到str 诸如"Hello world哈哈"
    则这种情况会涉及到转码问题encoding=utf-8等
'''

# 1.0 hex <--> bytes
def hex2bytes(hh):
    '''
        str("31323334") -> b"1234"
    '''
    return bytes.fromhex(hh)

def bytes2hex(bb):
    '''
        b"1234" -> str("31323334") 
    '''
    return bb.hex()


# 2.0 list <--> bytes
def list2bytes(ll):
    '''
        [0x31,0x32,0x33] -> b"123"
    '''
    return bytes(ll)

def bytes2list(bb):
    '''
         b"123" -> [0x31,0x32,0x33]
    '''
    return list(bb)


# 3.0 list <--> hex
def list2hex(ll):
    '''
        [0x31,0x32,0x33] -> str("313233")
    '''
    return bytes(ll).hex()

def hex2list(hh):
    '''
        str("313233") -> [0x31,0x32,0x33]
    '''
    bb = bytes.fromhex(hh)
    return list(bb)

# 4.0 str <--> list
def str2list(ss):
    '''
        str("123ABC") -> [0x31,0x32,0x33,0x41,0x42,0x43]
        str("我的世界")(本脚本为utf-8编码) -> [25105, 30340, 19990, 30028] (因为ord返回Unicode编码)
    '''
    return [ord(c) for c in list(ss)]

def list2str(ll):
    '''
        [0x31,0x32,0x33,0x41,0x42,0x43] -> str("123ABC")
    '''
    return ''.join([chr(i) for i in ll])

# 5.0 str <--> bytes
def str2bytes(ss):
    '''
        str("123ABC") -> b"123ABC"
    '''
    return bytes(ss, encoding='utf-8')
    
def bytes2str(bb):
    '''
        b"123ABC" -> str("123ABC")
    '''
    return str(bb, encoding='utf-8')
    

# ... 
'''
    其他各种转换便不再多写了，主要是因为有以上一些接口，
    对于实际应用的时候，用到什么，相互直接一调用也能实现各种数据之前的相互转化了。
    以后若再扩展，则必定是更加简洁/高效...的方式
'''


def py36_str_hex_bytes_test():
    # ------------------------------------------------------
    ll = [0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38]
    print('[list]         {} \t {}'.format(type(ll),ll))

    bb = list2bytes(ll)
    hh = list2hex(ll)
    print('[list2bytes]   {} \t {}'.format(type(bb),bb))
    print('[list2hex]     {} \t {}'.format(type(hh),hh))


    ll2 = bytes2list(bb)
    hh2 = bytes2hex(bb)
    print('[bytes2list]   {} \t {}'.format(type(ll2),ll2))
    print('[bytes2hex]    {} \t {}'.format(type(hh2),hh2))


    ll3 = hex2list(hh)
    bb2 = hex2bytes(hh)
    print('[hex2list]     {} \t {}'.format(type(ll3),ll3))
    print('[hex2bytes]    {} \t {}'.format(type(bb2),bb2))

    ll4 = str2list("我的世界")
    print('[str2list]     {} \t {}'.format(type(ll4), ll4))
    ss = list2str(ll4)
    print('[list2str]     {} \t {}'.format(type(ss), ss))

    bb4 = str2bytes(ss)
    print('[str2bytes]    {} \t {}'.format(type(bb4), bb4))
    ss4 = bytes2str(bb4)
    print('[bytes2str]    {} \t {}'.format(type(ss4), ss4))

    # 若想将汉字也转为list形式，可以相互调用实现
    bb5 = str2bytes("我的世界")
    ll5 = bytes2list(bb5)
    print('[汉字2list]    {} \t {}'.format(type(ll5), ll5))

# -------------- python2.7 ----------------------


def py27_bytes2hex(bb):
    b = bytes(bb)
    return b.encode('hex')
def py27_hex2bytes(hh):
    return hh.decode('hex')

def py27_list2bytes(ll):
    return bytearray(ll)
def py27_bytes2list(bb):
    return list(bb)

def py27_list2hex(ll):
    b = bytearray(ll)
    return bytes(b).encode('hex')
def py27_hex2list(hh):
    s = hh.decode('hex')
    return list(bytearray(s))

def py27_str_hex_bytes_test():
    # ------------------------------------------------------
    ll = [0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38]
    print('[py27_list]         {}'.format(ll))

    bb = py27_list2bytes(ll)
    hh = py27_list2hex(ll)
    print('[py27_list2bytes]   {}'.format(bb))
    print('[py27_list2hex]     {}'.format(hh))


    ll2 = py27_bytes2list(bb)
    hh2 = py27_bytes2hex(bb)
    print('[py27_bytes2list]   {}'.format(ll2))
    print('[py27_bytes2hex]    {}'.format(hh2))


    ll3 = py27_hex2list(hh)
    bb2 = py27_hex2bytes(hh)
    print('[py27_hex2list]     {}'.format(ll3))
    print('[py27_hex2bytes]    {}'.format(bb2))



py36_str_hex_bytes_test()
