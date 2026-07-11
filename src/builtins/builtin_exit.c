/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 14:02:34 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/10 18:20:14 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Counts arguments in an argv array.
1.	Handles NULL argv safely
2.	Returns the number of strings before the terminating NULL
*/
static int	argv_count(char **argv)
{
	int	i;

	i = 0;
	while (argv && argv[i])
		i++;
	return (i);
}

/*
Exits after an invalid numeric exit argument.
1.	Prints the required numeric argument error
2.	Clears both garbage collector scopes before leaving
3.	Exits with status 2, matching shell behavior for this error
*/
static void	exit_numeric_error(t_shell *shell, char *arg)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	gc_clear(&shell->line_gc);
	gc_clear(&shell->shell_gc);
	close(STDIN_FILENO);
	exit(2);
}

/*
Implements the exit builtin.
1.	Uses the last command status when no explicit code is given
2.	Exits immediately with status 2 for non-numeric arguments
3.	Refuses to exit when there are too many arguments
4.	Clears shell memory and exits with the code cast to unsigned char
*/
int	builtin_exit(t_shell *shell, t_cmd *cmd)
{
	long long	code;

	printf("exit\n");
	code = shell->last_exit;
	if (cmd->argv[1] && !parse_exit_code(cmd->argv[1], &code))
		exit_numeric_error(shell, cmd->argv[1]);
	if (argv_count(cmd->argv) > 2)
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (2);
	}
	gc_clear(&shell->line_gc);
	gc_clear(&shell->shell_gc);
	close(STDIN_FILENO);
	exit((unsigned char)code);
}
