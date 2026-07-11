/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 17:35:04 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/10 17:40:56 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Builds a candidate executable path from one PATH directory.
1.	Joins the directory with a slash
2.	Appends the command name
3.	Tracks the candidate path in line_gc
*/
static char	*join_path(t_shell *shell, char *dir, char *cmd)
{
	char	*tmp;
	char	*path;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	path = ft_strjoin(tmp, cmd);
	free(tmp);
	if (!path)
		return (NULL);
	if (!gc_add(&shell->line_gc, path))
		return (free(path), NULL);
	return (path);
}

/*
Searches PATH directories for an executable command.
1.	Builds one candidate path per PATH entry
2.	Returns the first candidate that is executable
3.	Returns NULL when no PATH entry works
*/
static char	*find_in_path(t_shell *shell, char *cmd, char **dirs)
{
	int		i;
	char	*path;

	i = 0;
	while (dirs && dirs[i])
	{
		path = join_path(shell, dirs[i], cmd);
		if (!path)
			return (NULL);
		if (access(path, X_OK) == 0)
			return (path);
		i++;
	}
	return (NULL);
}

/*
Reports a command-not-found lookup failure.
1.	Prints the command name with a shell-style error
2.	Sets the exit status to 127
*/
static char	*cmd_not_found(char *cmd, int *exit_status)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	*exit_status = 127;
	return (NULL);
}

/*
Finds a command by searching the PATH environment variable.
1.	Handles missing or empty PATH as a special case
2.	Splits PATH on ':' and tests each directory
3.	Returns command-not-found when no executable is found
*/
static char	*find_cmd_from_path(t_shell *shell, char *cmd, int *exit_status)
{
	char	*path_env;
	char	**dirs;
	char	*path;

	path_env = get_env_value(shell, "PATH");
	if (!path_env || path_env[0] == '\0')
	{
		if (access(cmd, X_OK) == 0)
			return (cmd);
		return (cmd_not_found(cmd, exit_status));
	}
	dirs = ft_split(path_env, ':');
	if (!dirs)
		return (*exit_status = 1, NULL);
	path = find_in_path(shell, cmd, dirs);
	free_split(dirs);
	if (!path)
		return (cmd_not_found(cmd, exit_status));
	return (path);
}

/*
Resolves the executable path for an external command.
1.	Rejects empty command names
2.	Handles special names like '~', '.' and '..'
3.	Validates direct paths that contain '/'
4.	Searches PATH for normal command names
*/
char	*get_cmd_path(t_shell *shell, char *cmd, int *exit_status)
{
	if (!cmd || cmd[0] == '\0')
		return (cmd_not_found("", exit_status));
	if (!handle_special_cmd_name(cmd, exit_status))
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (handle_direct_path(cmd, exit_status));
	return (find_cmd_from_path(shell, cmd, exit_status));
}
