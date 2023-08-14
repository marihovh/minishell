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
#define STDOUT 1
#define STDIN 0

// libraries

#include <unistd.h>
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
	int in;
	int out;
	int op;
	t_token *prev;
	t_token *next;
};

// struct amen masi hamar or mejynaev pahe statusy exit

struct s_command
{
	char **command;
	int in;
	int out;
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
	char		**paths;
	t_token		*stream;
	int			exit_status;
	char		**command;
	t_command	*com_stream;
};

void to_struct(char **command, t_command **com_stream, t_token *stream);   //done
void to_commands(t_data *data);    // done
t_envies *new_node(char *key, char *value);
void init_env(t_envies **envp, char **environ);
char	*what_path(char **paths, char *command);
int	ft_lstcnt(t_envies *lst);
void dups(t_command *command);
char **to_matrix(t_envies *envies);
void print_env(char **env);
void execute(t_data *data);
char *if_env(char *str, t_envies *env, int exs);
void open_fields(t_token *stream, t_envies *env, int exs);
void ft_echo(t_data *data, t_token *token);
void ft_cd(t_data *data, t_token *token);
void ft_pwd(t_data *data, t_token *token);
void signal_hend(int signum);
void init_line(t_data *data, char **environ);
int	in_and_out(t_token *stream);
t_token *cut_red(t_token *stream);
void	delete_files(t_token *stream);
int parse(t_data *data, char *str);
void	init_path(t_data *data);
int init_and_check_fd(int fd);
void	for_heredoc(char *filename, int fd);
char *file_name(t_token *stream);
void find_com(t_token **stream, int in, int out);
t_token	*token_1(char **str);
t_token	*token_2(char **str);
t_token	*token_3(char **str);
t_token	*token_4(char **str);
t_token	*token_5(char **str);
t_token *which_token(char **str);
void tokenize(t_token **stream, char *str);
int	redir_error(void);
void	open_eror(void);
int validation(t_token *stream);


void prin(t_token *stream, t_command *com_stream);
void pri(t_command *com_stream);
void print_en(t_envies *envies);
int	split_len(char **str);
t_command	*new_com(char **args, int in, int out);
int	ft_com_len(t_token *stream);
char	*one_dol(char **str);
char	*env_name(char **str);
t_token	*token_6(char **str);
t_token	*token_9(char **str);
void free_data(t_data *data);
char *file_join(char *buffer, char *stat);
int ft_strcmp(char *str, char *chm);
t_token *new_token(int type, char *str, int op);
void	esim(void);
int ft_isspace(int ch);
int correct_pipe(char *tmp, char *str);
char  *ft_ispipe(char *str);
void error_msg(char *str);

#endif