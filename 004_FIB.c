#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int fib(int n, int k) {
  if (n < 1)
    return 0;
  else if (n == 1)
    return 1;
  else if (n == 2)
    return 1;
  else
    return fib(n - 1, k) + k * fib(n - 2, k);
}

int main() {
  const char *input = "data/rosalind_fib.txt";
  const char *output = "output/004_FIB.txt";
  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  int n;
  int k;
  int result;
  
  fp = fopen(input, "r");
  if (fp == NULL) {
    perror("fopen");
    exit(EXIT_FAILURE);
  }
  
  if (getline(&line, &len, fp) == -1) {
    perror("getline");
    exit(EXIT_FAILURE);
  }
  fclose(fp);
  
  /* Strip terminal newline */
  line[strlen(line) - 1] = '\0';
  
  n = atoi(strtok(line, " "));
  k = atoi(strtok(NULL, " "));
  
  result = fib(n, k);
  
  printf("%d\n", result);
  
  fp = fopen(output, "w");
  if (fp == NULL) {
    perror("fopen");
    exit(EXIT_FAILURE);
  }
  fprintf(fp, "%d\n", result);
  fclose(fp);
 
  free(line); 
  
  return EXIT_SUCCESS;
}
