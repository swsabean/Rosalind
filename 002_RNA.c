#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  const char *input = "data/rosalind_rna.txt";
  const char *output = "output/002_RNA.txt";
  FILE *fp;
  char *dna = NULL;
  size_t len = 0;
  char *rna;
  
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
  
  rna = (char *) malloc((strlen(dna) + 1) * sizeof(char));
  if (rna == NULL) {
    perror("malloc");
    exit(EXIT_FAILURE);
  }
  
  for (int i = 0; i <= strlen(dna); i++)
    if (dna[i] == 'T')
      rna[i] = 'U';
    else
      rna[i] = dna[i];
      
  printf("%s\n", rna);
  
  fp = fopen(output, "w");
  if (fp == NULL) {
    perror("fopen");
    exit(EXIT_FAILURE);
  }
  fprintf(fp, "%s\n", rna);
  fclose(fp);
 
  free(dna); 
  free(rna);
  
  return EXIT_SUCCESS;
}
