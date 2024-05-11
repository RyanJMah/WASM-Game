TARGET_NAME = index

TARGET = $(TARGET_NAME).html
OPT    = -O2
CC     = emcc
DEBUG  = 0

# $1 is the build directory
define post_build
	@wasm-objdump -h $1/$(TARGET_NAME).wasm
endef

C_FLAGS += -s WASM=1 -s USE_SDL=2

C_FLAGS += -D WASM
