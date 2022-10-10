SRC_DIR := ./src
INCLUDE_DIR := ./include
VPATH := ${SRC_DIR}:${INCLUDE_DIR}

.PHONY: echo assemble compare

Assembler : Assembler.cpp Code.cpp Parser.cpp SymbolTable.cpp \
			AllHeaders.h Code.h Parser.h SymbolTable.h
	g++ ${SRC_DIR}/*.cpp -o $@

assemble :
	./Assembler Add.asm
	./Assembler Max.asm
	./Assembler MaxL.asm
# ./Assembler Pong.asm
	./Assembler PongL.asm
# ./Assembler Rect.asm
	./Assembler RectL.asm

compare :
	diff Add.hack ../CorrectBinary/Add.hack
	diff Max.hack ../CorrectBinary/Max.hack
	diff MaxL.hack ../CorrectBinary/MaxL.hack
# diff Pong.hack ../CorrectBinary/Pong.hack
	diff PongL.hack ../CorrectBinary/PongL.hack
# diff Rect.hack ../CorrectBinary/Rect.hack
	diff RectL.hack ../CorrectBinary/RectL.hack

echo :
	echo ${VPATH}
