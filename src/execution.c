/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 20:49:55 by marihovh          #+#    #+#             */
/*   Updated: 2023/08/30 15:29:20 by marihovh         ###   ########.fr       */
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

void dups(int in, int out)
{
	if (in != STDIN)
		dup2(in, STDIN);
	if((out != STDOUT))
		dup2(out, STDOUT);
}

void free_env(t_envies *env)
{
	if (!env)
		return ;
	t_envies *current = env;
    t_envies *nextNode;

    while (current != NULL)
	{
        nextNode = current->next;
        free(current->value);
        free(current->key);
		free(current);
        current = nextNode;
    }
}

int	execute(t_data *data)
{
	char **env = NULL;
	char *path;
	
	init_path(data);
	while (data->com_stream)
	{
		env = to_matrix(data->envies);
		path = what_path(data->paths, data->com_stream->command[0]);
		if (is_built_in(data->com_stream))
		{
			printf("built_in\n");
			init_env(&data->envies, env);
			built_in(data->com_stream, data); // return (value);
		}
		else if (path != NULL)
		{
			// env = to_matrix(data->envies);
			pid_t f = fork();
			if (f == 0)
			{
				signals();
				dups(data->com_stream->in, data->com_stream->out);
				data->exit_status = 1;
				// printf("aaaaa\n");
				// close(fds[0]);
				execve(path, data->com_stream->command, env);
				// write(fds[1, &tf, sizeof(int));
				exit(0);
				// if (execve(path, data->com_stream->command, env))
				// {
				// 	perror("execve");
				// }
				close(data->com_stream->in);
				close(data->com_stream->out);
			}
			init_env(&data->envies, env);
			free_spl(env);
		}
		else
		{
			printf("shyshell : %s: command not found\n", data->com_stream->command[0]);
			init_env(&data->envies, env);
			free_spl(env);
			data->exit_status = 127;
			return (0);
		}
		data->com_stream = data->com_stream->next;
	}
	waitpid(-1, 0, 0);
	return (0);
}
