#include "./../includes/wolf3d.h"
#include <stdio.h>

void	test_print_tab(int **grid, int line_value)
{
	int i;
	int j;

	i = 0;
	printf ("map:\n-----\n");
	while (i < line_value)
	{
		j = 0;
		while (grid[i][j] != -42)
		{
			printf("%d", grid[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	printf("-----\n");
	return ;
}

int		ft_count(char **tab)
{
	int count;

	count = 0;
	while (tab[count] != 0)
		count++;
	return (count);
}

int		**parse_in_int(char **tab, int line_value)
{
	int **grid;
	char **tmp;
	int i;
	int j;

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
		free(tmp);
		tmp = NULL;
		i++;
	}
	return (grid);
}

char	**fill_tab(int line_value, char *file)
{
	int fd;
	int i;
	char **tab;

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

	fd = open(filename, O_RDONLY, S_IREAD);
	Y_NBR = 0;
	while (get_next_line(fd , &buffer) > 0)
	{
		Y_NBR++;
		//printf("buffer=%s\n", buffer);
	}
	//printf("lines_value = %d\n", Y_NBR);
	free(buffer);
	close(fd);
	tab = fill_tab(Y_NBR, filename);
	GRID = parse_in_int(tab, Y_NBR);
	free(tab);
	test_print_tab(GRID, Y_NBR);
	return (0);
}
