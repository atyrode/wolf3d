/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atyrode <atyrode@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/05 15:27:01 by atyrode           #+#    #+#             */
/*   Updated: 2017/10/13 19:49:15 by atyrode          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/wolf3d.h"

void		hooks(t_mlx *mlx)
{
	mlx_hook(mlx->win, 2, 1L << 0, key_press, mlx);
	mlx_hook(mlx->win, 17, 1L << 0, hook_close, mlx);
}

void		right_left(t_mlx *mlx)
{
	if (KEYCODE == 124)
	{
		OLD_DIR_X = DIR_X;
		DIR_X = DIR_X * cos(-ROT_SPEED) - DIR_Y * sin(-ROT_SPEED);
		DIR_Y = OLD_DIR_X * sin(-ROT_SPEED) + DIR_Y * cos(-ROT_SPEED);
		OLD_PLANE_X = PLANE_X;
		PLANE_X = PLANE_X * cos(-ROT_SPEED) - PLANE_Y * sin(-ROT_SPEED);
		PLANE_Y = OLD_PLANE_X * sin(-ROT_SPEED) + PLANE_Y * cos(-ROT_SPEED);
	}
	else
	{
		OLD_DIR_X = DIR_X;
		DIR_X = DIR_X * cos(ROT_SPEED) - DIR_Y * sin(ROT_SPEED);
		DIR_Y = OLD_DIR_X * sin(ROT_SPEED) + DIR_Y * cos(ROT_SPEED);
		OLD_PLANE_X = PLANE_X;
		PLANE_X = PLANE_X * cos(ROT_SPEED) - PLANE_Y * sin(ROT_SPEED);
		PLANE_Y = OLD_PLANE_X * sin(ROT_SPEED) + PLANE_Y * cos(ROT_SPEED);
	}
}

void		up_down(t_mlx *mlx)
{
	if (KEYCODE == 126)
	{
		if (GRID[(int)(POS_X + (DIR_X * MOVE_SPEED) * 1.5)][(int)(POS_Y)] == 0)
			if ((POS_X + DIR_X * MOVE_SPEED) >= 1
					&& (POS_X + DIR_X * MOVE_SPEED) < Y_NBR - 1)
				POS_X += DIR_X * MOVE_SPEED;
		if (GRID[(int)(POS_X)][(int)(POS_Y + (DIR_Y * MOVE_SPEED) * 1.5)] == 0)
			if ((POS_Y + DIR_Y * MOVE_SPEED) >= 1
					&& (POS_Y + DIR_Y * MOVE_SPEED) < Y_NBR - 1)
				POS_Y += DIR_Y * MOVE_SPEED;
	}
	else
	{
		if (GRID[(int)(POS_X - (DIR_X * MOVE_SPEED) * 1.5)][(int)(POS_Y)] == 0)
			if ((POS_X - DIR_X * MOVE_SPEED) >= 1
					&& (POS_X - DIR_X * MOVE_SPEED) < Y_NBR - 1)
				POS_X -= DIR_X * MOVE_SPEED;
		if (GRID[(int)(POS_X)][(int)(POS_Y - (DIR_Y * MOVE_SPEED) * 1.5)] == 0)
			if ((POS_Y - DIR_Y * MOVE_SPEED) >= 1
					&& (POS_Y - DIR_Y * MOVE_SPEED) < Y_NBR - 1)
				POS_Y -= DIR_Y * MOVE_SPEED;
	}
}

int			key_press(int keycode, t_mlx *mlx)
{
	KEYCODE = keycode;
	if (KEYCODE == 124 || KEYCODE == 123)
		right_left(mlx);
	if (KEYCODE == 126 || KEYCODE == 125)
		up_down(mlx);
	if (KEYCODE == 53)
		mlx_free(mlx);
	redraw_raytracing(mlx);
	return (0);
}

int			hook_close(t_mlx *mlx)
{
	mlx_free(mlx);
	exit(EXIT_SUCCESS);
	return (0);
}
