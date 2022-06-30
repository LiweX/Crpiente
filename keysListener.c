#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

struct termios saved_attributes;

void detectInput(){
    while(-1){
        if(getchar()==27){
            getchar();
            switch (getchar())
            {
            case 65:
                printf("UP PRESS\n");
                break;
            case 66:
                printf("DOWN PRESS\n");
                break;
            case 67:
                printf("RIGHT PRESS\n");
                break;
            case 68:
                printf("LEFT PRESS\n");
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