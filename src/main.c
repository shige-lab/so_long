/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshigena <tshigena@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:16:16 by tshigena          #+#    #+#             */
/*   Updated: 2021/12/05 15:16:08 by tshigena         ###   ########.fr       */
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

void	free_all(char **map, size_t i)
{
	while (i > 0 )
		free(map[--i]);
	free(map);
}

void	select_image(t_game *game, char c)
{
	if (c == '1')
		game->img.img = mlx_xpm_file_to_image(game->mlx, (char *)g_assets_path[WALL], &game->img.img_height, &game->img.img_width);
	else if (c == '0' || c == 'P')
		game->img.img = mlx_xpm_file_to_image(game->mlx, (char *)g_assets_path[FLOOR], &game->img.img_height, &game->img.img_width);
	else if (c == 'C')
		game->img.img = mlx_xpm_file_to_image(game->mlx, (char *)g_assets_path[COLLECTIBLE], &game->img.img_height, &game->img.img_width);
	else if (c == 'E')
		game->img.img = mlx_xpm_file_to_image(game->mlx, (char *)g_assets_path[EXIT], &game->img.img_height, &game->img.img_width);
}

void	get_p_positon(t_game *game, int x, int y)
{
	game->img.img = mlx_xpm_file_to_image(game->mlx, (char *)g_assets_path[PLAYER], &game->img.img_height, &game->img.img_width); 
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img.img, x * IMAGE_SIZE, y * IMAGE_SIZE);
	game->player.x = x;
	game->player.y = y;
}

void	get_image(t_game *game)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (y < game->map.length)
	{
		x = 0;
		while (x < game->map.width)
		{
			select_image(game, game->map.map[y][x]);
			mlx_put_image_to_window(game->mlx, game->mlx_win, game->img.img, x * IMAGE_SIZE, y * IMAGE_SIZE);
			if (game->map.map[y][x] == 'P')
			{
				get_p_positon(game, x, y);
			}
			x++;
		}
		y++;
	}
}

int	ft_update (void *game_, int x, int y)
{
	t_game *game;

	game = (t_game *)game_;
	if (x != game->player.x || y != game->player.y)
	{
		game->img.img = mlx_xpm_file_to_image(game->mlx, (char *)g_assets_path[PLAYER], &game->img.img_height, &game->img.img_width); 
	}
	else
		return (0);

	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img.img, game->player.x * IMAGE_SIZE, game->player.y * IMAGE_SIZE);
	game->img.img = mlx_xpm_file_to_image(game->mlx, (char *)g_assets_path[FLOOR], &game->img.img_height, &game->img.img_width);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img.img, x * IMAGE_SIZE, y * IMAGE_SIZE);
	game->map.map[y][x] = '0';
	x = game->player.x;
	y = game->player.y;
	if (game->map.map[y][x] == 'C')
	{
		game->map.num_collectible -= 1;
	}
	game->map.map[y][x] = 'P';
	printf(" c = %ld\n", game->map.num_collectible);
	return (0);
}

t_bool	is_available_to_move(t_game *game, char next_position)
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
		printf("count-> %d\n", game->move_count);
		return (TRUE);
	}
	return (FALSE);
}

int	ft_input(int key, void *game_)
{
	int			x;
	int			y;
	t_game *game;

	game = (t_game *)game_;
	x = game->player.x;
	y = game->player.y;
	if (key == W)
	{
		if (is_available_to_move(game, game->map.map[y - 1][x]))
			game->player.y -= 1;
	}
	if (key == S)
	{
		if (is_available_to_move(game, game->map.map[y + 1][x]))
			game->player.y += 1;
	}
	if (key == A)
	{
		if (is_available_to_move(game, game->map.map[y][x - 1]))
			game->player.x -= 1;
	}
	if (key == D)
	{
		if (is_available_to_move(game, game->map.map[y][x + 1]))
			game->player.x += 1;
	}
	if (key == ESC)
		exit(1);
	ft_update(game, x, y);
	return (0);
}

int	close_window(void)
{
	printf("close\n");
	exit(1);
}

int	minimize_window(t_game *game)
{
	get_image(game);
	printf("minimize\n");
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
		game.map.length * IMAGE_SIZE, "so_long");
	get_image(&game);
	mlx_hook(game.mlx_win, E_KEY_PRESS, M_KEY_PRESS, &ft_input, &game);
	mlx_hook(game.mlx_win, E_WIN_CLOSE, M_WIN_RESIZE, &close_window, &game);
	mlx_hook(game.mlx_win, E_WIN_RESIZE, M_WIN_CLOSE, &minimize_window, &game);
	printf("main y-> %d\n", game.player.y);
	mlx_loop(game.mlx);
	free_all(game.map.map, game.map.length);
	return (0);
}

void	error_exit(char *message)
{
	ft_printf("Error\n");
	ft_printf("%s\n", message);
	system("leaks so_long");
	exit (1);
}
