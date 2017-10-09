/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atyrode <atyrode@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/30 19:23:07 by atyrode           #+#    #+#             */
/*   Updated: 2017/10/09 17:18:35 by atyrode          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/wolf3d.h"

t_mlx		*mlx_free(t_mlx *mlx)
{
	if (mlx->win != NULL)
		mlx_destroy_window(mlx->mlx, mlx->win);
	if (mlx->image != NULL)
		delete_image(mlx);
	if (mlx->env != NULL)
		ft_memdel((void **)&mlx->env);
	if (mlx->rt != NULL)
		ft_memdel((void **)&mlx->rt);
	if (mlx->algo != NULL)
		ft_memdel((void **)&mlx->algo);
	ft_memdel((void **)&mlx);
	exit(-1);
}

t_mlx		*initialize(void)
{
	t_mlx	*mlx;

	if ((mlx = ft_memalloc(sizeof(t_mlx))) == NULL)
		return (NULL);
	if ((mlx->mlx = mlx_init()) == NULL
		|| (mlx->win = mlx_new_window(mlx->mlx, W_WIDTH, W_HEIGHT,
			"Fract'Ol")) == NULL
		|| (mlx->image = new_image(mlx)) == NULL
		|| (mlx->rt = ft_memalloc(sizeof(t_rt))) == NULL
		|| (mlx->algo = ft_memalloc(sizeof(t_rosette))) == NULL
		|| (mlx->env = ft_memalloc(sizeof(t_env))) == NULL)
		return (mlx_free(mlx));
	return (mlx);
}
