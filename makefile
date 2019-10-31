CXX = g++  
CXXFLAGS = -g -std=c++14 -Wall -MMD -Werror=vla
EXEC = snake
OBJECTS = main.o snake.o  
DEPENDS = ${OBJECTS:.o=.d}  
  
${EXEC}: ${OBJECTS}  
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lncurses 

-include ${DEPENDS}  

.PHONY: clean  
  
clean:  
	rm ${OBJECTS} ${EXEC} ${DEPENDS}