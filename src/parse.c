/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 11:45:22 by marihovh          #+#    #+#             */
/*   Updated: 2023/07/17 21:03:23 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void init_env(t_envies **envp, char **environ)
{
	char **splited;
	int	i;

	i = -1;
	while (environ[++i])
	{
		splited = ft_split(environ[i], '=');
		if (!splited)
			break ;
		(*envp) = new_node(splited[0], splited[1]);
		if (!(*envp))
			break ;
		envp = &(*envp)->next;
	}
}

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
	// int i = -1;
	// while (data->command[++i])
	// 	free(data->command[i]);
	// free(data->command);
	free (data);
}


void init_line(t_data *data, char **environ)
{
	char *str;

	str = NULL;
	while(str == NULL || ft_strncmp("C", str, 1) != 0)
	{
		data = malloc(sizeof(t_data));
		init_env(&data->envies, environ);
		str = readline("shyshell$ ");
		if (str && ft_strlen(str) > 0)
		{
			add_history(str);
			parse(data, str);
			execve("/bin/ls", data->command, NULL);
			// printf("\n\nesiminch\n\n\n");
			// free_data(data);
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
		if (tmp)
			(*stream)->prev = tmp;
		if (!(*stream))
			break ;
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
	// open_fields(data->stream);
	to_commands(data);
	to_struct(data->command, &data->com_stream);
	// while (data->com_stream != NULL)
	// {
	// 	printf("command:%s args:%s\n", data->com_stream->command[0], data->com_stream->command[1]);
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


