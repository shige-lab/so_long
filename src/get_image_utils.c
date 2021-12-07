/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_image_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshigena <tshigena@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 17:08:41 by tshigena          #+#    #+#             */
/*   Updated: 2021/12/07 17:41:11 by tshigena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

const char	*g_assets_path[5] = {
	"assets/wall/wallA.xpm",
	"assets/floor/floorB.xpm",
	"assets/player/playerA/front/front1.xpm",
	"assets/exit/exitB2.xpm",
	"assets/sprite/spriteB/spriteB2.xpm",
};

void	ft_put_image_to_window(t_game *game, size_t x, size_t y)
{
	x *= IMAGE_SIZE;
	y *= IMAGE_SIZE;
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img.img, x, y);
}

void	select_image(t_game *game, char c)
{
	char	*path;

	if (c == '1')
		path = (char *)g_assets_path[WALL];
	else if (c == '0')
		path = (char *)g_assets_path[FLOOR];
	else if (c == 'C')
		path = (char *)g_assets_path[COLLECTIBLE];
	else if (c == 'P')
		path = (char *)g_assets_path[PLAYER];
	else if (c == 'E')
		path = (char *)g_assets_path[EXIT];
	game->img.img = mlx_xpm_file_to_image(game->mlx, path, \
		&game->img.img_height, &game->img.img_width);
	if (game->img.img == NULL)
		error_exit("Malloc failed.");
}

void	get_image(t_game *game)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			select_image(game, game->map.map[y][x]);
			ft_put_image_to_window(game, x, y);
			free(game->img.img);
			if (game->map.map[y][x] == 'P')
			{
				game->player.x = x;
				game->player.y = y;
			}
			x++;
		}
		y++;
	}
}

t_bool	can_move(t_game *game, char next_position)
{
	if (next_position == 'E')
	{
		if (game->map.num_collectible == 0)
			exit (0);
		return (FALSE);
	}
	if (next_position != '1')
	{
		game->move_count += 1;
		printf("move count-> %zu\n", game->move_count);
		return (TRUE);
	}
	return (FALSE);
}
