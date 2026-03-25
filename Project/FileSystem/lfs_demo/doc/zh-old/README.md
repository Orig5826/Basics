## littlefs

专为微控制器设计的故障保护文件系统。

```
   | | | .--.._____
  .-----。| |
-| o | --- | littlefs |
-| | --- | |
  '-----''----------'
   | | |
```

**功率损耗弹性**-littlefs旨在处理随机功率
失败。所有文件操作都有很强的写时复制保证，如果
断电，文件系统将恢复到最后一个已知的良好状态。

**动态磨损平衡**-littlefs在设计时考虑了闪光灯，并且
在动态块上提供磨损均衡。此外，littlefs可以
检测坏块并解决它们。

**有限的RAM / ROM **-littlefs设计用于少量的
记忆。RAM使用受到严格限制，这意味着RAM消耗不会
随着文件系统的增长而变化。文件系统不包含无界
递归和动态内存仅限于可配置的缓冲区
静态提供。

## 例子

这是一个简单的示例，每次更新一个名为`boot_count`的文件
主要运行。该程序可以随时中断而不会丢失曲目
它已启动多少次且未损坏文件系统的时间：

```c
#include“ lfs.h”

//文件系统使用的变量
lfs_t lfs;
lfs_file_t file;

//此结构提供文件系统的配置
const struct lfs_config cfg = {
    //阻止设备操作
    .read = user_provided_block_device_read，
    .prog = user_provided_block_device_prog，
    .erase = user_provided_block_device_erase，
    .sync = user_provided_block_device_sync，

    //阻止设备配置
    .read_size = 16
    .prog_size = 16
    .block_size = 4096，
    .block_count = 128，
    .cache_size = 16
    .lookahead_size = 16，
    .block_cycles = 500，
};

// 入口点
int main（void）{
    //挂载文件系统
     int err = lfs_mount(&lfs, &cfg);

    //如果我们无法挂载文件系统，则重新格式化
    //这应该只在第一次启动时发生
    if (err) {
        lfs_format(&lfs, &cfg);
        lfs_mount(&lfs, &cfg);
    }

    //读取当前计数
    uint32_t boot_count = 0;
    lfs_file_open(&lfs, &file, "boot_count", LFS_O_RDWR | LFS_O_CREAT);
    lfs_file_read(&lfs, &file, &boot_count, sizeof(boot_count));

    //更新启动次数
     boot_count += 1;
    lfs_file_rewind(&lfs, &file);
    lfs_file_write(&lfs, &file, &boot_count, sizeof(boot_count));

    //记住在文件成功关闭之前不会更新存储
     lfs_file_close(&lfs, &file);

    //释放我们正在使用的所有资源
    lfs_unmount(&lfs);

    //打印启动计数
    printf("boot_count: %d\n", boot_count);
}
```

## 用法

详细的文档（或至少与当前可用的详细信息一样多）
可以在[lfs.h]（lfs.h）的注释中找到。

littlefs采用一种定义文件系统的配置结构
运作。配置结构为文件系统提供了块
设备操作和尺寸，可折衷的参数，可以权衡存储器
性能的用法，如果用户想避免使用可选的静态缓冲区
动态内存。

littlefs的状态以lfs_t类型存储，该类型保留在左侧
给用户分配，从而允许使用多个文件系统
同时地。使用lfs_t和配置结构，用户可以
格式化块设备或挂载文件系统。

挂载后，littlefs将提供一整套类似POSIX的文件，并且
目录功能，带有偏差即表示文件系统的分配
结构必须由用户提供。

所有POSIX操作（例如删除和重命名）都是原子性的，即使在事件发生时也是如此
功率损耗。此外，文件更新实际上并未提交
在文件上调用同步或关闭之前的文件系统。

## 其他注意事项

Littlefs用C编写，特别应使用任何编译器进行编译
符合“ C99”标准。

所有littlefs调用都有可能返回负错误代码。这
错误可以是在“枚举lfs_error”中找到的任何一种
[lfs.h]（lfs.h），或用户的块设备操作返回的错误。

在配置结构中，
如果实现已经可以，用户可能会返回“ LFS_ERR_CORRUPT”错误。
检测损坏的块。但是，损耗平衡与返回值无关
这些功能的代码，而是读取并检查所有数据
正直。

如果您的存储缓存写入，请确保提供的`sync`函数
将所有数据刷新到内存，并确保下一次读取可读取数据
从内存中获取数据，否则无法保证数据完整性。如果`写`
函数不会执行缓存，因此每次“读取”或“写入”调用
碰到内存，`sync`函数可以简单地返回0。

## 设计

总体而言，littlefs是基于块的文件系统，它使用小日志来
存储元数据和较大的写时复制（COW）结构以存储文件数据。

在littlefs中，这些成分形成一种两层的蛋糕，
日志（称为元数据对）可提供对任何位置的元数据的快速更新
存储，而COW结构则紧凑地存储文件数据，没有任何存储空间
磨损放大成本。

