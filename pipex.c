/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 16:26:17 by jmatute-          #+#    #+#             */
/*   Updated: 2021/10/02 19:50:20 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i] != '\0')
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	return (envp[i]);
}

char	*location_comands(char **argv, char **envp, t_pipex *pipex)
{
	int		i;
	char	*aux;

	i = 0;
	pipex->path = find_path(envp);
	pipex->m_route = ft_split(pipex->path, ':');
	while (argv[2][i] != '\0')
	{
		if (argv[2][i] == ' ')
			break ;
		*aux == argv[2][i++];
		aux++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	int	fd[2];
	int	pid;

	pipe (fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[1]);
		dup2(fd[1], 1);
		close(fd[1]);
	}
}
