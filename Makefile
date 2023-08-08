NAME=minishell
SRC=src/main.c src/parse.c src/token_foos.c src/utils.c \
	src/validation.c src/impliment.c src/command.c src/utils_1.c src/expansion.c \
	src/paths.c src/execution.c src/envies.c src/utils_2.c
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

obj/%.o : src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME):$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -I readline/readline.h -lreadline $(LIBFT)

clean:
	@make -C libft clean
	$(RM) obj

fclean: clean
	$(RM) $(NAME)
	@make -C libft fclean

re: fclean all