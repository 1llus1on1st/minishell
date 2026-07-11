/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_marked_vars.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/09 12:40:49 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/10 15:16:45 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Appends an expanded variable value to a marked result.
1.	Ignores missing variables by appending nothing
2.	When split is true, converts whitespace to EXP_SPLIT markers
3.	When split is false, preserves whitespace literally
*/
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

/*
Expands $? into the marked result.
1.	Converts the last exit status to a temporary string
2.	Appends it with or without split marking depending on quote context
3.	Advances the input index past "$?"
*/
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

/*
Expands a variable outside quotes.
1.	Expands $? with field splitting enabled
2.	Keeps a literal '$' when it is not followed by a variable character
3.	Looks up the variable name and marks whitespace for later splitting
*/
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

/*
Expands a variable inside double quotes.
1.	Expands $? without field splitting
2.	Keeps a literal '$' when it is not followed by a variable character
3.	Preserves whitespace because double quotes protect the expanded value
*/
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
