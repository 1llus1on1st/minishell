/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_mutation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 14:33:24 by mshargan          #+#    #+#             */
/*   Updated: 2026/06/26 18:29:52 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	replace_env_entry(t_shell *shell, int index, char *entry)
{
	char	*copy;

	copy = gc_strdup_env(shell, entry);
	if (!copy)
		return (0);
	shell->env[index] = copy;
	return (1);
}

static int	append_env_entry(t_shell *shell, char *entry)
{
	char	**new_env;
	char	*copy;
	int		i;

	new_env = gc_malloc(&shell->shell_gc, sizeof(char *)
			* (env_count(shell->env) + 2));
	if (!new_env)
		return (0);
	i = 0;
	while (shell->env && shell->env[i])
	{
		new_env[i] = shell->env[i];
		i++;
	}
	copy = gc_strdup_env(shell, entry);
	if (!copy)
		return (0);
	new_env[i] = copy;
	new_env[i + 1] = NULL;
	shell->env = new_env;
	return (1);
}

int	env_set_entry(t_shell *shell, char *entry)
{
	int	index;

	index = env_find_index(shell, entry);
	if (index < 0)
		return (append_env_entry(shell, entry));
	if (!ft_strchr(entry, '='))
		return (1);
	return (replace_env_entry(shell, index, entry));
}

static char	**make_unset_env(t_shell *shell, int index)
{
	char	**new_env;
	int		i;
	int		j;

	new_env = gc_malloc(&shell->shell_gc, sizeof(char *)
			* env_count(shell->env));
	if (!new_env)
		return (NULL);
	i = 0;
	j = 0;
	while (shell->env[i])
	{
		if (i != index)
			new_env[j++] = shell->env[i];
		i++;
	}
	new_env[j] = NULL;
	return (new_env);
}

int	env_unset_key(t_shell *shell, char *key)
{
	char	**new_env;
	int		index;

	index = env_find_index(shell, key);
	if (index < 0)
		return (1);
	new_env = make_unset_env(shell, index);
	if (!new_env)
		return (0);
	shell->env = new_env;
	return (1);
}
