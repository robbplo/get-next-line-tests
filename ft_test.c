/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rploeger <rploeger.student@codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 19:38:30 by rploeger          #+#    #+#             */
/*   Updated: 2025/10/22 12:41:20 by rploeger         ###   ########.fr       */
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

	printf("\nTest pyramid of 9s\n");
	fd = open("./files/pyramid", O_RDONLY);
	for (int i = 0; i < 10; i++) {
		str = get_next_line(fd);
		printf("%s", str);
		assert(strlen(str) == i + 2);
		free(str);
	}
	assert(get_next_line(fd) == NULL);
}

void	test2()
{
	char *str;
	int fd;

	printf("\nTest with one line followed by two empty lines\n");
	fd = open("./files/one-line-two-empty", O_RDONLY);
	str = get_next_line(fd);
	printf("%s", str);
	assert(!strcmp("123456789\n", str));
	free(str);
	str = get_next_line(fd);
	printf("%s", str);
	assert(!strcmp("\n", str));
	free(str);
	str = get_next_line(fd);
	printf("%s", str);
	assert(!strcmp("\n", str));
	free(str);
	assert(get_next_line(fd) == NULL);
}

void	test3()
{
	char *str;
	int fd;

	printf("\nTest one line with two thousand characters\n");
	fd = open("./files/two-thousand", O_RDONLY);
	str = get_next_line(fd);
	printf("%s", str);
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

	printf("\nTest one line with a million characters\n");
	fd = open("./files/million", O_RDONLY);
	str = get_next_line(fd);
	printf("one million test\n");
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
	printf("\nTest with invalid file descriptors\n");
	assert(get_next_line(-1) == NULL);
	assert(get_next_line(INT32_MAX) == NULL);
	assert(get_next_line(INT32_MIN) == NULL);
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
