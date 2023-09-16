FOGGY_TREE_FILES = input_to_foggy_tree

FOGGY_TREE_SRCS_DIR = foggy_tree

FOGGY_TREE_SRCS = $(addprefix $(SRCS_DIR)/$(FOGGY_TREE_SRCS_DIR)/, $(addsuffix .c, $(FOGGY_TREE_FILES)))

FOGGY_TREE_OBJS = $(addprefix  $(OBJS_DIR)/$(FOGGY_TREE_SRCS_DIR)-, $(addsuffix .o, $(FOGGY_TREE_FILES)))

$(OBJS_DIR)/$(FOGGY_TREE_SRCS_DIR)-%.o: $(SRCS_DIR)/$(FOGGY_TREE_SRCS_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDES_DIR)