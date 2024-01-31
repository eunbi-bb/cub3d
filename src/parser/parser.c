/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozturk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:05:03 by gozturk           #+#    #+#             */
/*   Updated: 2024/01/31 12:05:06 by gozturk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parser(int argc, char **argv, t_file *file)
{
	(void)argc;
	init_file_struct(file);
	valid_file_extension(".cub", argv[1]);
	get_content_from_file(file, argv[1]);
	return (0);
}
