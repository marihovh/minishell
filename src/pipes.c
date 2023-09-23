/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 13:40:12 by marihovh          #+#    #+#             */
/*   Updated: 2023/09/23 16:08:25 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pip_signal(int status)
{
	while (wait(&status) != -1)
		;
	if (WIFSIGNALED(status))
	{
		g_exit_statuss = WTERMSIG((status));
		if (g_exit_statuss == SIGINT)
			write(1, "\n", 1);
	}
}

void	exec_2(t_data *data, t_token *stream, t_command *com_stream)
{
	pid_t	f;

	if (is_built_in(com_stream))
	{
		if (stream && stream->type == PIPE)
			while (stream && stream->type == WORD)
				stream = stream->next;
		built_in(com_stream, data, data->envies);
	}
	else
	{
		f = fork();
		if (f == 0)
		{
			signals();
			ft_run(data);
			exit(0);
		}
	}
	dup2(data->in_c, 0);
	dup2(data->out_c, 1);
}

int	**init_pipe(t_data *data)
{
	int	**pip;
	int	i;

	pip = malloc(sizeof(int *) * data->pip_cnt);
	i = -1;
	while (++i < data->pip_cnt)
	{
		if (pipe(pip[i]) == -1)
		{
			printf("Pipe error\n");
			return (0);
		}
	}
	return (pip);
}

int	piping(t_data *data)
{
	int	**pip;
	int	i;
	int	status;

	status = 0;
	pip = init_pipe(data);
	if (!pip)
		return (0);
	i = 0;
	while (data->com_stream)
	{
		data->index = i;
		dups(data->com_stream, pip, data);
		exec_2(data, data->stream, data->com_stream);
		close(pip[data->index][1]);
		i++;
		while (data->stream && data->stream->type != PIPE)
			data->stream = data->stream->next;
		free_spl(data->com_stream->command);
		data->com_stream = data->com_stream->next;
	}
	pip_signal(status);
	return (0);
}
