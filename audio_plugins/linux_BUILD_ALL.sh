find -type f \( -name 'makefile' -o -name 'makefile' -o -name 'Makefile' \) \
-exec bash -c 'cd "$(dirname "{}")" && make CONFIG=Release' \;
