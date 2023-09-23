#ifndef MINISHELL_H
#define MINISHELL_H

// token types
#define SP 1 // spaces // dont need validation
#define WORD 2 // words // partly done
#define FIELD 3 // '  ' // dont need vslidation
#define EXP_FIELD 4 // " " // not done
#define REDIR_OUT 5 // >
#define REDIR_IN 6 // <
#define REDIR_AP 7 // >>
#define REDIR_SO 8 // <<
#define PIPE 9 // |
#define STDOUT 1
#define STDIN 0

// libraries
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/stat.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include "./libft/libft.h"



typedef struct s_data		t_data;
typedef struct s_token		t_token;
typedef struct s_streams	t_streams;
typedef struct s_command	t_command;
typedef struct s_envies		t_envies;
typedef struct s_export		t_export;

struct s_token   //done
{
	int type;
	char *value;
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
	int sp;
	int out;
	t_command *prev;
	t_command *next;
};

struct s_envies       // done
{
	char *key;
	char *value;
	t_envies *next;
};

struct s_export      // done
{
	char *key;
	char *value;
	t_export *next;
};

struct s_data // my all data here 
{
	int			pip_cnt;
	char		**paths;
	int			in_c;
	int			out_c;
	int			index;
	char		*home;
	char		**command;
	t_token		*stream;
	t_envies	*envies;
	t_export	*export;
	t_command	*com_stream;
};

void	to_struct(t_data *data, t_command **com_stream);
// void	to_struct(t_data *data, t_command **com_stream, t_token *stream);
void to_commands(t_data *data);
void free_env(t_envies *env);
void frees(t_data *data);
int	one_com(t_data *data);
int piping(t_data *data);
int not_file(char *filename);
void	wait_and_sig(int status);
void free_export(t_export *export);
void free_spl(char **splited);
t_envies *new_node(char *key, char *value);
void init_env(t_envies **envp, char **environ);
char	*what_path(char **paths, char *command);
int	ft_lstcnt(t_envies *lst);
void	dups(t_command *com, int **pip, t_data *data);
char **to_matrix(t_envies *envies);
void print_env(char **env);
int execution(t_data *data);
char *if_env(char *str, t_envies *env);
void open_fields(t_token *stream, t_envies *env);
void signal_hend(int signum);
void init_line(t_data *data, char **environ);
int	redirs(t_token *stream);
t_token	*cut_red(t_token *stream);
void	delete_files(t_token **stream);
int parse(t_data *data, char *str);
void	init_path(t_data *data);
int signals (void);
int	for_heredoc(char *filename);
char *file_name(t_token *stream);
void find_com(t_token **stream, int fd , int fedo);
t_token	*token_1(char **str);
t_token	*token_2(char **str);
t_token	*token_3(char **str);
t_token	*token_4(char **str);
t_token	*token_5(char **str);
void free_tokens(t_token *stream);
t_token	*which_token(char **str);
int	tokenize(t_token **stream, char *str);
int		redir_error(void);
void	open_eror(void);
int		validation(t_token *stream);
void	prin(t_token *stream, t_command *com_stream);
void	pri(t_command *com_stream);
void print_en(t_envies *envies);
int	split_len(char **str);
t_command	*new_com(char **args, int in, int out);
char **init_com(t_token **stream);
int	ft_com_len(t_data *data);
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
void error_msg(char *str, int exs);
int	built_in(t_command *node, t_data *data,t_envies *env);
void	fill_the_export(t_export **export, t_envies *env);
int is_built_in(t_command *node);
void free_coms(t_command *stream);
int ft_pip_cnt(t_data *data);
int ft_norm_name(char ch);
void ft_run(t_data *data);

//built_insss davitashn 1 taxamas 8rd shenq

int ft_cd(t_command *node,  t_envies *env);
int ft_pwd(void);
void signal_hend(int signum);
int hand(void);
int signals (void);
void foo(int num);
void	ft_lstadd_gr(t_export **lst, t_export *new);
void	ft_lstadd_fr(t_envies **lst, t_envies *new);
int ft_exxport(t_command *node, t_data *data, t_export **export, t_envies **env);
void	delete_node(t_envies **env, char *del_node);
t_export	*new_expo_node(char *key, char *value);
int ft_unset(t_command *node, t_envies *env, t_export *export);
char	*f_v(char	*str);
char	*f_k(char	*str, int *flag);
int ft_echo(t_data *data, t_command *node);
void	printing_export(t_export *export);
int ft_env(t_command *node, t_envies *env);
int ft_strcmp_up(char *str, char *chm);
int ft_export(t_command *node, t_data *data);
void update_value(t_export **export, char *key, char *value);
void join_to_value(t_export **export, char *key, char *value);
long long int	ft_long_atoi(const char *str);
int is_export(t_export **export, char *str);
void	helpp(t_export **export, char *key, char *value, int flag);
void export_delete(t_export **export, char *node);
void free_kv(char *key, char *value);
void ft_exit(t_command *node, t_data *data);
char *find_env(t_envies **env, char *key);
unsigned long long for_llu(t_command *node);
long long for_ll(t_command *node);
void to_env(t_envies **env, char *key, char *value);
int option(t_token *stream, t_command *node);
int numeric(char **command);
int	g_exit_statuss;
#endif