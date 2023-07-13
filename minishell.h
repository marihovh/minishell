#ifndef MINISHELL_H
#define MINISHELL_H

// token types
#define SP 1 // spaces // dont need validation
#define WORD 2 // words // partly done
#define FIELD 3 // '  ' // dont need vslidation
#define EXP_FIELD 4 // " " // not done
#define REDIR_OUT 5 // > // 
#define REDIR_IN 6 // <
#define REDIR_AP 7 // >>
#define REDIR_SO 8 // <<
#define PIPE 9 // |
// libraries
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include "./libft/libft.h"
#include <readline/readline.h>

typedef struct s_data		t_data;
typedef struct s_token		t_token;
typedef struct s_streams	t_streams;
typedef struct s_command	t_command;


struct s_token
{
	int type;
	char *value;
	int command;
	int op;
	t_token *prev;
	t_token *next;
};

// struct amen masi hamar or mejynaev pahe statusy exit

struct s_command
{
	t_token *command;
	t_command *next;
};


struct s_data // my all data here
{
	t_token		*stream;
	t_command 	*com_stream;
	int			exit_status;
	char		*command;
};

void	init_line(t_data *data); // readline function in while
int		parse(t_data *data, char *str);
void tokenize(t_token **stream, char *str);
t_token *new_token(int type, char *str, int op);
int ft_isspace(int ch);
int ft_strcmp(char *str, char *chm);
void valid_word(t_data *data, t_token *token);
t_token *token_1(char **str);
t_token	*token_2(char **str);
t_token	*token_3(char **str);
t_token	*token_4(char **str);
t_token	*token_5(char **str);
t_token	*token_6(char **str);
t_token	*token_9(char **str);
char  *ft_ispipe(char *str);
void validation(t_data data);
int rec_pipe(char *str);
void error_msg(char *str);
void ft_echo(t_data *data, t_token *token);
void ft_cd(t_data *data, t_token *token);
void ft_pwd(t_data *data, t_token *token);
t_token *to_pipe(t_token *stream);
void to_commands(t_command **com_stream, t_token *stream);
t_command *new_com(t_token *stream);

#endif