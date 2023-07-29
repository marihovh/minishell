/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 14:09:56 by marihovh          #+#    #+#             */
/*   Updated: 2023/07/26 20:08:29 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void to_struct(char **command, t_command **stream)   //done
{
	// char *joined;  
	char **splited;
	int i;
	int j;

	i = -1;
	while (command[++i])
	{
		j = 0;
		splited = ft_split(command[i], ' ');
		(*stream) = new_com(splited);
		stream = &(*stream)->next;
	}
}

void to_commands(t_data *data)    // done
{
	char *str = NULL;
	int pip_cnt = ft_com_len(data->stream);
	int i = 0;

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
