# ----------------------------
# 1.0 学习一下sympy的使用
# ----------------------------

import sympy
from sympy import *
## print(dir(sympy))
rc,t = symbols('rc t')
f = Function('f')

s = rc * f(t).diff(t) + f(t)
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