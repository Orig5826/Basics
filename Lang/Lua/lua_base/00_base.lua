
-- --------------------------------------
-- 单行注释
print("Hello world!")

--[[
多行注释，若注释中有table则容易混淆
--]]

--[=[
有时候也采用这种方式来进行多行注释
--]=]

a = 10
print(a)
print(a*1.1)
a = nil -- 赋值nil，相当于删除了a
print(a)
print(b) -- 未赋值，默认就是nil

-- --------------------------------------
-- type的用法
print(type("aaa"))
print(type(10.2*3))
print(type(print))
print(type(false))
print(type(nil))

-- ---------------------------------------
-- 单行字符串，使用单or双引号
-- 多行字符串，（一块字符串）如下
html = [[
<html>
<head>HTML TEST</head>
<body>
	<a href="http://www.baidu.com/">百度一下，你就知道</a>
</body>
</html>
]]
print(html)

-- 注意：和其他语言不同的地方
print('21' + 6)	-- 其中会将字符串'21'当作数字21来进行计算
print("123".."abc")
print(type(123 .. 456)) -- 字符串的连接是采用 .. 的

-- 使用 # 来计算字符串的长度
print("字符串的长度为：", #"123abcd")


--[=[
-------------------------------------------------
			表table 的相关用法示例
Lua中的table本质上是个“关联数组”
table[key]

若key为字符串，则也可以采用如下方式进行调用
table.key

-------------------------------------------------
--]=]

-- 空表
local tbl1 = {}
print(tbl1)

-- 直接初始化表
local tbl2 = {"apple","pear","orange"}
print(tbl2)
for k,v in pairs(tbl2) do
	-- 此时注意：和其他语言不同的地方是Lua表中的索引是从1开始的
	print(k..":"..v)
end
print("------------------------")


-- 表是变长的（非固定长度）
-- 同时，参杂一下函数的用法
function display(tbl)
	for k,v in pairs(tbl) do
		print(k..":"..v)
	end
	print("------------------------")
end

a = {}
for i = 1,10 do
	a[i] = i * 10
end
display(a)

-- 可以通过匿名函数的方式传递参数
function display_lambda(tbl,fun)
	for k,v in pairs(tbl) do
		print(fun(k,v))
	end
	print("------------------------")
end
display_lambda(a,
function(key,value)
	return key..":"..value;
end
);


--[=[
-------------------------------------------------
	变量
- Lua默认都是全局，即便是在函数内部。
- 除非你使用关键字local来声明

尽量多使用local变量：
1. 避免命名冲突
2. 访问速度比全局的快
-------------------------------------------------
--]=]
a = 1
b = 2
print(a,b)
a,b = b,a -- 交换
print(a,b)


-- 多变量同时赋值操作
a,b,c = 4,5
print(a,b,c) -- 不足的value用nil补齐
a,b,c = 6,7,8,9
print(a,b,c) -- 多余的value将被忽略
