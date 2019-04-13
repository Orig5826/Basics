
import re


def calc_add_custon():
    while True:
        print('>> ', end='')

        content = input()
        if not isinstance(content, str):
            break
        if content == 'q':
            break

        # 对于：数字和运算符号的判断，暂没有想到合适的办法

        # 取消开头和结尾的空格
        content = content.strip()

        # re.split 和 str.split的区别在于
        # str.split仅能通过一个字符分割
        # re.split可以多个字符，且可以通过()来将分割用的字符也列举出来。功能更加强大
        formula = re.split(r'[\W+]+', content)  # 分隔符：空格，+
        # print(formula)
        result = sum(map(int, formula))
        print(result)


def calc_eval():
    while True:
        print('>> ', end='')

        content = input()
        if not isinstance(content, str):
            break
        if not content:
            continue
        if content == 'q':
            break

        # 嘿嘿... 这种方式有点不要脸哈
        result = eval(content)
        print(result)


calc_eval()
