#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <err.h>

#define BUF_SIZE 100

char buf[BUF_SIZE];
char message_buf[1];
int nread;

struct Exam {
  char name[20];
  char question[100];
  char possible_answers[100];
  char correct_answer[1];
  char exam_json[200];
};

/*strcpy( Question2.question, "How long do turtles live?");
strcpy( Question2.possible_answers, "A - 100, B - 20, C - 500.");
strcpy( Question2.correct_answer, "A");

strcpy( Question3.question, "What does the fox say?");
strcpy( Question3.possible_answers, "A - woof, B - meow, C - Ring-ding-ding.");
strcpy( Question3.correct_answer, "C");*/

struct Users {
   char  login[50];
   char  password[50];
};

char* create_json_string(struct Exam Question) {
  char* json = malloc(200* sizeof(char));
  sprintf(json, "{ \"%s\": { \"question\": \"%s\", \"possible_answers\": \"%s\", \"correct_answer\": \"%s\" } }", Question.name, Question.question, Question.possible_answers, Question.correct_answer);
  return json;
}

void start_server(int sock) {
  int one = 1;
  struct sockaddr_in svr_addr;
  if (sock < 0)
    err(1, "can't open socket");
 
  setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(int));
 
  int port = 6666;
  svr_addr.sin_family = AF_INET;
  svr_addr.sin_addr.s_addr = INADDR_ANY;
  svr_addr.sin_port = htons(port);
 
  if (bind(sock, (struct sockaddr *) &svr_addr, sizeof(svr_addr)) == -1) {
    close(sock);
    err(1, "Can't bind");
  }
 
  listen(sock, 5);
}



int main() {

  struct Users Admin;
  struct Users Teacher;
  struct Users Student;

  strcpy( Admin.login, "admin");
  strcpy( Admin.password, "admin");

  strcpy( Teacher.login, "teacher");
  strcpy( Teacher.password, "teacher");

  strcpy( Student.login, "student");
  strcpy( Student.password, "student");

  struct Exam Question1;
//struct Exam Question2;
//struct Exam Question3;
  strcpy( Question1.name, "Question1");
  strcpy( Question1.question, "What color is a chalkboard?");
  strcpy( Question1.possible_answers, "A - pink, B - green, C - yellow.");
  strcpy( Question1.correct_answer, "B");
  strcpy( Question1.exam_json, create_json_string(Question1));
  printf("%s\n", Question1.exam_json );
  
  int client_fd;
  struct sockaddr_in cli_addr;
  socklen_t sin_len = sizeof(cli_addr);
  int sock = socket(AF_INET, SOCK_STREAM, 0);

  start_server(sock);
  

  while (1) {
    client_fd = accept(sock, (struct sockaddr *) &cli_addr, &sin_len);
    printf("got connection\n");
 
    if (client_fd == -1) {
      perror("Can't accept");
      continue;
    }
    
    //read(client_fd, buf, BUF_SIZE);

    write(client_fd, Question1.exam_json, strlen(Question1.exam_json));
    //write(client_fd, "#", 1);
    /*write(client_fd, Question2.correct_answer, strlen(Question2.correct_answer));
    write(client_fd, Question2.question, strlen(Question2.question));
    write(client_fd, Question2.possible_answers, strlen(Question2.possible_answers));
    
    //write(client_fd, "#", 1);
    write(client_fd, Question3.correct_answer, strlen(Question3.correct_answer));
    write(client_fd, Question3.question, strlen(Question3.question));
    write(client_fd, Question3.possible_answers, strlen(Question3.possible_answers));*/

    close(client_fd);
  }
}