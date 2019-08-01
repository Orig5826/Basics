
function max(num1,num2)
	-- 函数基础
	if num1 > num2 then
		return num1
	else
		return num2
	end
end
print(max(3,5))
print("---------------------------")

function maxmum(tbl)
	-- 多返回值函数
	local index = 1
	local value = tbl[index]
	for k,v in pairs(tbl) do
		if v > value then
			index = k
			value = v
		end
	end
	return index,value
end
print(maxmum({11,13,15,16,12}))
print("---------------------------")

function average(...)
	local result = 0
	-- arg为一个表，局部变量
	local arg={...}
	for k,v in ipairs(arg) do
		result = result + v
	end
	-- select("#",...) 返回可变参数的长度
	-- select(n,...) 用于访问n到select("#",...)的参数
	print("数据个数："..select("#",...))
	return result/#arg
end
print("求均值："..average(1,2,3,4,5,6,7,8,9,10))
print("---------------------------")
