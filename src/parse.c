/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 11:45:22 by marihovh          #+#    #+#             */
/*   Updated: 2023/08/15 13:08:13 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void init_line(t_data *data, char **environ)
{
	char *str;

	str = NULL;
	data = malloc(sizeof(t_data));
	while(str == NULL || ft_strncmp("C", str, 1) != 0)
	{
		str = readline("shyshell$ ");
		if (str && ft_strlen(str) > 0)
		{
			init_env(&data->envies, environ);
			add_history(str);
			if (parse(data, str) == 0)
				execute(data);
		}
	}
}

//nayel tuylatreli cahrery filenameri hamar

int	in_and_out(t_token *stream)
{
	int fd;
	int fd2;
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
				find_com(&stream, fd, STDOUT);
			}
			else if (stream->type == REDIR_OUT && stream->next)
			{
				fd = open(filename,O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (init_and_check_fd(fd))
					return (1);
				find_com(&stream, STDIN, fd);
			}
			else if (stream->type == REDIR_AP && stream->next)
			{
				fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0777);
				if (init_and_check_fd(fd))
					return (1);
				find_com(&stream, STDIN, fd);
			}
			else if (stream->type == REDIR_SO && stream->next)
			{
				filename = file_join(filename, "tmp/");
				fd2 = open(filename, O_RDWR);
				printf("fd2:%i\n", fd2);
				if(fd2 > 0)
				{
					for_heredoc(filename , fd2);
					find_com(&stream, fd2, STDOUT);
				}
				else
				{
					fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0777);
					for_heredoc(filename , fd);
					find_com(&stream, fd, STDOUT);
				}
			}
		}
		stream = stream->next;
	}
	return (0);
}

//nayel tuylatreli cahrery filenameri hamar

//ctrl+d ev filename 
//heredoc

// void	cut_red(t_token **stream)
// {
// 	while (*stream)
// 	{
// 		if ((*stream)->type == WORD)
// 		{
// 			// free(*stream);
// 			return ;
// 		}
// 		free(*stream);
// 		(*stream) = (*stream)->next;
// 	}
// }

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


t_token *cut_red(t_token *stream)
{
	while (stream)
	{
		if (stream->type == WORD)
			return (stream->next);
		stream = stream->next;
	}
	return (NULL);
}


int	delete_files(t_token *stream)
{
	t_token *tmp;
	while (stream)
	{
		if (stream->op == 1)
		{
			if (stream->prev != NULL)
				stream->prev->next = cut_red(stream);
			else
			{
				tmp = cut_red(stream);
				if (tmp == NULL)
					return (1);
				*stream = *tmp;
			}
		}
		stream = stream->next;
	}
	return (0);
}

int parse(t_data *data, char *str)
{
	tokenize(&data->stream, str);
	if (!validation(data->stream))
	{
		data->exit_status = 1;
		return (1);
	}
	open_fields(data->stream, data->envies, data->exit_status);
	if (in_and_out(data->stream))
	{
		data->exit_status = 1;
		return (1);
	}
	if (delete_files(data->stream) == 1)
	{
		data->exit_status = 0;
		printf("inch anem e ay axper\n");
		return (0);
	}
	// if (!data->stream)
	// 	printf("chee axper jan command chunes\n");
	// // printf("yoo\n");	
	// while (data->stream)
	// {
		
	// 	printf("data->stream:%s\n", data->stream->value);
	// 	data->stream = data->stream->next;
	// }
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
