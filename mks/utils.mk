UTILS_FILES = ft_strcmp array_handlers is_operator get_left_length get_app_data add_grb has_quote signal

UTILS_SRCS_DIR = utils

UTILS_SRCS = $(addprefix $(SRCS_DIR)/$(UTILS_SRCS_DIR)/, $(addsuffix .c, $(UTILS_FILES)))

UTILS_OBJS = $(addprefix  $(OBJS_DIR)/$(UTILS_SRCS_DIR)-, $(addsuffix .o, $(UTILS_FILES)))

$(OBJS_DIR)/$(UTILS_SRCS_DIR)-%.o: $(SRCS_DIR)/$(UTILS_SRCS_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDES_DIR)
