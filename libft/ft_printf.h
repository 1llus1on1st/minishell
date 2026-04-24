/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshargan <mshargan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 12:30:38 by mshargan          #+#    #+#             */
/*   Updated: 2026/01/09 19:27:56 by mshargan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

typedef struct conversion_list
{
	int	conv;
	int	character;
	int	string;
	int	pointer;
	int	decimal;
	int	integer;
	int	u_decimal;
	int	lower_hex;
	int	upper_hex;
	int	percent;
}		t_conv_list;

// FT_PRINTF
int		ft_printf(const char *s, ...);
void	flags_initializer(t_conv_list *flags);
int		success_case(const char **s, va_list args, t_conv_list *flags);

// CHECKS
int		percent_check(const char **s);
int		flag_check(const char c);
int		conversion_check(const char *s, t_conv_list *flags);
int		trailing_percent_check(const char *s);
int		initial_check(const char *s);

// ADDITIONAL LIBFT
void	ft_puthex_fd(unsigned long long ptr, int fd);
char	*ft_htoa(unsigned int n);
char	*ft_uitoa(unsigned int n);

// PRINTS
int		print_char(va_list args);
int		print_string(va_list args);
int		print_pointer(va_list args);
int		print_integer(va_list args);
int		print_u_decimal(va_list args);
int		print_lower_hex(va_list args);
int		print_upper_hex(va_list args);
int		print_percent(void);

#endif
