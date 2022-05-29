NAME				=		dns_heartbeat

SRC_DIR			=		src/
INC_DIR			=		inc/
OBJ_DIR			=		obj/

SRCS				=		${SRC_DIR}main.c \
								${SRC_DIR}input_check.c \
								${SRC_DIR}fill_values.c \
								${SRC_DIR}ping_client.c

OBJS				=		$(SRCS:${SRC_DIR}%.c=${OBJ_DIR}%.o)

INCLUDES		=		-I ${INC_DIR}

CC					=		clang
CFLAGS			=		-Wall -Werror -Wextra ${INCLUDES} ${DEBUG}

all:						${NAME}

${NAME}:				${OBJS}
								${CC} ${CFLAGS} $^ ${INCLUDES} -o $@

${OBJ_DIR}%.o:	${SRC_DIR}%.c
								@mkdir -p ${OBJ_DIR}
								${CC} -c ${CFLAGS} $< ${INCLUDES} -o $@

clean:
								rm -rf ${OBJ_DIR}

fclean:					clean
								rm -f ${NAME}

re:							fclean all

debug:					fclean
debug:					DEBUG += -g3 -fsanitize=address -D DEBUG=1
debug:					re
