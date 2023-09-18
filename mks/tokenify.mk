TOKENIFY_FILES = line_to_words line_to_tokens words_to_tokens

TOKENIFY_SRCS_DIR = tokenify

TOKENIFY_SRCS = $(addprefix $(SRCS_DIR)/$(TOKENIFY_SRCS_DIR)/, $(addsuffix .c, $(TOKENIFY_FILES)))

TOKENIFY_OBJS = $(addprefix  $(OBJS_DIR)/$(TOKENIFY_SRCS_DIR)-, $(addsuffix .o, $(TOKENIFY_FILES)))

$(OBJS_DIR)/$(TOKENIFY_SRCS_DIR)-%.o: $(SRCS_DIR)/$(TOKENIFY_SRCS_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDES_DIR)
