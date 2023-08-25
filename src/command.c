/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 14:09:56 by marihovh          #+#    #+#             */
/*   Updated: 2023/08/24 21:32:35 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_spl(char **splited)
{
	int	k;

	k = -1;
	while (splited && splited[++k])
	{
		free(splited[k]);
		splited[k] = NULL;
	}
	free(splited);
}

void	to_struct(char **command, t_command **com_stream, t_token *stream)
{
	char	**splited;
	int		i;
	int		j;
	int		len;

	i = -1;
	while (command[++i])
	{
		j = 0;
		splited = ft_split(command[i], ' ');
		len = split_len(splited) * 2 - 2;
		while (len--)
			stream = stream->next;
		(*com_stream) = new_com(splited, stream->in, stream->out);
		if (!(*com_stream))
			break ;
		com_stream = &(*com_stream)->next;
	}
	i = -1;
	while (command[++i])
		free(command[i]);
	free(command);
}

void	to_commands(t_data *data)
{
	char	*str;
	t_token	*ptr;
	int		i;

	str = NULL;
	i = 0;
	ptr = data->stream;
	data->command = malloc(sizeof(char *) * (ft_com_len(data->stream) + 2));
	while (data->stream)
	{
		if (data->stream->type == PIPE)
		{
			data->command[i] = ft_strdup(str);
			free(str);
			str = NULL;
			i++;
			data->stream = data->stream->next;
		}
		str = ft_strjoin(str, data->stream->value);
		data->stream = data->stream->next;
	}
	data->stream = ptr;
	data->command[i] = ft_strdup(str);
	free(str);
	data->command[i + 1] = NULL;
}
