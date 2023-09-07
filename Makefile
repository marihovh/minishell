NAME=minishell
SRC = src/main.c src/parse.c src/token_foos.c src/validation.c built_in/impliment.c \
	src/command.c  src/expansion.c src/signal.c src/tokenize.c \
	src/paths.c src/execution.c src/envies.c src/redirection.c \
	src/utils.c src/utils_1.c src/utils_2.c src/utils_3.c src/del_ut.c \
	built_in/add_rm.c built_in/ft_cd_pwd.c built_in/utils.c built_in/utils_2.c \
	built_in/ft_ech_ex.c
OBJ=$(SRC:src/%.c=obj/%.o) 
CC=cc
LIBFT=libft/libft.a
CFLAGS=-Wall -Werror -Wextra
RM=rm -rf
INCLUDES = -I./readline-marihovh/include
LINKERS	= -L./readline-marihovh/lib -lreadline
PREFIX = $(shell pwd)/readline-marihovh

all: libcomp creat_dir $(NAME) $(OBJ)

libcomp:
	@make -C libft

creat_dir:
	mkdir -p obj

obj/%.o : src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@


$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(LIBFT) $(INCLUDES) $(LINKERS) $(OBJ) -o $(NAME)

clean:
	@make -C libft clean
	$(RM) obj

fclean: clean
	$(RM) $(NAME)
	@make -C libft fclean

readline:
	cd readline-master  && ./configure --prefix=$(PREFIX) && make && make install

re: fclean all