import os
import shutil

bak_folder = '__backup__'

def dir_list():
    dirlist = os.listdir('.')
    dirlist2 = [dd for dd in dirlist if os.path.isfile(
        dd) and dd != 'code_change.py']
    return dirlist2

def code_change(infile_list, coding_src='gbk', coding_des='utf-8'):
    # 1.0 备份原文件
    if not os.path.exists(bak_folder):
        os.mkdir(bak_folder)

    for infile in infile_list:
        des_file = bak_folder + '\\' + infile
        if not os.path.exists(des_file):
            shutil.copyfile(infile, des_file)
            # 采用二级制方式读写
            with open (infile, 'rb') as pf:
                content = pf.read()
            # 将解码前和编码后的内容显示出来
            print(content)
            content = content.decode(coding_src).encode(coding_des)
            print(content)
            with open (infile, 'wb') as pf:
                pf.write(content)
            
            print('file [' + infile + '] backup & code_change finished!')


if __name__ == "__main__":
    dirlist = dir_list()
    # code_change(dirlist,'gbk','utf8')
    code_change(dirlist,'utf8','gbk')