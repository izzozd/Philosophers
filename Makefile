GREEN = \033[0;32m
RED = \033[0;31m
YELLOW = \033[0;33m
NC = \033[0m

all: philos

philos:
	@echo "$(YELLOW)Building mandatory part...$(NC)"
	@make -C philos/
	@echo "$(GREEN)✓ philos built successfully$(NC)"

clean:
	@make -C philos/ clean
	@echo "$(GREEN)✓ Object files cleaned$(NC)"

fclean:
	@make -C philos/ fclean
	@echo "$(GREEN)✓ All files cleaned$(NC)"

re: fclean all

.PHONY: all philos clean fclean re 