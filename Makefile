CC = cc
CFLAGS = -g -I$(LIBNEXTLINE)
LDFLAGS = -L$(LIBNEXTLINE) -lnextline
SRCS = 
OUT = test
LIBNEXTLINE = ..

main: libnextline
	$(CC) $(CFLAGS) $(SRCS) ft_test.c $(LDFLAGS) -o $(OUT)

libnextline:
	make -C $(LIBNEXTLINE)

fclean:
	rm -f $(OUT)

test: main
	./$(OUT)
