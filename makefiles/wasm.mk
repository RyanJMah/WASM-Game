TARGET_NAME = index

TARGET = $(TARGET_NAME).html
OPT    = -O2
CC     = emcc -s USE_SDL=2 -s USE_SDL_IMAGE=2 -s SDL2_IMAGE_FORMATS='["png"]'
DEBUG  = 0

# $1 is the build directory
define post_build
	@wasm-objdump -h $1/$(TARGET_NAME).wasm
endef

C_FLAGS += -DWASM
LD_FLAGS += --preload-file assets@/assets
