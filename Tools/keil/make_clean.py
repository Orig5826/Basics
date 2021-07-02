"""
    2021-07-02 修改
"""

import shutil
import sys
import os
import re

def make_clean(current_path,re_rm_dirs,re_rm_files):
    reg_rm_files = re.compile(re_rm_files)

    for root, dirs, files in os.walk(current_path, topdown=False):
        for name in files:
            path = os.path.join(root, name)
            m = reg_rm_files.findall(path)
            if m != []:
                print('rmmove -> ',path)
                os.remove(path)
        
        for name in dirs:
            if name in re_rm_dirs:
                print('rmtree -> ', name)
                shutil.rmtree(name)

if __name__ == "__main__":
    # 1.0 待删除的文件夹名称（完全匹配）
    rm_dirs = r'Listings|Objects'
    # 2.0 待删除的文件名称（部分匹配）
    re_rm_files = r'uvguix|scvd'

    make_clean(".",rm_dirs,re_rm_files)
    
    # os.system('pause')
