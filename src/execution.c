/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 20:49:55 by marihovh          #+#    #+#             */
/*   Updated: 2023/10/09 01:05:17 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**to_matrix(t_envies *envies)
{
	char	**matrix;
	int		i;
	int		len;

	i = -1;
	matrix = NULL;
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

void	from_matrix(t_envies **envp, char **matrix)
{
	int	i;

	i = -1;
	while (matrix[++i])
	{
		(*envp) = new_node(matrix[0], matrix[1]);
		if (!(*envp))
			break ;
		envp = &(*envp)->next;
	}
}

void	ft_run_helper(char *com_stream, char *path)
{
	ft_putstr_fd("shyshell : ", 2);
	ft_putstr_fd(com_stream, 2);
	ft_putstr_fd(": command not found\n", 2);
	free(path);
	g_exit_statuss = 127;
}

void	ft_run(t_data *data)
{
	char	*path;
	char	**env;

	path = NULL;
	env = NULL;
	if (!data->com_stream->command[0])
		return ;
	init_path(data);
	if (data->paths == NULL)
	{
		fd_error(1, data->com_stream->command[0]);
		g_exit_statuss = 127;
		exit(127);
	}
	path = what_path(data->paths, data->com_stream->command[0]);
	env = to_matrix(data->envies);
	if (execve(path, data->com_stream->command, env) == -1) {
		ft_run_helper(data->com_stream->command[0], path);
		free_spl(env);
	}
}

void	dups(t_command *com, int **pip, t_data *data)
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
