BINARY = application
SRCDIR = src
SRCFILES = main.cc \
	   lexer.cc \
	   course.cc \
	   course_factory.cc \

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
