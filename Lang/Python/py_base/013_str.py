# 本文件中的示例都是str相关的操作
# 而对于bytes，很多Method都是类似的，用的时候可以类比，因此不再单独列出
# 


def default():
    # ---------------------------------------------------------------------------------
    ss = 'str_test ->> hello world! I am July Baker! this is a great idea!\
    1... 2... 3... ok! (^.^)好的'
    print(len(ss))

    # ------------------------------------------------------------------
    # 居中显示 -> 若设定的长度超过了字符串长度，默认空格填充
    r = ss.center(128, '-')
    print(r)
    # 左对齐
    r = ss.ljust(128, '<')
    print(r)
    # 右对齐
    r = ss.rjust(128, '>')
    print(r)
    # 用0左填充
    r = ss.zfill(128)
    print(r)

    # format
    r = '{1} + 0x{0:02d} = {2:f}'.format(0x01, 2, 1+2)
    print('format格式化的应用：', r)
    # format_map
    # ...

    # ----------------------------------------------------------------
    # 显示字符串中字串在范围内出现的不重叠次数
    r = ss.count('..')
    print('..出现的不重叠次数', r)

    # 若字符串以指定后缀结尾，则返回True
    r = ss.endswith('的')
    print('是否以"的"结尾？', r)
    #
    r = ss.startswith('的')
    print('是否以"的"开头？', r)

    # 返回-1表示没有找到。若找到，则返回最小索引值
    r = ss.find('july')
    print('查找"july"', r)
    r = ss.rfind('...')
    print('rfind返回最高索引', r)

    # 类似find，但找不到会报ValueError
    r = ss.index('July')
    print('查找"July"', r)
    r = ss.rindex('...')    # 类似rfind

    # -----------------------------------------------------------------
    # 以 bytes 对象形式返回字符串编码版本
    r = ss.encode('utf_8')
    print(type(r), r)

    # 首字符变为大写，其他都变为小写
    r = ss.capitalize()
    print(r)

    # 类似于lower()，但是功能更加夸张，可以查看python文件说明理解
    r = ss.casefold()
    print(r)
    r = ss.lower()
    print(r)
    r = ss.upper()
    print(r)

    # 所有tab都被size个空格所代替
    r = ss.expandtabs(16)
    print(r)

    # 所有单词首字母大小，类似于标题
    r = ss.title()
    print(r)

    r = ss.swapcase()
    print(r)

    # ---------------------------------------------------------------------------------
    # '好的list'isalpha() ->  True
    # 'asdf.123'isalpha() -> False
    r = ss.isalpha()
    print('是否都为字符？', r)
    r = ss.isascii()
    print('是否都为assic码(U+0000 =< x <= U+007F)？', r)

    # 数字判断
    r = '0123'.isdecimal()
    print(r)
    r = '1765'.isdigit()
    print(r)
    r = '123Ⅱ一二叁亿'.isnumeric()
    print(r)

    # ?
    # r = ss.isidentifier()

    # ?
    # r = ss.maketrans()
    # r = ss.translate()


    # 好理解的就不打印了
    r = ss.islower()
    r = ss.isprintable()
    r = ss.isspace()
    r = ss.istitle()

    # ----------------------------------------------------------------------------
    # 返回删除前导字符的字符串副本
    r = ss.lstrip('-> _tsre')
    print(r)
    r = ss.rstrip('好的()^. 123ok!')
    print(r)
    r = ss.strip('->_tsre好的()^. 123ok!')
    print(r)

    # -----------------------------------------------------------------------------
    r = '-'.join('JulyBaker')
    print(r)
    # 从第一次出现'is'的地方分割为3-tuple
    r = ss.partition('is')
    print(r)
    r = ss.rpartition('is')
    print(r)

    # 默认从空格分开，maxsplit=-1分割字符串全部(即没有次数限制)，若指定maxsplit则分割指定次数
    r = ss.rsplit()
    print(r)
    r = ss.split()
    print(r)

    r = ss.replace('...', '、')
    print(r)

    string = '''title
I am Bruce!
(^o^)'''
    r = string.splitlines()
    print(r)

# -------------------------------------------------------------------------
# 示例


def demo():
    r = '192.168.1.0'.split('.')
    print(r)
    r = '.'.join(r)
    print(r)


if __name__ == "__main__":
    default()
    # demo()
