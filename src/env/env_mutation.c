/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_mutation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 14:33:24 by mshargan          #+#    #+#             */
/*   Updated: 2026/06/23 14:34:10 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	key_len(char *entry)
{
	int	i;

	i = 0;
	while (entry[i] && entry[i] != '=')
		i++;
	return (i);
}

static int	env_count(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
		i++;
	return (i);
}

static int	find_env_index(t_shell *shell, char *key)
{
	int	i;
	int	len;

	i = 0;
	len = key_len(key);
	while (shell->env && shell->env[i])
	{
		if (key_len(shell->env[i]) == len
			&& ft_strncmp(shell->env[i], key, len) == 0)
			return (i);
		i++;
	}
	return (-1);
}

static char	*gc_strdup_env(t_shell *shell, char *str)
{
	char	*copy;

	copy = ft_strdup(str);
	if (!copy)
		return (NULL);
	if (!gc_add(&shell->shell_gc, copy))
		return (free(copy), NULL);
	return (copy);
}

int	env_set_entry(t_shell *shell, char *entry)
{
	char	**new_env;
	int		i;
	int		index;

	index = find_env_index(shell, entry);
	if (index >= 0 && !ft_strchr(entry, '='))
		return (1);
	if (index >= 0)
		return (shell->env[index] = gc_strdup_env(shell, entry), 1);
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
	new_env[i] = gc_strdup_env(shell, entry);
	new_env[i + 1] = NULL;
	shell->env = new_env;
	return (new_env[i] != NULL);
}

int	env_unset_key(t_shell *shell, char *key)
{
	char	**new_env;
	int		i;
	int		j;
	int		index;

	index = find_env_index(shell, key);
	if (index < 0)
		return (1);
	new_env = gc_malloc(&shell->shell_gc, sizeof(char *)
			* env_count(shell->env));
	if (!new_env)
		return (0);
	i = 0;
	j = 0;
	while (shell->env[i])
	{
		if (i != index)
			new_env[j++] = shell->env[i];
		i++;
	}
	new_env[j] = NULL;
	shell->env = new_env;
	return (1);
}
