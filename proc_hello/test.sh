#!/bin/bash

syslog=/var/log/messages
if [ ! -f $syslog ]; then
	syslog=/var/log/syslog
fi

make uninstall
make install && cat /proc/hello && tail -n 50 $syslog
