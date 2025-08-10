set -xe

CFLAGS='-Wall -Wextra -Werror'
# CFLAGS='-Wall -Wextra -Werror -fsanitize=address'
SRCS='transpose.c matrix.c matrix_utils.c'

gcc $CFLAGS $SRCS -o test