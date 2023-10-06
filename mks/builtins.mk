BUILTINS_FILES = env cd exit export unset pwd echo cd_utils export_utils1 export_utils2
BUILTINS_SRCS_DIR = builtins

BUILTINS_SRCS = $(addprefix $(SRCS_DIR)/$(BUILTINS_SRCS_DIR)/, $(addsuffix .c, $(BUILTINS_FILES)))

BUILTINS_OBJS = $(addprefix  $(OBJS_DIR)/$(BUILTINS_SRCS_DIR)-, $(addsuffix .o, $(BUILTINS_FILES)))

$(OBJS_DIR)/$(BUILTINS_SRCS_DIR)-%.o: $(SRCS_DIR)/$(BUILTINS_SRCS_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDES_DIR)
