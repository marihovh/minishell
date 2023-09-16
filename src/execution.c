/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 20:49:55 by marihovh          #+#    #+#             */
/*   Updated: 2023/09/15 14:39:19 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*what_path(char **paths, char *command)
{
	char *res;
	int i;
	
	i = -1;
	if (access(command, F_OK) == 0)
		return (command);
	while (paths[++i])
	{
		res = ft_strjoin(paths[i], "/");
		res = ft_strjoin(res, command);
		if (access(res, F_OK) == 0)
			return (res);
		else 
			free(res);
		res = NULL;
	}
	return (0);
}

int	ft_lstcnt(t_envies *lst)
{
	t_envies	*curr;
	int			cnt;

	curr = lst;
	cnt = 0;
	while (curr != NULL)
	{
		curr = curr -> next;
		cnt++;
	}
	return (cnt);
}

char **to_matrix(t_envies *envies)
{
	char **matrix = NULL;
	int i = -1;
	int len;

	len = ft_lstcnt(envies);
	matrix = malloc(sizeof(char *) * (len + 1));
	while (envies)
	{
		matrix[++i] = ft_strjoin(envies->key, "=");
		matrix[i] = ft_strjoin(matrix[i], envies->value);
		envies = envies->next;
	}
	matrix[i] = NULL;
	return (matrix);
}

void print_env(char **env)
{
	int i = -1;
	while (env[++i])
		printf("%s\n", env[i]);
}

void free_export(t_export *export)
{
	if (!export)
		return ;
	t_export *current = export;
    t_export *nextNode;
	printf("freeing\n");
    while (current != NULL)
	{
        nextNode = current->next;
        free(current->value);
        free(current->key);
		free(current);
        current = nextNode;
    }
}

void free_env(t_envies *env)
{
	if (!env)
		return ;
	t_envies *current = env;
    t_envies *nextNode;
	printf("freeing\n");
    while (current != NULL)
	{
        nextNode = current->next;
        free(current->value);
        free(current->key);
		free(current);
        current = nextNode;
    }
}

int ft_pip_cnt(t_data *data)
{
	t_command *tmp;

	tmp = data->com_stream;
	int i = 0;
	while (data->com_stream)
	{
		data->com_stream = data->com_stream->next;
		i++;
	}
	data->com_stream = tmp;
	return (i - 1);
}

void ft_run(t_data *data)
{
	char *path = NULL;
	char **env = NULL;
	init_path(data);
	path = what_path(data->paths, data->com_stream->command[0]);
	env = to_matrix(data->envies);
	if (execve(path, data->com_stream->command, env) == -1)
	{
		printf("shyshell : %s: command not found\n", data->com_stream->command[0]);
		init_env(&data->envies, env);
		free_spl(env);
		g_exit_statuss = 127;
	}else
	{
		ft_putstr_fd("advd\n", 1);
		init_env(&data->envies, env);
		free_spl(env);
	}
	exit(0);
}

void dups(t_command *com, int pip[][2], t_data *data)
{
	if (com->prev != NULL && com->in == 0)
		dup2(pip[data->index - 1][0], 0);
	else if (com->in != 0)
		dup2(com->in, 0);
	if (com->next != NULL && com->out == 1)
		dup2(pip[data->index][1], 1);
	else if (com->out != 1)
		dup2(com->out, 1);
}


int one_com(t_data *data)
{
	signals();
	if (data->com_stream->in != 0)
		dup2(data->com_stream->in, 0);
	if (data->com_stream->out != 1)
		dup2(data->com_stream->out, 1);
	if (is_built_in(data->com_stream))
		built_in(data->com_stream, data, data->envies);
	else
	{
		pid_t f = fork();
		if (f == 0)
		{
			ft_run(data);
			exit(0);
		}
		else
			waitpid(f, NULL, 0);
	}
	// system("leaks minishell");
	return (0);
}

int piping(t_data *data)
{
	int pip[data->pip_cnt][2];
	int i = -1;
	while (++i < data->pip_cnt)
	{
		if (pipe(pip[i]) == -1)
		{
			printf("Pipe error\n");
			return (0);
		}
	}
	i = 0;
	while (data->com_stream)
	{
		data->index = i;
		dups(data->com_stream, pip, data);
		if (is_built_in(data->com_stream))
			built_in(data->com_stream, data, data->envies);
		else
		{
			pid_t f = fork();
			if (f == 0)
			{
				signals();
				ft_run(data);
			}
			else
				waitpid(f, NULL, 0);
		}
		dup2(data->in_c, 0);
		dup2(data->out_c, 1);
		close(pip[data->index][1]);
		i++;
		free_spl(data->com_stream->command);
		data->com_stream = data->com_stream->next;
	}
	return (0);
}


int	execution(t_data *data)
{
	data->pip_cnt = ft_pip_cnt(data);
	if (!data->pip_cnt)
	{
		signals();
		one_com(data);
		// free_coms(data->com_stream);
		dup2(data->in_c, 0);
		dup2(data->out_c, 1);
	}else
	{
		piping(data);
	}
	return (0);
}
