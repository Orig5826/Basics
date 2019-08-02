
tbl = {"d","a","e","b","c"}
-- 参数都是顺序可选的
-- 第一个参数是指定分隔符
-- 第二个参数是start
-- 第三个参数是end
print(table.concat(tbl,"-",2,4))
table.insert(tbl,1,":")
print(table.concat(tbl))
table.remove(tbl,1)
print(table.concat(tbl))
table.sort(tbl)
print(table.concat(tbl))
