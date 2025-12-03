
GLOBAL_INSTALL_DIR := $(PRO_ROOT)output
#if you need,replace with your own cross_compile
CROSS_COMPILE ?= /home/xjh/ToolChain/arm-gnu-toolchain-11.3.rel1-x86_64-aarch64-none-linux-gnu/bin/aarch64-none-linux-gnu-
COMPILE_PREFIX := $(CROSS_COMPILE)
CFLAGS_EX  := -Wall -g -O2 -fstack-protector


TOP_DIR = $(shell realpath ${PRO_ROOT})
ifeq ($(LIB_DIR),)
LIB_DIR = ${TOP_DIR}/libs
$(info LIB_DIR not set so use default path: [$(LIB_DIR)])
endif

INC_DIR ?= $(TOP_DIR)/include
subdir := 
subdir += src

PLATFORM_LIBS_NAME := png z jpeg
PLATFORM_LIBS += $(patsubst %,-l%,$(PLATFORM_LIBS_NAME))
LDFLAGS_EX += -L$(LIB_DIR)

CC := $(COMPILE_PREFIX)gcc
CXX := $(COMPILE_PREFIX)c++
STRIP := $(COMPILE_PREFIX)strip
AR := $(COMPILE_PREFIX)ar
