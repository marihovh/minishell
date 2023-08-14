/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 14:09:56 by marihovh          #+#    #+#             */
/*   Updated: 2023/08/10 21:07:35 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void to_struct(char **command, t_command **com_stream, t_token *stream)   //done
{
	char **splited;
	int i;
	int j;

	i = -1;
	while (command[++i])
	{
		j = 0;
		splited = ft_split(command[i], ' ');
		(*com_stream) = new_com(splited, stream->in, stream->out);
		// (*com_stream) = new_com(splited);
		com_stream = &(*com_stream)->next;
		stream = stream->next;
	}
}

void to_commands(t_data *data)    // done
{
	char *str = NULL;
	t_token *ptr;
	int pip_cnt;
	int i = 0;

	if (!data->stream)
		return ;
	ptr = data->stream;
	pip_cnt = ft_com_len(data->stream);
	exit(0);
		printf("ttt\n");
		exit (0);
	data->command = malloc(sizeof(char *) * (pip_cnt + 2));
	while (data->stream)
	{
		if (data->stream->type == PIPE)
		{
			data->command[i] = str;
			str = NULL;
			i++;
			data->stream = data->stream->next;
		}
		str = ft_strjoin(str, data->stream->value);
		data->stream = data->stream->next;
	}
	data->stream = ptr;
	data->command[i] = str;
	data->command[i + 1] = NULL;
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

// word validation each of command 
// redirection validation
// pipe validation
// variables in fields
// $s validation
// builtins
