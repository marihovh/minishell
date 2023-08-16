/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 11:45:22 by marihovh          #+#    #+#             */
/*   Updated: 2023/08/16 14:09:07 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void init_line(t_data *data, char **environ)
{
	char *str;

	str = NULL;
	data = malloc(sizeof(t_data));
	while(1)
	{
		str = readline("shyshell$ ");
		if (str[0])
		{
			init_env(&data->envies, environ);
			add_history(str);
			// printf("data->exit_status:%i\n", data->exit_status);
			if (parse(data, str) == 0)
				execute(data);
		}
	}
}

//nayel tuylatreli cahrery filenameri hamar

int	in_and_out(t_token *stream)
{
	int fd;
	char *filename;
	
	while (stream)
	{
		if (stream->op == 1)
		{
			filename = file_name(stream);
			if (stream->type == REDIR_IN)
			{
				fd = open(filename, O_RDONLY);
				if (init_and_check_fd(fd))
					return (1);
				find_com(&stream, fd, 1);
			}
			else if (stream->type == REDIR_OUT && stream->next)
			{
				fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
				if (init_and_check_fd(fd))
					return (1);
				find_com(&stream, fd, 0);
			}
			else if (stream->type == REDIR_AP && stream->next)
			{
				fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0777);
				if (init_and_check_fd(fd))
					return (1);
				find_com(&stream, fd, 0);
			}
			else if (stream->type == REDIR_SO && stream->next)
			{
				filename = file_join(filename, "tmp/");
				fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0777);
				printf("fd:%i\n", fd);
				if (init_and_check_fd(fd))
					return (1);
				for_heredoc(filename , fd);
				find_com(&stream, fd, 1);
			}
		}
		stream = stream->next;
	}
	return (0);
}

//nayel tuylatreli cahrery filenameri hamar

//ctrl+d ev filename 
//heredoc


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

int parse(t_data *data, char *str)
{
	tokenize(&data->stream, str);
	if (!data->stream)
	{
		data->exit_status = 0;
		printf("Armaaaaan\n");
		return (1);
	}
	// while (data->stream)
	// {
	// 	printf(":%s\n", data->stream->value);
	// 	data->stream = data->stream->next;
	// }
	// return (1);
	if (validation(data->stream, &data->exit_status))
		return (1);
	open_fields(data->stream, data->envies, data->exit_status);
	if (in_and_out(data->stream))
	{
		data->exit_status = 1;
		return (1);
	}
		// printf("yooooooo\n");
	// print_stream(data->stream);
	to_commands(data);
	to_struct(data->command, &data->com_stream, data->stream);
	return (0);
}





// void parse(t_data *data, char *str)
// {
// 	tokenize(&data->stream, str);
// 	if (!validation(data->stream))
// 		return ;
// 	open_fields(data->stream, data->envies, data->exit_status);
// 	in_and_out(data->stream);
// 	to_commands(data);
// 	to_struct(data->command, &data->com_stream);
// }

// the syntax of rediraction
// 		command [arguments] < input_file > output_file
// 		command >> output_file
// the syntax of here-doc
	// command <<END_MARKER
	// 	input_lines
	// 	END_MARKER
// the syntax of pipe
// 			command1 | command2 | command3 ...
//  variable syntax
//      variable_name=value
// the syntax of echo
//        echo [options] [text or variable]
// -n is without \n at the end
