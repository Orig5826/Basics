
--[=[------------------------------------------------
	泛型 for 迭代器
--]=]
tbl = {"apple","orange","banana","watermelon"}
for k,v in ipairs(tbl)
do
	print(k,v)
end

--[=[------------------------------------------------
	无状态迭代器
--]=]
function power(iterator_max_count,current_number)
	if current_number < iterator_max_count
	then
		current_number = current_number + 1
		return current_number,current_number*current_number
	end
end

for i,n in power,5,0
do
	print(i,n)
end
