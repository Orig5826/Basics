
-- whileѭ��
a = 10
while( a ~= 0) -- ���Ⱥ�ע���£�~=
do
	-- ��ѭ�����Ҿ�˳���if����Ҳ˵��
	if(a%2 == 0)
	then
		print("a="..a)
	end
	a = a - 1
end
print("---------------------------")

-- forѭ��(��ֵ) ����
-- forѭ��(����) ��table���˵��
for i = 10,1,-1 do
	print("i="..i)
	-- ��ѭ�����Ҿ�˳���if����Ҳ˵��
	if(i%2 == 0)
	then
		print("ż��")
	else
		print("����")
	end
end
print("---------------------------")

-- repeatѭ��
a = 10
repeat
	print("a="..a)
	-- ��ѭ�����Ҿ�˳���if����Ҳ˵��
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
