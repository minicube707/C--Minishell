
# =======================================
#            MAKEFILE PROJET
# =======================================

# =======================================
#                FLAGS
# =======================================
CC = cc -Wall -Wextra -Werror -MMD -MP


# =======================================
#              FILE
# =======================================
FILE_NAMES =	main \
				here_doc \
				manage_error \
				execution \
				execute_here_doc

# =======================================
#              VARIABLE
# =======================================		
SRC_PATH = src
OBJ_PATH = obj
HEA_PATH = include

SRC_FILES = $(FILE_NAMES:%=$(SRC_PATH)/%.c)
OBJ_FILES = $(FILE_NAMES:%=$(OBJ_PATH)/%.o)
DEP_FILES = $(OBJ_FILES:.o=.d)
HEA_FILES = $(HEA_PATH)/minishell.h

INCLUDE = -I $(HEA_PATH) -I libft/include -I gnl/include
ARCHIVE = -L libft -l ft -L gnl -l gnl -lreadline

NAME = minishell
NAME_FOLDER := $(shell basename $(CURDIR))

MAKEFLAGS += --no-print-directory


# =======================================
#            COLOR
# =======================================
RESET       = \033[0m
BOLD        = \033[1m
RED         = \033[31m
GREEN       = \033[32m
YELLOW      = \033[38;5;227m
BLUE        = \033[38;5;26m
MAGENTA    = \033[35m
CYAN        = \033[38;5;51m	


# =======================================
#              RULES
# =======================================
.PHONY: all clean fclean re

all : $(NAME)

$(OBJ_PATH) :
	@mkdir -p $(OBJ_PATH)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(HEA_FILES) | $(OBJ_PATH)
	@echo "$(BLUE)[Compilation]$(RESET) $<"
	@$(CC) $(INCLUDE) -O3 -c $< -o $@


$(NAME): intro $(OBJ_FILES)
	@$(MAKE) -s -C  libft 
	@$(MAKE) -s -C gnl
	@echo "\n$(YELLOW)$(NAME_FOLDER): [Linking]$(RESET): $(NAME)"
	@$(CC) $(OBJ_FILES)  $(ARCHIVE) -o $(NAME)
	@echo "\n"
	@echo "$(GREEN)======================$(RESET)"
	@echo "$(GREEN)===PROJET COMPILER====$(RESET)"
	@echo "$(GREEN)======================$(RESET)"


clean :
	@$(MAKE) -s -C libft clean
	@$(MAKE) -s -C gnl clean
	@echo "\n$(RED)$(NAME_FOLDER): 🧹 Suppression des fichiers objets...$(RESET)"
	@rm -f $(OBJ_FILES) $(DEP_FILES)
	@echo "$(GREEN)$(NAME_FOLDER): ✅ Fichiers supprimés.$(RESET)"

fclean : clean	
	@$(MAKE) -s -C libft fclean
	@$(MAKE) -s -C gnl fclean
	@echo "\n$(RED)$(NAME_FOLDER): 🧹 Suppression des archive...$(RESET)"
	@rm -f $(NAME)
	@echo "$(GREEN)$(NAME_FOLDER): ✅ Fichiers supprimés.$(RESET)"

re : fclean all

intro :
	@printf "\n$(MAGENTA)📦 Compilation de $(shell basename $(CURDIR))$(RESET)\n"

# Inclusion automatique des fichiers .d s’ils existent
-include $(DEP_FILES)
