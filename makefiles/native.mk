TARGET = main
OPT    = -O2
CC     = clang
DEBUG  = 0

# $1 is the build directory
define post_build
	@echo ""
	@size $1/$(TARGET)
endef

ifeq ($(OS_TYPE), linux)
    C_INCLUDES += -I /usr/include/SDL2
    LD_FLAGS += -l SDL2
else
    C_INCLUDES += -I /opt/homebrew/include
    LD_FLAGS += -l SDL2 -L /opt/homebrew/opt/sdl2/lib
endif
