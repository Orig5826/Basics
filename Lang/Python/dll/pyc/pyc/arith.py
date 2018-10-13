

def factorial(n):
    if n < 0:
        print("参数输入错误\n")
        return False
    if n == 0:
        print(1)
        return True
    ret = 1
    for i in range(1, n+1):
        ret *= i
    print(ret)

    return True
