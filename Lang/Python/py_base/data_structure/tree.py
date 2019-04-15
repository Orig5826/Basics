from collections import deque
import random
import time
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

    def __lt__(self,other):
        return True if self._value < other._value else False

    def __eq__(self,other):
        return True if self._value == other._value else False

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

    @type_check
    def append(self, value):
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
                    node.parent = cur
                    return
                elif cur.right is None:
                    cur.right = node
                    node.parent = cur
                    return
                else:
                    # 若左右都不为空，则给判断列表加入子树，继续进行子树判断
                    queue.append(cur.left)
                    queue.append(cur.right)

    """
    # 2019.04.14 23:44:00
    # 之所以屏蔽，这种函数多重包含的原因是
    # 遍历的时候向使用生成器 yield 
    # 但是似乎，函数嵌套了之后，yield会出现和预期不一致的现象？
    # 
    def traversal(self, mode='breadth'):
        if self._root is None:
            print('空树')
        else:
            if mode == 'breadth':
                print('----- 广度优先遍历 -----', end='\n')
                self.__traversal_breadth_first()
            elif mode in ('depth', 'preorder', 'inorder', 'postorder'):
                print('----- 深度优先遍历 -----', end=' ')
                self.__traversal_depth_first(mode)
            else:
                raise ValueError('类"{}" -> 方法"{}" -> 参数"{}" 无效'.format(
                    self.__class__.__name__, self.traversal.__name__, mode))

    def __traversal_depth_first(self, mode='preorder'):
        if mode == 'preorder' or mode == 'depth':
            self.__traversal_preorder(self._root)
        elif mode == 'inorder':
            self.__traversal_inorder()
        elif mode == 'postorder':
            self.__traversal_postorder()
        else:
            raise ValueError('类"{}" -> 方法"{}" -> 参数"{}" 无效'.format(
                self.__class__.__name__, self.__traversal_depth_first.__name__, mode))
        print('')
    """

    def traversal_breadth_first(self):
        """
            广度优先遍历
        """
        queue = deque()
        queue.append(self._root)
        while queue:
            cur = queue.popleft()
            if cur is None:
                continue
            # print(str(cur) + ' -> ', end='')
            yield cur
            queue.append(cur.left)
            queue.append(cur.right)
        # print('')

    # def __traversal_preorder(self, root):
    def traversal_preorder(self):
        """
            深度优先遍历 -> 前序遍历
        """
        # 递归实现
        # if root is None:
        #     return
        # print(root, end=' -> ')
        # self.__traversal_preorder(root.left)
        # self.__traversal_preorder(root.right)

        # 非递归实现
        # print('<前序遍历>')
        queue = deque()
        cur = self._root
        while queue or cur:
            if cur:
                # print(cur, end=' -> ')
                yield cur
                queue.append(cur)
                cur = cur.left
            else:
                cur = queue.pop()
                cur = cur.right

    def traversal_inorder(self):
        """
            深度优先遍历 -> 中序遍历
        """
        # 非递归实现
        # print('<中序遍历>')
        queue = deque()
        cur = self._root
        while queue or cur:
            if cur:
                queue.append(cur)
                cur = cur.left
            else:
                cur = queue.pop()
                # print(cur, end=' -> ')
                yield cur
                cur = cur.right

    def traversal_postorder(self):
        """
            深度优先遍历 -> 后序遍历
        """
        # print('<后序遍历>')
        # """
        #     # 方法一
        #     # 借助的思想：
        #     # 前序遍历：根 -> 左 -> 右
        #     # 后续遍历: 左 -> 右 -> 根 （相当于 前序遍历的先右后左 情况，的逆序）
        #     # 因此：
        #     # 1. 前序遍历，先右后左
        #     # 2. 利用一个新栈，进行逆序
        # """
        # queue_temp = deque()

        # queue = deque()
        # cur = self._root
        # while queue or cur:
        #     if cur:
        #         queue_temp.append(cur)

        #         queue.append(cur)
        #         cur = cur.right
        #     else:
        #         cur = queue.pop()
        #         cur = cur.left

        # for i in range(len(queue_temp)):
        #     print(queue_temp.pop(), end=' -> ')

        """
            # 方法二
            # 借助的思想：
            # 加一个判断量，若当前节点的左右节点都已经被访问过了，那么也需要直接打印
            # 为什么直接cur.right==pre也可以呢？ ----- 这种说法错误，若某节点仅存在左子树的时候，就不行了
            # 其实是和我压栈的顺序相关的 
            # 右子树后出，因此上一次弹出的子树为右子树的时候，就可以证明左子树必定访问过了
        """
        queue = deque()
        queue.append(self._root)
        pre = None
        while queue:
            cur = queue[-1]     # 获取栈顶元素
            # if (cur.left is None and cur.right is None) or\
            #         (pre is not None and (cur.right == pre)):     # 此法考虑不够全面
            if (cur.left is None and cur.right is None) or\
                    (pre is not None and (cur.left is pre or cur.right is pre)):

                # print(cur, end=' -> ')
                yield cur
                cur = queue.pop()
                pre = cur
            else:
                if cur.right:
                    queue.append(cur.right)
                if cur.left:
                    queue.append(cur.left)

if __name__ == '__main__':
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

    # 必须执行一下，list(ret)才能真正实现map的功能？为什么？
    # 因为python3 之后，map返回的是一个迭代对象
    ret = map(t.append, range(1, 11))
    list(ret)


    trav = t.traversal_breadth_first()
    print('广度优先遍历: ', list(trav))

    trav = t.traversal_preorder()
    print('前序遍历: ', list(trav))

    trav = t.traversal_inorder()
    print('中序遍历: ', list(trav))

    trav = t.traversal_postorder()
    print('后序遍历: ', list(trav))
