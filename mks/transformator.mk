TRANSFORMATOR_FILES = expand_parameters expand_split_push replace_var transformators expand_tilde

TRANSFORMATOR_SRCS_DIR = transformator

TRANSFORMATOR_SRCS = $(addprefix $(SRCS_DIR)/$(TRANSFORMATOR_SRCS_DIR)/, $(addsuffix .c, $(TRANSFORMATOR_FILES)))

TRANSFORMATOR_OBJS = $(addprefix  $(OBJS_DIR)/$(TRANSFORMATOR_SRCS_DIR)-, $(addsuffix .o, $(TRANSFORMATOR_FILES)))

$(OBJS_DIR)/$(TRANSFORMATOR_SRCS_DIR)-%.o: $(SRCS_DIR)/$(TRANSFORMATOR_SRCS_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDES_DIR)