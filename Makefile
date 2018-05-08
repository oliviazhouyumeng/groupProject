CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD -Werror=vla -I/opt/X11/include -L/opt/X11/lib
EXEC = quadris
OBJECTS = main.o cell.o graphicsdisplay.o window.o textdisplay.o block.o iblock.o jblock.o lblock.o level.o level0.o level1.o level2.o level3.o level4.o oblock.o sblock.o starblock.o tblock.o zblock.o grid.o endexception.o 
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
