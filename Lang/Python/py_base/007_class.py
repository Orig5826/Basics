#! python

# -----------------------------------
# 			Class
# ----------------------------------
class Complex:
	r = 0.0
	i = 0.0
	#str = []		#1.0 str 观察现象哦~
					# 小结：放在这里，在追加的时候，不同的对象也会叠加
	
	# 相当于C++ 的构造函数
	def __init__(self,real,imag):
		#self.r = real
		#self.i = imag
		self.str = []	#2.0 str 观察现象哦~
						#小结：放在这里，不同的对象，各自追加自己的，不叠加
		pass
		print("Hehe")
	def change(self,real,imag):
		self.r = real
		self.i = imag
		self.str.append("{0:.2f} + {1:.2f}j".format(self.r,self.i))
		print("--------------")
	def real(self):
		return self.r
	def imag(self):
		return self.i
	def show(self):
		print( "{0:.2f} + {1:.2f}j".format(self.r,self.i) )

	# 相当于C++的 运算符重载
	def __add__(self,c):
		s = Complex(0.0,0.0)
		s.r = self.r + c.r
		s.i = self.i + c.i
		return s
	def __sub__(self,c):
		s = Complex(0.0,0.0)
		s.r = self.r - c.r
		s.i = self.i - c.i
		return s
	def __mul__(self,c):
		s = Complex(0.0,0.0)
		s.r = self.r * c.r - self.i * c.i
		s.i = self.r * c.i + self.i * c.r
		return s
	def __truediv__(self,c):
		s = Complex(0.0,0.0)
		denomi = c.r*c.r + c.i*c.i
		s.r = (self.r * c.r + self.i * c.i)/denomi
		s.i = (self.i * c.r - self.r * c.i)/denomi
		return s

c = Complex(3,5)
d = Complex(7,9)

c.change(2,4)
c.show()
print(c.str)

d.change(8,6)
d.show()
print(d.str)
c.show()
print(c.str)

c.change(1,2)
print(c.str)

c.show()
d.show()
print("------------------")
s = c + d
s.show()
c.show()
d.show()

s = c - d
s.show()
c.show()
d.show()

s = c * d
s.show()
c.show()
d.show()

s = c / d
s.show()
c.show()
d.show()