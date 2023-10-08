/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/07 16:24:27 by marihovh          #+#    #+#             */
/*   Updated: 2023/10/08 21:59:45 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*token_6(char **str)
{
	char	*ch;

	(*str)++;
	if (**str == 60)
	{
		(*str) += 1;
		ch = ft_strdup("<<");
		return (new_token(REDIR_SO, ch, 1));
	}
	else
	{
		ch = ft_strdup("<");
		return (new_token(REDIR_IN, ch, 1));
	}
	error_msg("shyshell: <: Token error", 1);
	return (0);
}

t_token	*token_9(char **str)
{
	char	*ch;

	(*str)++;
	ch = ft_strdup("|");
	return (new_token(PIPE, ch, 0));
}

void	free_data(t_data *data)
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

char	*file_join(char *buffer, char *stat)
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

void	wait_and_sig(int status)
{
	while (wait(&status) != -1)
		;
	g_exit_statuss = status / 256;
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG((status)) == SIGINT)
		{
			write(1, "\n", 1);
			g_exit_statuss = 130;
		}
		if (WTERMSIG((status)) == SIGQUIT)
		{
			write(1, "Quit: 3", 7);
			write(1, "\n", 1);
			g_exit_statuss = 131;
		}
	}
}
