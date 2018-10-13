from setuptools import setup, Extension

calc_module = Extension('calc_module', sources=["calc.c"])
setup(ext_modules=[calc_module])
