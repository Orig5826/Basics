
# with open('file.test.txt',) as f:
    #read_file = f.read()
# print(read_file)
# f.closed 
# ------------------------------------------
f = open('file.test.txt','r+')
i = 0
for line in f:
    print(i,line,end='')
    i+=1
print()

value = ('the answer', 42)
s = str(value)          # convert the tuple to string

f.write(s)
f.close()
# ------------------------------------------
