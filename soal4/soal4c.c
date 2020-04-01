#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

/**
 * Executes the command "cat scores | grep Villanova".  In this quick-and-dirty
 * implementation the parent doesn't wait for the child to finish and
 * so the command prompt may reappear before the child terminates.
 *
 * @author Jim Glenn
 * @version 0.1 9/23/2004
 */

int main(int argc, char **argv)
{
  int pipefd[2];
  int pid;

  char *ls_args[] = {"ls", "/home/test/SISOP2/TIGA/PRAKTIKUM", NULL};
  char *wc_args[] = {"wc", "-l", NULL};

  // make a pipe (fds go in pipefd[0] and pipefd[1])

  pipe(pipefd);

  pid = fork();

  if (pid == 0)
    {
      // child gets here and handles "grep Villanova"

      // replace standard input with input part of pipe

      dup2(pipefd[0], 0);

      // close unused hald of pipe

      close(pipefd[1]);

      // execute grep

      execvp("wc", wc_args);
    }
  else
    {
      // parent gets here and handles "cat scores"

      // replace standard output with output part of pipe

      dup2(pipefd[1], 1);

      // close unused unput half of pipe

      close(pipefd[0]);

      // execute cat

      execvp("ls", ls_args);
    }
}
