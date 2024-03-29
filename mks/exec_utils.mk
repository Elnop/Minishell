EXEC_UTILS_FILES = get_cmd_path wait_pids dup_fds pipe_cmds open_redirs pipe_heredoc_and_cmd

EXEC_UTILS_SRCS_DIR = exec
EXEC_UTILS_SRCS_SUB_DIR = utils

EXEC_UTILS_SRCS = $(addprefix $(SRCS_DIR)/$(EXEC_UTILS_SRCS_DIR)/$(EXEC_UTILS_SRCS_SUB_DIR)/, $(addsuffix .c, $(EXEC_UTILS_FILES)))

EXEC_UTILS_OBJS = $(addprefix  $(OBJS_DIR)/$(EXEC_UTILS_SRCS_DIR)-$(EXEC_UTILS_SRCS_SUB_DIR)-, $(addsuffix .o, $(EXEC_UTILS_FILES)))

$(OBJS_DIR)/$(EXEC_UTILS_SRCS_DIR)-$(EXEC_UTILS_SRCS_SUB_DIR)-%.o: $(SRCS_DIR)/$(EXEC_UTILS_SRCS_DIR)/$(EXEC_UTILS_SRCS_SUB_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDES_DIR)