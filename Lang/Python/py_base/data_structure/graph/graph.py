
from pydotplus import Dot, Node, Edge
import os

# 该图配置
graph = {'A': ['B', 'C', 'F'],
         'B': ['C', 'D'],
         'C': ['D'],
         'D': ['C'],
         'E': ['F', 'D'],
         'F': ['C']
         }


def dotgraph(graph):
    __graph = Dot(rankdir='TB', fontname="Fangsong",
                  fontcolor='blue', label="有向图的示例")
    __graph.set_type('digraph')
    __graph.set_name('digraph_demo')

    __graph.set_node_defaults(
        fontname="Fangsong", style='filled', fillcolor='yellow')
    __graph.set_edge_defaults(fontname="Fangsong", color='black')

    for key, value in graph.items():
        # 若节点没有特殊label或者其他属性需求
        # 可以直接以节点名称显示
        # 直接标记方向，不用手动添加
        # node = Node(key)
        # __graph.add_node(node)
        for v in value:
            edge = Edge(key, v)
            __graph.add_edge(edge)

    ret = __graph.write_raw("demo.dot")
    if ret is not True:
        print('生成demo.dot失败')
    ret = __graph.write_svg("demo.svg")
    if ret is not True:
        print('生成graph.svg失败')

    # ret = __graph.write_png("demo.png")
    # if ret is not True:
    #     print('生成graph.png失败')

    return __graph


def find_path(graph, start, end, path=[]):
    """
        在图graph中找路径：
        从顶点start到顶点end
        走过的路径为path
    """
    path = path + [start]
    # 3.0 若当找到路径尾部，则返回该路径
    if start == end:
        return path
    # 1.0 判断当前顶点是否在图内
    if start not in graph.keys():
        return None
    for node in graph[start]:
        if node not in path:
            # 2.0 以当前顶点为起点，继续找路径
            newpath = find_path(graph, node, end, path)
            # 4.0 返回该路径
            if newpath:
                return newpath
    # 这个没有什么用吗 ？
    # return path


def find_all_paths(graph, start, end, path=[], paths=[]):
    path = path + [start]
    if start == end:
        paths.append(path)
        return path
    if start not in graph.keys():
        return None
    for node in graph[start]:
        if node not in path:
            newpaths = find_all_paths(graph, node, end, path)
    if paths == []:
        return None
    return paths


def find_short_path(graph, start, end, path=[]):
    path = path + [start]
    if start == end:
        return path
    if start not in graph.keys():
        return None

    shortpath = None
    for node in graph[start]:
        if node not in path:
            newpath = find_path(graph, node, end, path)
            if newpath:
                if not shortpath or len(newpath) < len(shortpath):
                    shortpath = newpath
    return shortpath


def breadth_first_search(graph, start):
    prenodes = [start]   # 前驱节点
    travel = [start]    # 已遍历过的顶点

    graph_sets = set(graph.keys())
    travel_sets = set(travel)
    while travel_sets < graph_sets:
        # 当前驱节点未空时退出
        while prenodes:
            nextnodes = []   # 当前顶点的邻接点
            for prenode in prenodes:
                for curnode in graph[prenode]:      # 遍历当前层的节点
                    if curnode not in travel:       # 判断当前层节点是否被访问国
                        travel.append(curnode)      # 若没有被访问过，则入队
                        nextnodes.append(curnode)   # 将当前节点追加如新的前驱节点队列
            # 当前层的节点都遍历完毕，则开始下一层的遍历
            prenodes = nextnodes
        travel_sets = set(travel)
        prenodes = list(graph_sets - travel_sets)
        if prenodes != []:
            travel.append(prenodes[0])
    return travel


def depth_first_search(graph, start):
    travel = []
    stack = [start]

    graph_sets = set(graph.keys())
    travel_sets = set(travel)
    while travel_sets < graph_sets:
        # 堆栈空的时候退出
        while stack:
            curnode = stack.pop()           # 栈顶弹出
            if curnode not in travel:       # 判断当前节点是否已经被访问过
                travel.append(curnode)      # 若没访问过，则入队
            for nextnode in graph[curnode]: # 遍历当前节点林邻接点
                if nextnode not in travel:  # 没有被访问过的顶点全部入栈
                    stack.append(nextnode)
        travel_sets = set(travel)
        leftnode = list(graph_sets - travel_sets)
        if leftnode != []:
            stack.append(leftnode[0])
    return travel


if __name__ == '__main__':
    result = find_path(graph, 'A', 'D')
    print("1. 路径查找结果：", result)
    print('---------------------------------')

    result = find_all_paths(graph, 'A', 'D')
    print("2. 全路径查找结果：", result)
    print("路径个数：", len(result))
    i = 1
    for path in result:
        print('路径{0:2d}为：{1}'.format(i, path))
        i += 1
    print('---------------------------------')

    result = find_short_path(graph, 'A', 'D')
    print("3. 查找最短路径：", result)
    print('---------------------------------')

    # 生成图表
    dotgraph(graph)

    # 广度优先遍历
    result = breadth_first_search(graph, 'A')
    print(result)

    # 深度优先遍历
    result = depth_first_search(graph, 'F')
    print(result)
