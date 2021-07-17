#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  const char *input = "data/rosalind_revc.txt";
  const char *output = "output/003_REVC.txt";
  FILE *fp;
  char *dna = NULL;
  size_t len = 0;
  char *rev;
  
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
  
  rev = (char *) malloc((strlen(dna) + 1) * sizeof(char));
  if (rev == NULL) {
    perror("malloc");
    exit(EXIT_FAILURE);
  }
  
  for (int i = strlen(dna) - 1; i >= 0; i--)
    switch (dna[i]) {
      case 'A':
        rev[strlen(dna) - 1 - i] = 'T';
        break;
      case 'C':
        rev[strlen(dna) - 1 - i] = 'G';
        break;
      case 'G':
        rev[strlen(dna) - 1 - i] = 'C';
        break;
      case 'T':
        rev[strlen(dna) - 1 - i] = 'A';
        break;
    }
  rev[strlen(dna)] = '\0';
  
  printf("%s\n", rev);
  
  fp = fopen(output, "w");
  if (fp == NULL) {
    perror("fopen");
    exit(EXIT_FAILURE);
  }
  fprintf(fp, "%s\n", rev);
  fclose(fp);
 
  free(dna); 
  free(rev);
  
  return EXIT_SUCCESS;
}
