"""
    # 2021-01-08 第一次成功解析，可能还存在其他未知问题。但目前基本都能识别了。后续发现新方案再修改

    PAT文件格式说明：
    | pattern | block | crc16 | fun_len_total | fun_symbol | fun_reference | other_codes |
    1. pattern 该部分为函数前32字节（默认32，可以通过命令修改）。其中重定向的字段使用..显示
    2. block 从pattern尾部开始算起，到..或者函数末尾结束。用于进行crc计算的字节个数。
    3. crc16 使用的crc16-ccitt-x25模式，注意下最终生成的高低字节即可
    4. fun_len_total 函数总长
    5. fun_symbol 函数符号（函数名）
    6. fun_reference 函数引用（调用的其他函数符号及其他信息）
    7. other_codes 除了pattern和crc计算使用到的code之外的其他剩余所有代码


【注意】
    使用该脚本前，需要先将flair相关的bin添加到环境变量中。
    最后将生成的sig文件放到ida的sig/arm目录下即可。ida中可以通过shift+f5打开相关界面，随后添加该sig文件即可
"""
import struct
import re
import sys
import os
import shutil


def pat_big2little_endian(line):
    """
        因使用keil封的库，在小端代码大端数据的情况下。
        配置了bigendian之后，则输出为大端代码。
        因此在生成pat文件之后，需要手动进行切换。

        # 2020-01-08 为了方便，CRC直接使用0000取代。对于小量代码够用。
    """

    # --------------------------------------------------
    # 1. pattern 部分大小端切换
    # --------------------------------------------------
    l_1 = re.findall("^[^ ]*",line)[0]
    l_2 = re.findall("[0-9A-F.]{2}",l_1)
    if l_2 == []:
        return l_1
    
    for i in range(0,len(l_2),2):
        l_2[i],l_2[i+1] = l_2[i+1],l_2[i]

    l_3 = ""
    for i in range(len(l_2)):
        l_3 += l_2[i]

    l_4 = line.replace(l_1,l_3)

    # --------------------------------------------------
    # 2. 修改CRC，在代码量不大的情况下。直接将CRC用0替换
    # --------------------------------------------------
    l_5 = re.split('[ ]',l_4,3)
    l_5[1] = '00'
    l_5[2] = '0000'
    
    length = len(l_5)
    l_6 = ''
    for i in range(length - 1):
        l_6 += l_5[i] + ' '
    l_6 += l_5[length - 1]
    
    # --------------------------------------------------
    # 输出当前行的修改结果
    # --------------------------------------------------
    return l_6


def pat_big2little_chage(filename, file_output_name):
    """
        生成中间文件
    """
    with open(filename,'r') as fr:
        data = fr.readlines()
        
    pat_data = ""
    for line in data:
        pat_data += pat_big2little_endian(line)

    with open(file_output_name,'w') as fw:
        fw.write(pat_data)

def sigmake(file_lib_in, file_sig_out=None):
    file_name = os.path.basename(file_lib_in)
    file_lib_name = file_name.split('.')[0]
    file_pat = file_lib_name + '.pat'
    file_pat_pat = file_pat + '.pat'
    if file_sig_out == None:
        file_sig = file_lib_name + '.sig'
    else:
        file_sig = file_sig_out

    os.system('pelf.exe -f ' + file_name + ' ' + file_pat)
    pat_big2little_chage(file_pat, file_pat_pat)
    os.system('sigmake.exe "-n' + file_lib_name + '" ' + file_pat_pat + ' ' + file_sig)

    if os.path.exists(file_pat):
        os.remove(file_pat)
    if os.path.exists(file_pat_pat):
        os.remove(file_pat_pat)

if __name__ == "__main__":
    argv = sys.argv
    argc = len(argv)

    if argc == 1:
        print('[param] "file.lib" ')
        print('[param] "file.lib" "file.sig"')
    elif argc == 2:
        file_in = argv[1]
        sigmake(file_in)
    elif argc == 3:
        file_in = argv[1]
        file_out = argv[2]
        sigmake(file_in,file_out)
    else:
        print("param is illegal!")
