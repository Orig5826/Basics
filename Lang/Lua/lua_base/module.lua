-- �ļ���Ϊ module.lua
-- ����һ����Ϊ module ��ģ��
module = {}

-- ����һ������
module.constant = 10

-- ����һ������
function module.display_table(tbl)
	for k,v in pairs(tbl)
	do
		print(k,v)
		-- io.write(k,v)
	end
end


-- ע�⣺�������壬���Ǹ�ȫ�ֵ�
-- �������local�ؼ��֣����ܱ�Ϊ��module˽�е�
function display_table(tbl)
	for k,v in pairs(tbl)
	do
		print(k,v)
		-- io.write(k,v)
	end
end


return module
