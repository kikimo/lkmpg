#!/bin/bash

make uninstall
make install && cat /proc/hello && tail -n 50 /var/log/syslog
