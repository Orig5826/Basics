from distutils.core import setup, Extension


calc_module_module = Extension('_calc_module', # 该文件需要添加下划线，否则会和后面的冲突
                           sources=['calc_wrap.c', 'calc.c'],
                           )

setup ( name = 'calc_module',
        version = '0.1',
        author      = "SWIG Docs",
        description = """calc_module by swig & distutils""",
        ext_modules = [calc_module_module],
        py_modules = ["calc_module"],
        )
