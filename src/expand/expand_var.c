/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/11 11:37:05 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/05 19:58:50 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Checks whether a character can be part of an environment variable name.
1.	Accepts alphabetic and numeric characters
2.	Accepts underscore characters
3.	Rejects every other character
4.	Returns 1 when the character is valid and 0 when it is not
*/
static int	is_var_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

/*
Expands the special $? variable into the last exit status.
1.	Converts shell->last_exit into a string
2.	Adds the new string to the line garbage collector
3.	Appends the exit status string to the expansion result
4.	Moves the input index past the two characters "$?"
5.	Returns 1 on success and 0 if allocation or append fails
*/
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

/*
Expands a dollar expression inside a command string.
1.	Expands "$?" using the shell last exit status
2.	Keeps a literal "$" when the next character is not a variable character
3.	Reads the full variable name after the dollar sign
4.	Looks up the variable value in the shell environment
5.	Appends the value to the result, or an empty string if it does not exist
*/
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
