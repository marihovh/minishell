/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 20:49:55 by marihovh          #+#    #+#             */
/*   Updated: 2023/08/10 17:13:10 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*what_path(char **paths, char *command)
{
	char *res;
	int i;
	
	i = -1;
	while (paths[++i])
	{
		res = ft_strjoin(paths[i], "/");
		res = ft_strjoin(res, command);
		if (access(res, F_OK) == 0)
			return (res);
	}
	printf("shyshell: %s: command not found\n", command);
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

void dups(t_command *command)
{
	// (void)command;
	if (command->in != STDIN)
		dup2(command->in, STDIN_FILENO);
	if (command->out != STDOUT)
		dup2(command->out, STDOUT_FILENO);	
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

void execute(t_data *data)
{
	char **env;
	char *path;
	// skzbic fd-nery 
	// cmdnery lcnum enq u heto dup enq anum
	//hanum enq <  << >> > kam fd-neri het 
	//bultiner stugum enq ete chen uremn execeve
	//pipe-i qanakov fork enq anum
	while (data->com_stream)
	{
		init_path(data);
		path = what_path(data->paths, data->com_stream->command[0]);
		env = to_matrix(data->envies);
		pid_t f = fork();
		if (f == 0)
		{
			printf("yoo man  fd:%i\n", data->com_stream->in);
			if (data->com_stream->in != STDIN)
				dup2(data->com_stream->in, STDIN_FILENO);
			if (data->com_stream->out != STDOUT)
				dup2(data->com_stream->out, STDOUT_FILENO);
			execve(path, data->com_stream->command, env);
			// update_env();
			exit(0);
		}
		data->com_stream = data->com_stream->next;
	}
	waitpid(-1, 0, 0);
}
