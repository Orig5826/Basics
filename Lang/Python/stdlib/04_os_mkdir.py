import os


def mkdir(path):
    """[mkdir]
    用于新建目录
    """
    try:
        if not os.path.exists(path):
            os.mkdir(path)
            print("Create \"%s\" succeed!" % path)
        else:
            print("Failed! -> Because \"%s\" is exist!" % path)
    except:
        print("mkdir failed!")


mkdir("./txt/")
print(mkdir.__doc__)
