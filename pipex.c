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
	while (envp[i] != '\0')
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	return (envp[i]);
}

char	*location_commands(char *argv, char **envp, t_pipex *pipex)
{
	char	*command;
	char	*aux;
	char	**first;
	int		i;

	if (access(argv, X_OK) == 0)
		return (argv);
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
	if (access(command, X_OK) != 0)
		command = NULL;
	superfree(pipex->m_route);
	superfree(first);
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
	commands = ft_split(argv[2], ' ');
	execve(path,commands,envp);
	superfree(commands);
}
int	main(int argc, char **argv, char **envp)
{
	int	fd[2];
	int	pid;
	t_pipex pipex;

	pipe(fd);
	pid = fork();
	pipex.path = location_commands(argv,envp,&pipex);

	if (pid == 0)
		saltamontes1(pipex.path, argv, envp, fd);
	else


}
