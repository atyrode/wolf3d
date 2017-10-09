
#include "./../includes/wolf3d.h"

void			case1rosette(t_mlx *mlx)
{
	int			i;

	i = 0;
	while (i < RX)
	{
		image_set_pixel(mlx);
		i++;
		X1 += X_INCR;
		EX -= DY;
		if (EX < 0)
		{
			Y1 += Y_INCR;
			EX += DX;
		}
	}
	return ;
}

void			case2rosette(t_mlx *mlx)
{
	int			i;

	i = 0;
	while (i < RY)
	{
		image_set_pixel(mlx);
		i++;
		Y1 += Y_INCR;
		EY -= DX;
		if (EY < 0)
		{
			X1 += X_INCR;
			EY += DY;
		}
	}
	return ;
}

void			ft_line_tracer(t_mlx *mlx, int i)
{
	X1 = i;
	X2 = i;
	Y1 = DRAW_START;
	Y2 = DRAW_END;
	EY = abs(Y2 - Y1);
	EX = abs(X2 - X1);
	DX = 2 * EX;
	DY = 2 * EY;
	X_INCR = 1;
	Y_INCR = 1;
	RX = EX;
	RY = EY;
	if (X1 > X2)
		X_INCR = -1;
	if (Y1 > Y2)
		Y_INCR = -1;
	if (RX > RY)
		case1rosette(mlx);
	else if (RX < RY)
		case2rosette(mlx);
	return ;
}
