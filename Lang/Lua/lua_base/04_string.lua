
str = "Hello world! I am Bruce. "
print(string.upper(str))
print(string.lower(str))
print(string.gsub(str,"Bruce","Bluce"))
print(string.find(str,"world"))
print(string.reverse(str))
print(string.format("字符串：%s",str))
print(string.len(str))
print(string.rep(str,2))  -- 重复

--[=[
	匹配模式详细参数
可以参考：https://www.runoob.com/lua/lua-strings.html
--]=]
print(string.match(str,"o")) -- 寻找匹配1
print(string.match(str,"%a+! %a+")) -- 寻找匹配2

print(string.char(0x61,0x62,0x63)) -- 将整型转为字符并连接
print(string.char(97,98,99))
print(string.byte("abc")) -- 转换字符为整型，默认返回第一个
print(string.byte("abc",3)) -- 指定返回第三个字符的整型值

-- 迭代器
for word in string.gmatch(str, "%a+") do 
	print(word)
end
