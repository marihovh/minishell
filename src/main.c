/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 11:45:15 by marihovh          #+#    #+#             */
/*   Updated: 2023/08/18 16:56:35 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void signal_hend(int signum)
{
	(void)signum;
	write(1, "\n", 11);
	rl_on_new_line();
	rl_redisplay();
	// write(STDIN_FILENO, "\n\n", 2);
	// rl_replace_line("", 0);
	
}

void sig_hend(int num)
{
	(void)num;
	
	exit(0);
}

void signals (void)
{
	struct termios term_attr;

	tcgetattr(STDIN_FILENO, &term_attr);
	term_attr.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSADRAIN, &term_attr);
	signal(SIGINT, signal_hend);
	signal(SIGQUIT, sig_hend);
}

int main(int argc, char **argv, char **environ)
{
	(void)argc;
	(void)argv;
	t_data *data = NULL;
	char *str;
	
	(void)environ;
	str = NULL;
	// signal(SIGINT, signal_hend);
	// signals();
	data = malloc(sizeof(t_data));
	init_line(data, environ); 
	return (0);
}