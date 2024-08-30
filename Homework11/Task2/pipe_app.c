//UNIX version
/*
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MESSAGE "Hi, I'm your child!"
#define APPEND_MESSAGE " Hi!"

int main() {
    int pipefd[2];
    pid_t pid;
    char buffer[256];

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        close(pipefd[0]); 
        write(pipefd[1], MESSAGE, strlen(MESSAGE));
        close(pipefd[1]); 
        exit(EXIT_SUCCESS);
    } else { 
        close(pipefd[1]); 
        wait(NULL); 
        read(pipefd[0], buffer, sizeof(buffer));
        close(pipefd[0]); 

        strcat(buffer, APPEND_MESSAGE);

        int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd < 0) {
            perror("open");
            exit(EXIT_FAILURE);
        }

        write(fd, buffer, strlen(buffer));
        close(fd);
    }

    return 0;
}*/

//Windows version
#include <windows.h>
#include <stdio.h>
#include <string.h>

#define MESSAGE "Hi, I'm your child!"
#define APPEND_MESSAGE " Hi!"

int main() {
    HANDLE hRead, hWrite;
    SECURITY_ATTRIBUTES sa = { sizeof(SECURITY_ATTRIBUTES), NULL, TRUE };
    if (!CreatePipe(&hRead, &hWrite, &sa, 0)) {
        fprintf(stderr, "CreatePipe failed\n");
        return 1;
    }

    PROCESS_INFORMATION pi;
    STARTUPINFO si;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    si.hStdOutput = hWrite;
    si.dwFlags |= STARTF_USESTDHANDLES;

    char cmd[] = "child_process.exe";
    if (!CreateProcess(NULL, cmd, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi)) {
        DWORD error = GetLastError();
        fprintf(stderr, "CreateProcess failed with error code %lu\n", error);
        return 1;
    }

    CloseHandle(hWrite);

    char buffer[256];
    DWORD bytesRead;
    if (!ReadFile(hRead, buffer, sizeof(buffer) - 1, &bytesRead, NULL)) {
        fprintf(stderr, "ReadFile failed\n");
        return 1;
    }
    buffer[bytesRead] = '\0';
    CloseHandle(hRead);

    strcat(buffer, APPEND_MESSAGE);

    FILE *file = fopen("output.txt", "w");
    if (!file) {
        perror("fopen");
        return 1;
    }
    fprintf(file, "%s", buffer);
    fclose(file);

    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;
}