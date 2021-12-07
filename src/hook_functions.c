/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshigena <tshigena@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 17:01:47 by tshigena          #+#    #+#             */
/*   Updated: 2021/12/07 17:04:13 by tshigena         ###   ########.fr       */
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
	select_image(game, '0');
	ft_put_image_to_window(game, x, y);
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

int	ft_input(int key, void *game_)
{
	size_t	x;
	size_t	y;
	t_game	*game;

	game = (t_game *)game_;
	x = game->player.x;
	y = game->player.y;
	if (key == ESC)
		exit(1);
	if (key == W)
		game->player.y -= 1;
	if (key == S)
		game->player.y += 1;
	if (key == A)
		game->player.x -= 1;
	if (key == D)
		game->player.x += 1;
	if (can_move(game, game->map.map[game->player.y][game->player.x]))
		ft_update(game, x, y);
	else
	{
		game->player.x = x;
		game->player.y = y;
	}
	return (0);
}

int	close_window(void)
{
	exit(1);
}

int	minimize_window(t_game *game)
{
	get_image(game);
}
