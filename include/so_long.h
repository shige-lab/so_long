/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tshigena <tshigena@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 14:02:41 by tshigena          #+#    #+#             */
/*   Updated: 2021/11/16 17:27:09 by tshigena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include "../ft_printf/ft_printf.h"
# include "../minilibx-linux/mlx.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

typedef struct s_map
{
	char	**map;
	size_t	row_lens;
	size_t	number_of_rows;
	size_t	num_collectible;
	size_t	num_exit;
	size_t	num_s_position;
}	t_map;

typedef struct s_game
{
	t_map	map;
	t_list	*map_tmp;
}	t_game;

char	*get_next_line(int fd);
t_game	get_map_data(int fd, t_game *game);
void	error_exit(char *message);

#endif