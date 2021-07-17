#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 1024

int main() {
  const char *input = "data/rosalind_gc.txt";
  const char *output = "output/005_GC.txt";
  FILE *fp;
  char *line_buf = NULL;
  size_t line_buf_size = 0;
  ssize_t line_size;
  char *lines[MAX_LINES];
  int line_count = 0;
  char *id;
  int gc_count;
  int total_count;
  double gc;
  double max_gc = 0;
  char *max_id;

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

  for (int i = 0; i < line_count; i++) {
    if (lines[i][0] == '>') {
      id = lines[i] + 1;
      int j = 1;
      gc_count = 0;
      total_count = 0;
      while (i + j < line_count && lines[i + j][0] != '>') {
        for (int k = 0; k < strlen(lines[i + j]); k++)
          if (lines[i + j][k] == 'C' || lines[i + j][k] == 'G')
            gc_count++;
        total_count += strlen(lines[i + j]);
        j++;
      }
      gc = (double) gc_count / total_count * 100;
      if (gc > max_gc) {
        max_gc = gc;
        max_id = id;
      }
    }
  }
  printf("%s %f\n", max_id, max_gc);

  fp = fopen(output, "w");
  if (fp == NULL) {
    perror("fopen");
    exit(EXIT_FAILURE);
  }
  fprintf(fp, "%s %f\n", max_id, max_gc);
  fclose(fp);

  free(line_buf);
  for (int i = 0; i < line_count; i++)
    free(lines[i]);

  return EXIT_SUCCESS;
}
