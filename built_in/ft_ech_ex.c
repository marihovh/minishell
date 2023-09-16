/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ech_ex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 12:05:49 by marihovh          #+#    #+#             */
/*   Updated: 2023/09/16 18:03:55 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int option(t_command *node)
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
			return (12);
		j++;
	}
	return (flag);
}

int ft_echo(t_command *node) // echo done
{
	int i = 0;
	
	int flag = option(node);
	printf("flag:%i\n", flag);
	if (flag == -1)
	{
		ft_putstr_fd("\n", 1);
		return (0);
	}
	i += flag;
	while (node->command[++i])
		ft_putstr_fd(node->command[i], 1);
	if (!flag)
		ft_putstr_fd("\n", 1);
	return (0);
}

// int ft_echo(t_command *node)
// {
// 	int i;
// 	int j;
// 	int sharunakeli = 0;
// 	if(!(node->command[1]))
// 		write(1, "\n", 1);
// 	j = 0;
// 	i = 1;
// 	while(node->command[i] && node->command[i][0] == '-')
// 	{
// 		if(!(node->command[i][0] == '-'))
// 		{
// 			sharunakeli = i;
// 			break;
// 		}
// 		j = 1;
// 		while(node->command[i][j])
// 		{
// 			if(!(node->command[i][j] == 'n'))
// 				break;
// 			j++;
// 		}
// 		i++;
// 	}
// 	i = 0;
// 	if(sharunakeli == 0)
// 	{
// 		while(node->command[++i])
// 		{
// 			write(1, node->command[i], ft_strlen(node->command[i]));
// 			if(node->command[i + 1])
// 				write(1, "", 1);
// 		}
// 	}
// 	else
// 	{
// 		while(node->command[++sharunakeli])
// 		{
// 			write(1, node->command[sharunakeli], ft_strlen(node->command[sharunakeli]));
// 			if(node->command[sharunakeli + 1])
// 				write(1, " ", 1);
// 		}
// 	}
// 	return (g_exit_statuss);
// }

void ft_exit(t_command *node, t_data *data)
{
	(void)node;
	free_coms(data->com_stream);
	write(1, "exit\n", 5);
	exit(0);
}
