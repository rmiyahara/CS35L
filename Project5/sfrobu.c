//Ryan Miyahara
//UCID: 804585999

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <ctype.h>
#include <sys/stat.h>

int compare_count = 0;

int frobcmp(const char * a, const char * b)
{
  //a and b are arrays of frobnicated chars
  //Returns -1 if a < b
  //Returns 0 if a == b
  //Returns 1 if a > b
  compare_count++;
  printf("%d\n", compare_count);
  int i;
  for (i = 0; a[i] != ' ' && b[i] != ' '; i++)
  {
    char A =  (char)((int) a[i] ^ 42);
    char B =  (char)((int) b[i] ^ 42);
    if (A > B)
      return 1;
    else if (A < B)
      return -1;
  }
  if (a[i] == ' ' && b[i] == ' ') //Both are equal
    return 0;
  else if (a[i] == ' ') //a ends first
    return -1;
  else if (b[i] == ' ') //b ends first
    return 1;
  else //Something went wrong
    exit(1);
}

int frobcmpf(const char * a, const char * b)
{
  //a and b are arrays of frobnicated chars
  //Returns -1 if a < b
  //Returns 0 if a == b
  //Returns 1 if a > b
  compare_count++;
  printf("%d\n", compare_count);
  int i;
  for (i = 0; a[i] != ' ' && b[i] != ' '; i++)
  {
    int A = ((int) a[i] ^ 42);
    int B = ((int) b[i] ^ 42);
    if (A < CHAR_MIN || A > CHAR_MAX || B < CHAR_MIN || B > CHAR_MAX)
    {
      fprintf(stderr, "char out of range for toupper.");
      exit(0);
    }
    A = toupper(A);
    B = toupper(B);
    if (A > B)
      return 1;
    else if (A < B)
      return -1;
  }
  if (a[i] == ' ' && b[i] == ' ') //Both are equal
    return 0;
  else if (a[i] == ' ') //a ends first
    return -1;
  else if (b[i] == ' ') //b ends first
    return 1;
  else //Something went wrong
    exit(1);
}

int notfrobcmp(const void * a, const void * b)
{
    const char * A = *(char**)a;
    const char * B = *(char**)b;
    return frobcmp(A, B);
}

int notfrobcmpf(const void * a, const void * b)
{
    const char * A = *(char**)a;
    const char * B = *(char**)b;
    return frobcmpf(A, B);
}

void memcheck(char * a)
{
  if (a == NULL)
  {
    fprintf(stderr, "Memory allocation error.");
    exit(1);
  }
}

void doublememcheck(char ** a)
{
  if (a == NULL)
  {
    fprintf(stderr, "Memory allocation error.");
    exit(1);
  }
}

char * take_in_word()
{
  char * temp; //Word we are adding
  temp = (char *)malloc(sizeof(char));
  memcheck(temp);
  *temp = '\0';
  int num_letters = 1; //Remember zero byte
  char * buf;
  buf = malloc(sizeof(char));
  int i;
  while (read(0, buf, 1))
  {
    if (ferror(stdin))
    {
      fprintf(stderr, "Error taking from stdin.");
      exit(1);
    }
    num_letters++;
    char * neo;
    neo = (char *)realloc(temp, (sizeof(char) * num_letters));
    memcheck(neo);
    temp = neo;
    temp[num_letters - 2] = buf[0];
    temp[num_letters - 1] = '\0';
    if (buf[0] == ' ')
    {
      free(buf);
      return temp;
    }
  }
  free(buf);
  if (num_letters <= 1) //No more words to read
  {
    free(temp);
    return NULL;
  }
  else //Last char is not a space
  {
    num_letters++;
    char * neo;
    neo = (char *)realloc(temp, (sizeof(char) * num_letters));
    memcheck(neo);
    temp = neo;
    temp[num_letters - 2] = ' ';
    temp[num_letters - 1] = '\0';
    return temp;
  }
  exit(1); //Should never get here
}

void printwords(char ** array, int size)
{
  int i;
  for (i = 0; i < size; i++)
  {
    write(1, array[i], strlen(array[i]));
    if (ferror(stdout))
    {
      fprintf(stderr, "Error writing to stdout.");
      exit(1);
    }
  }
}

void freewords(char ** array, int size)
{
  int i;
  for (i = 0; i < size; i++)
  {
    free(array[i]);
  }
  free(array);
}

int main(int args, char ** arg)
{
  if (args > 2)
  {
    fprintf (stderr, "Error: Incorrect number of arguments");
    exit(1);
  }
  int fflag = 0;
  int c;
  while ((c = getopt (args, arg, "f")) != -1)
  {
    switch (c)
    {
      case 'f':
        fflag = 1;
        break;
      default:
        fprintf (stderr, "Only accepted flag is -f");
        exit(1);
    }
  }

  //Holds all all_words
  char ** all_words;
  int num_words = 0;
  all_words = (char **)malloc(1);
  doublememcheck(all_words);

  //Add input into list
  char * add;
  add = take_in_word();
  while (add != NULL)
  {
    num_words++;
    char ** neo;
    neo = (char **)realloc(all_words, (sizeof(char *) * ((size_t)num_words)));
    doublememcheck(neo);
    all_words = neo;
    all_words[num_words - 1] = add;
    add = take_in_word();
  }

  //Create function pointer for qsort
  int (*func_ptr)(const void *, const void *);
  if (fflag == 1)
    func_ptr = &notfrobcmpf;
  else
    func_ptr = &notfrobcmp;

  qsort(all_words, (size_t)num_words, sizeof(char *), func_ptr);
  //Print all sorted chars
  //printwords(all_words, num_words);
  //Free dynamically allocated memory
  freewords(all_words, num_words);
  exit(0);
}
