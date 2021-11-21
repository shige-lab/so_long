/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshigena <tshigena@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:16:16 by tshigena          #+#    #+#             */
/*   Updated: 2021/11/21 10:14:10 by tshigena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	free_all(char **map, size_t i)
{
	while (i > 0 )
		free(map[--i]);
	free(map);
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
	size_t i = 0;
	while (game.map.map[i] != NULL)
	{
		ft_printf("%s", (char *)game.map.map[i]);
		i++;
	}
	free_all(game.map.map, game.map.number_of_rows);
	system("leaks so_long"); 
	return (0);
}

void	error_exit(char *message)
{
	ft_printf("Error\n");
	ft_printf("%s\n", message);
	system("leaks so_long"); 
	exit (1);
}
