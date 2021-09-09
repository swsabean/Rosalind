
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 1024

int main() {
  const char *input = "data/rosalind_subs.txt";
  const char *output = "output/009_SUBS.txt";
  FILE *fp;
  char *line_buf = NULL;
  size_t line_buf_size = 0;
  ssize_t line_size;
  char *lines[MAX_LINES];
  int line_count = 0;
  char *position;
  size_t index;
  char str[1024] = "";
  char istr[1024] = "";
  
  fp = fopen(input, "r");
  if (fp == NULL) {
    perror("fopen");
    exit(EXIT_FAILURE);
  }
  
  // Get first line
  line_size = getline(&line_buf, &line_buf_size, fp);

  while (line_size >= 0) {
    // Strip terminal newline, if necessary
    if (line_buf[strlen(line_buf) - 1] == '\n')
      line_buf[strlen(line_buf) - 1] = '\0';
    // Allocate space for line string
    lines[line_count] = (char *) malloc((strlen(line_buf) + 1) * sizeof(char));
    if (lines[line_count] == NULL) {
      fprintf(stderr, "memory allocation failure");
      exit(EXIT_FAILURE);
    }
    // Copy line string
    strcpy(lines[line_count], line_buf);
    // Increment line counter and get next line
    line_count++;
    line_size = getline(&line_buf, &line_buf_size, fp);
  }

  fclose(fp);

  position = strstr(lines[0], lines[1]);
  while(position != NULL) {
    index = position - lines[0] + 1;
    sprintf(istr, "%d ", index);
    strcat(str, istr);
    position = strstr(position + 1, lines[1]);
  }
  
  printf("%s\n", str);
  
  fp = fopen(output, "w");
  if (fp == NULL) {
    perror("fopen");
    exit(EXIT_FAILURE);
  }
  fprintf(fp, "%s", str);
  fclose(fp);

  free(line_buf);
  for (int i = 0; i < line_count; i++)
    free(lines[i]);

  return EXIT_SUCCESS;
}
