/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ech_ex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 12:05:49 by marihovh          #+#    #+#             */
/*   Updated: 2023/09/18 17:47:23 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int option(t_token *stream, t_command *node)
{
	int flag = 0;
	int i = 0;
	int j = 1;

	if (!node->command[j])
		return (-1);
	while (node->command[j])
	{
		i = 0;
		if (node->command[j][i] == '-')
		{
			i++;
			while (node->command[j][i] && node->command[j][i] == 'n')
				i++;
			if (!node->command[j][i])
				flag++;
		}
		else
			return (flag);
		stream = stream->next;
		if (stream->type == SP)
			stream = stream->next;
		j++;
	}
	return (flag);
}

int ft_echo(t_data *data, t_command *node)
{
	int i = 0;
	
	int flag = option(data->stream, node);
	if (data->stream && data->stream->next)
	{
		data->stream = data->stream->next;
		if (data->stream->next->next)
			data->stream = data->stream->next;
	}
	if (flag == -1)
	{
		ft_putstr_fd("\n", 1);
		return (0);
	}
	i += flag;
	int j = 0;
	while (j++ < flag)
		data->stream = data->stream->next;
	if (data->stream->type == SP)
		data->stream = data->stream->next;
	while (node->command[++i])
	{
		data->stream = data->stream->next;
		ft_putstr_fd(node->command[i], 1);
		if (data->stream && data->stream->type == SP)
		{
			if (node->command[i + 1])
				ft_putstr_fd(" ", 1);
			data->stream = data->stream->next;
		}
	}
	if (!flag)
		ft_putstr_fd("\n", 1);
	return (0);
}


void ft_exit(t_command *node, t_data *data)
{
	(void)node;
	free_coms(data->com_stream);
	write(1, "exit\n", 5);
	exit(0);
}
