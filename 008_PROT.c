#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 1024

static const char *codon_table[4][4][4] =
{
  {
    {"F", "F", "L", "L"},
    {"S", "S", "S", "S"},
    {"Y", "Y", "Stop", "Stop"},
    {"C", "C", "Stop", "W"}
  },
  {
    {"L", "L", "L", "L"},
    {"P", "P", "P", "P"},
    {"H", "H", "Q", "Q"},
    {"R", "R", "R", "R"}
  },
  {
    {"I", "I", "I", "M"},
    {"T", "T", "T", "T"},
    {"N", "N", "K", "K"},
    {"S", "S", "R", "R"}
  },
  {
    {"V", "V", "V", "V"},
    {"A", "A", "A", "A"},
    {"D", "D", "E", "E"},
    {"G", "G", "G", "G"}
  }
};

int main() {
  const char *input = "data/rosalind_prot.txt";
  const char *output = "output/008_PROT.txt";
  FILE *fp;
  char *line_buf = NULL;
  size_t line_buf_size = 0;
  ssize_t line_size;
  char *lines[MAX_LINES];
  int line_count = 0;
  char *rna;
  size_t index[3];
  size_t protein_size;

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
  
  rna = lines[0];
  protein_size = strlen(rna) / 3;
  char protein[protein_size + 1];
  memset(protein, '\0', protein_size + 1);
  for (size_t i = 0; i < strlen(rna); i += 3) {
    for (size_t j = 0; j < 3; j++) {
      switch (rna[i + j]) {
        case 'U':
          index[j] = 0;
          break;
        case 'C':
          index[j] = 1;
          break;
        case 'A':
          index[j] = 2;
          break;
        case 'G':
          index[j] = 3;
          break;
      }
    }
    if (strcmp(codon_table[index[0]][index[1]][index[2]],"Stop") != 0)
      strcat(protein, codon_table[index[0]][index[1]][index[2]]);
  }
  printf("%s\n", protein);

  fp = fopen(output, "w");
  if (fp == NULL) {
    perror("fopen");
    exit(EXIT_FAILURE);
  }
  fprintf(fp, "%s\n", protein);
  fclose(fp);

  free(line_buf);
  for (int i = 0; i < line_count; i++)
    free(lines[i]);

  return EXIT_SUCCESS;
}
