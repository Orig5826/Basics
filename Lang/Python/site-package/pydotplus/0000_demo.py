
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


graph = Dot(rankdir='TB')
graph.set_type('digraph')
graph.set_name('Dot_Demo')

data = {'start': '开始',
        '1': '第一步',
        '2': '第二步',
        '3': '第三步',
        'end': '结束'}

node_name = tuple(data.keys())

graph.set_node_defaults(shape='record')
# 将结点和边关联
i = 0
for key, value in data.items():
    if i == 0 or i == len(data)-1:
        # node label中{}的作用，相当于开辟新的作用域，且垂直水平方向会相对于当前来进行切换
        """
        digraph G {
            node [shape=record];
            1 [label="<left>左|{<top>上|<buttom>下}|<right>右"];
        }
        """
        node = Node(key, shape='ellipse')
    else:
        label_value = "\"<data> " + value + "|<next>\""
        node = Node(key, label=label_value)
    
    # print(node.get_name())
    # node.set_shape('record')  # 直接配置默认了set_node_defaults
    graph.add_node(node)

    if i == 0:
        i += 1
        continue
    elif i == 1:
        edge = Edge(node_name[i-1], node.get_name()+':data')
    elif i == len(data) - 1:
        edge = Edge(node_name[i-1]+':next', node.get_name())
    else:
        edge = Edge(node_name[i-1]+':next', node.get_name()+':data')
    graph.add_edge(edge)
    print(edge.to_string())
    i += 1


# 2019.04.28 目前唯一的问题是不知道如何实现Edge
# start:b2 -> 1:b1;
# 2019.04.28(20:52)哈哈，已经解决了
# 原来Edge只需要传入node_name即可，没必要传入Node类
# edge = Edge(node_name[3]+':next', node_name[1]+':data')
# graph.add_edge(edge)
# print(edge.to_string())


ret = graph.write_raw("demo.dot")
if ret is not True:
    print('生成demo.dot失败')
ret = graph.write_svg("graph.svg")
if ret is not True:
    print('生成graph.svg失败')

os.system("graph.svg")
