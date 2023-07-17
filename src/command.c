/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 14:09:56 by marihovh          #+#    #+#             */
/*   Updated: 2023/07/16 20:48:38 by marihovh         ###   ########.fr       */
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
		printf("command:%s args:%s\n", (*stream)->command[0], (*stream)->command[1]);
		free(str);
		stream = &(*stream)->next;
	}
}

void to_commands(t_data *data)    // done
{
	int com_len;
	char *str = NULL;

	com_len = ft_com_len(data->stream);
	data->command = malloc(sizeof(char *) * (com_len + 2));
	int i = 0;
	while (data->stream)
	{
		if (data->stream->type == PIPE)
		{
			printf("str: %s\n", str);
			ft_strlcpy(data->command[i], str, ft_strlen(str));
			// free(str);
			i++;
			data->stream = data->stream->next;
		}
		str = ft_strjoin(str, data->stream->value);
		printf("data->command: %s\n", data->command[i]);   
		// printf("str: %s\n", str);
		// printf("command:%s args:%s\n", (*stream)->comman
		data->stream = data->stream->next;
	}
	printf("data->command: %s\n", data->command[1]);
		printf("yooo man\n");
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
