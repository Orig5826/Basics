
function max(num1,num2)
	-- ��������
	if num1 > num2 then
		return num1
	else
		return num2
	end
end
print(max(3,5))
print("---------------------------")

function maxmum(tbl)
	-- �෵��ֵ����
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
	-- argΪһ�����ֲ�����
	local arg={...}
	for k,v in ipairs(arg) do
		result = result + v
	end
	-- select("#",...) ���ؿɱ�����ĳ���
	-- select(n,...) ���ڷ���n��select("#",...)�Ĳ���
	print("���ݸ�����"..select("#",...))
	return result/#arg
end
print("���ֵ��"..average(1,2,3,4,5,6,7,8,9,10))
print("---------------------------")
