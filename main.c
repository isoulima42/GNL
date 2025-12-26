/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isoulima <soulimani.ilir@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/25 00:00:00 by isoulima          #+#    #+#             */
/*   Updated: 2025/12/25 15:33:41 by isoulima         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <string.h>

void	print_test_header(const char *test_name)
{
	printf("\n=================================\n");
	printf("TEST: %s\n", test_name);
	printf("=================================\n");
}

void	test_basic_file(void)
{
	int		fd;
	char	*line;
	int		line_count;

	print_test_header("Test basique - Lecture fichier");
	fd = open("file.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("❌ Erreur: Impossible d'ouvrir file.txt\n");
		return ;
	}
	line_count = 1;
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("Ligne %d: %s", line_count, line);
		if (strchr(line, '\n') == NULL)
			printf(" (pas de \\n)");
		printf("\n");
		free(line);
		line_count++;
	}
	printf("Total lignes lues: %d\n", line_count - 1);
	close(fd);
}

void	test_multiple_reads(void)
{
	int		fd;
	char	*line;

	print_test_header("Test lectures multiples");
	fd = open("file.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("❌ Erreur: Impossible d'ouvrir file.txt\n");
		return ;
	}
	printf("Lecture des 3 premières lignes uniquement:\n");
	line = get_next_line(fd);
	if (line)
	{
		printf("1: %s", line);
		free(line);
	}
	line = get_next_line(fd);
	if (line)
	{
		printf("2: %s", line);
		free(line);
	}
	line = get_next_line(fd);
	if (line)
	{
		printf("3: %s", line);
		free(line);
	}
	close(fd);
}

void	test_invalid_fd(void)
{
	char	*line;

	print_test_header("Test FD invalide");
	line = get_next_line(-1);
	if (line == NULL)
		printf("✅ FD -1: Retourne NULL (correct)\n");
	else
	{
		printf("❌ FD -1: Devrait retourner NULL\n");
		free(line);
	}

	line = get_next_line(1000);
	if (line == NULL)
		printf("✅ FD 1000: Retourne NULL (correct)\n");
	else
	{
		printf("❌ FD 1000: Devrait retourner NULL\n");
		free(line);
	}
}

void	test_empty_file(void)
{
	int		fd;
	char	*line;

	print_test_header("Test fichier vide");
	fd = open("empty.txt", O_CREAT | O_RDONLY, 0644);
	if (fd == -1)
	{
		printf("❌ Erreur: Impossible de créer empty.txt\n");
		return ;
	}
	line = get_next_line(fd);
	if (line == NULL)
		printf("✅ Fichier vide: Retourne NULL (correct)\n");
	else
	{
		printf("❌ Fichier vide: Devrait retourner NULL\n");
		free(line);
	}
	close(fd);
}

void	test_multiple_fds(void)
{
	int		fd1;
	int		fd2;
	char	*line1;
	char	*line2;

	print_test_header("Test FDs multiples (alternance)");
	fd1 = open("file.txt", O_RDONLY);
	fd2 = open("file.txt", O_RDONLY);
	if (fd1 == -1 || fd2 == -1)
	{
		printf("❌ Erreur: Impossible d'ouvrir les fichiers\n");
		return ;
	}
	printf("Lecture alternée entre FD1 et FD2:\n");
	line1 = get_next_line(fd1);
	if (line1)
	{
		printf("FD1: %s", line1);
		free(line1);
	}
	line2 = get_next_line(fd2);
	if (line2)
	{
		printf("FD2: %s", line2);
		free(line2);
	}
	line1 = get_next_line(fd1);
	if (line1)
	{
		printf("FD1: %s", line1);
		free(line1);
	}
	line2 = get_next_line(fd2);
	if (line2)
	{
		printf("FD2: %s", line2);
		free(line2);
	}
	close(fd1);
	close(fd2);
}

void	test_stdin(void)
{
	char	*line;

	print_test_header("Test STDIN (entrez du texte, CTRL+D pour terminer)");
	printf("Tapez une ligne: ");
	line = get_next_line(0);
	if (line)
	{
		printf("Vous avez tapé: %s", line);
		free(line);
	}
	else
		printf("EOF ou erreur\n");
}

int	main(int argc, char **argv)
{
	printf("\n╔════════════════════════════════════╗\n");
	printf("║  GET_NEXT_LINE - Tests Complets   ║\n");
	printf("║      Style Évaluation 42           ║\n");
	printf("╚════════════════════════════════════╝\n");
	printf("\nBUFFER_SIZE = %d\n", BUFFER_SIZE);

	if (argc > 1)
	{
		// Mode test spécifique
		if (strcmp(argv[1], "stdin") == 0)
		{
			test_stdin();
			return (0);
		}
	}

	// Tests automatiques
	test_basic_file();
	test_multiple_reads();
	test_invalid_fd();
	test_empty_file();
	test_multiple_fds();

	printf("\n╔════════════════════════════════════╗\n");
	printf("║        Tests terminés !            ║\n");
	printf("╚════════════════════════════════════╝\n\n");

	printf("💡 Pour tester STDIN: ./get_next_line stdin\n");
	printf("💡 Pour tester avec valgrind: valgrind --leak-check=full ./get_next_line\n");
	printf("💡 Pour changer BUFFER_SIZE: make re BUFFER_SIZE=1\n\n");

	return (0);
}
