#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main () {

  int READ = 0, WRITE = 1, val = 0, pipe1[2], pipe2[2];
  pipe(pipe1); // Parent writes to here
  pipe(pipe2); // Child writes to here

  int f = fork();

  if (f) {
    // Close uneeded pipes
    close(pipe1[READ]);
    close(pipe2[WRITE]);
    // Send data to child
    val = 13;
    printf("[PARENT] sending: %d\n", val);
    write(pipe1[WRITE], &val, sizeof(val));
    // Recieve data
    read(pipe2[READ], &val, sizeof(val));
    printf("[PARENT] recieved: %d\n", val);
  } else {
    // Close uneeded pipes
    close(pipe2[READ]);
    close(pipe1[WRITE]);
    // Recieving data from parent
    read(pipe1[READ], &val, sizeof(val));
    printf("[CHILD] doing maths on: %d\n", val);
    // Sending data back to parent
    val *= val;
    write(pipe2[WRITE], &val, sizeof(val));
  }

  return 0;
}
