/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 20:49:55 by marihovh          #+#    #+#             */
/*   Updated: 2023/09/07 21:19:18 by marihovh         ###   ########.fr       */
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



void ft_pip_cnt(t_data *data)
{
	t_command *tmp;

	tmp = data->com_stream;
	int i = 0;
	while (data->com_stream)
	{
		i++;
		data->com_stream = data->com_stream->next;
	}
	data->com_stream = tmp;
	data->pip_cnt = i - 1;
}

// int	**piping(t_data *data)
// {
// 	int i;

// 	i = -1;
// 	ft_pip_cnt(data);
// 	int pip[data->pip_cnt][2];
// 	while (++i < data->pip_cnt)
// 	{
// 		if (pipe(pip[i]) == -1)
// 		{
// 			printf("Pipe error\n");
// 			return (0);
// 		}
// 	}
// 	return (pip);
// }

void ft_run(t_data *data)
{
	char *path = NULL;
	char **env = NULL;
	init_path(data);
	// built_in
	if (is_built_in(data->com_stream))
	{
		// fill_the_export(&data->export, &data->envies);
		printf("built in\n");
		built_in(data->com_stream, data, data->envies);
		return ;
	}
	path = what_path(data->paths, data->com_stream->command[0]);
	if (path != NULL)
	{
		env = to_matrix(data->envies);
		if (execve(path, data->com_stream->command, env))
		init_env(&data->envies, env);
		free_spl(env);
	}else
	{
		printf("shyshell : %s: command not found\n", data->com_stream->command[0]);
		init_env(&data->envies, env);
		free_spl(env);
		*data->exit_status = 127;
		exit(0);
	}
}
void dups(t_command *com, int pip[][2], int i)
{
	if (com->prev != NULL)
		com->in = pip[i - 1][0];
	if (com->next != NULL)
		com->out = pip[i][1];
	if (com->in != STDIN)
		dup2(com->in, STDIN);
	if (com->out != STDOUT)
		dup2(com->out, STDOUT);
}

int	execute(t_data *data)
{
	int i = 0;

	i = -1;
	ft_pip_cnt(data);
	int pip[data->pip_cnt][2];
	while (++i < data->pip_cnt)
	{
		if (pipe(pip[i]) == -1)
		{
			printf("Pipe error\n");
			return (0);
		}
	}
	i = 0;
	while (data->com_stream && i < data->pip_cnt + 1)
	{
		signals();
		if (is_built_in(data->com_stream))
		{
			dups(data->com_stream, pip, i);
			built_in(data->com_stream, data, data->envies);
		}
		else
		{
			pid_t f = fork();
			if (f == 0)
			{
				signals();
				if (pip[i][0] != 0)
					close(pip[i][0]);
				dups(data->com_stream, pip, i);
				ft_run(data);
				exit(0);
			}
			else
			{
				signals();
				if (pip[i][1] != 1)
					close(pip[i][1]);
				waitpid(f, NULL, 0);
			}
		}
		i++;
		data->com_stream = data->com_stream->next;
	}
	// waitpid(-1, NULL, 0);
	return (0);
}
