/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ech_ex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 12:05:49 by marihovh          #+#    #+#             */
/*   Updated: 2023/09/28 11:02:50 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_w_sp(t_data *data, t_command *node, int flag)
{
	int	i;
	int	j;

	i = flag;
	j = 0;
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
}

int	ft_echo(t_data *data, t_command *node)
{
	t_token	*tmp;
	int		flag;

	flag = option(data->stream, node);
	tmp = data->stream;
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
	print_w_sp(data, node, flag);
	data->stream = tmp;
	g_exit_statuss = 0;
	return (0);
}

int	parse_ex(char **command)
{
	int	i;

	i = 0;
	if (!command[1])
		return (0);
	else
	{
		i = numeric(command);
		if (i >= 20)
		{
			ft_putstr_fd("shyshell: exit: ", 2);
			ft_putstr_fd(command[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			g_exit_statuss = 255;
			return (255);
		}
		if (command[2])
		{
			ft_putstr_fd("shyshell: exit: too many arguments\n", 2);
			g_exit_statuss = 1;
			return (-1);
		}
	}
	return (42);
}

void	free_for_exit(t_data *data)
{
	close(data->in_c);
	close(data->out_c);
}

void	ft_exit(t_command *node, t_data *data)
{
	unsigned long long	num;
	long long			num1;
	int					result;

	write(1, "exit\n", 5);
	result = parse_ex(node->command);
	if (result == -1)
		return ;
	if (result != 42)
	{
		free_for_exit(data);
		exit(result);
	}
	if (node->command[1][0] == '-')
	{
		num1 = for_ll(node);
		free_for_exit(data);
		exit(num1);
	}
	else
	{
		num = for_llu(node);
		free_for_exit(data);
		exit(num);
	}
}
