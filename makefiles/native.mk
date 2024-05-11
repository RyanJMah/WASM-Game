TARGET = main
OPT    = -O2
CC     = clang
DEBUG  = 0

# $1 is the build directory
define post_build
	@echo ""
	@size $1/$(TARGET)
endef
