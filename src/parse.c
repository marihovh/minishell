/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 11:45:22 by marihovh          #+#    #+#             */
/*   Updated: 2023/07/28 20:01:07 by marihovh         ###   ########.fr       */
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
			parse(data, str);
			execute(data);
			signal(SIGINT, signal_hend);
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

void parse(t_data *data, char *str)
{
	tokenize(&data->stream, str);
	if (!validation(data->stream))
		return ;
	open_fields(data->stream, data->envies, data->exit_status);
	to_commands(data);
	to_struct(data->command, &data->com_stream);
	// while (data->envies != NULL)
	// {
	// 	printf("key:%s\n", data->envies->key);
	// 	data->envies = data->envies->next;
	// }
	// int i;
	// while (data->com_stream != NULL)
	// {
	// 	i = -1;
	// 	while (data->com_stream->command[++i] != NULL)
	// 		printf("stream:%s\n", data->com_stream->command[i]);
	// 	data->com_stream = data->com_stream->next;
	// }
}

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
