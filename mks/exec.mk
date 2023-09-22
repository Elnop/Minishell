EXEC_FILES = exec

EXEC_SRCS_DIR = exec

EXEC_SRCS = $(addprefix $(SRCS_DIR)/$(EXEC_SRCS_DIR)/, $(addsuffix .c, $(EXEC_FILES)))

EXEC_OBJS = $(addprefix  $(OBJS_DIR)/$(EXEC_SRCS_DIR)-, $(addsuffix .o, $(EXEC_FILES)))

$(OBJS_DIR)/$(EXEC_SRCS_DIR)-%.o: $(SRCS_DIR)/$(EXEC_SRCS_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDES_DIR)