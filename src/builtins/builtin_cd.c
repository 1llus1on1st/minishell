/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 14:13:15 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/10 10:48:13 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	update_pwd(t_shell *shell, char *old_pwd)
{
	char	new_pwd[4096];
	char	*old_entry;
	char	*new_entry;

	if (!getcwd(new_pwd, sizeof(new_pwd)))
		return (perror("cd"), 1);
	old_entry = ft_strjoin("OLDPWD=", old_pwd);
	if (!old_entry)
		return (1);
	if (!env_set_entry(shell, old_entry))
		return (free(old_entry), 1);
	free(old_entry);
	new_entry = ft_strjoin("PWD=", new_pwd);
	if (!new_entry)
		return (1);
	if (!env_set_entry(shell, new_entry))
		return (free(new_entry), 1);
	free(new_entry);
	return (0);
}

static char	*join_home_path(char *home, char *arg)
{
	if (!arg[1])
		return (ft_strdup(home));
	if (arg[1] == '/')
		return (ft_strjoin(home, arg + 1));
	return (ft_strdup(arg));
}

static char	*get_cd_path(t_shell *shell, t_cmd *cmd, int *print_path)
{
	char	*home;
	char	*oldpwd;

	*print_path = 0;
	if (!cmd->argv[1] || ft_strncmp(cmd->argv[1], "--", 3) == 0)
	{
		home = get_env_value(shell, "HOME");
		if (!home)
			return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), NULL);
		return (ft_strdup(home));
	}
	if (ft_strncmp(cmd->argv[1], "-", 2) == 0)
	{
		oldpwd = get_env_value(shell, "OLDPWD");
		if (!oldpwd)
			return (ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2), NULL);
		*print_path = 1;
		return (ft_strdup(oldpwd));
	}
	if (cmd->argv[1][0] == '~')
	{
		home = get_env_value(shell, "HOME");
		if (!home)
			return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), NULL);
		return (join_home_path(home, cmd->argv[1]));
	}
	return (ft_strdup(cmd->argv[1]));
}

int	builtin_cd(t_shell *shell, t_cmd *cmd)
{
	char	old_pwd[4096];
	char	new_pwd[4096];
	char	*path;
	int		print_path;
	int		status;

	if (cmd->argv[1] && cmd->argv[2])
		return (ft_putstr_fd("minishell: cd: too many arguments\n", 2), 2);
	path = get_cd_path(shell, cmd, &print_path);
	if (!path)
		return (1);
	if (!getcwd(old_pwd, sizeof(old_pwd)))
		return (free(path), perror("cd"), 1);
	if (chdir(path) != 0)
		return (free(path), perror("cd"), 1);
	free(path);
	status = update_pwd(shell, old_pwd);
	if (status != 0)
		return (status);
	if (print_path)
	{
		if (!getcwd(new_pwd, sizeof(new_pwd)))
			return (perror("cd"), 1);
		printf("%s\n", new_pwd);
	}
	return (0);
}
