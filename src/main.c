/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshigena <tshigena@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:16:16 by tshigena          #+#    #+#             */
/*   Updated: 2021/12/07 16:56:58 by tshigena         ###   ########.fr       */
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

void	free_all(char **map, size_t i)
{
	while (i > 0 )
		free(map[--i]);
	free(map);
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

int	ft_update(void *game_, size_t x, size_t y)
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

t_bool	can_move(t_game *game, char next_position)
{
	if (next_position == 'E')
	{
		if (game->map.num_collectible == 0)
			exit (1);
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

int	main(int argc, char **argv)
{
	t_game	game;
	int		fd;

	if (argc != 2)
		error_exit("invalid argument");
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		error_exit("File open failed.");
	game = (t_game){0};
	get_map_data(fd, &game);
	game.mlx = mlx_init();
	game.mlx_win = mlx_new_window(game.mlx, game.map.width * IMAGE_SIZE, \
		game.map.height * IMAGE_SIZE, argv[0]);
	get_image(&game);
	mlx_hook(game.mlx_win, E_KEY_PRESS, M_KEY_PRESS, &ft_input, &game);
	mlx_hook(game.mlx_win, E_WIN_CLOSE, M_WIN_RESIZE, &close_window, &game);
	mlx_hook(game.mlx_win, E_WIN_RESIZE, M_WIN_CLOSE, &minimize_window, &game);
	mlx_loop(game.mlx);
	free_all(game.map.map, game.map.height);
	return (0);
}

void	error_exit(char *message)
{
	printf("Error\n");
	printf("%s\n", message);
	system("leaks so_long");
	exit (1);
}
