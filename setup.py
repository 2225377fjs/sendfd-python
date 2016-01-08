from distutils.core import setup
from distutils.extension import Extension
from Cython.Distutils import build_ext


CORE = Extension(name='sendfd',
                 sources=["test.c", "aa.pyx"])

ext_modules = [CORE]


setup(
    name='aa',
    cmdclass={'build_ext':build_ext},
    ext_modules=ext_modules
)