/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 10:55:59 by marihovh          #+#    #+#             */
/*   Updated: 2023/09/29 12:48:49 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*what_path(char **paths, char *command)
{
	char	*res;
	int		i;

	i = -1;
	if (access(command, F_OK) == 0)
		return (command);
	while (paths[++i])
	{
		res = ft_strjoin(paths[i], "/");
		res = ft_strjoin(res, command);
		if (access(res, F_OK) == 0)
			return (res);
		free(res);
		res = NULL;
	}
	return (0);
}

int	one_com(t_data *data)
{
	int		status;
	pid_t	f;

	status = 0;
	if (data->com_stream->in != 0)
		dup2(data->com_stream->in, 0);
	if (data->com_stream->out != 1)
		dup2(data->com_stream->out, 1);
	under_(data);
	if (is_built_in(data->com_stream))
		built_in(data->com_stream, data, data->envies);
	else
	{
		f = fork();
		if (f == 0)
		{
			ft_run(data);
			exit(g_exit_statuss);
		}
		wait_and_sig(status);
	}
	dup2(data->in_c, 0);
	dup2(data->out_c, 1);
	return (0);
}
