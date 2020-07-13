from setuptools import setup,find_packages
from Cython.Build import cythonize

setup(
    name = "demo",
    version = "1.0",
    packages = find_packages(),
    author = "wenjf",
    author_email = "Orig5826@163.com",
    python_requires=">=3.7",
    install_requires=["pyscard"],
    description="Used for upper layer debugging",
    ext_modules=cythonize("./demo/disp.py"),
)
