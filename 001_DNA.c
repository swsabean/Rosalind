#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  const char *input = "data/rosalind_dna.txt";
  const char *output = "output/001_DNA.txt";
  FILE *fp;
  char *dna = NULL;
  size_t len = 0;
  int a = 0;
  int c = 0;
  int g = 0;
  int t = 0;
  
  fp = fopen(input, "r");
  if (fp == NULL) {
    perror("fopen");
    exit(EXIT_FAILURE);
  }
  
  if (getline(&dna, &len, fp) == -1) {
    perror("getline");
    exit(EXIT_FAILURE);
  }
  fclose(fp);
  
  /* Strip terminal newline */
  dna[strlen(dna) - 1] = '\0';
  
  for (int i = 0; i < strlen(dna); i++)
    switch(dna[i]) {
      case 'A':
        a++;
        break;
      case 'C':
        c++;
        break;
      case 'G':
        g++;
        break;
      case 'T':
        t++;
        break;
    }
    
  free(dna);
  
  printf("%d %d %d %d\n", a, c, g, t);
  
  fp = fopen(output, "w");
  if (fp == NULL) {
    perror("fopen");
    exit(EXIT_FAILURE);
  }
  fprintf(fp, "%d %d %d %d\n", a, c, g, t);
  fclose(fp);
  
  return EXIT_SUCCESS;
}
