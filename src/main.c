/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 11:45:15 by marihovh          #+#    #+#             */
/*   Updated: 2023/08/16 14:06:49 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void signal_hend(int signum)
{
	struct termios term_attr;

	tcgetattr(STDIN_FILENO, &term_attr);
	term_attr.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &term_attr);
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();	
	}
}

int main(int argc, char **argv, char **environ)
{
	(void)argc;
	(void)argv;
	t_data *data = NULL;
	char *str;

	// (void)environ;
	str = NULL;
	data = malloc(sizeof(t_data));
	signal(SIGINT, signal_hend);
	// printf("yoo\n");
	// rl_redisplay();
	init_line(data, environ);
	return (0);
}