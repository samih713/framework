# Neural Network Library Makefile
# =================================

# Colors for output
RED := \033[0;31m
GREEN := \033[0;32m
YELLOW := \033[0;33m
BLUE := \033[0;34m
PURPLE := \033[0;35m
CYAN := \033[0;36m
WHITE := \033[0;37m
BOLD := \033[1m
RESET := \033[0m

NAME := libnn.a
MAIN_EXEC := neural_net

CC := gcc
CFLAGS := -Wall -Wextra -Werror -ggdb3 -fsanitize=address

LIBS :=
INC :=

SRCS := activation.c add.c cost.c gradient.c init_meta.c init_network.c matrix.c matrix_utils.c multiply.c network.c network_utils.c set_data.c test_network.c
OBJS := $(SRCS:.c=.o)

# Progress tracking
TOTAL_SRCS := $(words $(SRCS))
CURRENT := 0

# Default target
.DEFAULT_GOAL := help

# Help target
help:
	@echo "$(BOLD)$(BLUE)Neural Network Library Build System$(RESET)"
	@echo "$(CYAN)=====================================$(RESET)"
	@echo ""
	@echo "$(BOLD)Available targets:$(RESET)"
	@echo "  $(GREEN)all$(RESET)       - Build the neural network library"
	@echo "  $(GREEN)main$(RESET)      - Build the main executable"
	@echo "  $(GREEN)run$(RESET)       - Build and run the neural network"
	@echo "  $(GREEN)test$(RESET)      - Run quick test (5 iterations)"
	@echo "  $(GREEN)train$(RESET)     - Run full training (1000 iterations)"
	@echo "  $(GREEN)clean$(RESET)     - Remove object files"
	@echo "  $(GREEN)fclean$(RESET)    - Remove all generated files"
	@echo "  $(GREEN)re$(RESET)        - Clean and rebuild everything"
	@echo "  $(GREEN)help$(RESET)      - Show this help message"
	@echo ""

all: $(NAME)
	@echo "$(BOLD)$(GREEN)✓ Neural network library ready!$(RESET)"

$(NAME): $(OBJS)
	@echo "$(BOLD)$(YELLOW)📦 Creating library $(NAME)...$(RESET)"
	@ar -rcs $@ $^
	@echo "$(BOLD)$(GREEN)✓ Library $(NAME) created successfully!$(RESET)"

# Compilation with progress indicator
%.o: %.c
	$(eval CURRENT := $(shell echo $$(($(CURRENT) + 1))))
	@echo "$(BOLD)$(CYAN)[$(CURRENT)/$(TOTAL_SRCS)]$(RESET) $(PURPLE)🔨 Compiling$(RESET) $<"
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

main: main.c $(NAME) 
	@echo "$(BOLD)$(YELLOW)🔧 Building main executable...$(RESET)"
	@$(CC) $(CFLAGS) $^ -lm -o $(MAIN_EXEC)
	@echo "$(BOLD)$(GREEN)✓ Executable $(MAIN_EXEC) ready!$(RESET)"

run: main
	@echo "$(BOLD)$(BLUE)🚀 Running neural network...$(RESET)"
	@echo "$(CYAN)================================$(RESET)"
	@./$(MAIN_EXEC)
	@echo "$(CYAN)================================$(RESET)"
	@echo "$(BOLD)$(GREEN)✓ Execution completed!$(RESET)"

test: main
	@echo "$(BOLD)$(BLUE)🧪 Running quick test (5 iterations)...$(RESET)"
	@echo "$(CYAN)========================================$(RESET)"
	@sed 's/train_count, [0-9]*/train_count, 5/' main.c > main_test.c && \
	$(CC) $(CFLAGS) main_test.c $(NAME) -lm -o test_exec && \
	./test_exec && \
	rm -f main_test.c test_exec
	@echo "$(CYAN)========================================$(RESET)"
	@echo "$(BOLD)$(GREEN)✓ Quick test completed!$(RESET)"

train: main
	@echo "$(BOLD)$(BLUE)🎯 Running full training (1000 iterations)...$(RESET)"
	@echo "$(CYAN)===============================================$(RESET)"
	@sed 's/train_count, [0-9]*/train_count, 1000/' main.c > main_train.c && \
	$(CC) $(CFLAGS) main_train.c $(NAME) -lm -o train_exec && \
	./train_exec && \
	rm -f main_train.c train_exec
	@echo "$(CYAN)===============================================$(RESET)"
	@echo "$(BOLD)$(GREEN)✓ Training completed!$(RESET)"

clean:
	@echo "$(BOLD)$(YELLOW)🧹 Cleaning object files...$(RESET)"
	@rm -rf $(OBJS)
	@echo "$(BOLD)$(GREEN)✓ Object files cleaned!$(RESET)"

fclean: clean
	@echo "$(BOLD)$(YELLOW)🗑️  Removing all generated files...$(RESET)"
	@rm -rf $(NAME)
	@rm -rf $(MAIN_EXEC)
	@rm -rf main
	@echo "$(BOLD)$(GREEN)✓ All generated files removed!$(RESET)"

re: fclean all
	@echo "$(BOLD)$(GREEN)✓ Complete rebuild finished!$(RESET)"

# Mark targets as phony
.PHONY: all main run test train clean fclean re help

# Silent mode - suppress command echoing
.SILENT: help