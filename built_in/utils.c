/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 11:58:56 by marihovh          #+#    #+#             */
/*   Updated: 2023/09/24 00:23:04 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_lstadd_fr(t_envies **lst, t_envies *new)
{
	if (!lst)
		return ;
	new->next = *lst;
	*lst = new;
}

void	ft_lstadd_gr(t_export **lst, t_export *new)
{
	if (!lst)
		return ;
	new->next = *lst;
	*lst = new;
}

char	*f_k(char	*str, int *flag)
{
	char	*key;
	char	*esim;
	int		len;

	key = NULL;
	if (!str)
		return (NULL);
	esim = ft_strchr(str, '=');
	if (!esim)
		return (ft_strdup(str));
	len = ft_strlen(esim);
	if (((str + ft_strlen(str)) - len - 1)[0] == '+')
	{
		*flag = 1;
		len += 1;
	}
	if (esim)
		key = ft_substr(str, 0, ft_strlen(str) - len);
	return (key);
}

char	*f_v(char	*str)
{
	char	*tmp;

	str = ft_strchr(str, '=');
	if (!str)
		return (NULL);
	str++;
	tmp = ft_substr(str, 0, ft_strlen(str));
	return (tmp);
}

int	option(t_token *stream, t_command *node)
{
	int	flag;
	int	i;
	int	j;

	j = 0;
	flag = 0;
	if (!node->command[j])
		return (-1);
	while (node->command[++j])
	{
		i = 0;
		if (node->command[j][i++] == '-')
		{
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
	}
	return (flag);
}
