
import json
"""
    在shell中可以命令行直接将某json文件内容格式化显示
    cat *.json | python -m json.tool
"""
ret = json.dumps({'Name':'Bob','Grades':{'Math':100,'Physics':100}},indent=4)
print(ret)

# ----------------------------------
# 文件解析
fname = './res/trans.json'
print('-> 解析文件内容:',fname)

with open(fname,encoding='utf-8') as ff:
    fp_json = ff.read()
ff.close()

print('-------------------------')
js = json.loads(fp_json)
disp = json.dumps(js,indent=4)
print(disp)
print('-------------------------')
result = '\n'.join(js['basic']['explains'])
print(result)
print('-------------------------')
