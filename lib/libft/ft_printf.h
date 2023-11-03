/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: gozturk <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/16 14:25:25 by gozturk       #+#    #+#                 */
/*   Updated: 2022/11/16 14:29:03 by gozturk       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

size_t	ft_strlen(const char *s);
int		ft_putnbr(int i);
int		ft_putchar(char c);
int		ft_putstr(char *s);
int		ft_puthexupp(unsigned int i);
int		ft_puthexlow(unsigned int i);
int		ft_putaddr(unsigned long i);
int		ft_putunsigned(unsigned int i);
int		ft_printf(const char *fstr, ...);
#endif
