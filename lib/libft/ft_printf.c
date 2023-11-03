/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: gozturk <marvin@codam.nl>                    +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/11/10 18:05:45 by gozturk       #+#    #+#                 */
/*   Updated: 2022/11/16 16:00:47 by gozturk       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	convert_format(int sp, va_list *arg)
{	
	if (sp == 'c')
		return (ft_putchar(va_arg(*arg, int)));
	if (sp == 'd')
		return (ft_putnbr(va_arg(*arg, int)));
	if (sp == 'i')
		return (ft_putnbr(va_arg(*arg, int)));
	if (sp == 's')
		return (ft_putstr(va_arg(*arg, char *)));
	if (sp == 'p')
		return (write(1, "0x", 2) + ft_putaddr(va_arg(*arg, unsigned long)));
	if (sp == 'u')
		return (ft_putunsigned(va_arg(*arg, unsigned)));
	if (sp == 'x')
		return (ft_puthexlow(va_arg(*arg, unsigned)));
	if (sp == 'X')
		return (ft_puthexupp(va_arg(*arg, unsigned)));
	if (sp == '%')
		return (ft_putchar('%'));
	return (0);
}

int	ft_printf(const char *fstr, ...)
{
	va_list	arg;
	int		value;
	int		i;

	value = 0;
	i = 0;
	va_start(arg, fstr);
	while (fstr[i] != '\0')
	{
		if (fstr[i] == '%')
		{
			i++;
			if (fstr[i] == '\0')
				break ;
			value += convert_format(fstr[i], &arg);
		}
		else if (fstr[i] != '%')
			value += ft_putchar(fstr[i]);
		i++;
	}
	va_end(arg);
	return (value);
}
/*
int main()
{	
	int a = 369054;
	void *ptrc ;
	ptrc = &a;
	ft_printf("%p%2", ptrc);
}
*/
