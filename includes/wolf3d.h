# ifndef WOLF3D_H
# define WOLF3D_H

#include "./../libft/includes/libft.h"
#include "./../minilibx_macos/mlx.h"
#include <stdio.h>
#include <math.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

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

typedef struct			s_mlx {

	int			*mlx;
	int			*win;
	int			keycode;
	int			button;
	int			**grid;
	t_image		*image;
	t_env		*env;

}						t_mlx;

t_mlx		*initialize(void);
t_mlx		*mlx_free(t_mlx *mlx);
void		*new_image(t_mlx *mlx);
void		*delete_image(t_mlx *mlx);
int			parsing(char *filename, t_mlx *mlx);
void		hooks(t_mlx *mlx);
int 		loop_hook(t_mlx *mlx);
int			mouse_hook(int button, int x, int y, t_mlx *mlx);
int			mouse_mov(int x, int y, t_mlx *mlx);
int			key_func(int keycode, t_mlx *mlx);

#endif
