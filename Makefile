# 아키텍쳐 정의
ARCH = armv7-a
MCPU = cortex-a8	

# 컴파일러 변수 추가.
CC = /usr/bin/aarch64-linux-gnu-gcc
AS = /usr/bin/aarch64-linux-gnu-as
LD = /usr/bin/aarch64-linux-gnu-gcc
OC = /usr/bin/aarch64-linux-gnu-objcopy
OD = /usr/bin/aarch64-linux-gnu-objdump

# 출력 파일 이름 정의.
MAP_FILE = build/data_structure.map
ASM_FILE = build/data_structure.asm
data_structure = build/data_structure

# 컴파일 옵션 정의.
CFLAGS = -fdiagnostics-color=always -c -g -O0 -std=c11

# 링커 옵션 선언.
LDFLAGS = -static -lgcc

# 컴파일 목록들 정의.
C_SRCS = $(wildcard *.c)
C_SRCS += $(notdir $(wildcard 1_Background/*.c))
C_SRCS += $(notdir $(wildcard 2_LinkedList/*.c))
C_SRCS += $(notdir $(wildcard common/*.c))
C_OBJS = $(patsubst %.c, build/%.o, $(C_SRCS))

# 컴파일 경로 정의
INC_DIRS = -I 1_Background	\
		   -I 2_LinkedList	\
		   -I common

# Makefile의 검색 경로 설정
VPATH = 1_Background \
		2_LinkedList \
		common \

# Makefile 타겟 정의
.PHONY: all clean

all: $(data_structure)

clean:
	@rm -fr build

run: $(data_structure)
	qemu-system-arm -M realview-pb-a8 -kernel $(data_structure) -nographic -audiodev id=none,driver=none 

debug: $(data_structure)
	qemu-system-arm -M realview-pb-a8 -kernel $(data_structure) -S -nographic -audiodev id=none,driver=none -gdb tcp::1234,ipv4
	
gdb:
	gdb-multiarch

$(data_structure): $(C_OBJS)
	$(LD) -o $(data_structure) $(C_OBJS) -Wl,-Map=$(MAP_FILE) $(LDFLAGS)
	$(OD) -d $(data_structure) >> $(ASM_FILE)

build/%.o: %.c
	mkdir -p $(shell dirname $@)
	@echo $(CC) $(INC_DIRS) $(CFLAGS) -o $@ $<
	$(CC) $(INC_DIRS) $(CFLAGS) -o $@ $<