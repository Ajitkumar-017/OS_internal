#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>

int main()
{
 int choice;
 while(1)
 {
  printf("\n1.Open a file\n2.Create a file\n3.Read a file\n4.Write into file\n5.Traverse a file\n6.fork demonstration\n7.pipe demonstration\n8.fifo demonstration\n9.Exit");
  printf("Enter Your choice: ");
  scanf("%d",&choice);
  switch(choice)
  {
   case 1:
   //open system call
   int fd;
   fd=open("sample.txt",O_RDONLY);
   if(fd>0){
   printf("fd is %d",fd);//Open function returns a fd if successfull
   else
   printf("Error");
   }
 
 
   case 2:
   //creat system call
    int fd;
    fd=creat("sample.txt",O_WRONLY);
    if(fd>0){
    printf("fd is %d",fd);//Open function returns a fd if successfull

  case 3:
    int fd;
    fd=open("sample.txt",O_RDONLY);
    char buff[5];
    int number;
    number=read(fd,buff,5);  //Read returns no of bytes read
    printf("%d bytes read",number);
 
  case 4:
    int fd;
    fd=open("sample.txt",O_RDONLY);
    char buff[5]="Hi";
    int number;
    number=write(fd,buff,5);  //write returns no of bytes read
    printf("%d bytes written",number);
 

  case 5:
    ssize_t pos;
    int fd;
    fd=open("sample.txt",O_WRDONLY);
    pos=lseek(fd,20,SEEK_END) //SEEK_END add file offset + no of bytes traversed
    printf("traversed %ld ",pos);


  case 6:
    pid_t pid;
    printf("Hello")
    pid=fork();
    if(pid>0)
    printf("parent process id is %d",pid);
 
   case 7:
    int status;
    status=pipe(filedes[2])
    if(staus==0)
    printf("pipe created successfully");
    else
    printf("Error creating pipe");


   case 8
    int status;
    status=mkfifo("fifo-file")
    if(staus==0)
    printf("fifo created successfully");
    else
    printf("Error creating pipe");

  case 9:
    printf("\n exiting ..");
    break;
    
  default:
    printf("wrong choice");
}
}
