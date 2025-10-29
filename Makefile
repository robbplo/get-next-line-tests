CC = clang
CFLAGS = -g -I.. -fsanitize=address
LDFLAGS = -L..
OUT = test
LIBNEXTLINE = ..


test: test_1 test_42 test_10m

m_1:
	@$(CC) -D="BUFFER_SIZE 1" -g -fsanitize=address ../get_next_line.c ../get_next_line_utils.c -c
	@$(CC) $(CFLAGS) get_next_line.o get_next_line_utils.o ft_test.c $(LDFLAGS) -o $(OUT)

m_42:
	@$(CC) -D="BUFFER_SIZE 42" -g -fsanitize=address ../get_next_line.c ../get_next_line_utils.c -c
	@$(CC) $(CFLAGS) get_next_line.o get_next_line_utils.o ft_test.c $(LDFLAGS) -o $(OUT)

m_10m:
	@$(CC) -D="BUFFER_SIZE 10000000" -g -fsanitize=address ../get_next_line.c ../get_next_line_utils.c -c
	@$(CC) $(CFLAGS) get_next_line.o get_next_line_utils.o ft_test.c $(LDFLAGS) -o $(OUT)

b_42:
	@$(CC) -D="BUFFER_SIZE 42" -g -fsanitize=address ../get_next_line_bonus.c ../get_next_line_utils_bonus.c -c
	@$(CC) $(CFLAGS) get_next_line_bonus.o get_next_line_utils_bonus.o ft_test.c $(LDFLAGS) -o $(OUT)


test_1: m_1
	@echo "================================="
	@echo "= Testing BUFFER_SIZE 1         ="
	@echo "================================="
	@./$(OUT)
	@echo

test_42: m_42
	@echo "================================="
	@echo "= Testing BUFFER_SIZE 42        ="
	@echo "================================="
	@./$(OUT)
	@echo

test_10m: m_10m
	@echo "================================="
	@echo "= Testing BUFFER_SIZE 10000000  ="
	@echo "================================="
	@./$(OUT)
	@echo
