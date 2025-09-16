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
FILE_NAMES = ft_atoi \
		ft_bzero \
		ft_calloc \
		ft_isalnum \
		ft_isalpha \
		ft_isascii \
		ft_isdigit \
		ft_isprint \
		ft_itoa \
		ft_memchr \
		ft_memcmp \
		ft_memcpy \
		ft_memmove \
		ft_memset \
		ft_putchar_fd \
		ft_putendl_fd \
		ft_putnbr_fd \
		ft_putstr_fd \
		ft_split \
		ft_strchr \
		ft_strdup \
		ft_striteri \
		ft_strjoin \
		ft_strlcat \
		ft_strlcpy \
		ft_strlen \
		ft_strmapi \
		ft_strncmp \
		ft_strnstr \
		ft_strrchr \
		ft_strtrim \
		ft_substr \
		ft_tolower \
		ft_toupper      


# =======================================
#              VARIABLE
# =======================================	
SRC_PATH = src
OBJ_PATH = obj
HEA_PATH = include

SRC_FILES = $(FILE_NAMES:%=$(SRC_PATH)/%.c)
OBJ_FILES = $(FILE_NAMES:%=$(OBJ_PATH)/%.o)
DEP_FILES = $(OBJ_FILES:.o=.d)
HEA_FILES = $(HEA_PATH)/libft.h

INCLUDE = -I $(HEA_PATH)

NAME = libft.a
NAME_FOLDER := $(shell basename $(CURDIR))

MAKEFLAGS += --no-print-directory

# =======================================
#            COULOUR
# =======================================
RESET       = \033[0m
BOLD        = \033[1m
RED         = \033[31m
GREEN       = \033[32m
YELLOW      = \033[38;5;227m
BLUE        = \033[38;5;26m
MANGENTA    = \033[35m
CYAN        = \033[38;5;51m


# =======================================
#              RULES
# =======================================
.PHONY: all clean fclean re

all : $(NAME)

$(OBJ_PATH) :
	mkdir -p $(OBJ_PATH)

$(OBJ_PATH)/%.o : $(SRC_PATH)/%.c $(HEA_FILES) | $(OBJ_PATH)
	@echo "$(BLUE)[Compilation]$(RESET) $<"
	@$(CC) $(INCLUDE) -c $< -o $@

$(NAME) : intro $(OBJ_FILES)
	@echo "$(CYAN)$(NAME_FOLDER): [ARCHIVAGE]$(RESET): $(NAME)"
	@ar rcs $(NAME) $(OBJ_FILES)

clean :
	@echo "\n$(RED)$(NAME_FOLDER): 🧹 Suppression des fichiers objets...$(RESET)"
	@rm -f $(OBJ_FILES) $(DEP_FILES)
	@echo "$(GREEN)$(NAME_FOLDER): ✅ Fichiers supprimés.$(RESET)"

fclean : clean
	@echo "\n$(RED)$(NAME_FOLDER): 🧹 Suppression de l'archive...$(RESET)"
	@rm -f $(NAME)
	@echo "$(GREEN)$(NAME_FOLDER): ✅ Archive supprimée.$(RESET)"


re : fclean all

intro :
	@printf "\n$(MANGENTA)📦 Compilation de $(shell basename $(CURDIR))$(RESET)\n"

# Inclusion automatique des fichiers .d s’ils existent
-include $(DEP_FILES)
