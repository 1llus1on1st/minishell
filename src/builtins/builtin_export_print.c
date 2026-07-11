/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_print.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 14:37:17 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/10 15:15:25 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Copies environment entry pointers into a temporary sortable array.
1.	Does not duplicate the strings because the function only reorders refs
2.	Stores the array in line_gc so it is cleaned after the command
*/
static char	**copy_env_refs(t_shell *shell)
{
	char	**copy;
	int		i;

	copy = gc_malloc(&shell->line_gc, sizeof(char *)
			* (env_count(shell->env) + 1));
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

/*
Sorts environment references alphabetically for export output.
1.	Uses a simple in-place comparison sort
2.	Swaps only pointers, not the environment strings themselves
*/
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

/*
Prints one entry in declare -x format.
1.	Prints the key after the declare prefix
2.	Prints assigned values inside quotes
3.	Prints names without '=' as export-only declarations
*/
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

/*
Prints all exported environment entries.
1.	Copies references so sorting does not change shell->env order
2.	Sorts the temporary reference array
3.	Prints each entry using declare -x formatting
*/
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
