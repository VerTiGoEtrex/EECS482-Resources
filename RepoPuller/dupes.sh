#!/bin/sh
ls -d */ | grep -o "[a-z]*" | sort | uniq -d
