/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 14:51:19 by marihovh          #+#    #+#             */
/*   Updated: 2023/09/23 08:49:02 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	signal_hend(int signum)
{
	if (signum == SIGINT)
	{
		rl_replace_line("", 0);
		rl_done = 3;
	}
}

int	hand(void)
{
	return (0);
}

int	signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = &signal_hend;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa, 0);
	sigaction(SIGINT, &sa, 0);
	rl_catch_signals = 0;
	rl_event_hook = &hand;
	return (0);
}

void	foo(int num)
{
	static struct termios	term_attr;

	if (num == 0)
		tcgetattr(STDIN_FILENO, &term_attr);
	if (num == 1)
		tcsetattr(STDIN_FILENO, TCSANOW, &term_attr);
}
