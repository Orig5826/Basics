# ----------------------------
# 1.0 学习一下sympy的使用
# ----------------------------

from sympy import *
# x,y = symbols('x,y')
x = Symbol('x')
y = Symbol('y')


print('>> limit极限')
print(limit(sin(x)/x,x,0))


print('>> diff微分')
print(diff(x**3,x))
#1.
print(diff(x**3,x,1))
print(diff(x**3,x,2))
print(diff(x**3,x,3))
#2.diff 和1.等价
print(diff(x**3,x))
print(diff(x**3,x,x))
print(diff(x**3,x,x,x))


print('>> ingegrate积分')
print(integrate(6,x))
print(integrate(6,x,x))
print(integrate(6,x,x,x))

print('>> ingegrate定积分')
print(integrate(x,(x,0,3)))


print('>> eries级数展开')
s = exp(x).series(x,0,10)
# print(s)
pprint(s)


print('>> expand表达式展开')
expr = (sin(x + y)).expand(trig=True)
print(expr)
print('>> subs变量替换/求表达式的值')
print(expr.subs(x,pi/2))
print(expr.subs(y,pi))

print('>> factor提取公因式')
expr = x**2 + 2*x*y
pprint(factor(expr))


print('>> qsrt开平方根（以根号形式显示）')
pprint(sqrt(8))

print('>> Rational有理数(分子，分母)')
print(Rational(1,3))

print('>> latex打印公式')
l = latex(Integral(expr, (x, 0, pi)))
print(l)

print('>> factorial阶乘')
print(factorial(x))

print('>> 解方程 x**2-1=0')
ret = solve('x**2 - 1',x)
print(ret)


print('>> 矩阵运算')	# 可以带符号
M = Matrix(([1,2,3],[4,5,6],[7,8,9]))
N = Matrix(([1,x,0],[0,1,0],[0,0,1]))
pprint(M)
pprint(N)
pprint(M*N)
