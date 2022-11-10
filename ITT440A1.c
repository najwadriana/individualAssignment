#include <stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<errno.h>
#include<signal.h>


#define QTY_LENGTH 4
#define QTY_WAIT_INTERVAL 2

void getQTY(char qty[QTY_LENGTH + 1]){
srand(getpid() + getppid());

qty[0] = 49 + rand() % 7;

for(int i = 1; i < QTY_LENGTH; i++){
qty[i] = 48 + rand() % 7;
}

qty[QTY_LENGTH] = '\0';
}

void sigint_handler(int sig);
int main()
{
signal(SIGINT, sigint_handler);

while(1) {
int pipefds[2];
char qty[QTY_LENGTH + 1];
char buffer[QTY_LENGTH + 1];
char string[40];
char s[40];

pipe(pipefds);
pid_t pid = fork();

if(signal(SIGINT, sigint_handler) == SIG_ERR){
perror("signal");
exit(1);
}

if(pid == 0){
getQTY(qty);
close(pipefds[0]);
write(pipefds[1], qty, QTY_LENGTH + 1);


printf("Please enter your name:\n");
fgets(string, 40, stdin);
printf("Welcome %s", string);
printf("Generating Quantity in parent and sending to child...\n");

sleep(QTY_WAIT_INTERVAL);

exit(EXIT_SUCCESS);
}

if(pid > 0){
wait(NULL);

close(pipefds[1]);
read(pipefds[0], buffer, QTY_LENGTH + 1);
close(pipefds[0]);
printf("Child received Quantity '%s' from parent... \n\n", buffer);
}
}
return EXIT_SUCCESS;
}

void sigint_handler(int sig){
printf("**** Message was interrupted ! ****\n");
exit(1);
}
