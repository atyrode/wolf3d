
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
  //printf ("SIDE = %d\n", SIDE);
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
    SIDE_DIST_Y = (MAP_Y + 1.0 - RAY_POS_Y) * DELTA_DIST_Y;
  }
  printf ("SIDE_DIST_X (%f) | SIDE_DIST_Y (%f)\n", SIDE_DIST_X, SIDE_DIST_Y);
  return ;
}

void    rt_loop_init(t_mlx *mlx, int i)
{

    CAMERA_X = 2 * i / (double)W_WIDTH - 1;
    printf ("CAMERA_X (%f) = 2 * i (%d) / (double)(W_WIDTH (%d) - 1)\n", CAMERA_X, i, W_WIDTH);
    RAY_POS_X = POS_X;
    RAY_POS_Y = POS_Y;
    RAY_DIR_X = DIR_X + PLANE_X * CAMERA_X;
    printf ("RAY_DIR_X (%f) = DIR_X (%f) + PLANE_X (%f) * CAMERA_X (%f)\n", RAY_DIR_X, DIR_X, PLANE_X, CAMERA_X);
    RAY_DIR_Y = DIR_Y + PLANE_Y * CAMERA_X;
    printf ("RAY_DIR_Y (%f) = DIR_Y (%f) + PLANE_Y (%f) * CAMERA_X (%f)\n", RAY_DIR_Y, DIR_Y, PLANE_Y, CAMERA_X);
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
    POS_X = 5;
    POS_Y = 5;
    DIR_X = -1;
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

  i = 0;
  //printf ("RT!\n");
  while (i <= W_WIDTH)
  {
    //printf ("%d < %d\n", i, W_WIDTH);
    printf ("POS_X = %f | POS_Y = %f\n", POS_X, POS_Y);
      rt_loop_init(mlx, i);
      while (HIT == 0)
          hit_rt(mlx);
      if (SIDE == 0)
      {
          PERP_WALL_DIST = (MAP_X - RAY_POS_X + (1 - STEP_X) / 2) / RAY_DIR_X;
          printf ("PERP_WALL_DIST (%f) = (MAP_X (%d) - RAY_POS_X (%f) + (1 - STEP_X (%d) / 2) / RAY_DIR_X (%f)\n", PERP_WALL_DIST, MAP_X, RAY_POS_X, STEP_X, RAY_DIR_X);
      }
      else
      {
          PERP_WALL_DIST = (MAP_Y - RAY_POS_Y + (1 - STEP_Y) / 2) / RAY_DIR_Y;
          printf ("PERP_WALL_DIST (%f) = (MAP_Y (%d) - RAY_POS_Y (%f) + (1 - STEP_Y (%d) / 2) / RAY_DIR_Y (%f)\n", PERP_WALL_DIST, MAP_Y, RAY_POS_Y, STEP_Y, RAY_DIR_Y);
      }
      LINE_HEIGHT = (int)(W_HEIGHT / PERP_WALL_DIST);
      printf ("LINE_HEIGHT (%d) = (int)(W_HEIGHT (%d) / PERP_WALL_DIST (%f))\n", LINE_HEIGHT, W_HEIGHT, PERP_WALL_DIST);
      if ((DRAW_START = -LINE_HEIGHT / 2 + W_HEIGHT / 2) < 0)
          DRAW_START = 0;
      if ((DRAW_END = LINE_HEIGHT / 2 + W_HEIGHT / 2) >= W_HEIGHT)
      {
        printf ("DRAW_END (%d) = LINE_HEIGHT (%d) / 2 + W_HEIGHT (%d) / 2) >= W_HEIGHT (%d)\n", DRAW_END, LINE_HEIGHT, W_HEIGHT, W_HEIGHT);
        DRAW_END = W_HEIGHT;
      }
      if (GRID[MAP_X][MAP_Y] == 1)
          COLOR = 0x5555AA;
      if (SIDE == 1)
          COLOR = COLOR / 2;
      X1 = i;
      Y1 = DRAW_START;
      Y2 = DRAW_END;
      printf ("DRAW_START = %d | DRAW_END = %d\n\n\n  ", DRAW_START, DRAW_END);
      while (Y1 <= Y2)
      {
        //printf ("loop\n");
		     image_set_pixel(mlx);
         Y1++;
      }
      Y1 = DRAW_START;
      COLOR = 0x00AA00 / 2;
      while (Y1 - 1 >= 0)
      {
        image_set_pixel(mlx);
        Y1--;
      }
      Y1 = DRAW_END;
      COLOR = 0x00AA00;
      while (Y1 <= W_HEIGHT && Y1 >= 0)
      {
        if (DRAW_END <= 0 || DRAW_START <= 0)
        COLOR = 0x000000;
        image_set_pixel(mlx);
        //printf ("stuck\n");
        Y1++;
      }
      OLD_FRAME = CUR_FRAME;
      CUR_FRAME = clock();
      FRAME = (CUR_FRAME - OLD_FRAME) / 1000.0;
      MOVE_SPEED = FRAME * 30.0;
      ROT_SPEED = FRAME * 18.0;
	  //ft_line_tracer(mlx, i);
      i++;
      //printf ("i = %d\n", i);
  }
  return ;
}

void    redraw_raytracing(t_mlx *mlx)
{
  mlx_clear_window(mlx->mlx, mlx->win);
	delete_image(mlx);
	new_image(mlx);
	raytracing(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->image->image, 0, 0);
	mlx_do_sync(mlx->mlx);
}
