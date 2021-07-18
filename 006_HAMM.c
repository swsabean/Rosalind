#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 1024

int main() {
  const char *input = "data/rosalind_hamm.txt";
  const char *output = "output/006_HAMM.txt";
  FILE *fp;
  char *line_buf = NULL;
  size_t line_buf_size = 0;
  ssize_t line_size;
  char *lines[MAX_LINES];
  int line_count = 0;
  int hamm = 0;

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
      perror("malloc");
      exit(EXIT_FAILURE);
    }
    // Copy line string
    strcpy(lines[line_count], line_buf);
    // Increment line counter and get next line
    line_count++;
    line_size = getline(&line_buf, &line_buf_size, fp);
  }

  fclose(fp);

  for(int i = 0; i < strlen(lines[0]); i++)
    if (lines[0][i] != lines[1][i])
      hamm++;
 
  printf("%d\n", hamm);

  fp = fopen(output, "w");
  if (fp == NULL) {
    perror("fopen");
    exit(EXIT_FAILURE);
  }
  fprintf(fp, "%d\n", hamm);
  fclose(fp);

  free(line_buf);
  for (int i = 0; i < line_count; i++)
    free(lines[i]);

  return EXIT_SUCCESS;
}
