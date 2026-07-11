/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit_parse.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 14:50:15 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/10 14:12:56 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Checks for whitespace accepted around an exit argument.
1.	Accepts a normal space
2.	Accepts ASCII control whitespace from tab through carriage return
*/
static int	is_space_char(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

/*
Checks whether a character is an explicit number sign.
*/
static int	is_sign(char c)
{
	return (c == '+' || c == '-');
}

/*
Returns the absolute parsing limit for a signed long long.
1.	Allows one extra value for LLONG_MIN
2.	Uses LLONG_MAX for positive numbers
*/
static unsigned long long	get_limit(int sign)
{
	if (sign == -1)
		return (9223372036854775808ULL);
	return (9223372036854775807ULL);
}

/*
Reads and validates the digit part of an exit argument.
1.	Requires at least one digit
2.	Accumulates the value as unsigned long long
3.	Rejects overflow before multiplying by 10
*/
static int	read_digits(char *str, int *i, int sign,
		unsigned long long *value)
{
	unsigned long long	limit;
	int					digit;

	limit = get_limit(sign);
	if (!ft_isdigit(str[*i]))
		return (0);
	while (ft_isdigit(str[*i]))
	{
		digit = str[*i] - '0';
		if (*value > (limit - digit) / 10)
			return (0);
		*value = (*value * 10) + digit;
		(*i)++;
	}
	return (1);
}

/*
Parses a shell exit code argument.
1.	Skips leading and trailing whitespace
2.	Accepts one optional '+' or '-' sign
3.	Rejects missing digits, overflow and extra trailing characters
4.	Stores the parsed value in code when it is valid
*/
int	parse_exit_code(char *str, long long *code)
{
	unsigned long long	value;
	int					sign;
	int					i;

	i = 0;
	sign = 1;
	value = 0;
	while (is_space_char(str[i]))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (is_sign(str[i]))
		i++;
	if (!read_digits(str, &i, sign, &value))
		return (0);
	while (is_space_char(str[i]))
		i++;
	if (str[i])
		return (0);
	set_exit_code(code, value, sign);
	return (1);
}
