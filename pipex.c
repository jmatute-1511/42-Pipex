/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 16:26:17 by jmatute-          #+#    #+#             */
/*   Updated: 2021/10/03 19:50:49 by jmatute-         ###   ########.fr       */
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

void	superfree(char **matriz)
{
	int i;

	i = 0;
	while (matriz[i])
	{
		free(matriz[i]);
		matriz[i] = NULL;
		i++;
	}
	matriz = NULL;
}

char	*location_commands(char *argv, char **envp, t_pipex *pipex)
{
	char	*command;
	char	*aux;
	char	**first;
	int		i;

	i = 0;
	pipex->path = find_path(envp);
	pipex->m_route = ft_split(&pipex->path[5], ':');
	first = ft_split(argv, ' ');
	while (pipex->m_route[i])
	{
		aux = ft_strjoin(pipex->m_route[i],"/");
		command = ft_strjoin(aux, first[0]);
		if (access(command, X_OK) == 0)
			break ;
		free(command);
		command = NULL;
		free(aux);
		aux = NULL;
		i++;
	}
	free(aux);
	aux = NULL;
	superfree(pipex->m_route);
	superfree(first);
	first =NULL;
	pipex->m_route =NULL;
	return (command);
}
void saltamontes1(char *path,char **argv, char **envp, int *fd)
{
	int fd_read;
	char **commands;

	fd_read = open(argv[1], O_RDONLY);
	close(fd[READ_END]);
	dup2(fd_read, STDIN_FILENO);
	close(fd_read);
	dup2(fd[WRITE_END],STDOUT_FILENO);
	close(fd[WRITE_END]);
	commands = ft_split(argv[2], ' ');
	execve(path,commands,envp);
	superfree(commands);
}
void saltamontes2(char *path,char **argv, char **envp, int *fd)
{
	int fd_read;
	char **commands;

	fd_read = open(argv[4], O_WRONLY | O_CREAT);
	dup2(fd[READ_END], STDIN_FILENO);
	close(fd[READ_END]);
	dup2(fd[WRITE_END],STDOUT_FILENO);
	close(fd_read);
	commands = ft_split(argv[3], ' ');
	execve(path,commands,envp);
	superfree(commands);
}
int	main(int argc, char **argv, char **envp)
{
	int	fd[2];
	int	pid;
	int status;
	t_pipex pipex;

	pipe(fd);
	pipex.secure_path = location_commands(argv[2],envp,&pipex);
	pid = fork();
	if (pid == 0)
		saltamontes1(pipex.secure_wsl+path, argv, envp, fd);
	else
		{
			close(fd[WRITE_END]);
			pid =fork();
			free(pipex.secure_path);
			pipex.secure_path= location_commands(argv[3],envp,&pipex);
			if (pid == 0)
			saltamontes2(pipex.secure_path, argv, envp, fd);
			wait(&status);
		}
	return(0);
}
