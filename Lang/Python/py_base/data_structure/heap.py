from tree import Tree

class Heap(Tree):
    
    def __init__(self):
        """
            若子类不显示调用__init__，则默认调用父类__init__
            若子类显示调用__init__，则也必须调用父类__init__
        """
        # super(Heap,self).__init__()
        super().__init__()
    pass
    
    
if __name__ == '__main__':
    h = Heap()
    list(map(h.append,range(1,8)))

    trav = h.traversal_breadth_first()
    print('广度优先遍历: ', list(trav))

    trav = h.traversal_preorder()
    print('前序遍历: ', list(trav))

    trav = h.traversal_inorder()
    print('中序遍历: ', list(trav))

    trav = h.traversal_postorder()
    print('后序遍历: ', list(trav))
