BINARY = application
SRCDIR = src
SRCFILES = structs/course.cc \
	   structs/employee.cc \
	   structs/employee_day.cc \
	   structs/solution.cc \
	   course_factory.cc \
	   lexical/lexer.cc \
	   lexical/token.cc \
	   parsical/parser.cc \
	   parsical/parser_exception.cc \
	   tabu.cc \
	   main.cc \

CPPFLAGS += -I${SRCDIR}
CXXFLAGS += -Wall -Wextra
LDFLAGS  += -lpthread

SRC = ${SRCFILES:%=${SRCDIR}/%}
OBJ = ${SRC:.cc=.o}

RM ?= rm -f

all: bin

debug: CPPFLAGS +=-DDEBUG
debug: CXXFLAGS +=-g3 -O0 -Wshadow
#debug: CXXFLAGS += -fsanitize=address -fno-omit-frame-pointer -fno-optimize-sibling-calls
#debug: LDFLAGS += -fsanitize=address
debug: all

bin: ${OBJ}
	${CXX} -o ${BINARY} ${OBJ} ${LDFLAGS}

clean:
	${RM} ${OBJ}
	${RM} ${BINARY}
