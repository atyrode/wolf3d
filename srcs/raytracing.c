/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atyrode <atyrode@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/13 19:41:24 by atyrode           #+#    #+#             */
/*   Updated: 2017/10/13 19:54:02 by atyrode          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/wolf3d.h"

void	hit_rt(t_mlx *mlx)
{
	if (SIDE_DIST_X < SIDE_DIST_Y)
	{
		SIDE_DIST_X = SIDE_DIST_X + DELTA_DIST_X;
		MAP_X = MAP_X + STEP_X;
		SIDE = 0;
	}
	else
	{
		SIDE_DIST_Y = SIDE_DIST_Y + DELTA_DIST_Y;
		MAP_Y = MAP_Y + STEP_Y;
		SIDE = 1;
	}
	if (GRID[MAP_X][MAP_Y] > 0)
		HIT = 1;
}

void	check_rt_init(t_mlx *mlx)
{
	if (RAY_DIR_X < 0)
	{
		STEP_X = -1;
		SIDE_DIST_X = (RAY_POS_X - MAP_X) * DELTA_DIST_X;
	}
	else
	{
		STEP_X = 1;
		SIDE_DIST_X = (MAP_X + 1.0 - RAY_POS_X) * DELTA_DIST_X;
	}
	if (RAY_DIR_Y < 0)
	{
		STEP_Y = -1;
		SIDE_DIST_Y = (RAY_POS_Y - MAP_Y) * DELTA_DIST_Y;
	}
	else
	{
		STEP_Y = 1;
		SIDE_DIST_Y = (MAP_Y + 1.0 - RAY_POS_Y) * DELTA_DIST_Y;
	}
	return ;
}

void	rt_loop_init(t_mlx *mlx, int i)
{
	CAMERA_X = 2 * i / (double)W_WIDTH - 1;
	RAY_POS_X = POS_X;
	RAY_POS_Y = POS_Y;
	RAY_DIR_X = DIR_X + PLANE_X * CAMERA_X;
	RAY_DIR_Y = DIR_Y + PLANE_Y * CAMERA_X;
	MAP_X = (int)(RAY_POS_X);
	MAP_Y = (int)(RAY_POS_Y);
	DELTA_DIST_X = sqrt(1 + (RAY_DIR_Y * RAY_DIR_Y) / (RAY_DIR_X * RAY_DIR_X));
	DELTA_DIST_Y = sqrt(1 + (RAY_DIR_X * RAY_DIR_X) / (RAY_DIR_Y * RAY_DIR_Y));
	HIT = 0;
	SIDE = 0;
	check_rt_init(mlx);
	return ;
}

void	rt_colors(t_mlx *mlx, int i)
{
	X1 = i;
	Y1 = DRAW_START;
	Y2 = DRAW_END;
	if (GRID[MAP_X][MAP_Y] == 1)
	{
		if (STEP_X == -1 && STEP_Y == -1)
			COLOR = (SIDE == 1) ? 0x594F4F / 2 : 0x9DE0AD;
		else if (STEP_X == 1 && STEP_Y == -1)
			COLOR = (SIDE == 1) ? 0x594F4F / 2 : 0xE5FCC2;
		else if (STEP_X == -1 && STEP_Y == 1)
			COLOR = (SIDE == 1) ? 0x45ADA8 : 0x9DE0AD;
		else if (STEP_X == 1 && STEP_Y == 1)
			COLOR = (SIDE == 1) ? 0x45ADA8 : 0xE5FCC2;
	}
	while (Y1++ <= Y2)
		image_set_pixel(mlx);
	Y1 = DRAW_START + 1;
	COLOR = 0x594F4F;
	while (Y1-- >= 0)
		image_set_pixel(mlx);
	Y1 = DRAW_END;
	COLOR = 0x547980;
	while (Y1++ <= W_HEIGHT && Y1 >= 0)
		image_set_pixel(mlx);
}

void	raytracing(t_mlx *mlx)
{
	int	i;

	i = 0;
	while (i <= W_WIDTH)
	{
		rt_loop_init(mlx, i);
		while (HIT == 0)
			hit_rt(mlx);
		PERP_WALL_DIST = (SIDE == 0) ? (MAP_X - RAY_POS_X + (1 - STEP_X) / 2)
			/ RAY_DIR_X : (MAP_Y - RAY_POS_Y + (1 - STEP_Y) / 2) / RAY_DIR_Y;
		LINE_HEIGHT = (int)(W_HEIGHT / PERP_WALL_DIST);
		if ((DRAW_START = -LINE_HEIGHT / 2 + W_HEIGHT / 2) < 0)
			DRAW_START = 0;
		if ((DRAW_END = LINE_HEIGHT / 2 + W_HEIGHT / 2) >= W_HEIGHT)
			DRAW_END = W_HEIGHT;
		rt_colors(mlx, i);
		OLD_FRAME = CUR_FRAME;
		CUR_FRAME = clock();
		FRAME = (CUR_FRAME - OLD_FRAME) / 1000.0;
		MOVE_SPEED = FRAME * 30.0;
		ROT_SPEED = FRAME * 18.0;
		i++;
	}
	return ;
}
