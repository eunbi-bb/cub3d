/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_extension.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozturk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:04:26 by gozturk           #+#    #+#             */
/*   Updated: 2024/01/31 12:04:31 by gozturk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** Compares expected extension (param1) and extension of
** given file (param2)
*/
bool	valid_file_extension(char *extension, char *file_name)
{
	int	len_1;
	int	len_2;

	len_1 = ft_strlen(extension) - 1;
	len_2 = ft_strlen(file_name) - 1;
	while (len_1 >= 0 && len_2 >= 0)
	{
		if (extension[len_1] != file_name[len_2])
			err_msg("Invalid file extension");
		len_1--;
		len_2--;
	}
	return (true);
}
