#!/usr/bin/python3

import datetime
import getpass
import json
import os
import random
import socket
import sys
import uuid

# Don't complain. It's not critical that this is random.
random.seed(os.getpid())
r = random.randint(0, 0xffffffff)

arches = {
	'x86': ('X86', 0)
}

types = {
	'free': ('FREE', 0),
	'debug': ('DEBUG', 1)
}

try:
	if os.path.exists(sys.argv[1]):
		fd = open(sys.argv[1], "r")
		for line in fd:
			try:
				if line.split()[1] == "BUILDLAB_VERSION":
					line = line.split()[2][2:]
					line = line[:len(line)-2]
					line = line.split(".")
					major = int(line[0])
					minor = int(line[1])
					arch = line[2]
					type = line[3]
					number = int(line[4])+1
			except IndexError:
				pass
		fd.close()
	else:
		major = 0
		minor = 0
		arch = "none"
		type = "none"
		number = 0
except:
		major = 0
		minor = 0
		arch = "none"
		type = "none"
		number = 0

try:
	if sys.argv[2]:
		dict = json.loads(sys.argv[2])
		print(dict)
		try:
			major = int(dict['major'])
		except KeyError:
			pass
		try:
			minor = int(dict['minor'])
		except KeyError:
			pass
		try:
			arch = dict['arch']
		except KeyError:
			pass
		try:
			type = dict['type']
		except KeyError:
			pass
		try:
			number = int(dict['number'])
		except KeyError:
			pass
except IndexError:
	pass

user = getpass.getuser()
host = socket.gethostname()
datetimestr = str(datetime.datetime.today())

fd = open(sys.argv[1], "w")
fd.write("/*        COMPUTER GENERATED! DO NOT EDIT!        */\n")
fd.write("/*       YOU WILL MESS UP THE BUILD PROCESS!      */\n")
fd.write("/* THERE ARE WAYS TO INFLUENCE THE BUILD PROCESS. */\n")
fd.write("/*                   USE THEM.                    */\n")
fd.write("#ifndef BUILDLAB_%08x\n" % r)
fd.write("#define BUILDLAB_%08x\n" % r)
for x in arches:
	fd.write("#define BUILDLAB_ARCHES_%s (%d)\n" % (arches[x][0], arches[x][1]))
for x in types:
	fd.write("#define BUILDLAB_TYPES_%s (%d)\n" % (types[x][0], types[x][1]))
fd.write("#define BUILDLAB_UUID (\"%s\")\n" % str(uuid.uuid1()))
fd.write("#define BUILDLAB_VERSION (\"%u.%u.%s.%s.%04u\")\n" % (major, minor, arch, type, number))
fd.write("#define BUILDLAB_MAJOR (%u)\n" % major)
fd.write("#define BUILDLAB_MINOR (%u)\n" % minor)
fd.write("#define BUILDLAB_ARCH (%u)\n" % arches[arch][1])
fd.write("#define BUILDLAB_TYPE (%u)\n" % types[type][1])
fd.write("#define BUILDLAB_NUMBER (%u)\n" % number)
fd.write("#define BUILDLAB_DATE (__DATE__)\n")
fd.write("#define BUILDLAB_TIME (__TIME__)\n")
fd.write("#define BUILDLAB_DATETIME (\"%s\")\n" % datetimestr)
fd.write("#define BUILDLAB_USER (\"%s\")\n" % user)
fd.write("#define BUILDLAB_HOST (\"%s\")\n" % host)
fd.write("#define BUILDLAB_MUID (\"%s@%s on %s\")\n" % (user, host, datetimestr))
fd.write("#endif /* BUILDLAB_%08x */\n" % r)
fd.close()
