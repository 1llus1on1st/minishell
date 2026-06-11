/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 11:37:05 by mshargan          #+#    #+#             */
/*   Updated: 2026/06/11 11:38:55 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

static int	expand_exit_status(t_shell *shell, char **res, int *i)
{
	char	*value;

	value = ft_itoa(shell->last_exit);
	if (!value)
		return (0);
	if (!gc_add(&shell->line_gc, value))
		return (free(value), 0);
	if (!append_str(shell, res, value))
		return (0);
	*i += 2;
	return (1);
}

int	expand_variable(t_shell *shell, char *str, char **res, int *i)
{
	int		start;
	char	*key;
	char	*value;

	if (str[*i + 1] == '?')
		return (expand_exit_status(shell, res, i));
	if (!is_var_char(str[*i + 1]))
		return (append_char(shell, res, str[(*i)++]));
	(*i)++;
	start = *i;
	while (is_var_char(str[*i]))
		(*i)++;
	key = ft_substr(str, start, *i - start);
	if (!key)
		return (0);
	value = get_env_value(shell, key);
	free(key);
	return (append_str(shell, res, value));
}