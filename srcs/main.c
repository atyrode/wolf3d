/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atyrode <atyrode@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/13 19:40:36 by atyrode           #+#    #+#             */
/*   Updated: 2017/10/13 19:45:35 by atyrode          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/wolf3d.h"

void	rt_init(t_mlx *mlx)
{
	POS_X = 2;
	POS_Y = 2;
	DIR_X = -1;
	DIR_Y = 0;
	PLANE_X = 0;
	PLANE_Y = 0.66;
	CUR_FRAME = 0;
	OLD_FRAME = 0;
	return ;
}

void	redraw_raytracing(t_mlx *mlx)
{
	mlx_clear_window(mlx->mlx, mlx->win);
	delete_image(mlx);
	new_image(mlx);
	raytracing(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->image->image, 0, 0);
	mlx_do_sync(mlx->mlx);
}

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
		printf("parsing -> OK!\n");
	hooks(mlx);
	rt_init(mlx);
	raytracing(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->image->image, 0, 0);
	mlx_loop(mlx->mlx);
	return (0);
}
