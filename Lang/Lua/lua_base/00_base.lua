
-- --------------------------------------
-- ����ע��
print("Hello world!")

--[[
����ע�ͣ���ע������table�����׻���
--]]

--[=[
��ʱ��Ҳ�������ַ�ʽ�����ж���ע��
--]=]

a = 10
print(a)
print(a*1.1)
a = nil -- ��ֵnil���൱��ɾ����a
print(a)
print(b) -- δ��ֵ��Ĭ�Ͼ���nil

-- --------------------------------------
-- type���÷�
print(type("aaa"))
print(type(10.2*3))
print(type(print))
print(type(false))
print(type(nil))

-- ---------------------------------------
-- �����ַ�����ʹ�õ�or˫����
-- �����ַ�������һ���ַ���������
html = [[
<html>
<head>HTML TEST</head>
<body>
	<a href="http://www.baidu.com/">�ٶ�һ�£����֪��</a>
</body>
</html>
]]
print(html)

-- ע�⣺���������Բ�ͬ�ĵط�
print('21' + 6)	-- ���лὫ�ַ���'21'��������21�����м���
print("123".."abc")
print(type(123 .. 456)) -- �ַ����������ǲ��� .. ��

-- ʹ�� # �������ַ����ĳ���
print("�ַ����ĳ���Ϊ��", #"123abcd")


--[=[
-------------------------------------------------
			��table ������÷�ʾ��
Lua�е�table�������Ǹ����������顱
table[key]

��keyΪ�ַ�������Ҳ���Բ������·�ʽ���е���
table.key

-------------------------------------------------
--]=]

-- �ձ�
local tbl1 = {}
print(tbl1)

-- ֱ�ӳ�ʼ����
local tbl2 = {"apple","pear","orange"}
print(tbl2)
for k,v in pairs(tbl2) do
	-- ��ʱע�⣺���������Բ�ͬ�ĵط���Lua���е������Ǵ�1��ʼ��
	print(k..":"..v)
end
print("------------------------")


-- ���Ǳ䳤�ģ��ǹ̶����ȣ�
-- ͬʱ������һ�º������÷�
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

-- ����ͨ�����������ķ�ʽ���ݲ���
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
	����
- LuaĬ�϶���ȫ�֣��������ں����ڲ���
- ������ʹ�ùؼ���local������

������ʹ��local������
1. ����������ͻ
2. �����ٶȱ�ȫ�ֵĿ�
-------------------------------------------------
--]=]
a = 1
b = 2
print(a,b)
a,b = b,a -- ����
print(a,b)


-- �����ͬʱ��ֵ����
a,b,c = 4,5
print(a,b,c) -- �����value��nil����
a,b,c = 6,7,8,9
print(a,b,c) -- �����value��������
