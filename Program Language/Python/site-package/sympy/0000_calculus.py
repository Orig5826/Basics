# ----------------------------
# 1.0 学习一下sympy的使用
# ----------------------------

from sympy import *
x = Symbol('x')
y = Symbol('y')
r = limit(sin(x)/x,x,0)
print(r)

#		diff
print(diff(x**3,x))
#1.
print(diff(x**3,x,1))
print(diff(x**3,x,2))
print(diff(x**3,x,3))
#2.diff 和1.等价
print(diff(x**3,x))
print(diff(x**3,x,x))
print(diff(x**3,x,x,x))


r = integrate(6,x)
print(r)
r = integrate(6,x,x)
print(r)
r = integrate(6,x,x,x)
print(r)


##
r = integrate(x,(x,0,3))
print(r)

##----------------------------------
s = exp(x).series(x,0,10)
print(s)
pprint(s)

##
s = (sin(x + y)).expand(trig=True)
print(s)
s = s.subs(x,pi/2)
print(s)
s = s.subs(y,pi)
print(s)
##----------------------------------
f = Function('f')
s = -f(x).diff(x) + 2
r = dsolve(s,f(x))
print(r)