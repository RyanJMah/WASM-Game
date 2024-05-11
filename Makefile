ifeq ($(TARGET_PLATFORM), native)
    include makefiles/native.mk
else ifeq ($(TARGET_PLATFORM), wasm)
    include makefiles/wasm.mk
else
    $(error TARGET_PLATFORM is not set correctly. Please set it to either 'native' or 'wasm')
endif
