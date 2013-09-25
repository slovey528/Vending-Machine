CXX = g++				    # compiler
CXXFLAGS = -g -Wall -MMD		    # compiler flags
OBJECTS = driver.o printer.o bottlingplant.o truck.o student.o nameserver.o vendingmachine.o watcard.o watcardoffice.o         # all .o files
DEPENDS = ${OBJECTS:.o=.d}                  # substitue ".o" with ".d"
EXEC = soda                                # executable name

${EXEC} : ${OBJECTS}                        # link step
	${CXX} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}                         # copies files *.d (if exits)

.PHONY : clean
clean :					    # remove files that can be regenerated
	rm -rf ${DEPENDS} ${OBJECTS} ${EXECS}
