/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 11:45:22 by marihovh          #+#    #+#             */
/*   Updated: 2023/09/23 15:49:41 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	not_file(char *filename)
{
	struct stat	path_stat;

	if (stat(filename, &path_stat) == 0)
	{
		if (S_ISREG(path_stat.st_mode))
			return (0);
		if (S_ISDIR(path_stat.st_mode))
		{
			write(2, "shyshell: ", 10);
			write(2, filename, ft_strlen(filename));
			write(2, ": Is a directory\n", 17);
			g_exit_statuss = 1;
			return (1);
		}
		else
			return (1);
	}
	return (0);
}

void	tilda(t_token *stream, char *home)
{
	while (stream)
	{
		if (stream->value[0] == '~' && (!stream->value[1] \
			|| stream->value[1] == '/'))
		{
			stream->value++;
			stream->value = ft_strjoin(home, stream->value);
		}
		stream = stream->next;
	}
}

void	free_com_p(char **command)
{
	int	i;

	i = -1;
	while (command[++i])
		free(command[i]);
	free(command);
}

int	parse(t_data *data, char *str)
{
	int	t;

	if (tokenize(&data->stream, str))
	{
		free(str);
		free_tokens(data->stream);
		return (1);
	}
	tilda(data->stream, data->home);
	open_fields(data->stream, data->envies);
	free(str);
	if (validation(data->stream))
	{
		free_tokens(data->stream);
		return (1);
	}
	t = redirs(data->stream);
	if (t == 1 || t == 3)
	{
		free_tokens(data->stream);
		g_exit_statuss = 0;
		return (1);
	}
	return (0);
}
