CC = cc

CFLAGS = -Wall -Wextra -Werror -g3

SRCS_DIR = srcs

OBJS_DIR = .build

INCLUDES_DIR = includes

INCLUDES_FILES = minishell

INCLUDES = $(addprefix $(INCLUDES_DIR)/, $(addsuffix .h, $(INCLUDES_FILES)))