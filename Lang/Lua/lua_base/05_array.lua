
function table2_display(tbl)
	for i=1,#tbl do 
		for j=1,#tbl[1] do
			print(tbl[i][j])
		end
	end
end

-- ¶àÎ¬Êý×é
row_max = 3
col_max = 5
array = {}
for i=1,row_max do
	array[i] = {}
	for j=1,col_max do
		array[i][j] = (i-1) * col_max + (j-1)
	end
end
table2_display(array)
