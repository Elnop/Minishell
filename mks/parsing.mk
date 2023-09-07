PARSING_FILES = line_to_array array_handlers get_next_word

PARSING_SRCS_DIR = parsing

PARSING_SRCS = $(addprefix $(SRCS_DIR)/$(PARSING_SRCS_DIR)/, $(addsuffix .c, $(PARSING_FILES)))

PARSING_OBJS = $(addprefix  $(OBJS_DIR)/$(PARSING_SRCS_DIR)-, $(addsuffix .o, $(PARSING_FILES)))

$(OBJS_DIR)/$(PARSING_SRCS_DIR)-%.o: $(SRCS_DIR)/$(PARSING_SRCS_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDES_DIR)
