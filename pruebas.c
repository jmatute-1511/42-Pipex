/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pruebas.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 17:54:53 by jmatute-          #+#    #+#             */
/*   Updated: 2021/10/03 14:56:35 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
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

int	count_location(char **envp)
{
	char	*aux;
	int		i;

	i = 0;
	aux = find_path(envp);
	while (*aux != '\0')
	{
		if (*aux == ':')
			i++;
		aux++;
	}
	return (i);
}
void	superfree(char **matriz)
{
	int i;

	i = 0;
	while (matriz[i])
	{
		free(matriz[i]);
		i++;
	}
}

char	*location_commands(char **argv, char **envp, t_pipex *pipex)
{
	char	*command;
	char	*aux;
	char	**first;
	int		i;

	pipex->path = find_path(envp);
	pipex->m_route = ft_split(&pipex->path[5], ':');
	first = ft_split(argv[1], ' ');
	while (pipex->m_route[i])
	{
		aux = ft_strjoin(pipex->m_route[i],"/");
		command = ft_strjoin(aux, first[0]);
		if (access(command, X_OK) == 0)
			break ;
		free(command);
		i++;
	}
	superfree(pipex->m_route);
	return (command);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex pipex;

	printf("%s", location_commands(argv,envp,&pipex));
}