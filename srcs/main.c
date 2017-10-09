#include "./../includes/wolf3d.h"

int		main(int argc, char **argv)
{
	t_mlx	*mlx;
	char	*filename;

	if (!(argc == 1) || !(argv))
		return (-1);
	if ((mlx = initialize()) == NULL)
		return (-1);
	filename = "maps/map.wolf";
	if (parsing(filename, mlx) == 0)
		printf ("parsing -> OK!\n");
	hooks(mlx);
	raytracing(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->image->image, 0, 0);
	printf ("mlx loop!\n");
	mlx_loop(mlx->mlx);
	return (0);
}
