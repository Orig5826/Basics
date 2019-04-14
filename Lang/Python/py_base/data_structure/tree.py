from collections import deque
import random
import sys


class Node(object):
    # 限制class 的属性
    # 仅对当前类有效，对继承的子类无效
    __slots__ = ('_value', '_parent', '_left', '_right')

    def __init__(self, value=None):
        self._value = value
        self._parent = None
        self._left = None
        self._right = None

    def type_check(fun):
        def type_check_wapper(self, *args, **kw):
            if len(args) != 1 or not isinstance(*args, Node):
                raise ValueError('类"{}" -> 方法"{}" -> 参数"{}" 无效'.format(
                    self.__class__.__name__, fun.__name__, args))
            fun(self, *args, **kw)
        return type_check_wapper

    def __str__(self):
        return str(self._value)
    __repr__ = __str__

    @property
    def value(self):
        return self._value

    @value.setter
    def value(self, value):
        self._value = value

    @property
    def parent(self):
        return self._parent

    @parent.setter
    @type_check
    def parent(self, parent):
        self._parent = parent

    @property
    def left(self):
        return self._left

    @left.setter
    @type_check
    def left(self, left):
        self._left = left

    @property
    def right(self):
        return self._right

    @right.setter
    @type_check
    def right(self, right):
        self._right = right


class Tree(object):
    def __init__(self, root=None):
        # 添加一个没有数据的 HEAD
        self._root = root

    def __str__(self):
        return str(self._root)
    __repr__ = __str__

    def type_check(fun):
        def type_check_wapper(self, *args, **kw):
            if len(args) != 1 or not isinstance(*args, int):
                raise ValueError('类"{}" -> 方法"{}" -> 参数"{}" 无效'.format(
                    self.__class__.__name__, fun.__name__, args))
            fun(self, *args, **kw)
        return type_check_wapper

    # @type_check
    def add(self, value):
        node = Node(value)
        if self._root is None:
            self._root = node
        else:
            queue = deque()
            queue.append(self._root)
            while queue:
                cur = queue.popleft()
                if cur.left is None:
                    cur.left = node
                    return
                elif cur.right is None:
                    cur.right = node
                    return
                else:
                    # 若左右都不为空，则给判断列表加入子树，继续进行子树判断
                    queue.append(cur.left)
                    queue.append(cur.right)

    def traversal(self):
        if self._root is None:
            print('Tree is None')
        else:
            self.__traversal_depth_first()

    def __traversal_depth_first(self):
        """
            深度优先遍历
        """
        self.__traversal_preorder(self._root)
        print('')

    def __traversal_breadth_first(self):
        """
            广度优先遍历
        """
        pass

    def __traversal_preorder(self, root):
        """
            深度优先遍历 -> 前序遍历
        """
        if root is None:
            return
        print(root, end=' -> ')
        self.__traversal_preorder(root.left)
        self.__traversal_preorder(root.right)

    def __traversal_inorder(self):
        """
            深度优先遍历 -> 中序遍历
        """
        pass

    def __traversal_postorder(self):
        """
            深度优先遍历 -> 后序遍历
        """
        pass


# ----------------------------------------------
# n = Node('root')
# print(n)

# n2 = Node('parent_text')
# n.parent = n2
# print(n.parent)

# n3 = Node('left_test')
# n.left = n3
# print(n.left)

# n4 = Node('right_test')
# n.right = n4
# print(n.right)

# ----------------------------------------------
t = Tree()
t.traversal()

ret = map(t.add, [0, 1, 2, 3, 4, 5, 6, 7, 8])
# 必须执行一下，list才能真正实现map的功能？为什么？
list(ret)
t.traversal()

t.add(9)
t.traversal()
