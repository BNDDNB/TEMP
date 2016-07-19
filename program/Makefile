CXX = g++
CXXFLAGS = -g -Wall -MMD
OBJECTS =  main.o block.o board.o coords.o display.o nextblock.o interpret.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = quadris

${EXEC} : ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY : clean


clean :
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}
