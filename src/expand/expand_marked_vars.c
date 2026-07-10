/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_marked_vars.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 12:40:49 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/10 12:49:03 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

static int	append_marked_value(t_shell *shell, char **res,
	char *value, int split)
{
	int	i;

	if (!value)
		return (1);
	i = 0;
	while (value[i])
	{
		if (split && (value[i] == ' ' || value[i] == '\t'
				|| value[i] == '\n'))
		{
			if (!append_char(shell, res, EXP_SPLIT))
				return (0);
			i++;
		}
		else if (!append_char(shell, res, value[i++]))
			return (0);
	}
	return (1);
}

static int	expand_marked_status(t_shell *shell, char **res, int *i, int split)
{
	char	*value;
	int		ok;

	value = ft_itoa(shell->last_exit);
	if (!value)
		return (0);
	ok = append_marked_value(shell, res, value, split);
	free(value);
	*i += 2;
	return (ok);
}

int	expand_unquoted_variable(t_shell *shell, char *str, char **res, int *i)
{
	int		start;
	char	*key;
	char	*value;
	int		ok;

	if (str[*i + 1] == '?')
		return (expand_marked_status(shell, res, i, 1));
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
	ok = append_marked_value(shell, res, value, 1);
	free(key);
	return (ok);
}

int	expand_quoted_variable(t_shell *shell, char *str, char **res, int *i)
{
	int		start;
	char	*key;
	char	*value;
	int		ok;

	if (str[*i + 1] == '?')
		return (expand_marked_status(shell, res, i, 0));
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
	ok = append_marked_value(shell, res, value, 0);
	free(key);
	return (ok);
}
