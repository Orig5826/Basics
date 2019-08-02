-- 文件名为 module.lua
-- 定义一个名为 module 的模块
module = {}

-- 定义一个常量
module.constant = 10

-- 定义一个函数
function module.display_table(tbl)
	for k,v in pairs(tbl)
	do
		print(k,v)
		-- io.write(k,v)
	end
end


-- 注意：这样定义，则是个全局的
-- 除非添加local关键字，才能变为该module私有的
function display_table(tbl)
	for k,v in pairs(tbl)
	do
		print(k,v)
		-- io.write(k,v)
	end
end


return module
