/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/24 19:04:35 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/10 15:14:57 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	init_env(t_shell *shell, char **envp)
{
	int	i;

	shell->env = gc_malloc(&shell->shell_gc, sizeof(char *)
			* (env_count(envp) + 1));
	if (!shell->env)
		return (0);
	i = 0;
	while (envp && envp[i])
	{
		shell->env[i] = ft_strdup(envp[i]);
		if (!shell->env[i])
			return (0);
		if (!gc_add(&shell->shell_gc, shell->env[i]))
			return (free(shell->env[i]), 0);
		i++;
	}
	shell->env[i] = NULL;
	return (1);
}
