"""
    adjacency matrix 
"""
tag = ['A', 'B', 'C', 'D', 'E', 'F']
g = [[0, 1, 1, 0, 0, 1],
     [0, 0, 1, 1, 0, 0],
     [0, 0, 0, 1, 0, 0],
     [0, 0, 1, 0, 0, 0],
     [0, 0, 0, 1, 0, 1],
     [0, 0, 1, 0, 0, 0],
     ]


def breadth_first_search(graph, start='A'):
    tag_count = len(tag)
    # 利用list 实现队列
    queue = [start]
    access = [start]
    while True:
        if queue:
            item = queue.pop()
            index = tag.index(item)
            for i in range(tag_count):
                if graph[index][i] == 1 and tag[i] not in access:
                    queue.insert(0, tag[i])
                    access.append(tag[i])
        else:
            # break
            # 查看还有哪个节点没有被访问
            left = set(tag) - set(access)
            if left:
                left = list(left)
                left.sort()
                item = left[0]
                queue.insert(0, item)
                access.append(item)
            else:
                break
    return access


def depth_first_search(graph, start='A'):
    tag_count = len(tag)
    # 利用list 实现栈
    stack = [start]
    access = [start]
    while True:
        if stack:
            item = stack.pop()
            if item not in access:
                access.append(item)
            index = tag.index(item)
            for i in range(tag_count):
                if graph[index][i] == 1 and tag[i] not in access:
                    stack.append(tag[i])
        else:
            # break
            # 查看还有哪个节点没有被访问
            left = set(tag) - set(access)
            if left:
                left = list(left)
                left.sort()
                item = left[0]
                stack.append(item)
            else:
                break
    return access


result = breadth_first_search(g, 'A')
print(result)

result = depth_first_search(g, 'A')
print(result)
