EXPANDS_FILES = expand

EXPANDS_SRCS_DIR = expands

EXPANDS_SRCS = $(addprefix $(SRCS_DIR)/$(EXPANDS_SRCS_DIR)/, $(addsuffix .c, $(EXPANDS_FILES)))

EXPANDS_OBJS = $(addprefix  $(OBJS_DIR)/$(EXPANDS_SRCS_DIR)-, $(addsuffix .o, $(EXPANDS_FILES)))

$(OBJS_DIR)/$(EXPANDS_SRCS_DIR)-%.o: $(SRCS_DIR)/$(EXPANDS_SRCS_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDES_DIR)