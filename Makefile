NAME=minishell
SRC=src/main.c src/parse.c src/token_foos.c src/validation.c src/impliment.c \
	src/command.c  src/expansion.c src/signal.c src/tokenize.c \
	src/paths.c src/execution.c src/envies.c src/redirection.c \
	src/utils.c src/utils_1.c src/utils_2.c src/utils_3.c src/del_ut.c 
OBJ=$(SRC:src/%.c=obj/%.o) 
CC=cc
LIBFT=libft/libft.a
CFLAGS=-Wall -Werror -Wextra
RM=rm -rf

all: libcomp creat_dir $(NAME)

libcomp:
	@make -C libft

creat_dir:
	mkdir -p obj
	mkdir -p tmp

obj/%.o : src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME):$(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) -I readline/readline.h -lreadline $(OBJ) $(LIBFT)

clean:
	@make -C libft clean
	$(RM) obj

fclean: clean
	$(RM) $(NAME)
	@make -C libft fclean
	$(RM) tmp

re: fclean all