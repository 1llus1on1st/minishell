/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 14:13:23 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/10 10:50:24 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	export_option_error(char *arg)
{
	ft_putstr_fd("minishell: export: ", 2);
	ft_putchar_fd(arg[0], 2);
	if (arg[1])
		ft_putchar_fd(arg[1], 2);
	ft_putstr_fd(": invalid option\n", 2);
	return (2);
}

static int	export_error(char *arg)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

static int	is_append_assignment(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '+' && arg[i + 1] == '=')
			return (1);
		if (arg[i] == '=')
			return (0);
		i++;
	}
	return (0);
}

static char	*get_append_name(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && !(arg[i] == '+' && arg[i + 1] == '='))
		i++;
	return (ft_substr(arg, 0, i));
}

static char	*make_append_entry(char *name, char *old_value, char *append_value)
{
	char	*joined_value;
	char	*left;
	char	*entry;

	if (!old_value)
		old_value = "";
	joined_value = ft_strjoin(old_value, append_value);
	if (!joined_value)
		return (NULL);
	left = ft_strjoin(name, "=");
	if (!left)
		return (free(joined_value), NULL);
	entry = ft_strjoin(left, joined_value);
	free(left);
	free(joined_value);
	return (entry);
}

static int	export_append(t_shell *shell, char *arg)
{
	char	*name;
	char	*entry;
	char	*append_value;
	int		status;

	name = get_append_name(arg);
	if (!name)
		return (1);
	if (!is_valid_identifier(name, 0))
		return (free(name), export_error(arg));
	append_value = ft_strchr(arg, '=') + 1;
	entry = make_append_entry(name, get_env_value(shell, name), append_value);
	free(name);
	if (!entry)
		return (1);
	status = env_set_entry(shell, entry);
	free(entry);
	if (!status)
		return (1);
	return (0);
}

int	builtin_export(t_shell *shell, t_cmd *cmd)
{
	int	i;
	int	status;

	if (!cmd->argv[1])
		return (print_export(shell));
	i = 1;
	status = 0;
	while (cmd->argv[i])
	{
		if (cmd->argv[i][0] == '-')
			return (export_option_error(cmd->argv[i]));
		if (is_append_assignment(cmd->argv[i]))
		{
			if (export_append(shell, cmd->argv[i]) != 0)
				status = 1;
		}
		else if (!is_valid_identifier(cmd->argv[i], 1))
			status = export_error(cmd->argv[i]);
		else if (!env_set_entry(shell, cmd->argv[i]))
			status = 1;
		i++;
	}
	return (status);
}
