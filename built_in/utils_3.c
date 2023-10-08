/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 08:28:26 by marihovh          #+#    #+#             */
/*   Updated: 2023/10/08 20:49:16 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

unsigned long long int	for_llu(t_command *node)
{
	int					len;
	unsigned long long	num;

	len = ft_strlen(node->command[1]);
	printf("len:%i\n", len);
	num = ft_long_atoi(node->command[1]);
	if (num > 9223372036854775807 || len > 19)
	{
		ft_putstr_fd("shyshell: exit: ", 2);
		ft_putstr_fd(node->command[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		g_exit_statuss = 255;
		return (255);
	}
	if (num >= 256)
		num %= 256;
	return (num);
}

long long int	for_ll(t_command *node)
{
	long long	num1;

	num1 = ft_long_atoi(node->command[1]);
	if (num1 < -9223372036854775807)
	{
		ft_putstr_fd("shyshell: exit: ", 2);
		ft_putstr_fd(node->command[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
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
			ft_putstr_fd(": numeric argument required\n", 2);
			return (255);
		}
		i++;
	}
	return (i);
}

void	update_env_value(t_envies **env, char *key, char *value)
{
	while ((*env))
	{
		if (!ft_strcmp(key, (*env)->key))
		{
			free((*env)->value);
			(*env)->value = ft_strdup(value);
			return ;
		}
		env = &(*env)->next;
	}
}

char	*find_env(t_envies **env, char *key)
{
	while (*env)
	{
		if (!ft_strcmp((*env)->key, key))
			return (ft_strdup((*env)->value));
		env = &(*env)->next;
	}
	return (0);
}
