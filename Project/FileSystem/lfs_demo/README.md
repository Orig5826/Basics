
# lfs

## 介绍
- C99标准
- little-endian 字节顺序存储
- 元数据

### 特点
- 轻量
- 磨损均衡
- 掉电恢复

## 版本
| 版本宏 |  说明
| :----: | :----:
| LFS_VERSION | “littlefs 代码发行版号”
| LFS_DISK_VERSION | “盘上目录/日志结构版本号”

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
| block_cycles | 擦周期（深度磨损均衡触发周期） | -1表示关闭基于计数的块级均衡（但有基本的LFS机制），建议配置到100-1000之间，有额外的块级均衡。当计数到达这个阈值时，littlefs 可能会选择在擦除时回收该块、把旧元数据迁移到更健康块上，降低该块继续写操作的概率。
| cache_size | 缓存大小 | 约束：缓存大小必须同时是读/写操作单位的整数倍，且能整除块大小。这样才能确保对齐、完整覆盖块里的范围。
| lookahead_size | 预读大小 | 前瞻缓存，本质上是位图，用于存储块占用情况。一般配置成16/32，也即预读128块或256块。越大越快，但ram资源占用也越高。比如lfs_alloc的时候需要一个lookahead缓存，用于存储预读的位图。
| compact_thresh | compact阈值 |
| read_buffer | 读取缓存 | 和cache_size有关，如果支持malloc，则使用malloc分配缓存，否则需要指定缓存。
| prog_buffer | 写入缓存 | 同上
| lookahead_buffer | 预读缓存 | 和lookahead_size有关，如果支持malloc，则使用malloc分配缓存，否则需要指定缓存。
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
| void *buffer | 缓存区 | 大小等于cache_size，若指针为NULL，则默认调用malloc分配。不同的file_open接口使用需要注意
| struct lfs_attr *attrs | 属性 | 字段指向一个可选的自定义属性列表。这些属性与文件关联，每个属性由 8 位类型标识，大小限制在 LFS_ATTR_MAX 字节以内。
| uint32_t attr_count | 属性数量 | 字段指定属性列表中的数量，用于遍历和处理这些自定义属性。

```c
// lfs_file_open 使用动态缓存
// lfs_file_opencfg 使用静态缓存
```

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


## 元数据

## 存储结构
| 序号 | 含义 | 字节数 | 说明
|:----:| :----: | :----: | :----:
|1 | **revision count** | 4 | 修订计数，比较新旧。（序列比较而非简单的数值比较）
|2 | **entries** | --- | ----
| | tag ~A | 4 | 描述文件属性的tag和属性值，实际存储的值是上一文件的tag和当前文件tag的异或值
| | data | N | 可变长数据
|3 | **CRC*** | 4 | CRC校验，0x04c11db7的CRC-32


## 元数据标签
```
[----            32             ----]
[1|--  11   --|--  10  --|--  10  --]
 ^.     ^     .     ^          ^- length
 |.     |     .     '------------ id
 |.     '-----.------------------ type (type3)
 '.-----------.------------------ valid bit
  [-3-|-- 8 --]
    ^     ^- chunk
    '------- type (type1)
```

### 元数据类型

## `0x0ff` LFS_TYPE_SUPERBLOCK
> 超级块，总大小32字节

| 含义 | 字节数 | 说明
| :----: | :----: | :----:
| Magic string | 8 | "littlefs"
| Version | 4 | 0x00020000
| Block size | 4 | 块大小
| Block count | 4 | 块数量
| Name max | 4 | 文件名最大长度
| File max | 4 | 文件最大长度
| Attribute max | 4 | 属性最大长度
