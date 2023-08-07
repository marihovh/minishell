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
#include <signal.h>
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
typedef struct s_envies		t_envies;

struct s_token   //done
{
	int type;
	char *value;
	int command;
	int out;
	int in;
	int op;
	t_token *prev;
	t_token *next;
};

// struct amen masi hamar or mejynaev pahe statusy exit

struct s_command
{
	char **command;
	int exit_status;
	t_command *next;
};

struct s_envies       // done
{
	char *key;
	char *value;
	t_envies *next;
};

struct s_data // my all data here 
{
	t_envies	*envies;
	char		*paths[6];
	t_token		*stream;
	int			exit_status;
	char		**command;
	t_command	*com_stream;
};

int ft_isspace(int ch);
int rec_pipe(char *str);
char  *ft_ispipe(char *str);
int	ft_lstcnt(t_envies *lst);
void *ashxatel(t_data *data);
void signal_hend(int signum);
t_token *token_1(char **str);
t_token	*token_2(char **str);
t_token	*token_3(char **str);
t_token	*token_4(char **str);
t_token	*token_5(char **str);
t_token	*token_6(char **str);
t_token	*token_9(char **str);
int validation(t_token *stream);
int ft_strcmp(char *str, char *chm);
void parse(t_data *data, char *str);
void tokenize(t_token **stream, char *str);
void init_line(t_data *data, char **environ); // readline function in while
void valid_word(t_data *data, t_token *token);
void init_env(t_envies **envp, char **environ);
char *if_env(char *str, t_envies *env, int exs);
t_token *new_token(int type, char *str, int op);
char *find_rep(char *str, int exs, t_envies *env);
void to_struct(char **command, t_command **stream);
void open_fields(t_token *stream, t_envies *env, int exs);
char	*env_name(char **str);
void error_msg(char *str);
void ft_echo(t_data *data, t_token *token);
void ft_cd(t_data *data, t_token *token);
void ft_pwd(t_data *data, t_token *token);
t_token *to_pipe(t_token *stream);
t_command *new_com(char **args);
void to_commands(t_data *data);
int ft_com_len(t_token *stream);
void	init_path(t_data *data);
void execute(t_data *data);
t_envies *new_node(char *key, char *value);
#endif