ifeq ($(TARGET_PLATFORM), native)
    include native.mk
else ifeq ($(TARGET_PLATFORM), wasm)
    include wasm.mk
else
    $(error TARGET_PLATFORM is not set correctly. Please set it to either 'native' or 'wasm')
endif

.PHONY: wasm_toolchain
wasm_toolchain:
	cd emsdk && ./emsdk install latest
	cd emsdk && ./emsdk activate latest
