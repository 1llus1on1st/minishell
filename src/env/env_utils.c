/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 19:04:42 by mshargan          #+#    #+#             */
/*   Updated: 2026/06/26 18:29:36 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_env_value(t_shell *shell, char *key)
{
	int		i;
	size_t	len;

	if (!shell || !shell->env || !key)
		return (NULL);
	len = ft_strlen(key);
	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], key, len) == 0
			&& shell->env[i][len] == '=')
			return (shell->env[i] + len + 1);
		i++;
	}
	return (NULL);
}

int	env_key_len(char *entry)
{
	int	i;

	i = 0;
	while (entry[i] && entry[i] != '=')
		i++;
	return (i);
}

int	env_count(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
		i++;
	return (i);
}

int	env_find_index(t_shell *shell, char *key)
{
	int	i;
	int	len;

	i = 0;
	len = env_key_len(key);
	while (shell->env && shell->env[i])
	{
		if (env_key_len(shell->env[i]) == len
			&& ft_strncmp(shell->env[i], key, len) == 0)
			return (i);
		i++;
	}
	return (-1);
}

char	*gc_strdup_env(t_shell *shell, char *str)
{
	char	*copy;

	copy = ft_strdup(str);
	if (!copy)
		return (NULL);
	if (!gc_add(&shell->shell_gc, copy))
		return (free(copy), NULL);
	return (copy);
}
