/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 09:44:10 by marihovh          #+#    #+#             */
/*   Updated: 2023/09/23 08:46:37 by marihovh         ###   ########.fr       */
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
	new_com->prev = NULL;
	return (new_com);
}

int	ft_com_len(t_data *data)
{
	int	i;

	i = 0;
	t_token	*tmp = data->stream;
	while (data->stream)
	{
		if (data->stream->type == PIPE)
			i++;
		data->stream = data->stream->next;
	}
	data->stream = tmp;
	return (i);
}

char	*one_dol(char **str)
{
	char	*chunk;

	if (!(*str))
	{
		chunk = (char *)malloc(sizeof(char) * 1);
		chunk[0] = '\0';
		return (chunk);
	}
	return (NULL);
}

int ft_norm_name(char ch)
{
	return ((ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122) || (ch >= 48 && ch <= 57) || ch == 95);
}

