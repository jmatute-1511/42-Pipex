/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/02 16:26:17 by jmatute-          #+#    #+#             */
/*   Updated: 2021/10/17 17:02:01 by jmatute-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*location_commands(char *argv, char **envp, t_pipex *pipex)
{
	char	*command;
	char	**first;
	int		i;

	i = 0;
	if (argv[0] == '.' || access(argv, X_OK) == 0)
	{
		command = check_path(argv);
		return (command);
	}
	pipex->path = find_path(envp);
	pipex->m_route = ft_split(&pipex->path[5], ':');
	first = ft_split(argv, ' ');
	while (pipex->m_route[i])
	{
		command = ft_strnjoin(3, pipex->m_route[i], "/", first[0]);
		if (access(command, X_OK) == 0)
			break ;
		free(command);
		i++;
	}
	free_matrix(pipex->m_route);
	free_matrix(first);
	return (command);
}

void	saltamontes1(char *path, char **argv, char **envp, int *fd)
{
	int		fd_read;
	int		a;

	a = 0;
	close(fd[READ_END]);
	fd_read = open(argv[1], O_RDONLY);
	dup2(fd_read, STDIN_FILENO);
	close(fd_read);
	dup2(fd[WRITE_END], STDOUT_FILENO);
	close(fd[WRITE_END]);
	a = execve(path, ft_split(argv[2], ' '), envp);
	if (a < 0)
		write(2, "First command not found\n", 25);
}

void	saltamontes2(char *path, char **argv, char **envp, int *fd)
{
	int		fd_read;
	int		a;

	a = 0;
	close(fd[WRITE_END]);
	fd_read = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	dup2(fd[READ_END], STDIN_FILENO);
	close(fd[READ_END]);
	dup2(fd_read, STDOUT_FILENO);
	close(fd_read);
	a = execve(path, ft_split(argv[3], ' '), envp);
	if (a < 0)
		write(2, "Second command not found", 24);
}

void	second_proces(char **argv, char **envp, int *fd, t_pipex *pipex)
{
	int	pid;

	close(fd[WRITE_END]);
	pid = fork();
	if (pid < 0)
		exit (0);
	if (pipex->secure_path != NULL)
		free(pipex->secure_path);
	pipex->secure_path = location_commands(argv[3], envp, pipex);
	if (pid == 0)
		saltamontes2(pipex->secure_path, argv, envp, fd);
	if (pipex->secure_path != NULL)
		free(pipex->secure_path);
}

int	main(int argc, char **argv, char **envp)
{
	int		fd[2];
	int		pid;
	int		status;
	t_pipex	pipex;

	if (return_error(argc, argv) < 0)
		exit (0);
	pipe(fd);
	pipex.secure_path = location_commands(argv[2], envp, &pipex);
	pid = fork();
	if (pid < 0)
		exit (0);
	if (pid == 0)
		saltamontes1(pipex.secure_path, argv, envp, fd);
	else
	{
		second_proces(argv, envp, fd, &pipex);
		wait(&status);
	}
	return (0);
}
