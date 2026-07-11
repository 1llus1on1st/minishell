/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 14:13:15 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/11 14:20:32 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Updates PWD and OLDPWD after a successful directory change.
1.	Uses old_pwd as the previous working directory value
2.	Reads the new current directory with getcwd
3.	Stores both values in the shell environment
*/
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

/*
Expands a cd argument that begins with '~'.
1.	Returns HOME for a bare '~'
2.	Joins HOME with the rest of the path for '~/...'
3.	Leaves unusual '~name' forms unchanged
*/
static char	*join_home_path(char *home, char *arg)
{
	if (!arg[1])
		return (ft_strdup(home));
	if (arg[1] == '/')
		return (ft_strjoin(home, arg + 1));
	return (ft_strdup(arg));
}

/*
Chooses the path that cd should use.
1.	Uses HOME for no argument, '--' or '~'
2.	Expands paths that begin with '~'
3.	Uses OLDPWD for cd - and asks the caller to print the new path
4.	Returns NULL after printing an error when HOME or OLPWD is missing
*/
static char	*get_cd_path(t_shell *shell, t_cmd *cmd, int *print_path)
{
	char	*home;
	char	*arg;

	*print_path = 0;
	arg = cmd->argv[1];
	if (!arg || ft_strncmp(arg, "--", 3) == 0 || arg[0] == '~')
	{
		home = get_env_value(shell, "HOME");
		if (!home)
			return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), NULL);
		if (!arg || ft_strncmp(arg, "--", 3) == 0)
			return (ft_strdup(home));
		return (join_home_path(home, arg));
	}
	if (ft_strncmp(arg, "-", 2) == 0)
	{
		*print_path = 1;
		arg = get_env_value(shell, "OLDPWD");
		if (!arg)
			return (ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2), NULL);
	}
	return (ft_strdup(arg));
}

/*
Implements the cd builtin in the parent shell.
1.	Rejects more than one path argument
2.	Resolves special cd forms before calling chdir
3.	Saves the old directory so OLDPWD can be updated
4.	Updates PWD and OLDPWD after chdir succeeds
5.	Prints the new directory for cd -
*/
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
	if (!getcwd(old_pwd, sizeof(old_pwd)) || chdir(path) != 0)
		return (free(path), perror("cd"), 1);
	free(path);
	status = update_pwd(shell, old_pwd);
	if (status != 0)
		return (status);
	if (print_path && !getcwd(new_pwd, sizeof(new_pwd)))
		return (perror("cd"), 1);
	if (print_path)
		printf("%s\n", new_pwd);
	return (0);
}
