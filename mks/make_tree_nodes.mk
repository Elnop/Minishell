MAKE_TREE_NODES_FILES = make_and_node \
						make_or_node \
						make_cmd_node \
						make_pipeline_node \
						make_redir_node

MAKE_TREE_NODES_SRCS_DIR = make_tree
MAKE_TREE_NODES_SRCS_SUB_DIR = make_nodes

MAKE_TREE_NODES_SRCS = $(addprefix $(SRCS_DIR)/$(MAKE_TREE_NODES_SRCS_DIR)/$(MAKE_TREE_NODES_SRCS_SUB_DIR)/, $(addsuffix .c, $(MAKE_TREE_NODES_FILES)))

MAKE_TREE_NODES_OBJS = $(addprefix  $(OBJS_DIR)/$(MAKE_TREE_NODES_SRCS_DIR)-$(MAKE_TREE_NODES_SRCS_SUB_DIR)-, $(addsuffix .o, $(MAKE_TREE_NODES_FILES)))

$(OBJS_DIR)/$(MAKE_TREE_NODES_SRCS_DIR)-$(MAKE_TREE_NODES_SRCS_SUB_DIR)-%.o: $(SRCS_DIR)/$(MAKE_TREE_NODES_SRCS_DIR)/$(MAKE_TREE_NODES_SRCS_SUB_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDES_DIR)