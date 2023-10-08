/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 11:45:22 by marihovh          #+#    #+#             */
/*   Updated: 2023/10/08 20:23:59 by marihovh         ###   ########.fr       */
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
			return (3);
	}
	return (0);
}

void	tilda(t_token *stream, char *home)
{
	char	*tmp;

	tmp = NULL;
	while (stream)
	{
		if (stream->value[0] == '~' && (!stream->value[1] \
			|| stream->value[1] == '/'))
		{
			tmp = ft_strdup(stream->value);
			free(stream->value);
			stream->value = ft_strjoin(ft_strdup(home), tmp + 1);
			free(tmp);
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
	// t_token *es;
	if (tokenize(&data->stream, str, &data->token_cnt))
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
	// normalize(&data->stream);
	// es = data->stream;
	normalize(&data->stream);
		// return (1);
	// printf("asa%s\n", data->stream->value);
	// data->stream = es;
	// prin(data->stream, NULL);
	// exit(0);
	t = redirs(&data->stream, data->envies, data->token_cnt);
	if (t == 1 || t == 3)
	{
		free_tokens(data->stream);
		return (1);
	}
	// prin(data->stream, data->com_stream);
	if (t == 2)
	{
		free_tokens(data->stream);
		return (1);
	}
	return (0);
}
