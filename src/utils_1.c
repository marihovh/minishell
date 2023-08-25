/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 09:44:10 by marihovh          #+#    #+#             */
/*   Updated: 2023/08/24 21:53:11 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	split_len(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

t_command	*new_com(char **args, int in, int out)
{
	t_command	*new_com;
	int			i;
	int			len;

	i = -1;
	new_com = malloc(sizeof(t_command));
	len = split_len(args);
	new_com->command = malloc(sizeof(char *) * (len + 1));
	if (!new_com)
		return (NULL);
	while (++i < len)
	{
		new_com->command[i] = ft_strdup(args[i]);
		free(args[i]);
	}
	free(args);
	new_com->command[i] = NULL;
	new_com->out = out;
	new_com->in = in;
	new_com->next = NULL;
	return (new_com);
}

int	ft_com_len(t_token *stream)
{
	int	i;

	i = 0;
	t_token	*tmp = stream;
	while (tmp)
	{
		if (tmp->type == PIPE)
			i++;
		tmp = tmp->next;
	}
	return (i);
}

char	*one_dol(char **str)
{
	char	*chunk;

	if (!(**str))
	{
		chunk = (char *)malloc(sizeof(char) * 1);
		chunk[0] = '\0';
		return (chunk);
	}
	return (NULL);
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
		if (**str == '$' || **str == '?')
		{
			if (i != 1)
				i--;
			else
				(*str)++;
			break ;
		}
		(*str)++;
	}
	// if (!(*str[0]))
	// 	*str = NULL;
	chunk[i] = '\0';
	return (chunk);
}
