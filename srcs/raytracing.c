
#include "./../includes/wolf3d.h"

void    hit_rt(t_mlx *mlx)
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
  return ;
}

void    check_rt_init(t_mlx *mlx)
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
    SIDE_DIST_X = (MAP_Y + 1.0 - RAY_POS_Y) * DELTA_DIST_Y;
  }
  return ;
}

void    rt_loop_init(t_mlx *mlx, int i)
{
    CAMERA_X = 2 * i / (double)PARSER_X - 1;
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

void    rt_init(t_mlx *mlx)
{
    POS_X = 3;
    POS_Y = 3;
    DIR_X = 0;
    DIR_Y = 0;
    PLANE_X = 0;
    PLANE_Y = 0.66;
    CUR_FRAME = 0;
    OLD_FRAME = 0;
    return ;
}

void		raytracing(t_mlx *mlx)
{
  int   i;

  rt_init(mlx);
  i = 0;
  while (i < Y_NBR)
  {
    printf ("%d < %d\n", i, Y_NBR);
      rt_loop_init(mlx, i);
      while (HIT == 0)
          hit_rt(mlx);
      if (SIDE == 0)
          PERP_WALL_DIST = (MAP_X - RAY_POS_X + (1 - STEP_X) / 2) / RAY_DIR_X;
      else
          PERP_WALL_DIST = (MAP_Y - RAY_POS_Y + (1 - STEP_Y) / 2) / RAY_DIR_Y;
      LINE_HEIGHT = (int)(W_HEIGHT / PERP_WALL_DIST);
      if ((DRAW_START = -LINE_HEIGHT / 2 + W_HEIGHT / 2) < 0)
          DRAW_START = 0;
      if ((DRAW_END = LINE_HEIGHT / 2 + W_HEIGHT / 2) >= W_HEIGHT)
          DRAW_END = 0;
      if (GRID[MAP_X][MAP_Y] == 1)
          COLOR = 0xAA0000;
      if (SIDE == 1)
          COLOR = COLOR / 2;
	  ft_line_tracer(mlx, i);
      i++;
      printf ("i = %d\n", i);
  }
  return ;
}
