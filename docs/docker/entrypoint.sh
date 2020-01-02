#!/bin/bash

if [ "$1" = 'serve' ]; then
    mkdocs serve -a $(ip addr show eth0 | grep "inet\b" | awk '{print $2}' | cut -d/ -f1):8000
else
    mkdocs $@
fi
