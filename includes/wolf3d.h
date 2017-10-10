# ifndef WOLF3D_H
# define WOLF3D_H

#include "./../libft/includes/libft.h"
#include "./../minilibx_macos/mlx.h"
#include <stdio.h>
#include <math.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define W_WIDTH 896
#define W_HEIGHT 800

#define COORD_X mlx->env->x
#define COORD_Y mlx->env->y
#define COLOR mlx->env->color
#define BPP mlx->image->bpp
#define X_NBR mlx->env->parser_x
#define Y_NBR mlx->env->parser_y
#define GRID mlx->grid
#define KEYCODE mlx->keycode
#define BUTTON mlx->button
#define MOUSE_X mlx->env->mouse_x
#define MOUSE_Y mlx->env->mouse_y
#define POS_X mlx->rt->pos_x
#define POS_Y mlx->rt->pos_y
#define DIR_X mlx->rt->direction_x
#define DIR_Y mlx->rt->direction_y
#define PLANE_X mlx->rt->plane_x
#define PLANE_Y mlx->rt->plane_y
#define CUR_FRAME mlx->rt->cur_frame
#define OLD_FRAME mlx->rt->old_frame
#define CAMERA_X mlx->rt->camera_x
#define CAMERA_Y mlx->rt->CAMERA_Y
#define RAY_POS_X mlx->rt->ray_pos_x
#define RAY_POS_Y mlx->rt->ray_pos_y
#define RAY_DIR_X mlx->rt->ray_dir_x
#define RAY_DIR_Y mlx->rt->ray_dir_y
#define MAP_X mlx->rt->map_x
#define MAP_Y mlx->rt->map_y
#define SIDE_DIST_X mlx->rt->side_dist_x
#define SIDE_DIST_Y mlx->rt->side_dist_y
#define DELTA_DIST_X mlx->rt->delta_dist_x
#define DELTA_DIST_Y mlx->rt->delta_dist_y
#define PERP_WALL_DIST mlx->rt->perpendicular_wall_distance
#define STEP_X mlx->rt->step_x
#define STEP_Y mlx->rt->step_y
#define HIT mlx->rt->hit
#define SIDE mlx->rt->side
#define LINE_HEIGHT mlx->rt->line_height
#define PARSER_X mlx->env->parser_x
#define PARSER_Y mlx->env->parser_y
#define DRAW_END mlx->rt->draw_end
#define DRAW_START mlx->rt->draw_start
#define WALL_COLOR mlx->rt->color
#define X1 mlx->algo->x1
#define Y1 mlx->algo->y1
#define X2 mlx->algo->x2
#define Y2 mlx->algo->y2
#define EY mlx->algo->ey
#define EX mlx->algo->ex
#define DX mlx->algo->dx
#define DY mlx->algo->dy
#define X_INCR mlx->algo->Xincr
#define Y_INCR mlx->algo->Yincr
#define RX mlx->algo->Rx
#define RY mlx->algo->Ry
#define MOVE_SPEED mlx->rt->move_speed
#define ROT_SPEED mlx->rt->rot_speed
#define FRAME mlx->rt->frame
#define OLD_DIR_X mlx->rt->old_dir_x
#define OLD_PLANE_X mlx->rt->old_plane_x

typedef struct			s_rosette {

	int		x1;
	int		x2;
	int		y1;
	int		y2;
	int		dx;
	int		dy;
	int		ex;
	int		ey;
	int		Xincr;
	int		Yincr;
	int		Rx;
	int		Ry;
	int		i;
	int		color;

}						t_rosette;

typedef struct			s_env
{
	int			x;
	int			y;
	int			parser_x;
	int			parser_y;
	int			mouse_x;
	int			mouse_y;
	int			color;
}						t_env;

typedef struct			s_image
{

	void		*image;
	char		*ptr;
	int			bpp;
	int			stride;
	int			endian;

}						t_image;

typedef struct			s_rt
{
	double		pos_x;
	double		pos_y;
	double		direction_x;
	double		direction_y;
	double		plane_x;
	double		plane_y;
	double		cur_frame;
	double		old_frame;
	double		frame;
	double		camera_x;
	double		camera_y;
	double		ray_pos_x;
	double		ray_pos_y;
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perpendicular_wall_distance;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			wall_color;
	double		move_speed;
	double		rot_speed;
	double		old_dir_x;
	double		old_plane_x;
}						t_rt;

typedef struct			s_mlx
{

	int			*mlx;
	int			*win;
	int			keycode;
	int			button;
	int			**grid;
	t_image		*image;
	t_env		*env;
	t_rt		*rt;
	t_rosette	*algo;

}						t_mlx;

t_mlx		*initialize(void);
t_mlx		*mlx_free(t_mlx *mlx);
void		*new_image(t_mlx *mlx);
void		*delete_image(t_mlx *mlx);
void		image_set_pixel(t_mlx *mlx);
void    	rt_init(t_mlx *mlx);
void		raytracing(t_mlx *mlx);
int			parsing(char *filename, t_mlx *mlx);
void		hooks(t_mlx *mlx);
int 		loop_hook(t_mlx *mlx);
int			mouse_hook(int button, int x, int y, t_mlx *mlx);
int			mouse_mov(int x, int y, t_mlx *mlx);
int			key_func(int keycode, t_mlx *mlx);
void		ft_line_tracer(t_mlx *mlx, int i);
void   		 redraw_raytracing(t_mlx *mlx);

#endif
