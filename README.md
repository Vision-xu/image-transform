#  测试yuv转png/jpg

# 工具链解压到自己的路径，自行配置

# zlib、libpng、libjpeg动态库编译生成

```bash
# 创建编译目录
mkdir /home/xjh/work

# 配置编译参数
./configure --prefix=/home/xjh/install --shared

-------------- Makefile 配置---------------
CROSS_COMPILE ?= /home/xjh/ToolChain/arm-gnu-toolchain-11.3.rel1-x86_64-aarch64-none-linux-gnu/bin/aarch64-none-linux-gnu-
COMPILE_PREFIX := $(CROSS_COMPILE)

CC=$(COMPILE_PREFIX)gcc

CFLAGS=-O3 -D_LARGEFILE64_SOURCE=1 -DHAVE_HIDDEN
# 可选调试配置：
# CFLAGS=-g -DZLIB_DEBUG
# CFLAGS=-O3 -Wall -Wwrite-strings [...]

SFLAGS=-O3 -fPIC -D_LARGEFILE64_SOURCE=1 -DHAVE_HIDDEN
LDFLAGS=
TEST_LIBS=-L. libz.a
LDSHARED=$(COMPILE_PREFIX)gcc -shared -Wl,-soname,libz.so.1,--version-script,zlib.map

STATICLIB=libz.a
SHAREDLIB=libz.so
SHAREDLIBV=libz.so.1.3.1
SHAREDLIBM=libz.so.1
LIBS=$(STATICLIB) $(SHAREDLIBV)

# 安装路径配置
prefix = /home/xjh/install
exec_prefix = ${prefix}
libdir = ${exec_prefix}/lib
----------------------------------------------
# 执行编译安装
make && make install
```
# libpng编译
```bash
export PATH=/home/xjh/ToolChain/arm-gnu-toolchain-11.3.rel1-x86_64-aarch64-none-linux-gnu/bin:$PATH

./configure \
  --host=aarch64-none-linux-gnu \
  --prefix=/home/xjh/install/libpng \
  --with-sysroot=/home/xjh/ToolChain/arm-gnu-toolchain-11.3.rel1-x86_64-aarch64-none-linux-gnu/aarch64-none-linux-gnu/libc \
  --enable-shared \
  CPPFLAGS="-I/home/xjh/install/zlib/include" \
  LDFLAGS="-L/home/xjh/install/zlib/lib" \
  LIBS="-lz"
```
# libjpeg编译

```bash
export PATH=/home/xjh/ToolChain/arm-gnu-toolchain-11.3.rel1-x86_64-aarch64-none-linux-gnu/bin:$PATH

./configure --host=aarch64-none-linux-gnu \
--prefix=/home/xjh/install/libjpeg

```


