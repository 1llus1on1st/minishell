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

/*
Returns the value part of an environment entry.
1.	Looks for an entry whose key exactly matches the requested key
2.	Requires the match to be followed by '=' to avoid partial key matches
3.	Returns a pointer inside shell->env, not a newly allocated string
*/
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

/*
Counts the key length of an environment entry.
1.	Starts at the first character of the entry
2.	Stops at '=' or the end of the string
*/
int	env_key_len(char *entry)
{
	int	i;

	i = 0;
	while (entry[i] && entry[i] != '=')
		i++;
	return (i);
}

/*
Counts entries in a NULL-terminated environment array.
1.	Handles a NULL environment pointer as an empty array
2.	Returns the number of strings before the final NULL
*/
int	env_count(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
		i++;
	return (i);
}

/*
Finds the index of an environment key in shell->env.
1.	Compares only the key part before '='
2.	Requires both keys to have the same length
3.	Returns -1 when the key is not present
*/
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

/*
Duplicates an environment string into shell-level memory.
1.	Uses ft_strdup because env entries must remain mutable by minishell
2.	Registers the copy in shell_gc so it lives until shell exit
3.	Returns NULL if allocation or registration fails
*/
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
