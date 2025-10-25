/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rploeger <rploeger.student@codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 19:38:30 by rploeger          #+#    #+#             */
/*   Updated: 2025/10/25 09:05:35 by rploeger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdint.h>
#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	test1()
{
	char *str;
	int fd;

	printf("Test pyramid of 9s\n");
	fd = open("./files/pyramid", O_RDONLY);
	for (int i = 0; i < 10; i++) {
		str = get_next_line(fd);
		assert(strlen(str) == i + 2);
		free(str);
	}
	str = get_next_line(fd);
	assert(str == NULL);
}

void	test2()
{
	char *str;
	int fd;

	printf("Test with one line followed by two empty lines\n");
	fd = open("./files/one-line-two-empty", O_RDONLY);
	str = get_next_line(fd);
	assert(!strcmp("123456789\n", str));
	free(str);
	str = get_next_line(fd);
	assert(!strcmp("\n", str));
	free(str);
	str = get_next_line(fd);
	assert(!strcmp("\n", str));
	free(str);
	assert(get_next_line(fd) == NULL);
}

void	test3()
{
	char *str;
	int fd;

	printf("Test one line with two thousand characters\n");
	fd = open("./files/two-thousand", O_RDONLY);
	str = get_next_line(fd);
	assert(str[0] == '1');
	assert(str[1000] == '1');
	assert(str[1999] == '1');
	assert(str[2000] == '\n');
	assert(get_next_line(fd) == NULL);
	free(str);
}

void	test4()
{
	char *str;
	int fd;

	printf("Test one line with a million characters\n");
	fd = open("./files/million", O_RDONLY);
	str = get_next_line(fd);
	assert(str[0] == '1');
	assert(str[1000] == '1');
	assert(str[10000] == '1');
	assert(str[100000] == '1');
	assert(str[1000000] == '\n');
	assert(get_next_line(fd) == NULL);
	free(str);
}

void	test5()
{
	printf("Test with invalid file descriptors\n");
	assert(get_next_line(-1) == NULL);
	assert(get_next_line(INT32_MAX) == NULL);
	assert(get_next_line(INT32_MIN) == NULL);
}

void test6()
{
	char *str;
	int fd;

	printf("Test one char\n");
	fd = open("./files/1char", O_RDONLY);
	str = get_next_line(fd);
	assert(str[0] == '1');
	assert(get_next_line(fd) == NULL);
	free(str);

	printf("Test one char without newline\n");
	fd = open("./files/1char-no-nl", O_RDONLY);
	str = get_next_line(fd);
	assert(str[0] == '1');
	assert(get_next_line(fd) == NULL);
	free(str);
}

void test7()
{
	char *str;
	int fd;

	printf("Test alternating line with newline\n");
	fd = open("./files/alternate_lines", O_RDONLY);
	str = get_next_line(fd);
	assert(!strcmp(str, "98765432109876543210987654321098765432109\n"));
	free(str);
	str = get_next_line(fd);
	assert(!strcmp(str, "\n"));
	free(str);
	str = get_next_line(fd);
	assert(!strcmp(str, "012345678901234567890123456789012345678901\n"));
	free(str);
	str = get_next_line(fd);
	assert(!strcmp(str, "\n"));
	free(str);
	str = get_next_line(fd);
	assert(!strcmp(str, "9876543210987654321098765432109876543210987\n"));
	free(str);
	str = get_next_line(fd);
	assert(!strcmp(str, "\n"));
	free(str);
	str = get_next_line(fd);
	assert(!strcmp(str, "012345678901234567890123456789012345678901\n"));
	free(str);
	str = get_next_line(fd);
	assert(!strcmp(str, "\n"));
	free(str);
	str = get_next_line(fd);
	assert(!strcmp(str, "98765432109876543210987654321098765432109"));
	free(str);
	str = get_next_line(fd);
	assert(str == NULL);
}

int main(int argc, char **argv)
{
	char *str;
	int fd;

	if (argc == 1) {
		test1();
		test2();
		test3();
		test4();
		test5();
		test6();
		test7();
	} 
	if (argc == 2) {
		if (!strcmp("-", argv[1]))
			fd = 0;
		else 
			fd = open(argv[1], O_RDONLY);
		while ((str = get_next_line(fd)))
			printf("line: %s", str);
	}
}
