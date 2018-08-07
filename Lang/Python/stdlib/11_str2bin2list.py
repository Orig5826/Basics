# ------------------------------------
# python3.6
# ------------------------------------
# 1.0 str2bin,bin2str
def str2bin(ss):
    return bytes.fromhex(ss)

def bin2str(bb):
    return bb.hex()



# 2.0 list2bin,bin2list
def list2bin(ll):
    return bytes(ll)

def bin2list(bb):
    return list(bb)



# 3.0 list2str,str2list
def list2str(ll):
    return bytes(ll).hex()

def str2list(ss):
    bb = bytes.fromhex(ss)
    return list(bb)


# ------------------------------------------------------
ll = [0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38]
bb = list2bin(ll)
ss = list2str(ll)

ll2 = bin2list(bb)
ss2 = bin2str(bb)

ll3 = str2list(ss)
bb2 = str2bin(ss)

print(ll)
print(bb)
print(ss)
print(ll2)
print(ss2)
print(ll3)
print(bb2)
