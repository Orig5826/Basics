
-- while循环
a = 10
while( a ~= 0) -- 不等号注意下：~=
do
	-- 在循环中我就顺便把if语言也说了
	if(a%2 == 0)
	then
		print("a="..a)
	end
	a = a - 1
end
print("---------------------------")

-- for循环(数值) 见下
-- for循环(泛型) 见table相关说明
for i = 10,1,-1 do
	print("i="..i)
	-- 在循环中我就顺便把if语言也说了
	if(i%2 == 0)
	then
		print("偶数")
	else
		print("奇数")
	end
end
print("---------------------------")

-- repeat循环
a = 10
repeat
	print("a="..a)
	-- 在循环中我就顺便把if语言也说了
	if(a == 2)
	then
		print("2222222")
	elseif(a == 5)
	then
		print("5555555")
	else
		print("???")
	end
	a = a - 1
until a == 0
