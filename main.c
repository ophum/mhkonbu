#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defines.h"

int main(int argc, char **argv)
{
  char *filename;
  FILE *fp;
  int col = 0;
  int cnt;
  int ch;

  if(argc < 2)
  {
    return 1;
  }

  filename = argv[1];

  if((fp = fopen(filename, "r")) == NULL)
  {
    return 1;
  }

  while((ch = fgetc(fp)) != EOF)
  {
    if(col == 0 && ch == ' ') continue;
    
    switch(ch)
    {
      case '\n': col = 0; break;
      case '-':
        cnt = 1;
        while((ch = fgetc(fp)) != EOF)
        {
          if(ch == '-') cnt++;
          else if(ch == ' ') continue;
          else
          {
            ungetc(ch, fp);
            break;
          }
        }

        if(cnt == 1)
        {
          printf("<li>");

          while((ch = fgetc(fp)) != EOF)
          {
            if(ch == '\n')
            {
              break;
            }else {
              putchar(ch);
            }
          }

          printf("</li>");
        }else {
          printf("<hr>");
        }
        break;
      case '#':
        for(cnt = 1; (ch = fgetc(fp)) == '#'; cnt++);
        printf("<h%d>%c", cnt, ch);			
        while((ch = fgetc(fp)) != EOF && ch != '\n'){
          putchar(ch);
        }
        printf("</h%d>\n", cnt);
        break;
      default:
        printf("<p>");
        cnt = 0;
        while((ch = fgetc(fp)) != EOF)
        {
          if(ch == '\n')
          {
            if(cnt == 0) break;

            cnt = 0;
            continue;
          }
          switch(ch)
          {
            case ' ':
              ch = fgetc(fp);
              if(ch == ' ')
              {
                printf("<br>");
              }else {
                putchar(' ');
                ungetc(ch, fp);
              }
              break;
            default:
              putchar(ch);
              break;
          }
          cnt++;
        }
        printf("</p>\n");
        break;
    }
    putchar('\n');
  }

  fclose(fp);
  return 0;
}
