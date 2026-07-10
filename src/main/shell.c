/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 12:14:25 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/10 13:11:01 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*read_piped_line(void)
{
	char	*line;
	char	*new_line;
	size_t	len;
	ssize_t	bytes;
	char	c;

	line = malloc(1);
	if (!line)
		return (NULL);
	line[0] = '\0';
	len = 0;
	while (1)
	{
		bytes = read(STDIN_FILENO, &c, 1);
		if (bytes <= 0 || c == '\n')
			break ;
		new_line = malloc(len + 2);
		if (!new_line)
			return (free(line), NULL);
		ft_memcpy(new_line, line, len);
		new_line[len] = c;
		new_line[len + 1] = '\0';
		free(line);
		line = new_line;
		len++;
	}
	if (bytes <= 0 && len == 0)
		return (free(line), NULL);
	return (line);
}

static char	*read_input(void)
{
	char	*line;

	if (!isatty(STDIN_FILENO))
		return (read_piped_line());
	line = readline("minishell$ ");
	if (line && *line)
		add_history(line);
	return (line);
}

static void	exit_shell(t_shell *shell)
{
	int	status;

	status = shell->last_exit;
	if (isatty(STDIN_FILENO))
		printf("exit\n");
	gc_clear(&shell->line_gc);
	gc_clear(&shell->shell_gc);
	exit((unsigned char)status);
}

/*
Keeps minishell running until EOF is received
1.	Sets up the prompt signal handling before reading input
2.	Reads the user input and updates last_exit after SIGINT
3.	Exits the shell if readline returns NULL
4.	Processes the input line and frees it after execution
*/
void	shell_loop(t_shell *shell)
{
	char	*line;

	while (1)
	{
		setup_prompt_signals();
		line = read_input();
		if (g_signal == SIGINT)
		{
			shell->last_exit = 130;
			g_signal = 0;
		}
		if (!line)
			exit_shell(shell);
		process_line(line, shell);
		free(line);
	}
}
