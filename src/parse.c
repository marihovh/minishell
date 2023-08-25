/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 11:45:22 by marihovh          #+#    #+#             */
/*   Updated: 2023/08/24 21:54:11 by marihovh         ###   ########.fr       */
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
        } else {
			printf("shyshell: %s: No such file or directory\n", filename);
			return (1);
        }
    }
	return (0);
}

int	in_and_out(t_token *stream)
{
	int fd;
	char *filename;
	
	while (stream)
	{
		if (stream->op == 1)
		{
			filename = file_name(stream);
			if (not_file(filename) == 1)
			{
				free(filename);
				return (1);
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
			if (!stream)
				return (1);
			free(filename);
		}
		stream = stream->next;
	}
	return (0);
}

//nayel tuylatreli cahrery filenameri hamar

t_token *prev_word(t_token *stream)
{
	while (stream)
	{
		if (stream->type == WORD)
			return (stream);
		printf("yoo:%s\n", stream->value);
		stream = stream->prev;
	}
	printf("no  command here\n");
	return (0);
}


void print_stream(t_token *stream)
{
	while (stream)
	{
		printf("token:%s\n\tin:%i\n\tout:%i\n", stream->value, stream->in, stream->out);
		stream = stream->next;
	}
}

void free_com_p(char **command)
{
	int i = -1;
	while (command[++i])
		free(command[i]);
	free(command);
}

int parse(t_data *data, char *str)
{
	tokenize(&data->stream, str, &data->exit_status);
	free(str);
	if (!data->stream)
	{
		data->exit_status = 0;
		// free_tokens(data->stream);
		return (1);
	}
	if (validation(data->stream, &data->exit_status))
	{
		free_tokens(data->stream);
		return (1);
	}
	open_fields(data->stream, data->envies, data->exit_status);
	prin(data->stream, NULL);
	printf("aaaaaa\n");
	// if (in_and_out(data->stream))
	// {
	// 	data->exit_status = 1;
	// 	free_tokens(data->stream);
	// 	return (1);
	// }
	// if (!data->stream)
	// {
	// 	data->exit_status = 0;
	// 	free_tokens(data->stream);
	// 	return (1);
	// }
	// to_commands(data);
	// to_struct(data->command, &data->com_stream, data->stream);
	return (0);
}
