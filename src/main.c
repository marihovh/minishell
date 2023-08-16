/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 11:45:15 by marihovh          #+#    #+#             */
/*   Updated: 2023/08/16 19:49:24 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void signal_hend(int signum)
{
	if (signum == SIGINT)
	{
		// write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void sigquit_handler (int signum)
{
	if (signum == SIGQUIT)
	{
		// free ()
		printf("printf\n");
	}
}

void signals (void)
{
	struct termios term_attr;

	tcgetattr(STDIN_FILENO, &term_attr);
	term_attr.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &term_attr);
	signal(SIGQUIT, sigquit_handler);
	signal(SIGINT, signal_hend);
}

int main(int argc, char **argv, char **environ)
{
	(void)argc;
	(void)argv;
	t_data *data = NULL;
	char *str;
	
	(void)environ;
	str = NULL;
	data = malloc(sizeof(t_data));
	signals();
	// printf("yoo\n");
	// rl_redisplay();
	init_line(data, environ); 
	return (0);
}