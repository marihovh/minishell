/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 14:09:56 by marihovh          #+#    #+#             */
/*   Updated: 2023/07/12 21:17:03 by marihovh         ###   ########.fr       */
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
 
t_command *new_com(t_token *stream)
{
	t_command	*new_com;

	new_com = malloc(sizeof(t_command));
	if (!new_com)
		return (NULL);
	new_com->command = stream;
	new_com->next = NULL;
	return (new_com);
}

void	tpel(t_token *stream)
{
	while(stream != NULL)
	{
		printf("stream value: %s\n", stream->value);
		stream = stream->next;
	}
}

void esiminch(t_token **tmp)
{
	printf("aaaaa: %s\n", (*tmp)->value);
}

void to_commands(t_command **com_stream, t_token *stream)
{
	// tpel((*com_stream)->command);

	(void)com_stream;
	t_token *tmp2 = stream;
	t_token **tmp = &tmp2;
	(*tmp) = stream;
	while (stream != NULL)
	{
		if (stream->type == PIPE)
			{
				esiminch(tmp);
				// (*tmp)->next = NULL;
				// (*com_stream) = new_com((*tmp));
				// com_stream = &(*com_stream)->next;
				// (*tmp) = stream->next;
				// tpel((*com_stream)->command);
			}
		tmp = &(*tmp)->next;
		stream = stream->next;
	}
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
