CXX      := clang++
LD       := ld.lld
TARGET   := --target=i686-elf
CXXFLAGS := $(TARGET) -ffreestanding -fno-exceptions -fno-rtti -nostdlib \
            -std=c++20 -O2 -Wall -Wextra -mno-sse -mno-mmx -IOS
BUILD    := build
KERNEL   := mykernel.bin

# Find source files: top level + everything under OS/
CPP_SRCS := $(wildcard *.cpp) $(shell find OS -name '*.cpp')
ASM_SRCS := $(wildcard *.s)   $(shell find OS -name '*.s')

# Each source becomes build/<same path>.o
OBJS := $(patsubst %,$(BUILD)/%.o,$(ASM_SRCS) $(CPP_SRCS))
DEPS := $(OBJS:.o=.d)

$(KERNEL): $(OBJS) linker.ld
	$(LD) -m elf_i386 -T linker.ld -o $@ $(OBJS)

$(BUILD)/%.cpp.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

$(BUILD)/%.s.o: %.s
	@mkdir -p $(dir $@)
	$(CXX) $(TARGET) -c $< -o $@

run: $(KERNEL)
	qemu-system-i386 -kernel $(KERNEL)

clean:
	rm -rf $(BUILD) $(KERNEL)

.PHONY: run clean
-include $(DEPS)