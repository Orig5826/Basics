"""
    2020-06-05 用于递归卸载pip安装的第三方库。
    这个脚本是从网上学来的，不小心忘记出处了。

    备注：
    个人觉得该脚本还存在一个问题，比如依赖的库不能直接删除，
而是应该先判断该依赖库是否还被其他模块依赖。若存在，则不能删除。
"""
import os

def check_dependents(module_name):
    """
    查看一个模块的依赖
    :param module_name: 模块名
    :return: module_name 所依赖的模块的列表
    """
    with os.popen('pip show %s' % module_name) as p:
        dependents = p.readlines()
        if not len(dependents):
            return None
        # dependents = dependents[-1]
        dependents = dependents[-2]
        dependents = dependents.split(':')[-1].replace(' ', '').strip()
        # print("---------- Requires -----------")
        # print(dependents)
        if dependents:
            dependents = dependents.split(',')
        else:
            dependents = None
        return dependents


def remove(module_name):
    """
    递归地卸载一个模块
    :param module_name: 模块名称
    :return: None
    """
    dependents = check_dependents(module_name)
    if dependents:
        for package in dependents:
            remove(package)
    print('----- %s 开始卸载 -----' % module_name)
    # os.system('pip uninstall -y %s' % module_name)
    print('----- %s 卸载完成 -----\n' % module_name)


if __name__ == '__main__':
    pkg_name = input('请输入要卸载的第三方模块包: ')
    remove(pkg_name)
