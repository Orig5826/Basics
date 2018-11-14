
# 数字起始和总数
index_start = 1
index_count = 1000

# 将文件名为data_*.bin(*代表数字)的二级制文件
# 合并到同一个文件data_merge.bin中去
file_out = 'data_merge.bin'
with open(file_out,'wb') as file_merge:
    index_max = index_start + index_count - 1 

    for cnt in range(index_start,index_count+1):
        fname = 'data_' + '{}'.format(cnt) + '.bin'
        with open(fname,'rb') as ff:
            data = ff.read()
            file_merge.write(data)
        ff.close()
file_merge.close()
