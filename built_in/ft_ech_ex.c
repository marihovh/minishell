/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ech_ex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 12:05:49 by marihovh          #+#    #+#             */
/*   Updated: 2023/09/07 15:28:01 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_echo(t_command *node)
{
	int i;
	int j;
	int sharunakeli = 0;
	if(!(node->command[1]))
		printf("\n");
	j = 0;
	i = 1;
	while(node->command[i] && node->command[i][0] == '-')
	{
		if(!(node->command[i][0] == '-'))
		{
			sharunakeli = i;
			break;
		}
		j = 1;
		while(node->command[i][j])
		{
			if(!(node->command[i][j] == 'n'))
				break;
			j++;
		}
		i++;
	}
	i = 0;
	if(sharunakeli == 0)
	{
		while(node->command[++i])
		{
			printf("%s",node->command[i]);
			if(node->command[i + 1])
				printf("");
		}
	}
	else
	{
		while(node->command[++sharunakeli])
		{
			printf("%s",node->command[sharunakeli]);
			if(node->command[sharunakeli + 1])
				printf(" ");
		}
	}
	return (node->exit_status);
}

void ft_exit(t_data *data)
{
	free_coms(data->com_stream);
	printf("exit\n");
	exit(0);
}