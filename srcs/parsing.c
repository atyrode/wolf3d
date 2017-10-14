/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atyrode <atyrode@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/13 19:41:03 by atyrode           #+#    #+#             */
/*   Updated: 2017/10/13 23:24:11 by atyrode          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/wolf3d.h"
#include <stdio.h>

int		ft_count(char **tab)
{
	int count;

	count = 0;
	while (tab[count] != 0)
		count++;
	return (count);
}

void	*free_tab(char **tmp)
{
	int		k;

	k = -1;
	while (tmp[++k])
		free(tmp[k]);
	free(tmp);
	return (NULL);
}

int		**parse_in_int(char **tab, int line_value)
{
	int		**grid;
	char	**tmp;
	int		i;
	int		j;

	i = 0;
	if ((grid = (int **)malloc(sizeof(int*) * line_value)) == NULL)
		return (NULL);
	while (i < line_value)
	{
		tmp = ft_split(tab[i], " ");
		j = 0;
		if ((grid[i] = (int*)malloc(sizeof(int) * ft_count(tmp) + 1)) == NULL)
			return (NULL);
		while (j < ft_count(tmp))
		{
			grid[i][j] = ft_getnbr(tmp[j]);
			j++;
		}
		grid[i][j] = -42;
		tmp = free_tab(tmp);
		i++;
	}
	return (grid);
}

char	**fill_tab(int line_value, char *file)
{
	int		fd;
	int		i;
	char	**tab;

	i = 0;
	if ((tab = (char**)malloc(sizeof(char*) * line_value)) == NULL)
		return (NULL);
	fd = open(file, O_RDONLY, S_IREAD);
	while (i < line_value)
	{
		get_next_line(fd, &tab[i]);
		i++;
	}
	return (tab);
}

int		parsing(char *filename, t_mlx *mlx)
{
	int		fd;
	char	*buffer;
	char	**tab;
	int		k;

	k = -1;
	fd = open(filename, O_RDONLY, S_IREAD);
	Y_NBR = 0;
	while (get_next_line(fd, &buffer) > 0)
	{
		Y_NBR++;
		free(buffer);
	}
	free(buffer);
	close(fd);
	tab = fill_tab(Y_NBR, filename);
	GRID = parse_in_int(tab, Y_NBR);
	while (++k < Y_NBR)
		free(tab[k]);
	free(tab);
	return (0);
}
