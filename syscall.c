#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 256
#define FIFO_NAME "my_fifo"

int main() {
    int choice;
    char buffer[BUFFER_SIZE];

    while (1) {
        printf("\n1. Open a file\n2. Create a file\n3. Read a file\n4. Write into file\n5. Traverse a file\n6. Fork demonstration\n7. Pipe demonstration\n8. FIFO demonstration\n9. Exit\nEnter Your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int fd;
                fd = open("sample.txt", O_RDONLY); //open system call returns fd, we opened file with read only mode
                if (fd > 0) {			   //fd is positive if file opened successfully
                    printf("Opened successfully, fd is %d\n", fd);
                } else {
                    printf("Error\n");
                }
                break;
            }

            case 2: {
                int fd;
                fd = creat("sample1.txt", O_CREAT|O_RDWR); // Creating a file with read/write permissions
                if (fd > 0) {
                    printf("Created successfully, fd is %d\n", fd);
                } else {
                    printf("Error\n");
                }
                break;
            }

            case 3: {
                int fd,number;
                fd = open("sample.txt", O_RDONLY);   //To read a file it must be opened first
                number = read(fd, buffer, 5);    //read returns no of bytes read 
                printf("%d bytes read: %s\n", number, buffer);
                break;
            }

            case 4: {
                int fd;
                fd = open("sample.txt", O_WRONLY | O_APPEND); //Append mode is  to append to existing file without erasing all contents
                char buff[] = "Hi";
                int number;
                number = write(fd, buff, strlen(buff)); // Writing "Hi" to the file
                printf("%d bytes written\n", number);
                break;
            }

            case 5: {
                ssize_t pos;
                int fd;
                fd = open("sample.txt", O_RDWR);
                pos = lseek(fd, 20, SEEK_END); // Moving the file pointer to 20 bytes before the end
                printf("Traversed to position %ld\n", pos);
                break;
            }

            case 6: {
                pid_t pid;
                printf("Hello\n");
                pid = fork();
                if (pid == 0) {
                    printf("Child process ID is %d\n", pid);
                } else if (pid > 0) {
                    printf("Parent process ID is %d\n", getppid());
                } else {
                    perror("fork");
                }
                break;
            }

            case 7: {
                int pipefd[2];
                pid_t pid;

                if (pipe(pipefd) == -1) {
                    perror("pipe");
                    exit(EXIT_FAILURE);
                }

                pid = fork();

                if (pid == -1) {
                    perror("fork");
                    exit(EXIT_FAILURE);
                }

                if (pid > 0) { // Parent process
                    close(pipefd[0]); // Close the read end of the pipe in the parent process
                    const char *parent_message = "Hello from parent!";
                    printf("Parent process sending message: %s\n", parent_message);
                    write(pipefd[1], parent_message, strlen(parent_message) + 1);
                    close(pipefd[1]); // Close the write end of the pipe in the parent process
                } else { // Child process
                    close(pipefd[1]); // Close the write end of the pipe in the child process
                    read(pipefd[0], buffer, BUFFER_SIZE);
                    printf("Child process received message: %s\n", buffer);
                    close(pipefd[0]); // Close the read end of the pipe in the child process
                }
                break;
            }

            case 8: {
                pid_t pid;
                pid = fork();

                if (pid == -1) {
                    perror("fork");
                    exit(EXIT_FAILURE);
                }

                if (pid > 0) { // Parent process writes to the FIFO
                    int fd;
                    const char *message = "Hello, FIFO!";
                    mkfifo(FIFO_NAME, 0666);  //0666 is equivalent to O_RDWR it gives read and writing perminssion
                    fd = open(FIFO_NAME, O_WRONLY);
                    write(fd, message, strlen(message) + 1);
                    close(fd);
                    unlink(FIFO_NAME); // Remove the FIFO from the filesystem
                } else { // Child process reads from the FIFO
                    int fd;
                    fd = open(FIFO_NAME, O_RDONLY);
                    read(fd, buffer, BUFFER_SIZE);
                    printf("Received message from FIFO: %s\n", buffer);
                    close(fd);
                    exit(EXIT_SUCCESS);
                }
                break;
            }

            case 9:
                printf("\nExiting...\n");
                exit(0);
                break;

            default:
                printf("Wrong choice\n");
                break;
        }
    }

    return 0;
}
