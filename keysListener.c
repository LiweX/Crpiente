#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

struct termios saved_attributes;

void inputHandler(int*head_direction){
    while(-1){
        if(getchar()==27){
            getchar();
            switch (getchar())
            {
            case 65:
                *head_direction=1;
                break;
            case 66:
                *head_direction=2;
                break;
            case 67:
                *head_direction=4;
                break;
            case 68:
                *head_direction=3;
                break;
            default:
                break;
            }
        }
    }
}

void reset_input_mode ()
{
  tcsetattr (STDIN_FILENO, TCSANOW, &saved_attributes);
}

void noncanonical_mode ()
{
  struct termios tattr;

  /* Make sure stdin is a terminal. */
  if (!isatty (STDIN_FILENO))
    {
      fprintf (stderr, "Not a terminal.\n");
      exit (EXIT_FAILURE);
    }

  /* Save the terminal attributes so we can restore them later. */
  tcgetattr (STDIN_FILENO, &saved_attributes);
  atexit (reset_input_mode);

  /* Set the funny terminal modes. */
  tcgetattr (STDIN_FILENO, &tattr);
  tattr.c_lflag &= ~(ICANON|ECHO); /* Clear ICANON and ECHO. */
  tattr.c_cc[VMIN] = 1;
  tattr.c_cc[VTIME] = 0;
  tcsetattr (STDIN_FILENO, TCSAFLUSH, &tattr);
}