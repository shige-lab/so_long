/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshigena <tshigena@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 17:01:47 by tshigena          #+#    #+#             */
/*   Updated: 2022/01/06 17:17:50 by tshigena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

static int	ft_update(void *game_, size_t x, size_t y)
{
	t_game	*game;

	game = (t_game *)game_;
	if (x != game->player.x || y != game->player.y)
		select_image(game, 'P');
	else
		return (0);
	ft_put_image_to_window(game, game->player.x, game->player.y);
	mlx_destroy_image(game->mlx, game->img.img);
	select_image(game, '0');
	ft_put_image_to_window(game, x, y);
	mlx_destroy_image(game->mlx, game->img.img);
	game->map.map[y][x] = '0';
	x = game->player.x;
	y = game->player.y;
	if (game->map.map[y][x] == 'C')
	{
		game->map.num_collectible -= 1;
	}
	game->map.map[y][x] = 'P';
	return (0);
}

static void	set_player_position(t_game *game, size_t x, size_t y)
{
	game->player.x = x;
	game->player.y = y;
}

int	ft_input(int key, void *game_)
{
	size_t	x;
	size_t	y;
	t_game	*game;

	game = (t_game *)game_;
	x = game->player.x;
	y = game->player.y;
	if (key == ESC)
		mlx_loop_end(game->mlx);
	else if (key == W)
		game->player.y -= 1;
	else if (key == S)
		game->player.y += 1;
	else if (key == A)
		game->player.x -= 1;
	else if (key == D)
		game->player.x += 1;
	else
		return (0);
	if (can_move(game, game->map.map[game->player.y][game->player.x]))
		ft_update(game, x, y);
	else
		set_player_position(game, x, y);
	return (0);
}

int	close_window(t_game *game)
{
	mlx_loop_end(game->mlx);
}

int	minimize_window(t_game *game)
{
	get_image(game);
}
