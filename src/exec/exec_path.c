/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 17:35:04 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/10 14:06:29 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static char	*cmd_not_found(char *cmd, int *exit_status)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
	*exit_status = 127;
	return (NULL);
}

static char	*find_cmd_from_path(t_shell *shell, char *cmd, int *exit_status)
{
	char	*path_env;
	char	**dirs;
	char	*path;

	path_env = get_env_value(shell, "PATH");
	if (!path_env)
		path_env = "/bin:/usr/bin";
	if (path_env[0] == '\0')
		return (cmd_not_found(cmd, exit_status));
	dirs = ft_split(path_env, ':');
	if (!dirs)
		return (*exit_status = 1, NULL);
	path = find_in_path(shell, cmd, dirs);
	free_split(dirs);
	if (!path)
		return (cmd_not_found(cmd, exit_status));
	return (path);
}

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
