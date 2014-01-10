BINARY = application
SRCDIR = src
SRCFILES = course.cc \
	   course_factory.cc \
	   option.cc \
	   lexical/lexer.cc \
	   lexical/token.cc \
	   parsical/parser.cc \
	   parsical/parser_exception.cc \
	   main.cc \

CPPFLAGS += -I${SRCDIR}
CXXFLAGS += -Wall -Wextra

SRC = ${SRCFILES:%=${SRCDIR}/%}
OBJ = ${SRC:.cc=.o}

RM ?= rm -f

all: bin

bin: ${OBJ}
	${CXX} -o ${BINARY} ${OBJ} ${LDFLAGS}

clean:
	${RM} ${OBJ}
	${RM} ${BINARY}
