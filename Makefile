include mks/common_vars.mk
include mks/builtins.mk
include mks/tokenify.mk
include mks/expands.mk
include mks/utils.mk
include mks/foggy_tree.mk

NAME = minishell

FILES = main start

SRCS = $(addprefix $(SRCS_DIR)/, $(addsuffix .c, $(FILES)))

OBJS = $(addprefix $(OBJS_DIR)/, $(addsuffix .o, $(FILES))) \
	$(BUILTINS_OBJS) $(TOKENIFY_OBJS) $(EXPANDS_OBJS) $(UTILS_OBJS) $(FOGGY_TREE_OBJS)

LIBS_DIR = libs

LIBLP_DIR = $(LIBS_DIR)/liblp_c

LIBLP = $(LIBLP_DIR)/liblp_c.a

$(NAME): $(LIBLP) $(OBJS_DIR) $(OBJS)
	$(CC) $(OBJS) $(LIBLP) -o $(NAME) -lreadline

$(LIBLP):
	make -C ${LIBLP_DIR}

$(OBJS_DIR):
	mkdir -p $(OBJS_DIR)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(INCLUDES)
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDES_DIR)

all: $(NAME)

clean: cleanlibs
	rm -rf $(OBJS_DIR)

cleanlibs:
	make fclean -C ${LIBLP_DIR}

fclean: clean
	rm -f $(NAME)

re: clean all

bonus: all

.PHONY: all clean fclean re cleanlibs