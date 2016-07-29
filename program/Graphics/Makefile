CXX = g++
CXXFLAGS = -Wall -MMD -L/usr/X11R6/lib -lX11
OBJECTS =  main.o coords.o interpret.o board.o block.o nextblock.o graphic.o window.o textdisplay.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = quadris

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY : clean


clean :
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}
