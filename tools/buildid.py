#!/usr/bin/python

import subprocess

p = subprocess.Popen('git show | head -n1 | cut -b8-', shell=True, stdout=subprocess.PIPE)
rev = p.stdout.readline().replace('\n', '')
p.stdout.close()

print('#define SCM_REV "%s"' % rev)
