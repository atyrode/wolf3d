/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atyrode <atyrode@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 15:27:01 by atyrode           #+#    #+#             */
/*   Updated: 2017/10/10 20:26:27 by atyrode          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/wolf3d.h"

void		hooks(t_mlx *mlx)
{
	mlx_mouse_hook(mlx->win, mouse_hook, mlx);
	mlx_hook(mlx->win, 6, 0, mouse_mov, mlx);
	mlx_key_hook(mlx->win, key_func, mlx);
	mlx_loop_hook(mlx->mlx, loop_hook, mlx);
}

int			loop_hook(t_mlx *mlx)
{
	if (KEYCODE == 69)
	{}
		//+
	if (KEYCODE == 78)
	{}
		//-
	return (0);
}

int			mouse_hook(int button, int x, int y, t_mlx *mlx)
{
	BUTTON = button;
	if (button == 4 && x >= 0 && x < W_WIDTH && y >= 0 && y < W_HEIGHT)
	{}
		//molette haut
	if (button == 5 && x >= 0 && x < W_WIDTH && y >= 0 && y < W_HEIGHT)
	{}
		//molette bas
	return (0);
}

int			mouse_mov(int x, int y, t_mlx *mlx)
{
	MOUSE_X = x;
	MOUSE_Y = y;
	return (0);
}

int			key_func(int keycode, t_mlx *mlx)
{
	KEYCODE = keycode;
	if (KEYCODE == 53)
		mlx_free(mlx);
	if (KEYCODE == 49)
	{}
		//space bar
	if (KEYCODE == 35)
	{}
		//p
	if (KEYCODE == 124)
	{
		OLD_DIR_X = DIR_X;
		DIR_X = DIR_X * cos(-ROT_SPEED) - DIR_Y * sin(-ROT_SPEED);
		DIR_Y = OLD_DIR_X * sin(-ROT_SPEED) + DIR_Y * cos(-ROT_SPEED);
		OLD_PLANE_X = PLANE_X;
		PLANE_X = PLANE_X * cos(-ROT_SPEED) - PLANE_Y * sin(-ROT_SPEED);
		PLANE_Y = OLD_PLANE_X * sin(-ROT_SPEED) + PLANE_Y * cos(-ROT_SPEED);
		printf ("\n\n-------------- fleche gauche ---------------\n\n");
	}
		//fleche gauche
	if (KEYCODE == 123)
	{
		OLD_DIR_X = DIR_X;
		DIR_X = DIR_X * cos(ROT_SPEED) - DIR_Y * sin(ROT_SPEED);
		DIR_Y = OLD_DIR_X * sin(ROT_SPEED) + DIR_Y * cos(ROT_SPEED);
		OLD_PLANE_X = PLANE_X;
		PLANE_X = PLANE_X * cos(ROT_SPEED) - PLANE_Y * sin(ROT_SPEED);
		PLANE_Y = OLD_PLANE_X * sin(ROT_SPEED) + PLANE_Y * cos(ROT_SPEED);
	}
		//fleche droite
	if (KEYCODE == 126)
	{
		if (GRID[(int)(POS_X + DIR_X * MOVE_SPEED)][(int)(POS_Y)] == 0)
			POS_X += DIR_X * MOVE_SPEED;
		if (GRID[(int)(POS_X)][(int)(POS_Y + DIR_Y * MOVE_SPEED)] == 0)
			POS_Y += DIR_Y * MOVE_SPEED;
	}
		//fleche haute
	if (KEYCODE == 125)
	{
		if (GRID[(int)(POS_X + DIR_X * MOVE_SPEED)][(int)(POS_Y)] == 0)
			POS_X -= DIR_X * MOVE_SPEED;
		if (GRID[(int)(POS_X)][(int)(POS_Y + DIR_Y * MOVE_SPEED)] == 0)
			POS_Y -= DIR_Y * MOVE_SPEED;
	}
		//fleche basse
	if (KEYCODE == 18)
	{}
		//touche 1
	if (KEYCODE == 19 || KEYCODE == 20)
	{}
		//touche 2 et 3
	if (KEYCODE == 18 || KEYCODE == 19 || KEYCODE == 20 || KEYCODE == 15)
	{}
		//touche 1 2 3 ou r
	if (KEYCODE == 36)
	{}
		//touche entrée

	redraw_raytracing(mlx);
	return (0);
}
