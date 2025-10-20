/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rploeger <rploeger.student@codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 19:38:30 by rploeger          #+#    #+#             */
/*   Updated: 2025/10/20 17:54:25 by rploeger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// todo: multiple consecutive newlines print remaining data in buffer

void	test1()
{
	char *str;
	int fd;

	printf("\nTest 1\n");
	fd = open("./files/test1", O_RDONLY);
	for (int i = 0; i < 11; i++) {
		str = get_next_line(fd);
		printf("%s", str);
		if (str)
			assert(strlen(str) == i + 2);
		free(str);
	}
}

void	test2()
{
	char *str;
	int fd;

	printf("\nTest 2\n");
	fd = open("./files/test2", O_RDONLY);
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
	str = get_next_line(fd);
	printf("%s", str);
	assert(str == NULL);
}

void	test3()
{
	char *str;
	int fd;

	printf("\nTest 3\n");
	fd = open("./files/two-thousand", O_RDONLY);
	str = get_next_line(fd);
	printf("%s", str);
	assert(str[0] == '1');
	assert(str[1000] == '1');
	assert(str[1999] == '1');
	assert(str[2000] == '\n');
	free(str);
}

void	test4()
{
	char *str;
	int fd;

	printf("\nTest 4\n");
	fd = open("./files/million", O_RDONLY);
	str = get_next_line(fd);
	printf("one million test\n");
	assert(str[0] == '1');
	assert(str[1000] == '1');
	assert(str[10000] == '1');
	assert(str[100000] == '1');
	assert(str[1000000] == '\n');
	free(str);
}

int main(int argc, char **argv)
{
	char *str;
	int fd;

	if (argc == 1) {
		// test1();
		// test2();
		// test3();
		test4();
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
