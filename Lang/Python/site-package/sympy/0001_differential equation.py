# ----------------------------
# 1.0 学习一下sympy的使用
# 2.0 针对rc延时电路做了简单的分析
# 3.0 求解某函数式极限
# ----------------------------

# from sympy import *
from sympy import symbols,Function,dsolve
from sympy import pprint,limit,cos,pi

## print(dir(sympy))
r,c,t = symbols('r,c t')
f = Function('f')

s = r*c * f(t).diff(t) + f(t)
r = dsolve(s,f(t))
pprint(r)

print("")
r = r.expand(power_exp=True)
pprint(r)

#----------------------------------------------
## 这个图也太简陋了点吧。。
## 果然直接使用sympy没法看
## 还得matplotlib啊

# t = symbols('t')
# plot(exp(t),(t,-4,1))

#----------------------------------------------
r = limit(cos(t-pi/2)/t,t,0)
print(r)

input("请按任意键退出")
