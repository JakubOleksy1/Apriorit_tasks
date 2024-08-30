// Unix & Windows version
#include <stdio.h>
#include "file_copy.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source> <destination>\n", argv[0]);
        return 1;
    }

    if (copy_file(argv[1], argv[2]) == 0) {
        printf("File copied successfully.\n");
    } else {
        printf("File copy failed.\n");
    }

    return 0;
}