CC=gcc
CCFLAGS=-g
TEST_SCRIPT=test.sh

TARGET=riscv-sim
OBJS=riscv32.o rv32bp.o rv32disasm.o rv32exec.o vmem.o vm.o main.o

DUMP_TARGET=dump-riscv-sim
DUMP_OBJS=riscv32.o rv32bp.o rv32disasm.o rv32exec.o vmem.o vm.o dump_main.o

default: $(TARGET)

all: $(TARGET) $(DUMP_TARGET)
$(TARGET) : $(OBJS)
	$(CC) $(CCFLAGS) -o $@ $^

dump: $(DUMP_TARGET)
$(DUMP_TARGET) : $(DUMP_OBJS)
	$(CC) $(CCFLAGS) -o $@ $^

test: $(TARGET)
	python3 test.py

run: $(TARGET)
	python3 test.py --no-compare

.PHONY: clean
clean:
	rm -f *.o $(TARGET) $(DUMP_TARGET)
	rm -f ./test/output/*
