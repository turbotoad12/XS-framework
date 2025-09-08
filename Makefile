#---------------------------------------------------------------------------------
# XS-Framework 3DS Static Library Makefile
#---------------------------------------------------------------------------------

# Check environment
ifeq ($(strip $(DEVKITPRO)),)
$(error "Please set DEVKITPRO in your environment. e.g., export DEVKITPRO=/opt/devkitpro")
endif

ifeq ($(strip $(DEVKITARM)),)
$(error "Please set DEVKITARM in your environment. e.g., export DEVKITARM=$(DEVKITPRO)/devkitARM")
endif

# Include devkitPro 3DS rules
include $(DEVKITARM)/3ds_rules

#---------------------------------------------------------------------------------
# Project settings
#---------------------------------------------------------------------------------
TARGET      := xs-framework
BUILD       := build
SOURCES     := $(shell find source -type d)
INCLUDES    := include
DATA        := data

#---------------------------------------------------------------------------------
# Compiler settings (use devkitARM explicitly)
#---------------------------------------------------------------------------------
CXX        := $(DEVKITARM)/bin/arm-none-eabi-g++
CC         := $(DEVKITARM)/bin/arm-none-eabi-gcc
AS         := $(DEVKITARM)/bin/arm-none-eabi-as
AR         := $(DEVKITARM)/bin/arm-none-eabi-ar

ARCH       := -march=armv6k -mtune=mpcore -mfloat-abi=hard -mtp=soft

CFLAGS     := -g -Wall -O2 -mword-relocations -ffunction-sections $(ARCH) -D__3DS__
CXXFLAGS   := $(CFLAGS) -fno-rtti -fno-exceptions
ASFLAGS    := -g $(ARCH)

#---------------------------------------------------------------------------------
# Library include paths
#---------------------------------------------------------------------------------
LIBCTRU_INCLUDE := $(DEVKITPRO)/libctru/include
CITRO2D_INCLUDE := $(DEVKITPRO)/citro2d/include

INCLUDE_FLAGS := $(foreach dir,$(INCLUDES),-I$(CURDIR)/$(dir)) \
                 -I$(LIBCTRU_INCLUDE) \
                 -I$(CITRO2D_INCLUDE) \
                 -I$(CURDIR)/$(BUILD)

#---------------------------------------------------------------------------------
# Source files
#---------------------------------------------------------------------------------
CPPFILES := $(foreach dir,$(SOURCES),$(wildcard $(dir)/*.cpp))
CFILES   := $(foreach dir,$(SOURCES),$(wildcard $(dir)/*.c))
SFILES   := $(foreach dir,$(SOURCES),$(wildcard $(dir)/*.s))
BINFILES := $(foreach dir,$(DATA),$(notdir $(wildcard $(dir)/*.*)))

# Object files go into build/
OFILES := $(addprefix $(BUILD)/, \
           $(CPPFILES:.cpp=.o) \
           $(CFILES:.c=.o) \
           $(SFILES:.s=.o))

DEPENDS := $(OFILES:.o=.d)

#---------------------------------------------------------------------------------
# Main targets
#---------------------------------------------------------------------------------
.PHONY: all clean

all: lib/$(TARGET).a

lib/$(TARGET).a: $(OFILES)
	@mkdir -p lib
	@echo "Archiving $@"
	@$(AR) rcs $@ $^

#---------------------------------------------------------------------------------
# Compile rules
#---------------------------------------------------------------------------------
$(BUILD)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@echo "CXX $<"
	@$(CXX) $(CXXFLAGS) $(INCLUDE_FLAGS) -MMD -MP -c $< -o $@

$(BUILD)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "CC $<"
	@$(CC) $(CFLAGS) $(INCLUDE_FLAGS) -MMD -MP -c $< -o $@

$(BUILD)/%.o: %.s
	@mkdir -p $(dir $@)
	@echo "AS $<"
	@$(AS) $(ASFLAGS) -c $< -o $@

#---------------------------------------------------------------------------------
# Binary data conversion
#---------------------------------------------------------------------------------
%.bin.o: %.bin
	@echo "BIN $<"
	@$(bin2o)

#---------------------------------------------------------------------------------
# Cleanup
#---------------------------------------------------------------------------------
clean:
	@echo "Cleaning..."
	@rm -rf $(BUILD) lib

#---------------------------------------------------------------------------------
-include $(DEPENDS)
#---------------------------------------------------------------------------------
