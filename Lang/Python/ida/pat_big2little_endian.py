
import struct
import re
import sys
import os


def pat_big2little_endian(line):
    """
        将前n字节进行大端转小端，2bytes
        n一般为32

        l_0 = re.split('[:^]',line,3)
        length_0 = len(l_0)
        if length_0 < 2:
            return line
        elif length_0 == 2:
            line = l_0[0] + ':' + l_0[1]
        else:
            line = l_0[0] + ':' + l_0[1] + '\n'
        # print(line)
    """

    l_1 = re.findall("^[^ ]*",line)[0]
    # print(l_1)
    l_2 = re.findall("[0-9A-F.]{2}",l_1)
    if l_2 == []:
        return l_1
    
    # print(l_2)
    for i in range(0,len(l_2),2):
        l_2[i],l_2[i+1] = l_2[i+1],l_2[i]
    # print(l_2)

    l_3 = ""
    for i in range(len(l_2)):
        l_3 += l_2[i]
    # print(l_3)

    l_4 = line.replace(l_1,l_3)
    return l_4


def pat_big2little_chage(filename):
    with open(filename,'r') as fr:
        data = fr.readlines()

    pat_data = ""
    for line in data:
        pat_data += pat_big2little_endian(line)

    # print(pat_data)
    with open(filename+'.pat','w') as fw:
        fw.write(pat_data)


if __name__ == "__main__":
    argc = len(sys.argv)
    if argc != 2:
        print("参数出错")
        sys.exit(-1)

    pat_big2little_chage(sys.argv[1])
