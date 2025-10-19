/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_test.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rploeger <rploeger.student@codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 19:38:30 by rploeger          #+#    #+#             */
/*   Updated: 2025/10/19 20:19:08 by rploeger         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
	char *str;
	int fd;

	if (argc == 1) {
		fd = open("./testfile", O_RDONLY);
	} else if (argc == 2) {
		if (!strcmp("-", argv[1])) {
			fd = 0;
		} else {
			fd = open(argv[1], O_RDONLY);
		}
	}
	for (int i = 0; i < 10; i++) {
		str = get_next_line(fd);
		if (!str)
		{
			printf("String was null\n");
			exit(1);
		}
		printf("%s", str);
		assert(strlen(str) == i + 2);
		free(str);
	}
}
