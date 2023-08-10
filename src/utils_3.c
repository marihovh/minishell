/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 21:09:24 by marihovh          #+#    #+#             */
/*   Updated: 2023/08/09 21:24:49 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void free_data(t_data *data)
{
	while (data->envies)
	{
		free(data->envies);
		data->envies = data->envies->next;
	}
	while (data->stream)
	{
		free (data->stream);
		data->stream = data->stream->next;
	}
	free (data);
}

char *file_join(char *buffer, char *stat)
{
	char	*join;
	size_t	i;
	size_t	c;

	if (!stat)
	{
		stat = (char *)malloc(sizeof(char) * 1);
		stat[0] = '\0';
	}
	if (!stat || !buffer)
		return (NULL);
	i = -1;
	c = -1;
	join = (char *)malloc(sizeof(char)
			* (ft_strlen(stat) + ft_strlen(buffer) + 1));
	if (!join)
		return (NULL);
	while (stat[++i] != '\0')
		join[i] = stat[i];
	while (buffer[++c])
		join[i++] = buffer[c];
	join[i] = '\0';
	return (join);
}