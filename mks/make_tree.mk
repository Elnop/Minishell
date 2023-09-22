MAKE_TREE_FILES = line_to_words \
				make_tree \
				words_to_tree \

MAKE_TREE_SRCS_DIR = make_tree

MAKE_TREE_SRCS = $(addprefix $(SRCS_DIR)/$(MAKE_TREE_SRCS_DIR)/, $(addsuffix .c, $(MAKE_TREE_FILES)))

MAKE_TREE_OBJS = $(addprefix  $(OBJS_DIR)/$(MAKE_TREE_SRCS_DIR)-, $(addsuffix .o, $(MAKE_TREE_FILES)))

$(OBJS_DIR)/$(MAKE_TREE_SRCS_DIR)-%.o: $(SRCS_DIR)/$(MAKE_TREE_SRCS_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDES_DIR)
