#! python

# -----------------------------------
# 			抛出异常
# ----------------------------------
def divide(x, y):
	try:
		result = x / y
	except ZeroDivisionError:
		print("division by zero!")
	else:
		print("result is", result)
	# finally:
		# # 这个finally是用来做什么的？
		# print("executing finally clause")
		
		
if __name__ == "__main__":
	import sys
	divide(int(sys.argv[1]),int(sys.argv[2]))
	#divide(5,0)