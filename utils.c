/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 15:02:58 by jmatute-          #+#    #+#             */
/*   Updated: 2021/10/17 17:00:10 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != 0)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	return (envp[i]);
}

int	return_error(int argc, char **argv)
{
	int		a;
	int		fd_read;

	a = 0;
	if (argc != 5)
	{
		write(1, "[file1 command1 command2 file2]", 32);
		a = -1;
	}
	else if (open(argv[1], O_WRONLY) < 0)
	{
		write (1, "no access to file 1", 20);
		fd_read = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
		a = -1;
	}
	else if (open(argv[4], O_WRONLY) < 0)
	{
		write (1, "no access to file 2", 20);
		a = -1;
	}
	return (a);
}

char	*check_path(char *argv)
{
	char	**matrix;
	char	*path;

	if (access(argv, X_OK) == 0)
		path = ft_strdup(argv);
	else
	{
		matrix = ft_split(argv, ' ');
		path = ft_strdup(matrix[0]);
		free_matrix(matrix);
	}
	return (path);
}
