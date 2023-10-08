/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 13:40:12 by marihovh          #+#    #+#             */
/*   Updated: 2023/10/09 01:01:35 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pip_signal(int status)
{
	while (wait(&status) != -1)
		;
	g_exit_statuss = status / 256;
	if (WIFSIGNALED(status))
	{
		g_exit_statuss = WTERMSIG((status));
		if (g_exit_statuss == SIGINT)
			write(1, "\n", 1);
	}
}

void	exec_2(t_data *data, t_token *stream, t_command *com_stream, int **pip)
{
	pid_t	f;

	under_(data);
	f = fork();
	if (f == 0)
	{
		signals();
		if (is_built_in(com_stream))
		{
			if (stream && stream->type == PIPE)
				while (stream && stream->type == WORD)
					stream = stream->next;
			built_in(com_stream, data, data->envies);
		}
		else
		{
			free_pip(pip, data->pip_cnt);
			ft_run(data);
		}
		exit(g_exit_statuss);
	}
	if (stream && stream->type == PIPE)
		while (stream && stream->type == WORD)
			stream = stream->next;
}

int	**init_pipe(t_data *data)
{
	int	**pip;
	int	i;

	pip = malloc((sizeof(int *)) * data->pip_cnt);
	i = -1;
	while (++i < data->pip_cnt)
	{
		pip[i] = malloc(sizeof(int) * 2);
		if (pipe(pip[i]) == -1)
		{
			printf("Pipe error\n");
			return (0);
		}
	}
	return (pip);
}

void	free_pip(int **pip, int pip_cnt)
{
	int	i;

	i = -1;
	while (++i < pip_cnt)
	{
		close(pip[i][1]);
		close(pip[i][0]);
		free(pip[i]);
	}
	free(pip);
}

int	piping(t_data *data)
{
	int	**pip;
	int	status;

	status = 0;
	pip = init_pipe(data);
	if (!pip)
		return (0);
	data->index = 0;
	while (data->index <= data->pip_cnt && data->com_stream->command)
	{
		if (data->com_stream->command[0])
		{
			dups(data->com_stream, pip, data);
			exec_2(data, data->stream, data->com_stream, pip);
			dup2(data->in_c, 0);
			dup2(data->out_c, 1);
			if (data->index < data->pip_cnt)
				close(pip[data->index][1]);
			// if (data->index - 1 >= 0)
			// 	close(pip[data->index - 1][0]);
			while (data->stream && data->stream->type != PIPE)
				data->stream = data->stream->next;
		}
		data->index++;
		data->com_stream = data->com_stream->next;
	}
	pip_signal(status);
	free_pip(pip, data->pip_cnt);
	// if (data->com_stream->in != STDIN)
	// 	close(data->com_stream->in);
	// if (data->com_stream->out != STDOUT)
	// 	close(data->com_stream->out);
	return (0);
}
