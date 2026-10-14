# gcc -m32 -O0 -fno-reorder-blocks -fstack-protector-all -z noexecstack -Wno-format-security -Wno-unused-result -no-pie target.c -o target

CC ?= gcc
CFLAGS ?= -std=gnu99 -O0
LDFLAGS ?=
LIBS ?=

# 32b or 64b
CFLAGS += -m32
# CFLAGS += -m64

# supress warning
CFLAGS += -Wno-format-security -Wno-unused-result

# disable code reordering
CFLAGS += -fno-reorder-blocks

# enable executable stack
# CFLAGS += -z execstack

# disable executable stack (NX protection)
LDFLAGS += -z noexecstack

# enable SSP (all functions)
CFLAGS += -fstack-protector-all

# disable SSP
# CFLAGS += -fno-stack-protector

# enable ASLR
# CFLAGS += -pie -fPIE

# disable ASLR
CFLAGS += -no-pie

ALL := target

.PHONY: all
all: $(ALL)

target: target.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS) $(LIBS)
	checksec --file $@

.PHONY: clean
clean:
	$(RM) -f $(ALL)