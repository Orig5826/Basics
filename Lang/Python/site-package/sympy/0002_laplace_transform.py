
from sympy import *
t,x,y,s = symbols('t,x,y,s')
eq = 5*(1-exp(-t/1))
ret = solve(eq,[t])
print(ret)
# plot(eq,(t,0,5))
# ret = solve([0.7*exp(-t/0.2) + 5*(1-exp(-t/0.2))],[t])
# print(ret)
# ret = solve([x+2,y*2+1],[x,y])
# print(ret)
# ret = solve([x+2,y**2+1],[x,y])
# print(ret)


ret = laplace_transform(1,t,s)
print(ret)
ret = laplace_transform(t,t,s)
print(ret)
ret = laplace_transform(t**2,t,s)
print(ret)

r = limit(pow(1+1/x,x),x,oo)
print(r)
r = limit(pow(1+x,1/x),x,0)
pprint(r)
