/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 11:45:15 by marihovh          #+#    #+#             */
/*   Updated: 2023/07/15 18:04:46 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int main(int argc, char **argv, char **environ)
{
	(void)argc;
	(void)argv;
	t_data *data;

	data = malloc(sizeof(t_data));
	// printf("\n%s\n", getenv("PWD"));
	init_line(data, environ);
	return (0);
}

// int main() {
//     char *const argv[] = {"ls  ", "-l", NULL};
//     char *const envp[] = {NULL};
//     execve("/bin/ls", argv, envp);
    
//     // Execve only returns if there was an error
//     perror("execve"); 
//     return 1;
// }