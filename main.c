#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "defines.h"

int getFileSize(char *filename)
{
  struct stat st;
  if(stat(filename, &st) == 0)
  {
    return st.st_size;
  }
  return -1;
}

int getLineLength(int *lsegs, int ln, int n){
  if(ln == n) return 0; 
  return lsegs[n + 1] - lsegs[n] - 1;
}

int main(int argc, char **argv)
{
  char *filename;
  char *body;
  int *lsegs;
  int fsize = 0;
  int ln = 1;
  FILE *fp;
  int col = 0;
  int cnt;
  int ch;
  int i, j, len;
  int space = 0;
  if(argc < 2)
  {
    return 1;
  }

  filename = argv[1];
  fsize = getFileSize(filename);
  body = (char *)malloc(sizeof(char) * fsize);
  
  if(fsize == -1 || (fp = fopen(filename, "r")) == NULL)
  {
    return 1;
  }

  fread(body, sizeof(char), fsize, fp);
 
  for(i = 0; i < fsize; i++)
  {
    if(body[i] == '\n') ln++;
  }

  lsegs = (int *)malloc(sizeof(int) * ln + 1);
  
  lsegs[0] = 0;
  for(i = 0, j = 1; i < fsize; i++)
  {
    if(body[i] == '\n') lsegs[j++] = i + 1;
  }

  fclose(fp);

  printf("<pre>debug>\n");
  for(i = 0; i < ln; i++)
  {
    printf("%04d:%.*s", i + 1, lsegs[i+1] - lsegs[i], &body[lsegs[i]]);
  }
  printf("</pre>\n");

  for(i = 0; i < ln; i++)
  {
    switch(body[lsegs[i]])
    {
      case ' ': space++;
      case '\n': space = 0; break;
      // heading
      case '#':
        for(j = 0; body[lsegs[i] + j] == '#'; j++);
        printf("<h%d>%.*s</h%d>\n",
            j,
            getLineLength(lsegs, ln, i) - j,
            &body[lsegs[i] + j],
            j);
        break;
      // horizontal
      // list
      case '-':
        len = getLineLength(lsegs, ln, i);
        cnt = 0;
        for(j = 0; j < len; j++){
          if(body[lsegs[i] + j] == '-') cnt++;
          else if(body[lsegs[i] + j] != ' ') break;
        }

        if(cnt >= 3){ // horizontal
          printf("<hr>\n");
        }else if(cnt == 2){ // other
          printf("%.*s\n", len, &body[lsegs[i]]);
        }else { // list
          printf("<li>%.*s</li>\n", len - j, &body[lsegs[i] + j]);
        }
        break;
      // paragraph
      default:
        printf("<p>");
        for(i; i < ln; i++)
        {
          if(body[lsegs[i+1]-2] == ' ' && body[lsegs[i+1]-3] == ' ')
          {
            printf("%.*s<br>",
                getLineLength(lsegs, ln, i) - 2,
                &body[lsegs[i]]);
          }else {
            printf("%.*s",
                getLineLength(lsegs, ln, i),
                &body[lsegs[i]]);
          }
          if(body[lsegs[i]] == '\n') break; 
        }
        printf("</p>\n");
        break;
    }
  }
  free(body);
  free(lsegs);
  return 0;
}
