#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#define STRLEN 6

char inputChar()
{
    int val = rand() % 95 + 32;  // num printable ascii chars: 95, add 32 to offset past control chars
    // if (val < 32 || val > 126)
    // {
    //   printf("%d\n", val);
    // }
    //printf("%c\n", (char)val);
    return (char)val;
}

char *inputString()
{
    char str[STRLEN];
    for (int i = 0; i < STRLEN - 1; i++)
    {
      str[i] = (char)(rand() % 26 + 97); 
    }
    str[STRLEN - 1] = '\0';
    // printf("%s\n", str);
    return str;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    if (!(tcCount % 10000))
    {
      printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);
    }

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error at iteration %d ", tcCount);
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
