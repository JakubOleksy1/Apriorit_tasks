//Don't need that file in UNIX version
#include <windows.h>
#include <stdio.h>

#define MESSAGE "Hi, I'm your child!"

int main() {
    DWORD bytesWritten;
    WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), MESSAGE, strlen(MESSAGE), &bytesWritten, NULL);
    return 0;
}