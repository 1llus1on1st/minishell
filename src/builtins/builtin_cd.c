/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 14:13:15 by mshargan          #+#    #+#             */
/*   Updated: 2026/06/23 14:34:23 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int	builtin_cd(t_shell *shell, t_cmd *cmd)
{
	char	old_pwd[4096];
	char	*path;

	if (cmd->argv[1] && cmd->argv[2])
		return (ft_putstr_fd("minishell: cd: too many arguments\n", 2), 1);
	path = cmd->argv[1];
	if (!path)
		path = get_env_value(shell, "HOME");
	if (!path)
		return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
	if (!getcwd(old_pwd, sizeof(old_pwd)))
		return (perror("cd"), 1);
	if (chdir(path) != 0)
		return (perror("cd"), 1);
	return (update_pwd(shell, old_pwd));
}