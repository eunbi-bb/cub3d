/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gozturk <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 12:06:18 by gozturk           #+#    #+#             */
/*   Updated: 2024/01/31 12:06:22 by gozturk          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*protect_mem(char *str)
{
	if (str == NULL)
		err_msg("Memory");
	return (str);
}

int	ft_strlen_protect(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	ft_strsame(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	if (s1 == NULL || s2 == NULL)
		return (0);
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

char	**array_dup(t_file *file, char **arr)
{
	char	**dup;
	int		arr_len;
	int		i;

	arr_len = file->total_lines;
	i = 0;
	dup = (char **)malloc(sizeof(char *) * (arr_len + 1));
	if (dup == NULL)
		exit(1);
	while (arr[i] != NULL && i < arr_len)
	{
		dup[i] = ft_strdup(arr[i]);
		if (dup[i] == NULL)
			exit(1);
		i++;
	}
	dup[i] = NULL;
	return (dup);
}
