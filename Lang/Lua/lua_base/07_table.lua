
tbl = {"d","a","e","b","c"}
-- ��������˳���ѡ��
-- ��һ��������ָ���ָ���
-- �ڶ���������start
-- ������������end
print(table.concat(tbl,"-",2,4))
table.insert(tbl,1,":")
print(table.concat(tbl))
table.remove(tbl,1)
print(table.concat(tbl))
table.sort(tbl)
print(table.concat(tbl))
