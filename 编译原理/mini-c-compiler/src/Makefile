OBJ = grammar.o lex.o code_gen.o ast.o main.o
CC = /usr/bin/clang++
LLVM_AS = /usr/lib/llvm-10/bin/llvm-as 
LLI = /usr/lib/llvm-10/bin/lli

LLVM_INCLUDE = -I /usr/lib/llvm-10/include
LLVM_LIBS = -L /usr/lib/llvm-10/lib
LD_FLAG = -lpthread -ldl -lz -lncurses -rdynamic -L/usr/local/lib -ljsoncpp

.PHONY: all debug test tmp_test clean

all:
	flex -o lex.cpp lex.l
	bison -d -o grammar.cpp grammar.y
	$(CC) $(LLVM_INCLUDE) $(LLVM_LIBS) $(LD_FLAG) -lLLVM ./*.cpp -o compiler

debug:
	flex -o lex.cpp lex.l
	bison -d -o grammar.cpp grammar.y
	$(CC) -D DEBUG $(LLVM_INCLUDE) $(LLVM_LIBS) $(LD_FLAG) -lLLVM ./*.cpp -o compiler

test:
#	test for quick sort
	$(shell ./compiler < ./test/test_1/input.c > ./test/test_1/test.ll)
	$(shell llvm-as-10 ./test/test_1/test.ll -o ./test/test_1/test.bc)
	$(shell $(CC) ./test/test_1/test.bc -o ./test/test_1/test.out)
	@echo -e '>> 'build quick sort successfully

# test for matrix mul
# $(shell ./compiler < ./test/test_2/input.c > ./test/test_2/test.ll)
# $(shell llvm-as-10 ./test/test_2/test.ll -o ./test/test_2/test.bc)
# $(shell $(CC) ./test/test_2/test.bc -o ./test/test_2/test.out)
# @echo -e '>> 'build matrix-mul successfully


#	test for adv
# $(shell ./compiler < ./test/test_3/input.c > ./test/test_3/test.ll)
# $(shell llvm-as-10 ./test/test_3/test.ll -o ./test/test_3/test.bc)
# $(shell $(CC) ./test/test_3/test.bc -o ./test/test_3/test.out)
# @echo -e '>> 'build advertise successfully

	
# $(shell ./compiler < ./test/test_4/input.c > ./test/test_4/test.ll)
# $(shell llvm-as-10 ./test/test_4/test.ll -o ./test/test_4/test.bc)
# $(shell $(CC) ./test/test_4/test.bc -o ./test/test_4/test.out)
# @echo -e '>> 'build advertise successfully
	
# $(shell ./compiler < ./test/test_5/input.c > ./test/test_5/test.ll)
# $(shell llvm-as-10 ./test/test_5/test.ll -o ./test/test_5/test.bc)
# $(shell $(CC) ./test/test_5/test.bc -o ./test/test_5/test.out)
# @echo -e '>> 'build advertise successfully
	
# $(shell ./compiler < ./test/test_6/input.c > ./test/test_6/test.ll)
# $(shell llvm-as-10 ./test/test_6/test.ll -o ./test/test_6/test.bc)
# $(shell $(CC) ./test/test_6/test.bc -o ./test/test_6/test.out)
# @echo -e '>> 'build advertise successfully

tmp_test:
	$(shell ./compiler < ./test/test_tmp/input.c > ./test/test_tmp/test.ll)
	$(shell llvm-as-10 ./test/test_tmp/test.ll -o ./test/test_tmp/test.bc)
	$(shell $(CC) ./test/test_tmp/test.bc -o ./test/test_tmp/test.out)
	@echo -e '>> 'build temp test successfully

clean:
	$(shell rm -rf $(OBJS) grammar.cpp grammar.hpp lex.cpp test.* compiler)
	$(shell rm -f ./test/test_1/test.*)
	$(shell rm -f ./test/test_2/test.*)
	@echo -e '>> 'clean successfully