
# lfs

## 介绍
> C99标准

### 特点
- 轻量
- 磨损均衡
- 掉电恢复

## 结构体

### lfs_config
| 成员变量| 描述 | 说明
| :----: | :----: | :----:
| context | 存储设备上下文 |
| read | 读取函数 |
| prog | 写入函数 |
| erase | 擦除函数 |
| sync | 同步函数 |
| lock | 锁函数 |
| unlock | 解锁函数 |
| read_size | 读取函数大小 |
| prog_size | 写入函数大小 |
| block_size | 存储设备块大小 |
| block_count | 存储设备块数量 |
| block_cycles | 存储设备块擦除次数 |
| cache_size | 缓存大小 |
| lookahead_size | 预读大小 |
| compact_thresh | compact阈值 |
| read_buffer | 读取缓存 |
| prog_buffer | 写入缓存 |
| lookahead_buffer | 预读缓存 |
| name_max | 文件名最大长度 |
| file_max | 文件最大长度 |
| attr_max | 属性最大长度 |
| metadata_max | 元数据最大长度 |
| inline_max | 内联数据最大长度 |
| disk_version | 磁盘版本 |

### lfs_info
| 成员变量| 描述 | 说明
| :----: | :----: | :----:
| type | 文件类型 |
| size | 文件大小 |
| name | 文件名 |

### lfs_fsinfo
| 成员变量| 描述 | 说明
| :----: | :----: | :----:
| disk_version | 磁盘版本 |
| block_size | 块大小 |
| block_count | 块数量 |
| name_max | 文件名最大长度 |
| file_max | 文件最大长度 |
| attr_max | 文件属性最大长度 |

### lfs_attr
| 成员变量| 描述 | 说明
| :----: | :----: | :----:
| type | 属性类型 |
| buffer | 属性数据 |
| size | 属性数据大小 |

### lfs_file_config
| 成员变量| 描述 | 说明
| :----: | :----: | :----:
| buffer | 缓存区 |
| attrs | 属性 |
| attr_count | 属性数量 |

### lfs_cache_t
| 成员变量| 描述 | 说明
| :----: | :----: | :----:
| block | 块号 |
| off | 偏移 |
| size | 大小 |
| buffer | 缓存区 |

### lfs_mdir_t
| 成员变量| 描述 | 说明
| :----: | :----: | :----:
| pair |  |
| rev | 版本号 |
| off | 偏移 |
| etag | 块标签 |
| count | 块数量 |
| erased | 块是否被擦除 |
| split | 块是否被分割 |
| tail |  |

### lfs_dir_t
> littlefs directory type

| 成员变量| 描述 | 说明
| :----: | :----: | :----:
| next | 指针 |
| id | id |
| type | 类型 |
| m | lfs_mdir_t |
| pos | 偏移 |
| head | head |

### lfs_file_t
| 成员变量| 描述 | 说明
| :----: | :----: | :----:
| next | 指向下一个文件 |
| id | 文件id |
| type | 文件类型 |
| m | 目录类型 |
| ctz | 压缩信息 |
| flags | 文件标志 |
| pos | 文件位置 |
| block | 文件块 |
| off | 文件偏移 |
| cache | 文件缓存 |
| cfg | 文件配置 |

### lfs_superblock_t

### lfs_gstate_t
| 成员变量| 描述 | 说明
| :----: | :----: | :----:
| tag | 文件标志 |
| pair[2] | 文件块 |

### lfs_t
> The littlefs filesystem type

| 成员变量| 描述 | 说明
| :----: | :----: | :----:
| rcache | 读缓存 | 
| wcache | 写缓存 | 
| root[2] | 根目录 |
| mlist | 链表
| seed | 随机数种子 |
| gstate | 状态 |
| gdisk | 磁盘信息 |
| gdelta | 状态差
| lookahead | 缓存 |
| cfg | 配置 |
| block_count | 块数 |
| name_max | 文件名最大长度 |
| file_max | 文件最大长度 |
| attr_max | 属性最大长度 |
| inode_max | inode最大长度 |
| lfs1 | lfs1 |

#### lfs_mlist
| 成员变量| 描述 | 说明
| :----: | :----: | :----:
| next | 链表指针 |
| id | 文件id |
| type | 文件类型 |
| m | 文件信息 |

#### lfs_lookahead
| 成员变量| 描述 | 说明
| :----: | :----: | :----:
| start | 文件起始块号 |
| size | 文件大小 |
| next | 文件下一个块号 |
| ckpoint | 文件检查点块号 |
| buffer | 文件缓存 |
