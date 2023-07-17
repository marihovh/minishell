/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marihovh <marihovh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 11:45:15 by marihovh          #+#    #+#             */
/*   Updated: 2023/07/17 21:05:31 by marihovh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int main(int argc, char **argv, char **environ)
{
	(void)argc;
	(void)argv;
	t_data *data = NULL;

	// data = malloc(sizeof(t_data));
	// printf("\n%s\n", getenv("PWD"));
	init_line(data, environ);
	printf("esiminch\n");
	return (0);
}

// int main() {
//     char *const argv[] = {"ls  ", "-l", NULL};
//     char *const envp[] = {NULL};
//     execve("/bin/ls", argv, envp);
    
//     // Execve only returns if there was an error
//     perror("execve"); 
// 	// printf("yppppp\n");
//     return 1;
// }