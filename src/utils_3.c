/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 21:09:24 by marihovh          #+#    #+#             */
/*   Updated: 2023/10/08 01:26:59 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

long long int	ft_long_atoi(const char *str)
{
	int				i;
	int				minus;
	long long int	num;

	i = 0;
	minus = 1;
	num = 0;
	while (str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r' || str[i] == 32)
		i++;
	if (str[i] == '-')
		minus = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= 48 && str[i] <= 57)
		num = (num * 10) + (str[i++] - 48);
	return (num * minus);
}

char	*env_name(char **str)
{
	char	*chunk;
	int		i;

	i = 0;
	(*str)++;
	chunk = one_dol(str);
	if (chunk)
		return (chunk);
	chunk = malloc(sizeof(char) * ft_strlen(*str) + 1);
	while (**str)
	{
		chunk[i++] = **str;
		if (!ft_norm_name(**str))
		{
			if (i != 1)
				i--;
			else
				(*str)++;
			break ;
		}
		(*str)++;
	}
	chunk[i] = '\0';
	return (chunk);
}

void	set_fd(t_token **stream, int fd, int fedo)
{
	if (!(*stream))
		return ;
	if (fedo == 1)
		(*stream)->in = fd;
	else
		(*stream)->out = fd;
}
