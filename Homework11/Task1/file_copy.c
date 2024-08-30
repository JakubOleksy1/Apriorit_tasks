/* UNIX version
#include "file_copy.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/sendfile.h>
#include <sys/stat.h>
#include <stdio.h>

int copy_file(const char *src, const char *dest) {
    int source = open(src, O_RDONLY);
    if (source < 0) {
        perror("open source");
        return -1;
    }

    int destination = open(dest, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (destination < 0) {
        perror("open destination");
        close(source);
        return -1;
    }

    struct stat stat_buf;
    fstat(source, &stat_buf);

    off_t offset = 0;
    if (sendfile(destination, source, &offset, stat_buf.st_size) == -1) {
        perror("sendfile");
        close(source);
        close(destination);
        return -1;
    }

    close(source);
    close(destination);
    return 0;
}*/

// Windows version
#include "file_copy.h"
#include <windows.h>
#include <stdio.h>

int copy_file(const char *src, const char *dest) {
    BOOL success = CopyFile(src, dest, FALSE);
    if (!success) {
        DWORD error = GetLastError();
        fprintf(stderr, "CopyFile failed with error code %lu\n", error);
        return -1;
    }
    return 0;
}