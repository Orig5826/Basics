
--[=[----------------------------------------
	加载模块的方式1
--]=]
require("module")

print(module.constant)
a = {"a","b","c"}
-- display_table(a)  -- 测试全局的
module.display_table(a) -- 测试模块的

--[=[----------------------------------------
	加载模块的方式2
--]=]
m = require("module")
print(m.constant)
