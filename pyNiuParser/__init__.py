import subprocess
import six
import sys
import os
from os.path import dirname, join
from fcntl import fcntl, F_SETFL, F_GETFD

__all__ = ['NiuParser']


class NiuParser(object):
    def __del__(self):
        self.din.close()
        try:
            self.process.kill()
            self.process.wait()
        except OSError:
            pass

    def __init__(self):
        command = 'bash -c "./depend"'
        pwd = dirname(__file__)
        print command, pwd
        env = os.environ.copy()
        env['LD_LIBRARY_PATH'] = pwd
        subproc_args = {'stdin': subprocess.PIPE, 'stdout': subprocess.PIPE,
                        'stderr': subprocess.STDOUT, 'cwd': pwd,
                        'env': env, 'close_fds': True}
        self.process = subprocess.Popen(command, shell=True, **subproc_args)
        self.out = self.process.stdout
        self.din = self.process.stdin
        self.ready = False
        fcntl(self.out.fileno(), F_SETFL, fcntl(self.out.fileno(), F_GETFD) | os.O_NONBLOCK)

    def isReady(self):
        '''A blocking function to wait for NiuParser program ready.
        '''
        if self.ready:
            return
        result = ''
        while not result.startswith(u'NiuParser Init'):
            try:
                result = self.out.readline().decode('utf8')[:-1]
                print result
            except:
                result = ''
        self.ready = True

    def query(self, text):
        self.isReady()  # blocked until ready
        self.din.write(text.encode('utf8') + six.b('\n'))
        self.din.flush()
        results = []
        result = None
        while not result:
            try:
                result = self.out.readline().decode('utf8')[:-1]
            except:
                result = None
        results.append(result)
        try:
            while True:
                results.append(self.out.readline().decode('utf8')[:-1])
        except:
            pass
        return [r.split('\t') for r in results]

