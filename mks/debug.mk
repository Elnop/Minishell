DEBUG_FILES = print_str_array print_tree

DEBUG_SRCS_DIR = debug

DEBUG_SRCS = $(addprefix $(SRCS_DIR)/$(DEBUG_SRCS_DIR)/, $(addsuffix .c, $(DEBUG_FILES)))

DEBUG_OBJS = $(addprefix  $(OBJS_DIR)/$(DEBUG_SRCS_DIR)-, $(addsuffix .o, $(DEBUG_FILES)))

$(OBJS_DIR)/$(DEBUG_SRCS_DIR)-%.o: $(SRCS_DIR)/$(DEBUG_SRCS_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDES_DIR)