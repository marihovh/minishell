/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 11:08:50 by marihovh          #+#    #+#             */
/*   Updated: 2023/10/08 20:38:24 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fd_error(int sign, char *filename)
{
	ft_putstr_fd("shyshell: ", 2);
	ft_putstr_fd(filename, 2);
	if (sign == 0)
		ft_putstr_fd(": Can't open file\n", 2);
	else
		ft_putstr_fd(": No such file or directory\n", 2);
	g_exit_statuss = 1;
	free(filename);
	return (-42);
}

int	open_fd(t_token *stream, char *filename, t_envies *env)
{
	int	fd;

	fd = 0;
	if (stream->type == REDIR_IN)
	{
		fd = open(filename, O_RDONLY);
		if (fd < 0)
			return (fd_error(1, filename));
	}
	else if (stream->type == REDIR_OUT && stream->next)
	{
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (fd < 0)
			return (-42);
	}
	else if (stream->type == REDIR_AP && stream->next)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (stream->type == REDIR_SO && stream->next)
	{
		fd = for_heredoc(filename, env);
		if (fd == -2)
			return (-42);
	}
	return (fd);
}

t_token	*try(t_token **stream)
{
	t_token	*com;
	t_token	*tmp;
	t_token	*redir;

	com = (*stream);
	redir = (*stream);
	if ((*stream)->next)
		tmp = (*stream)->next;
	else
		tmp = (*stream);
	if ((com)->prev)
		while (com && ((com)->type != PIPE && com->type != WORD \
			&& com->type != FIELD && com->type != EXP_FIELD))
			com = com->prev;
	soo_word(&tmp);
	if ((com && com->type == PIPE) || !com || com->op == 1)
	{
		if (tmp->next && tmp->next->type != PIPE)
			com = tmp->next;
		else
			com = NULL;
		while (com && (com->type != WORD && com->type != PIPE))
			com = com->next;
		if (com)
		{
			if (com->next)
			{
				com->prev->next = com->next;
				com->next->prev = tmp;
			}
			else
				com->prev->next = NULL;
			if (redir->prev)
			{
				com->prev = redir->prev;
				redir->prev = com;
				com->next = redir;
			}
			else
			{
				redir->prev = com;
				com->next = redir;
			}
			return (com);
		}
	}
	return (*stream);
}

int	redirs(t_token **stream, t_envies *env, int cnt)
{
	int		sign;
	char	*filename;
	t_token	*re;
	t_token	*ret;
	int		fd;

	fd = 0;
	(void)cnt;
	ret = (*stream);
	while (*stream != NULL)
	{
		if ((*stream)->op == 1)
		{
			sign = 0;
			re = (*stream);
			filename = file_name((*stream));
			(*stream) = re;
			if (valid_name(filename) == 1)
				return (1);
			if ((*stream)->type == REDIR_IN || (*stream)->type == REDIR_SO)
				sign = 1;
			fd = open_fd((*stream), filename, env);
			if (fd == -42)
				return (3);
			free(filename);
			(*stream) = find_com(stream, fd, sign);
			if (!(*stream))
			{
				close(fd);
				return (2);
			}
		}
		(*stream) = (*stream)->next;
	}
	(*stream) = ret;
	return (0);
}

void	write_here_doc(int fd, char *filename, t_envies *env)
{
	char	*line;
	char	*dol;
	char	*tmp;

	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_DFL);
	while (1)
	{
		line = readline("> ");
		if ((line == NULL || ft_strcmp(line, filename) == 0))
			break ;
		dol = ft_strchr(line, '$');
		if (dol)
		{
			tmp = ft_strdup(line);
			free(line);
			line = open_dol(dol, tmp, env);
			free(tmp);
		}
		ft_putstr_fd(line, fd);
		ft_putstr_fd("\n", fd);
		free(line);
	}
	close(fd);
}
