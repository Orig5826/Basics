#!/usr/bin/python
# -*- coding: utf-8 -*-

# -------------- python3.6 ----------------------


# 1.0 str2bytes,bytes2str
def str2bytes(ss):
    return bytes.fromhex(ss)

def bytes2str(bb):
    return bb.hex()



# 2.0 list2bytes,bytes2list
def list2bytes(ll):
    return bytes(ll)

def bytes2list(bb):
    return list(bb)



# 3.0 list2str,str2list
def list2str(ll):
    return bytes(ll).hex()

def str2list(ss):
    bb = bytes.fromhex(ss)
    return list(bb)


def py36_str_hex_bytes_test():
    # ------------------------------------------------------
    ll = [0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38]
    print('[list]         {}'.format(ll))

    bb = list2bytes(ll)
    ss = list2str(ll)
    print('[list2bytes]   {}'.format(bb))
    print('[list2str]     {}'.format(ss))


    ll2 = bytes2list(bb)
    ss2 = bytes2str(bb)
    print('[bytes2list]   {}'.format(ll2))
    print('[bytes2str]    {}'.format(ss2))


    ll3 = str2list(ss)
    bb2 = str2bytes(ss)
    print('[str2list]     {}'.format(ll3))
    print('[str2bytes]    {}'.format(bb2))



# -------------- python2.7 ----------------------


def py27_bytes2str(bb):
    b = bytes(bb)
    return b.encode('hex')
def py27_str2bytes(ss):
    return ss.decode('hex')

def py27_list2bytes(ll):
    return bytearray(ll)
def py27_bytes2list(bb):
    return list(bb)

def py27_list2str(ll):
    b = bytearray(ll)
    return bytes(b).encode('hex')
def py27_str2list(ss):
    s = ss.decode('hex')
    return list(bytearray(s))

def py27_str_hex_bytes_test():
    # ------------------------------------------------------
    ll = [0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38]
    print('[py27_list]         {}'.format(ll))

    bb = py27_list2bytes(ll)
    ss = py27_list2str(ll)
    print('[py27_list2bytes]   {}'.format(bb))
    print('[py27_list2str]     {}'.format(ss))


    ll2 = py27_bytes2list(bb)
    ss2 = py27_bytes2str(bb)
    print('[py27_bytes2list]   {}'.format(ll2))
    print('[py27_bytes2str]    {}'.format(ss2))


    ll3 = py27_str2list(ss)
    bb2 = py27_str2bytes(ss)
    print('[py27_str2list]     {}'.format(ll3))
    print('[py27_str2bytes]    {}'.format(bb2))



py27_str_hex_bytes_test()
