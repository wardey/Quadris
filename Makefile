CXX = g++-5
CXXFLAGS = -std=c++14 -MMD -Werror=vla
EXEC = quadris
OBJECTS = GraphicsDisplay.o window.o TextDisplay.o Board.o Cell.o Subject.o Game.o Block.o TBlock.o OBlock.o IBlock.o SBlock.o ZBlock.o JBlock.o LBlock.o OneBlock.o Level.o Level0.o Level1.o Level2.o Level3.o Level4.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}

