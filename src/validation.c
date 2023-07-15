/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 14:09:56 by marihovh          #+#    #+#             */
/*   Updated: 2023/07/15 17:05:05 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void open_field(char *str)
{
	(void)str;
	// int i;

	// i = -1;
	// while (str[++i])
	// {
	// 	if (str[++i] == '$')
	// 		// returns the cahr * and adds to the str find_in_env();
	// }	
}

// void validation(t_data data)
// {
// 	t_token *yoo;
	
// 	while (data.stream)
// 	{
// 		if (data.stream->op == 1)
// 		{
// 			// drop_to_stream; or redirect
// 			if (data.stream->type == PIPE)
// 			{
// 				printf("I am a pipe\n");
// 				to_p
// 			// }else 
// 			// 	// to_redir(data->streaam);
// 			}
// 		}
// 		// if (data->stream->type == EXP_FIELD)
// 		// 	open_field(data->stream->value);
// 		// if (data->stream->type == WORD)
// 			// valid_word(data, data->stream);
// 		// else if (data->stream->type == PIPE)
// 		// 	valid_pipe();
// 		// else if (data->stream->type == FIELD)
// 		// 	valid_field();
// 		// else if (data->stream->type == EXP_FIELD)
// 		// 	valid_exp_field();
// 		// else if (data->stream->type == REDIR_OUT)
// 		// 	valid_redir_out();
// 		// else if (data->stream->type == REDIR_IN)
// 		// 	valid_redir_in();
// 		// else if (data->stream->type == REDIR_AP)
// 		// 	valid_redir_ap();
// 		// else if (data->stream->type == REDIR_SO)
// 		// 	valid_redir_so();
// 		data.stream = data.stream->next;
// 	}
// }
 
t_command *new_com(char *command)
{
	t_command	*new_com;

	new_com = malloc(sizeof(t_command));
	if (!new_com)
		return (NULL);
	new_com->command = command;
	new_com->next = NULL;
	return (new_com);
}

int ft_com_len(t_token *stream)
{
	int i = 0;
	while (stream)
	{
		if (stream->type == PIPE)
			i++;
		stream = stream->next;
	}
	return (i);
}


void to_commands(t_data *data)
{
	int com_len;

	com_len = ft_com_len(data->stream);
	data->command = malloc(sizeof(char *) * (com_len + 1));
	int i = 0;
	while (data->stream)
	{
		if (data->stream->type == PIPE)
		{
			printf(":data->command: %s\n", data->command[i]);
			i++;
			data->stream = data->stream->next;
		}
		data->command[i] = ft_strjoin(data->command[i], data->stream->value);
		data->stream = data->stream->next;
	}
	printf(":data->command: %s\n", data->command[i]);
}

/*          cd validation
with nothing -> going to HOME
with wrong dir -> error
with no permissions -> error
not directory -> error


*/

/*              pwd validation
no exeptions it works always the same

*/


void if_command(t_data *data, t_token *token)
{
	printf("word:%s\n", token->value);
	if (!ft_strcmp(token->value, "echo"))
		ft_echo(data, token); // token->command = 1;
	else if (!ft_strcmp(token->value, "cd"))
		ft_cd(data, token);   // token->command = 1;
	else if (!ft_strcmp(token->value, "pwd"))
		ft_pwd(data, token);  // token->command = 1;
	else
	{
		printf("Syntax error\n");
		data->exit_status = 1;
		return ;
	}
}

void valid_word(t_data *data, t_token *token)
{
	if (!token)
		return ;
	if_command(data, token);
}

// word validation each of command 
// redirection validation
// pipe validation
// variables in fields
// $s validation
// builtins
