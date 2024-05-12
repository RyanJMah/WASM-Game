# OS_TYPE = macos
ifndef OS_TYPE
    OS_TYPE = macos
    $(warning OS is not set. Defaulting to "macos")
endif

ifeq ($(TARGET_PLATFORM), native)
    include makefiles/native.mk
else ifeq ($(TARGET_PLATFORM), wasm)
    include makefiles/wasm.mk
else
    $(error TARGET_PLATFORM is not set correctly. Please set it to either 'native' or 'wasm')
endif

BUILD_DIR = build

C_SOURCES  += $(wildcard src/*.c)
C_INCLUDES += -I ./inc

C_FLAGS += $(C_INCLUDES) $(OPT) -Wall -MMD -MP -MF"$(@:%.o=%.d)"

ifndef RELEASE
	C_FLAGS += -g -DDEBUG
endif


OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))

.PHONY: all
all: $(BUILD_DIR)/$(TARGET)

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) -c $(C_FLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET): $(OBJECTS) assets
	$(CC) $(OBJECTS) $(LD_FLAGS) -o $@
	$(call post_build, $(BUILD_DIR))

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

.PHONY: assets
assets: $(BUILD_DIR)
ifndef RELEASE
	cd $(BUILD_DIR) && ln -sf ../assets .
else
	@echo "Copying assets to build directory..."
	cp -r assets $(BUILD_DIR)
endif


.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)/*
