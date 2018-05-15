# -*- coding=utf_8 -*-
# --------------------------------------------
# 相对于difflib其他成员，
# 我比较习惯使用unified_diff
# 即 unified diff format
# --------------------------------------------
import difflib
import sys

# #比较两个字符串
# str1 = '''hello world!
# I am Bruce
# 2018.5.14
# '''.splitlines(keepends=True)
# str2 = '''Hello World!
# I am Bruce
# 2018/5/14
# '''.splitlines(keepends=True)
# diffresult = difflib.unified_diff(str1,str2)
# sys.stdout.writelines(diffresult)


def diff(file, file_patch):
    # 用于比较的两个文件
    # file = '01_urllib.py'
    # file_patch = '01_urllib_2.py'

    # 打开需要比较的文件
    with open(file, encoding='utf-8') as f:
        read_file = f.read()
    f.close()
    with open(file_patch, encoding='utf-8') as f:
        read_file_patch = f.read()
    f.close()

    # ---------------------------------------
    # unified_diff参数解析
    # @param n 表示在生成diff文件中，内容不同行的
    # 			显示其上下相同内容多少行
    #			n = 0 表示不显示相同行
    diffresult = difflib.unified_diff(read_file.splitlines(keepends=True), read_file_patch.splitlines(keepends=True),
                                      fromfile=file, tofile=file_patch, n=0)

    sys.stdout.writelines(diffresult)


if __name__ == "__main__":
    if(len(sys.argv) == 3):
        # 显示当前两个文件的比较结果
        diff(sys.argv[1], sys.argv[2])
    else:
        print("Usage: 08_difflib.py fromfile tofile")
