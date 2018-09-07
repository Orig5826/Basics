#! /bin/bash

# 手动挂载VMware下的共享目录
vmhgfs-fuse .host:/ /mnt/hgfs
ls -hl /mnt/hgfs
ls /mnt/hgfs/Share
