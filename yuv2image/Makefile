include ./makefile.param

TARGET = x5_yuv2png

COMPILE_TIME = $(shell date +"%Y%M%d%H%M%S")

INC := $(patsubst %,-I%,$(INC_DIR))
LIB := $(patsubst %,-L%,$(LIB_DIR))

SRC := $(foreach dir,$(subdir),$(wildcard $(dir)/*.c))
OBJS := $(patsubst %.c,%.o,$(SRC))
DEPS := $(patsubst %.c,%.d,$(SRC))

CFLAGS := $(INC) -Werror -O0 $(CFLAGS_EX)
CXXFLAGS := $(CFLAGS)

LIBRARY_LINK_OPTS = $(LDFLAGS_EX) $(PLATFORM_LIBS)

%.o : %.c
	$(CC) $(CFLAGS) -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c $< -o $@

$(TARGET) : $(OBJS)
	$(CC) -o $@ $^ $(LIBRARY_LINK_OPTS)

install: $(TARGET)
	-mkdir -p $(GLOBAL_INSTALL_DIR)/bin
	#$(STRIP) $(TARGET)
	mv $(TARGET) $(GLOBAL_INSTALL_DIR)/bin

clean:
	@rm -rf $(OBJS) $(DEPS) $(TARGET)
