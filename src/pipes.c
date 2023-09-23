/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 13:40:12 by marihovh          #+#    #+#             */
/*   Updated: 2023/09/22 13:40:57 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int piping(t_data *data)
{
	int pip[data->pip_cnt][2];
	int i = -1;
	int status;
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
		{
			if (data->stream && data->stream->type == PIPE)
			{
				while (data->stream && data->stream->type == WORD)
					data->stream = data->stream->next;
			}
			built_in(data->com_stream, data, data->envies);
		}
		else
		{
			pid_t f = fork();
			if (f == 0)
			{
				signals();
				ft_run(data);
				exit(0);
			}
		}
		dup2(data->in_c, 0);
		dup2(data->out_c, 1);
		close(pip[data->index][1]);
		i++;
		while (data->stream && data->stream->type != PIPE)
			data->stream = data->stream->next;
		free_spl(data->com_stream->command);
		data->com_stream = data->com_stream->next;
	}
	while(wait(&status) != -1)
		;
	if (WIFSIGNALED(status))
	{
		g_exit_statuss = WTERMSIG((status));
		if (g_exit_statuss == SIGINT)
			write(1, "\n", 1);
	}
	return (0);
}
