/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 14:09:56 by marihovh          #+#    #+#             */
/*   Updated: 2023/07/16 09:47:58 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void to_struct(char **command, t_command **stream)   //done
{
	char *str;
	int i;
	int j;

	i = -1;
	while (command[++i])
	{
		j = 0;
		str = command[i];
		while (*str == ' ' && *str)
			str++;
		while (str[j] != ' ' && str[j])
			j++;
		command[i] = str;
		command[i] += j;			
		while (*command[i] == ' ' && command[i])
			command[i]++;
		str = ft_substr(str, 0, j);
		(*stream) = new_com(str, command[i]);
		free(str);
		stream = &(*stream)->next;
	}
}

void to_commands(t_data *data)    // done
{
	int com_len;

	com_len = ft_com_len(data->stream);
	data->command = malloc(sizeof(char *) * (com_len + 1));
	int i = 0;
	while (data->stream)
	{
		if (data->stream->type == PIPE)
		{
			i++;
			data->stream = data->stream->next;
		}
		data->command[i] = ft_strjoin(data->command[i], data->stream->value);
		data->stream = data->stream->next;
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

// word validation each of command 
// redirection validation
// pipe validation
// variables in fields
// $s validation
// builtins