这两个数据结构都是由块构成的，这些块由
通用块分配器。通过限制块上允许的擦除次数
每次分配时，分配器会在整个分配过程中提供动态损耗均衡
文件系统。

```
                    root
                   .--------.--------.
                   | A'| B'|         |
                   |   |   |->       |
                   |   |   |         |
                   '--------'--------'
                .----'   '--------------.
       A       v                 B       v
      .--------.--------.       .--------.--------.
      | C'| D'|         |       | E'|new|         |
      |   |   |->       |       |   | E'|->       |
      |   |   |         |       |   |   |         |
      '--------'--------'       '--------'--------'
      .-'   '--.                  |   '------------------.
     v          v              .-'                        v
.--------.  .--------.        v                       .--------.
|   C    |  |   D    |   .--------.       write       | new E  |
|        |  |        |   |   E    |        ==>        |        |
|        |  |        |   |        |                   |        |
'--------'  '--------'   |        |                   '--------'
                         '--------'                   .-'    |
                         .-'    '-.    .-------------|------'
                        v          v  v              v
                   .--------.  .--------.       .--------.
                   |   F    |  |   G    |       | new F  |
                   |        |  |        |       |        |
                   |        |  |        |       |        |
                   '--------'  '--------'       '--------'
```

有关littlefs如何工作的更多详细信息，请参见[DESIGN.md]（DESIGN.md）和
[SPEC.md]（SPEC.md）。

-[DESIGN.md]（DESIGN.md）-关于littlefs工作原理的详细介绍。
  我建议您阅读它，因为工作中的权衡是非常有趣的。

-[SPEC.md]（SPEC.md）-littlefs的磁盘规范，包含所有
  细腻的细节。可能对工具开发有用。

## 测试

littlefs带有一个测试套件，旨在使用以下软件在PC上运行：
在emubd目录中找到[仿真块设备]（emubd / lfs_emubd.h）。
这些测试假定在Linux环境中进行，并且可以使用make进行启动：

```bash
make test
```

## 执照

littlefs是根据[BSD-3-Clause]许可提供的。看
[LICENSE.md]（LICENSE.md）了解更多信息。对这个项目的贡献
在相同的许可下被接受。

单个文件包含以下标记，而不是完整的许可证文本。

    SPDX许可证标识符：BSD-3条款

这样可以基于SPDX对许可证信息进行机器处理
可用的许可证标识符：http://spdx.org/licenses/

## 相关项目

-[littlefs-fuse]-littlefs的[FUSE]包装器。该项目允许您
  将littlefs直接安装在Linux机器上。对调试很有用
  littlefs（如果您有SD卡）。

-[littlefs-js]-littlefs的JavaScript包装器。我不确定你为什么会
  想要这个，但是对于演示很方便。您可以看到它的实际效果
  [这里] [littlefs-js-demo]。

-[littlefs-python]-littlefs的Python包装器。该项目允许您
  在您的PC上创建文件系统的映像。检查littlefs是否适合
  根据您的需要，创建映像以供以后下载到目标内存或
  检查目标内存的二进制映像的内容。

-[mklfs]-由[Lua RTOS]家伙构建的命令行工具，用于制作
  来自主机PC的littlefs图像。支持Windows，Mac OS和Linux。

-[Mbed OS]-开始使用littlefs的最简单方法是跳入Mbed
  它已经具有用于大多数形式的嵌入式存储的块设备驱动程序。
  littlefs在Mbed OS中可以作为[LittleFileSystem]类使用。

-[SPIFFS]-另一个用于NOR闪存的出色嵌入式文件系统。作为更多
  具有完全静态耗损均衡的传统日志记录文件系统，SPIFFS将
  在小内存（例如内置闪存）上的性能可能优于littlefs
  微控制器。

-[Dhara]-专为小型设计的有趣的NAND闪存转换层
  MCU。它仅需固定即可提供静态磨损均衡和功率恢复能力
  _O（| address |）_指针结构存储在每个块中和RAM中。


[BSD-3-Clause]：https://spdx.org/licenses/BSD-3-Clause.html
[littlefs-fuse]：https://github.com/geky/littlefs-fuse
[保险丝]：https://github.com/libfuse/libfuse
[littlefs-js]：https：//github.com/geky/littlefs-js
[littlefs-js-demo]：http：//littlefs.geky.net/demo.html
[mklfs]：https://github.com/whitecatboard/Lua-RTOS-ESP32/tree/master/components/mklfs/src
[Lua RTOS]：https://github.com/whitecatboard/Lua-RTOS-ESP32
[Mbed OS]：https://github.com/armmbed/mbed-os
[LittleFileSystem]：https://os.mbed.com/docs/mbed-os/v5.12/apis/littlefilesystem.html
[SPIFFS]：https：//github.com/pellepl/spiffs
[Dhara]：https://github.com/dlbeer/dhara
[littlefs-python]：https://pypi.org/project/littlefs-python/

```

```