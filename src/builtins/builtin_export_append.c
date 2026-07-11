/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_append.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/10 18:39:04 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/10 18:41:33 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Checks whether an export argument uses NAME+=value syntax.
1.	Returns true only when '+' appears immediately before '='
2.	Stops at a plain '=' because normal assignments are not append mode
*/
int	is_append_assignment(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '+' && arg[i + 1] == '=')
			return (1);
		if (arg[i] == '=')
			return (0);
		i++;
	}
	return (0);
}

/*
Extracts the variable name from a NAME+=value argument.
1.	Finds the '+=' separator
2.	Returns a newly allocated substring before that separator
*/
static char	*get_append_name(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && !(arg[i] == '+' && arg[i + 1] == '='))
		i++;
	return (ft_substr(arg, 0, i));
}

/*
Builds the environment entry produced by export append mode.
1.	Treats a missing old value as an empty string
2.	Concatenates the old value and the appended value
3.	Prefixes the combined value with NAME=
*/
static char	*make_append_entry(char *name, char *old_value, char *append_value)
{
	char	*joined_value;
	char	*left;
	char	*entry;

	if (!old_value)
		old_value = "";
	joined_value = ft_strjoin(old_value, append_value);
	if (!joined_value)
		return (NULL);
	left = ft_strjoin(name, "=");
	if (!left)
		return (free(joined_value), NULL);
	entry = ft_strjoin(left, joined_value);
	free(left);
	free(joined_value);
	return (entry);
}

/*
Applies one NAME+=value export argument.
1.	Extracts and validates the variable name before changing env
2.	Reads the current value from the shell environment
3.	Builds a normal NAME=value entry with the combined value
4.	Stores the resulting entry through env_set_entry
*/
int	export_append(t_shell *shell, char *arg)
{
	char	*name;
	char	*entry;
	char	*append_value;
	int		status;

	name = get_append_name(arg);
	if (!name)
		return (1);
	if (!is_valid_identifier(name, 0))
		return (free(name), export_error(arg));
	append_value = ft_strchr(arg, '=') + 1;
	entry = make_append_entry(name, get_env_value(shell, name), append_value);
	free(name);
	if (!entry)
		return (1);
	status = env_set_entry(shell, entry);
	free(entry);
	if (!status)
		return (1);
	return (0);
}
