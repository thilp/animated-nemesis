BINARY = application
SRCDIR = src
SRCFILES = course.cc \
	   course_factory.cc \
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

debug: CPPFLAGS +=-DDEBUG
debug: CXXFLAGS +=-g3 -O0 -fsanitize=address \
    -fno-omit-frame-pointer -fno-optimize-sibling-calls
debug: LDFLAGS += -fsanitize=address
debug: all

bin: ${OBJ}
	${CXX} -o ${BINARY} ${OBJ} ${LDFLAGS}

clean:
	${RM} ${OBJ}
	${RM} ${BINARY}
