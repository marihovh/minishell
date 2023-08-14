/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 11:45:22 by marihovh          #+#    #+#             */
/*   Updated: 2023/08/09 21:36:23 by marihovh         ###   ########.fr       */
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
			if (!parse(data, str))
				execute(data);
		}
	}
}

t_token *which_token(char **str)
{
	t_token *token;
	
	token = NULL;
	if (*str[0] == '|')
		token = token_9(str);
	else if (*str[0] == 39)
		token = token_3(str);
	else if (*str[0] == '>')
		token = token_5(str);
	else if (*str[0] == '<')
		token = token_6(str);
	else if (*str[0] == 34)
		token = token_4(str);
	else if (ft_isprint(*str[0]))
		token = token_2(str);
	else if (ft_isspace(*str[0]))
		token = token_1(str);
	else
		error_msg("Token error\n");
	return (token);
}


void tokenize(t_token **stream, char *str)
{
	t_token *tmp;
	
	tmp = NULL;
	while (*str)
	{
		(*stream) = which_token(&str);
		if (!(*stream))
			break ;
		if (tmp)
			(*stream)->prev = tmp;
		tmp = (*stream);
		// printf("<%s>\n", (*stream)->value);
		stream = &(*stream)->next;
	}
}

int init_and_check_fd(int fd)
{
	if (fd == -1)
		printf("that file doesn't exist\n");
	return(-1);
}

char *araj_gna(t_token **stream)
{
	while (*stream && (*stream)->type != WORD)
	{
		*stream = (*stream)->next;
	}
	if (!(*stream))
		return (NULL);
	return ((*stream)->value);
}


//function for heredoc
//function for dup2
void	for_heredoc(char *filename, int fd)
{
	char *line;

	line = readline("here_doc");
	printf(":%s\n",line);
	while(!(ft_strncmp(filename, line, ft_strlen(filename))))
	{
		write(fd ,line, ft_strlen(line));
		free(line);
		line = readline("here_doc");
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
			filename = araj_gna(&stream);
			fd = open(filename, O_RDONLY);
			init_and_check_fd(fd);
			stream->in = fd;
		}
		else if (stream->type == REDIR_OUT && stream->next)
		{
			filename = araj_gna(&stream);
			fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			init_and_check_fd(fd);
			stream->out = fd;
		}
		else if (stream->type == REDIR_AP && stream->next)
		{
			filename = araj_gna(&stream);
			fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
			init_and_check_fd(fd);
			stream->out = fd;			
		}
		else if (stream->type == REDIR_SO && stream->next)
		{
			filename = araj_gna(&stream);
			fd = open(filename, O_RDWR);
			init_and_check_fd(fd);
			for_heredoc(filename , fd);
			stream->in = fd;

		}
		stream = stream->next;
	}
	return (0);
}

//nayel tuylatreli cahrery filenameri hamar

//ctrl+d ev filename 
//heredoc

t_token *cut_red(t_token *stream)
{
	while (stream)
	{
		if (stream->type == WORD)
			return (stream->next);
		stream = stream->next;
	}
	return (0);
}

void	delete_files(t_token *stream)
{
	while (stream)
	{
		if (stream->op == 1)
		{
			stream->prev->next = cut_red(stream);
			free(stream);
		}
		stream = stream->next;
	}
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
	delete_files(data->stream);
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
