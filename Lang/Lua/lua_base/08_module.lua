
--[=[----------------------------------------
	����ģ��ķ�ʽ1
--]=]
require("module")

print(module.constant)
a = {"a","b","c"}
-- display_table(a)  -- ����ȫ�ֵ�
module.display_table(a) -- ����ģ���

--[=[----------------------------------------
	����ģ��ķ�ʽ2
--]=]
m = require("module")
print(m.constant)
