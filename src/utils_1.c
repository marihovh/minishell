/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 09:44:10 by marihovh          #+#    #+#             */
/*   Updated: 2023/08/07 16:21:41 by marihovh         ###   ########.fr       */
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

t_command	*new_com(char **args)
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
		new_com->command[i] = args[i];
	new_com->command[i] = NULL;
	new_com->out = STDOUT;
	new_com->in = STDIN;
	new_com->next = NULL;
	return (new_com);
}

int	ft_com_len(t_token *stream)
{
	int	i;

	i = 0;
	while (stream)
	{
		if (stream->type == PIPE)
			i++;
		stream = stream->next;
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
	chunk[i] = '\0';
	return (chunk);
}
