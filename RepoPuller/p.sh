#!/bin/sh
find -name \*.$1 -type d -mindepth 1 -maxdepth 1 | parallel git --git-dir={}/.git --work-tree=/Users/ncrocker/IA/repos/{} pull
