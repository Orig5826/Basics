
str = "Hello world! I am Bruce. "
print(string.upper(str))
print(string.lower(str))
print(string.gsub(str,"Bruce","Bluce"))
print(string.find(str,"world"))
print(string.reverse(str))
print(string.format("�ַ�����%s",str))
print(string.len(str))
print(string.rep(str,2))  -- �ظ�

--[=[
	ƥ��ģʽ��ϸ����
���Բο���https://www.runoob.com/lua/lua-strings.html
--]=]
print(string.match(str,"o")) -- Ѱ��ƥ��1
print(string.match(str,"%a+! %a+")) -- Ѱ��ƥ��2

print(string.char(0x61,0x62,0x63)) -- ������תΪ�ַ�������
print(string.char(97,98,99))
print(string.byte("abc")) -- ת���ַ�Ϊ���ͣ�Ĭ�Ϸ��ص�һ��
print(string.byte("abc",3)) -- ָ�����ص������ַ�������ֵ

-- ������
for word in string.gmatch(str, "%a+") do 
	print(word)
end
