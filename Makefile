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

ifeq ($(DEBUG), 1)
	C_FLAGS += -g
endif

ifeq ($(OS_TYPE), linux)
    C_INCLUDES += -I /usr/include/SDL2
    LD_FLAGS += -l SDL2
else
    C_INCLUDES += -I /opt/homebrew/include
    LD_FLAGS += -l SDL2 -L /opt/homebrew/opt/sdl2/lib
endif


OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(C_SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(C_SOURCES)))


.PHONY: all
all: $(BUILD_DIR)/$(TARGET)

$(BUILD_DIR)/%.o: %.c | $(BUILD_DIR)
	$(CC) -c $(C_FLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) $(LD_FLAGS) -o $@
	$(call post_build, $(BUILD_DIR))

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)
