/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 20:49:55 by marihovh          #+#    #+#             */
/*   Updated: 2023/08/22 11:19:51 by marihovh         ###   ########.fr       */
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
		free(envies);
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

void dups(int in, int out)
{
	if (in != STDIN)
		dup2(in, STDIN);
	if((out != STDOUT))
		dup2(out, STDOUT);
}

void execute(t_data *data)
{
	char **env;
	char *path;
	
	while (data->com_stream)
	{
		init_path(data);
		path = what_path(data->paths, data->com_stream->command[0]);
		if (!path && is_built_in(data->com_stream))
			built_in(data->com_stream, &data->exit_status);
		else if (!path)
		{
			printf("shyshell : %s: command not found\n", data->com_stream->command[0]);
			data->exit_status = 127;
		}
		else
		{
			env = to_matrix(data->envies);
			pid_t f = fork();
			if (f == 0)
			{
				dups(data->com_stream->in, data->com_stream->out);
				execve(path, data->com_stream->command, env);
				close(data->com_stream->in);
				close(data->com_stream->out);
			}
			init_env(&data->envies, env);
		}
		data->com_stream = data->com_stream->next;
	}
	waitpid(-1, 0, 0);
}
