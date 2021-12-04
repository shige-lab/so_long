/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshigena <tshigena@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:16:16 by tshigena          #+#    #+#             */
/*   Updated: 2021/12/04 17:46:16 by tshigena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	free_all(char **map, size_t i)
{
	while (i > 0 )
		free(map[--i]);
	free(map);
}

void	select_image(t_game *game, char c)
{
	if (c == '1')
		game->img.img = mlx_xpm_file_to_image(game->mlx, "assets/wall/wallA.xpm", &game->img.img_height, &game->img.img_width);
	else if (c == '0' || c == 'P')
		game->img.img = mlx_xpm_file_to_image(game->mlx, "assets/floor/floorB.xpm", &game->img.img_height, &game->img.img_width);
	else if (c == 'C')
		game->img.img = mlx_xpm_file_to_image(game->mlx, "assets/sprite/spriteB/spriteB2.xpm", &game->img.img_height, &game->img.img_width);
	else if (c == 'E')
		game->img.img = mlx_xpm_file_to_image(game->mlx, "assets/exit/exitB2.xpm", &game->img.img_height, &game->img.img_width);
}

void	get_p_positon(t_game *game, int x, int y)
{
	game->img.img = mlx_xpm_file_to_image(game->mlx, "assets/player/playerA/front/front1.xpm", &game->img.img_height, &game->img.img_width); 
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img.img, x * 32, y * 32);
	game->player.x_position = x;
	game->player.y_position = y;
	game->map.p_x_position = x;
	game->map.p_y_position = y;
}

void	get_image(t_game *game)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (y < game->map.number_of_rows)
	{
		x = 0;
		while (x < game->map.row_lens)
		{
			select_image(game, game->map.map[y][x]);
			mlx_put_image_to_window(game->mlx, game->mlx_win, game->img.img, x * 32, y * 32);
			if (game->map.map[y][x] == 'P')
			{
				get_p_positon(game, x, y);
			}
			x++;
		}
		y++;
	}
}

int	ft_update (void *game_)
{
	static int	x = 0;
	static int	y = 0;
	t_game *game;

	game = (t_game *)game_;
	if (x == 0 || y == 0)
	{
		x = game->map.p_x_position;
		y = game->map.p_y_position;
	}
	if (x != game->player.x_position || y != game->player.y_position)
	{
		game->img.img = mlx_xpm_file_to_image(game->mlx, "assets/player/playerA/front/front1.xpm", &game->img.img_height, &game->img.img_width); 
	}
	else
		return (0);

	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img.img, game->player.x_position * 32, game->player.y_position * 32);
	game->img.img = mlx_xpm_file_to_image(game->mlx, "assets/floor/floorB.xpm", &game->img.img_height, &game->img.img_width);
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img.img, x * 32, y * 32);
	x = game->player.x_position;
	y = game->player.y_position;
	if (game->map.map[y][x] == 'C')
	{
		game->map.map[y][x] = '0';
		game->map.num_collectible -= 1;
	}
	printf(" c = %ld\n", game->map.num_collectible);
	return (0);
}

t_bool	is_avalable_to_move(t_game *game, char next_position)
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
	x = game->player.x_position;
	y = game->player.y_position;
	if (key == W)
	{
		if (is_avalable_to_move(game, game->map.map[y - 1][x]))
			game->player.y_position -= 1;
	}
	if (key == S)
	{
		if (is_avalable_to_move(game, game->map.map[y + 1][x]))
			game->player.y_position += 1;
	}
	if (key == A)
	{
		if (is_avalable_to_move(game, game->map.map[y][x - 1]))
			game->player.x_position -= 1;
	}
	if (key == D)
	{
		if (is_avalable_to_move(game, game->map.map[y][x + 1]))
			game->player.x_position += 1;
	}
	if (key == ESC || key == 432986416)
		exit(1);
	ft_update(game);
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
		error_exit("invalid map");
	game = (t_game){0}; 
	get_map_data(fd, &game);
	game.mlx = mlx_init();
	game.mlx_win = mlx_new_window(game.mlx, game.map.row_lens * 32, game.map.number_of_rows * 32, "so_long");
	get_image(&game);
	// mlx_key_hook(game.mlx_win, *ft_input, &game);
	mlx_hook(game.mlx_win, 2, 1, &ft_input, &game);
	mlx_hook(game.mlx_win, 17, 131072, &close_window, &game);
	mlx_hook(game.mlx_win, 9, 2097152, &minimize_window, &game);
	printf("main y-> %d\n", game.player.y_position);
	mlx_loop(game.mlx);
	free_all(game.map.map, game.map.number_of_rows);
	// system("leaks so_long");
	return (0);
}

void	error_exit(char *message)
{
	ft_printf("Error\n");
	ft_printf("%s\n", message);
	system("leaks so_long");
	exit (1);
}
