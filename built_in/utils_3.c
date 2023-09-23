/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 08:28:26 by marihovh          #+#    #+#             */
/*   Updated: 2023/09/23 10:27:37 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

unsigned long long	for_llu(t_command *node)
{
	unsigned long long	num;

	num = ft_long_atoi(node->command[1]);
	if (num > 9223372036854775807)
	{
		ft_putstr_fd("shyshell: exit: ", 2);
		ft_putstr_fd(node->command[1], 2);
		ft_putstr_fd(" :numeric argument required\n", 2);
		g_exit_statuss = 255;
		return (255);
	}
	if (num >= 256)
		num %= 256;
	return (num);
}

long long	for_ll(t_command *node)
{
	long long	num1;

	num1 = ft_long_atoi(node->command[1]);
	if (num1 < -9223372036854775807)
	{
		ft_putstr_fd("shyshell: exit: ", 2);
		ft_putstr_fd(node->command[1], 2);
		ft_putstr_fd(" :numeric argument required\n", 2);
		g_exit_statuss = 255;
		return (255);
	}
	if (num1 < 0)
		while (num1 < 0)
			num1 += 256;
	if (num1 >= 256)
		num1 %= 256;
	return (num1);
}

int	numeric(char **command)
{
	int	i;

	i = 0;
	if (command[1][i] == '-' || command[1][i] == '+')
			i++;
	while (command[1][i])
	{
		if (!(command[1][i] >= '0' && command[1][i] <= '9'))
		{
			ft_putstr_fd("shyshell: exit: ", 2);
			ft_putstr_fd(command[1], 2);
			ft_putstr_fd("numeric argument required\n", 2);
			return (255);
		}
		i++;
	}
	return (i);
}
