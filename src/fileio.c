#include "include/fileio.h"
#include <stdio.h>
#include <stdlib.h>

static void open_file(FILE **p_file, char *fpath, char *modes) {
  *p_file = fopen(fpath, modes);

  if (*p_file == NULL) {
    fprintf(stderr, "Opening file '%s' failed", fpath);
    perror(NULL);
    exit(EXIT_FAILURE);
  }
}

void fread_to_buf(char *fpath, char **p_buf) {
  FILE *file;
  long num_chars;

  open_file(&file, fpath, "r");

  if (fseek(file, 0L, SEEK_END) != EXIT_SUCCESS) {
    perror("Could not read file");
    fclose(file);
    exit(EXIT_FAILURE);
  }

  num_chars = ftell(file);

  if (num_chars == -1) {
    perror("Could not read file");
    fclose(file);
    exit(EXIT_FAILURE);
  }

  rewind(file);

  // Allocating number of characters + 1 for the null terminator.
  *p_buf = calloc(num_chars + 1, sizeof(char));

  if (*p_buf == NULL) {
    perror("Out of memory");
    fclose(file);
    exit(EXIT_FAILURE);
  }

  fread(*p_buf, sizeof(char), num_chars, file);

  if (ferror(file) != EXIT_SUCCESS) {
    perror("Could not read file");
    fclose(file);
    exit(EXIT_FAILURE);
  }

  fclose(file);
}
