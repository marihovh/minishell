/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 14:09:56 by marihovh          #+#    #+#             */
/*   Updated: 2023/07/17 21:01:03 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void to_struct(char **command, t_command **stream)   //done
// {
// 	char *str;
// 	int i;
// 	int j;

// 	i = -1;
// 	while (command[++i])
// 	{
// 		str = NULL;
// 		j = 0;
// 		str = command[i];
// 		while (*str == ' ' && *str)
// 			str++;
// 		while (str[j] != ' ' && str[j])
// 			j++;
// 		command[i] = str;
// 		command[i] += j;
// 		while (*command[i] == ' ' && command[i])
// 			command[i]++;
// 		str = ft_substr(str, 0, j);
// 		(*stream) = new_com(str, command[i]);
// 		// printf("command:%s args:%s\n", (*stream)->command[0], (*stream)->command[1]);
// 		free(str);
// 		stream = &(*stream)->next;
// 	}
// }




void to_struct(char **command, t_command **stream)   //done
{
	// (void)stream;
	char *str;
	char *str2;
	int i;
	int j;

	i = -1;
	while (command[++i])
	{
		j = 0;
		while (*command[i] && *command[i] == ' ')
			command[i]++;
		while (command[i][j] != '\0' && command[i][j] != ' ')
			j++;
		str = ft_substr(command[i], 0, j);
		command[i] += j;
		while (command[i] && *command[i] == ' ')
			command[i]++;
		str2 = ft_substr(command[i], 0, ft_strlen(command[i]));
		(*stream) = new_com(str, str2);
		// printf("command:%s args:%s\n", stream->command[0], data->com_stream->command[1]);
		if (!(*stream))
			break ;
		str = NULL;
		str2 = NULL;
		free(str);
		free(str2);
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
