# ------------------------------------
# python3.6
# ------------------------------------
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
