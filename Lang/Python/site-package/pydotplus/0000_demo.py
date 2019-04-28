
"""
import pydotplus
dot_data ='''
digraph G{
    start [label="开始"];
    end [label="结束"];
    start -> end;
}
'''
graph = pydotplus.graph_from_dot_data(dot_data)
# graph.write_svg("graph.svg")

# png和jpg生成的中文是乱码，不知道为啥。svg没有乱码问题
graph.write_png("graph.png")

# 将dot源码写入文件"demo.dot"
ret = graph.write_raw("demo.dot")
print(ret)  #返回True
"""

import pydotplus
import sys
import os
from pydotplus import graph_from_dot_data
from pydotplus import Dot, Node, Edge


graph = Dot(rankdir='LR')
graph.set_type('digraph')
graph.set_name('Dot_Demo')

data = {'start':'开始',
        '1':'第一步',
        '2':'第二步',
        '3':'第三步',
        'end':'结束'}

dot_list = []

# 将结点和边关联
i = 0
for key, value in data.items():
    if i == 2:
        node = Node(key, label="{<b1> " + value + "|<b2>}", shape='record')
    else:
        node = Node(key, label="{<b1> " + value + "|<b2>}", shape='record')
    print(node.to_string())
    dot_list.append(node)

    if i != 0:
        edge = Edge(old_node, node)
        print(edge.to_string())
        graph.add_edge(edge)
    
    graph.add_node(node)
    old_node = node
    i += 1

# 2019.04.28 目前唯一的问题是不知道如何实现Edge
# start:b2 -> 1:b1;
edge = Edge(dot_list[3], dot_list[1])
print(edge.to_string())
graph.add_edge(edge)


ret = graph.write_raw("demo.dot")
if ret != True:
    print('生成demo.dot失败')
ret = graph.write_svg("graph.svg")
if ret != True:
    print('生成graph.svg失败')

os.system("graph.svg")
