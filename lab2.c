#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>



int main(int argc, char **argv){
int pid; /*process ID*/

switch(pid = fork()){
case 0: /* a fork returns 0 to the child*/
printf("I am the child process:pid=%d\n", getpid());
break;

default: /*a fork returns a pid to the parent*/
printf("I am the parent process:pid=%d, child pid=%d\n", getpid(),pid);
break;

case -1:/*something went wronf*/
perror("fork");
exit(1);
}
exit(0);
}
