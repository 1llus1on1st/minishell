/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_identifier.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 14:33:09 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/05 20:01:01 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Checks whether a character is allowed inside an identifier name.
1.	Accepts letters, digits and underscores
2.	Used after the first character, where digits are allowed
*/
static int	is_name_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

/*
Validates an environment identifier for export and unset.
1.	Requires the first character to be a letter or underscore
2.	Allows later characters to be letters, digits or underscores
3.	When allow_equal is true, stops successfully at the first '='
4.	Rejects empty strings and invalid assignment names
*/
int	is_valid_identifier(char *str, int allow_equal)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i])
	{
		if (allow_equal && str[i] == '=')
			return (1);
		if (!is_name_char(str[i]))
			return (0);
		i++;
	}
	return (1);
}
