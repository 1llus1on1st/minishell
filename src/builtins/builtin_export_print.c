/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_print.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 14:37:17 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/01 14:38:27 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	env_size(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
		i++;
	return (i);
}

static char	**copy_env_refs(t_shell *shell)
{
	char	**copy;
	int		i;

	copy = gc_malloc(&shell->line_gc, sizeof(char *)
			* (env_size(shell->env) + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (shell->env && shell->env[i])
	{
		copy[i] = shell->env[i];
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

static void	sort_env_refs(char **env)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (env && env[i])
	{
		j = i + 1;
		while (env[j])
		{
			if (ft_strncmp(env[i], env[j],
					ft_strlen(env[i]) + ft_strlen(env[j]) + 1) > 0)
			{
				tmp = env[i];
				env[i] = env[j];
				env[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

static void	print_export_entry(char *entry)
{
	int	i;

	i = 0;
	ft_putstr_fd("declare -x ", 1);
	while (entry[i] && entry[i] != '=')
		ft_putchar_fd(entry[i++], 1);
	if (entry[i] == '=')
	{
		ft_putstr_fd("=\"", 1);
		i++;
		while (entry[i])
			ft_putchar_fd(entry[i++], 1);
		ft_putchar_fd('"', 1);
	}
	ft_putchar_fd('\n', 1);
}

int	print_export(t_shell *shell)
{
	char	**sorted;
	int		i;

	sorted = copy_env_refs(shell);
	if (!sorted)
		return (1);
	sort_env_refs(sorted);
	i = 0;
	while (sorted[i])
	{
		print_export_entry(sorted[i]);
		i++;
	}
	return (0);
}