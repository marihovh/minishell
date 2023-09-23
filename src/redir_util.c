/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 11:08:50 by marihovh          #+#    #+#             */
/*   Updated: 2023/09/23 14:36:17 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int valid_name(char *filename)
{
	int	nb;
	
	nb = not_file(filename);
	if (nb != 0)
		free(filename);
	return (nb);
}

int fd_error(int sign, char *filename)
{
	ft_putstr_fd("shyshell: ", 2);
	ft_putstr_fd(filename, 2);
	if (sign == 0)
		ft_putstr_fd(": Can't open file\n", 2);
	else
		ft_putstr_fd(": No such file or directory\n", 2);
	g_exit_statuss = 1;
	free(filename);
	return (1);
}

int open_fd(t_token *stream, char *filename)
{
	int fd = 0;
	
	if (stream->type == REDIR_IN)
	{
		fd = open(filename, O_RDONLY);
		if (fd < 0)
			return (fd_error(1, filename));
	}else if (stream->type == REDIR_OUT && stream->next)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (stream->type == REDIR_AP && stream->next)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (stream->type == REDIR_SO && stream->next)
	{
		fd = for_heredoc(filename);
		if (fd == -2)
			return (-42);
	}
	return (fd);
}

int redirs(t_token *stream)
{
	int sign;
	char *filename;
	int fd;
	
	while (stream)
	{
		if (stream->op == 1)
		{
			sign = 0;
			filename = file_name(stream);
			if (valid_name(filename) != 0)
				return (1);
			if (stream->type == REDIR_IN || stream->type == REDIR_SO)
				sign = 1;
			fd = open_fd(stream, filename);
			if (fd == -42)
				return (3);
			find_com(&stream, fd, sign);
			free(filename);
		}
		stream = stream->next;
	}
	return (0);
}
