/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 11:45:22 by marihovh          #+#    #+#             */
/*   Updated: 2023/09/18 17:21:09 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//nayel tuylatreli cahrery filenameri hamar

int not_file(char *filename)
{
	struct stat path_stat;

    if (stat(filename, &path_stat) == 0)
	{
        if (S_ISREG(path_stat.st_mode)) {
            return (0);
        } else if (S_ISDIR(path_stat.st_mode)) {
            printf("shyshell: %s: Is a directory\n", filename);
			return (1);
        } else
			return (2);
    }
	return (0);
}

int	in_and_out(t_token *stream)
{
	int fd;
	char *filename;
	int nb;
	
	while (stream)
	{
		if (stream->op == 1)
		{
			filename = file_name(stream);
			nb = not_file(filename);
			if (nb == 1 || nb == 2)
			{
				// printf("voch mek\n");
				free(filename);
				return (nb);
			}
			if (stream->type == REDIR_IN)
			{
				fd = open(filename, O_RDONLY);
				if (fd < 0)
				{
					free(filename);
					printf("the file does not exist\n");
					return (1);
				}
				find_com(&stream, fd, 1);
			}
			else if (stream->type == REDIR_OUT && stream->next)
			{
				fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
				find_com(&stream, fd, 0);
				// prin(stream, NULL);
			}
			else if (stream->type == REDIR_AP && stream->next)
			{
				fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0777);
				find_com(&stream, fd, 0);
			}
			else if (stream->type == REDIR_SO && stream->next)
			{
				fd = for_heredoc(filename);
				if (fd == -1)
					return (1);
				find_com(&stream, fd, 1);
			}
			free(filename);
			if (!stream)
				return (2);
		}
		stream = stream->next;
	}
	return (0);
}

//nayel tuylatreli cahrery filenameri hamar


void free_com_p(char **command)
{
	int i = -1;
	while (command[++i])
		free(command[i]);
	free(command);
}

int parse(t_data *data, char *str)
{
	if (tokenize(&data->stream, str))
		return (1);
	free(str);
	if (!data->stream)
	{
		g_exit_statuss = 0;
		return (1);
	}
	open_fields(data->stream, data->envies);
	if (validation(data->stream))
	{
		free_tokens(data->stream);
		return (1);
	}
	if (in_and_out(data->stream))
	{
		g_exit_statuss = 1;
		return (1);
	}
	if (!data->stream)
	{
		g_exit_statuss = 0;
		free_tokens(data->stream);
		return (1);
	}
	to_struct(data, &data->com_stream);
	// prin(data->stream, data->com_stream);
	// exit (0);
	return (0);
}
