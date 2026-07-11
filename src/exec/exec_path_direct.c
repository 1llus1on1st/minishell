/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path_direct.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 14:06:06 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/10 14:06:40 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Prints a direct-path execution error.
1.	Uses minishell's command prefix
2.	Sets the status chosen by the caller
3.	Returns NULL so path lookup can fail directly
*/
static char	*direct_path_error(char *cmd, int *exit_status,
	int status, char *message)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(message, 2);
	ft_putchar_fd('\n', 2);
	*exit_status = status;
	return (NULL);
}

/*
Checks whether a path points to a directory.
*/
static int	is_directory(char *path)
{
	struct stat	st;

	if (stat(path, &st) != 0)
		return (0);
	return (S_ISDIR(st.st_mode));
}

/*
Validates a command that already contains a slash.
1.	Reports 127 when the path does not exist
2.	Reports 126 for directories or permission errors
3.	Returns the original command path when it is executable
*/
char	*handle_direct_path(char *cmd, int *exit_status)
{
	if (access(cmd, F_OK) != 0)
		return (direct_path_error(cmd, exit_status, 127,
				"No such file or directory"));
	if (is_directory(cmd))
		return (direct_path_error(cmd, exit_status, 126,
				"Is a directory"));
	if (access(cmd, X_OK) != 0)
		return (direct_path_error(cmd, exit_status, 126,
				"Permission denied"));
	*exit_status = 0;
	return (cmd);
}
