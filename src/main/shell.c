/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 12:14:25 by mshargan          #+#    #+#             */
/*   Updated: 2026/04/24 13:05:16 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*read_input(void)
{
	char	*line;

	line = readline("minishell$ ");
	if (line && *line)
		add_history(line);
	return (line);
}

static void	process_line(char *line, t_shell *shell)
{
	(void)shell;
	printf("You typed: %s\n", line);
}

static void	exit_shell(void)
{
	printf("exit\n");
	exit(0);
}

void	shell_loop(t_shell *shell)
{
	char	*line;

	while (1)
	{
		line = read_input();
		if (!line)
			exit_shell();
		process_line(line, shell);
		free(line);
	}
}
