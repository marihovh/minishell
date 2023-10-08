NAME=minishell
SRC = src/main.c src/parse.c src/token_foos.c src/validation.c built_in/impliment.c \
	src/command.c  src/expansion.c src/signal.c src/tokenize.c \
	src/paths.c src/execution.c src/envies.c src/redirection.c \
	src/utils.c src/utils_1.c src/utils_2.c src/utils_3.c src/del_ut.c \
	built_in/add_rm.c built_in/ft_cd_pwd.c built_in/utils.c built_in/utils_2.c \
	built_in/ft_inch_mnac.c built_in/ft_ech_ex.c src/pipes.c built_in/utils_1.c \
	built_in/export_util.c built_in/utils_3.c src/utils_4.c src/redir_util.c \
	src/exec_util.c src/execution_.c src/free_util.c 
OBJ=$(SRC:src/%.c=obj/%.o) 
CC=cc
LIBFT=libft/libft.a
CFLAGS=-Wall -Werror -Wextra #-fsanitize=address -static-libsan -g
RM=rm -rf
INCLUDES = -Ireadline/include
LINKERS	= -Lreadline/lib -lreadline -lhistory
PREFIX = $(shell pwd)/readline

all: libcomp creat_dir $(NAME) $(OBJ)

libcomp:
	@make -C libft

creat_dir:
	mkdir -p obj

obj/%.o : src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(INCLUDES) -o $(NAME) $(LINKERS)

clean:
	@make -C libft clean
	$(RM) obj

fclean: clean
	$(RM) $(NAME)
	@make -C libft fclean

readline:
	cd readline-8.1  && ./configure --prefix=$(PREFIX) && make && make install

re: fclean all

.PHONY: re readline fclean clean all