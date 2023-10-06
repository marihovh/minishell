/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:08:29 by marihovh          #+#    #+#             */
/*   Updated: 2023/10/06 13:28:44 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_coms(t_command *stream)
{
	t_command	*current;
	t_command	*next_node;
	int			i;

	current = stream;
	while (current != NULL)
	{
		next_node = current->next;
		i = -1;
		while (current->command[++i])
			free(current->command[i]);
		free(current->command);
		free(current);
		current = next_node;
	}
}

void	free_tokens(t_token *stream)
{
	t_token	*current;
	t_token	*next_node;

	current = stream;
	while (current != NULL)
	{
		next_node = current->next;
		free(current->value);
		free(current);
		current = next_node;
	}
}

int	valid_helper(void)
{
	g_exit_statuss = 0;
	return (1);
}

void	soo_word(t_token **tmp)
{
	while (*tmp && ((*tmp)->type != PIPE && (*tmp)->type != WORD && (*tmp)->type != FIELD && (*tmp)->type != EXP_FIELD))
		(*tmp) = (*tmp)->next;
}

void free_part(t_token **stream, t_token *com, t_token *redir)
{
	(void)stream;
    t_token *nextNode;

	t_token *current = redir;
    while (current != NULL && current != com) {
	
        nextNode = current->next;
        free(current->value);
        free(current);
		// current = NULL;
        current = nextNode;
    }
	// free(stream);
	// (*stream) = com;
}

int find_com(t_token **stream, int fd, int fedo, t_token *redir)
{
	(void)redir;
	t_token	*com;
	int new_fd;
	t_token	*file;

	new_fd = -42;
	com = (*stream)->prev;
	if ((*stream)->next)
		file = (*stream)->next;
	else
		file = (*stream);
	while (com && (com->type != WORD && com->type != PIPE))
		com = com->prev;
	if (!com || com->type != WORD)
	{
		// printf("aaaaa\n");
		if ((*stream)->next)
			com = (*stream)->next;
		else
			return (1); 
		while (com && (com->type != WORD && com->type != PIPE))
			com = com->next;
		t_token *an;
		an = com->next;
		while (an && (an->type != WORD))
			an = an->next;
		if (an)
		{
			
			free_part(stream, com, redir);
			// prin(*stream, NULL);
			// exit(0);
			// free redira and another file
		}
		else
		{
			//set_fd to com
			;
		}
		// printf("{%s}\n", com->value);
		// exit(0);
	}
	else
	{
		// check is there a another ile
		// t_token *ant;
		// if (file->next)
		// {
		// 	ant = file->next;
		// 	while (ant && (ant->type != WORD))
		// 		ant = ant->next;
		// }
		// printf("morquri mard\n");
		if (file->next != NULL)
			file->next->prev = com;
		else
			com->next = NULL;
		find_com_2(stream, file, com);
		set_fd(stream, fd, fedo);
	}
	// exit(0);
	return (0);
}
