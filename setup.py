from setuptools import setup
from setuptools.command.install import install
import subprocess
from os.path import join, dirname


class CompileNiuParser(install):
    def run(self):
        cmd = ['g++', 'depend.cpp', '-O3', '-o', 'depend', '-I./includes',
               '-lniuparser_sdk_linux', '-L.']
        pwd = join(dirname(__file__), 'pyNiuParser')
        print (cmd, pwd)
        subprocess.Popen(cmd, cwd=pwd) 
        install.run(self)


setup(name='pyNiuParser',
      version='0.1.0',
      description='Wrapping NiuParser as a python package',
      url='https://github.com/banyh/pyNiuParser',
      author='Ping Chu Hung',
      author_email='banyhong@gliacloud.com',
      license='MIT',
      packages=['pyNiuParser'],
      zip_safe=False,
      cmdclass={
          'install': CompileNiuParser,
      },
      install_requires=[
      ],
      test_suite='nose.collector',
      tests_require=['nose'],
      include_package_data=True,)
