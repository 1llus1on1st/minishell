/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/05 17:35:04 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/10 11:19:12 by mshargan         ###   ########.fr       */
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

static int	is_directory(char *path)
{
	struct stat	st;

	if (stat(path, &st) != 0)
		return (0);
	return (S_ISDIR(st.st_mode));
}

static char	*handle_direct_path(char *cmd, int *exit_status)
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

static int	is_exact_cmd(char *cmd, char *target)
{
	return (ft_strncmp(cmd, target, ft_strlen(target) + 1) == 0);
}
static char	*handle_special_cmd_name(char *cmd, int *exit_status)
{
	if (is_exact_cmd(cmd, "~"))
	{
		ft_putstr_fd("minishell: ~: Is a directory\n", 2);
		*exit_status = 126;
		return (NULL);
	}
	if (is_exact_cmd(cmd, ".") || is_exact_cmd(cmd, ".."))
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		*exit_status = 127;
		return (NULL);
	}
	return ((char *)1);
}

char	*get_cmd_path(t_shell *shell, char *cmd, int *exit_status)
{
	char	*path_env;
	char	**dirs;
	char	*path;
	char	*special;

	if (!cmd || cmd[0] == '\0')
	{
		ft_putstr_fd(": command not found\n", 2);
		*exit_status = 127;
		return (NULL);
	}
	special = handle_special_cmd_name(cmd, exit_status);
	if (!special)
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (handle_direct_path(cmd, exit_status));
	path_env = get_env_value(shell, "PATH");
	if (!path_env)
		path_env = "/bin:/usr/bin";
	if (path_env[0] == '\0')
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		*exit_status = 127;
		return (NULL);
	}
	dirs = ft_split(path_env, ':');
	if (!dirs)
		return (*exit_status = 1, NULL);
	path = find_in_path(shell, cmd, dirs);
	free_split(dirs);
	if (!path)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		*exit_status = 127;
	}
	return (path);
}
