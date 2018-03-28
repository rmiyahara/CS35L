//Ryan Miyahara
//UCID: 804585999

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int args, char ** arg)
{
  //Check to see if number of arguments is 3.
  //arg[0] is the name
  //arg[1] is the "from"
  //arg[2] is the "to"
  if (args != 3)
  {
    fprintf (stderr, "Error: 2 strings must be passed in.");
    exit(1);
  }

  //Check that "from" and "to" are of the same length
  if (strlen(arg[1]) != strlen(arg[2]))
  {
    fprintf (stderr, "Error: Length of 2 strings must be the same.");
    exit(1);
  }

  //Check for duplicates, if no duplicates, move all char into from.
  int i;
  int j;
  char * from;
  from = (char *)malloc(strlen(arg[1]) * (sizeof(char)));
  for (i = 0; i < strlen(arg[1]); i++)
  {
    for (j = 0; j < i; j++)
    {
      if (arg[1][i] == from[j])
      {
        fprintf (stderr, "Error: There can be no duplicates in the from string.");
        free(from);
        exit(1);
      }
    }
    from[i] = arg[1][i];
  }

  //Check for duplicates, if no duplicates, move all char into to.
  char * to;
  to = (char *)malloc(strlen(arg[2]) * (sizeof(char)));
  for (i = 0; i < strlen(arg[2]); i++)
  {
    for (j = 0; j < i; j++)
    {
      if (arg[2][i] == to[j])
      {
        fprintf (stderr, "Error: There can be no duplicates in the to string.");
        free(from);
        free(to);
        exit(1);
      }
    }
    to[i] = arg[2][i];
  }

  //Take in chars using buffered I/O and transliterate them.
  int ggez = getchar();
  while (ggez != EOF)
  {
    int position = -1;
    for (i = 0; i < strlen(from); i++)
    {
      if ((char)ggez == from[i]) //Match found
      {
        position = i;
        break;
      }
    }
    if (position >= 0)
      putchar((int) to[position]);
    else
      putchar(ggez);
    ggez = getchar();
  }

  //Program has run all the way through.
  free(from);
  free(to);
  exit(0);
}
