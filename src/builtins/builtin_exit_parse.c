/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit_parse.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 14:50:15 by mshargan          #+#    #+#             */
/*   Updated: 2026/07/01 14:50:34 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	is_space_char(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

static int	is_sign(char c)
{
	return (c == '+' || c == '-');
}

static unsigned long long	get_limit(int sign)
{
	if (sign == -1)
		return (9223372036854775808ULL);
	return (9223372036854775807ULL);
}

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
	if (is_sign(str[i]))
	{
		if (str[i++] == '-')
			sign = -1;
	}
	if (!read_digits(str, &i, sign, &value))
		return (0);
	while (is_space_char(str[i]))
		i++;
	if (str[i])
		return (0);
	if (sign == -1 && value == 9223372036854775808ULL)
		*code = -9223372036854775807LL - 1;
	else if (sign == -1)
		*code = -(long long)value;
	else
		*code = (long long)value;
	return (1);
}