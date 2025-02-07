#include "include/fileio.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  char **data;
  size_t count;
  size_t chunklen;
} Chunks;

// TODO: Rewrite this so it works with the Chunks struct.
int double_rows(char **sections[], size_t current_rows, size_t sec_len) {
  size_t new_len = current_rows * 2;
  *sections = realloc(*sections, sizeof(char *) * new_len);

  if (*sections == NULL) {
    perror("Out of memory");
    exit(EXIT_FAILURE);
  }

  for (size_t i = 0; i < new_len; i++) {
    *sections[i] = malloc(sizeof(char) * sec_len);

    if (*sections[i] == NULL) {
      perror("Out of memory");
      exit(EXIT_FAILURE);
    }
  }

  return new_len;
}

Chunks init_chunks(size_t chunklen) {
  Chunks chunks;

  chunks.count = 1;
  chunks.chunklen = chunklen;
  chunks.data = malloc(sizeof(char *) * chunks.count);

  for (size_t i = 0; i < chunks.count; i++) {
    chunks.data[i] = malloc(sizeof(char) * chunks.chunklen);
  }

  return chunks;
}

Chunks chunk_file(FILE **infile, size_t chunklen) {
  Chunks chunks = init_chunks(chunklen);

  size_t i = 0;

  while (true) {
    if (i > chunks.count) {
      // TODO: Double amount of rows in chunks
    }

    fread(chunks.data[i], sizeof(char), chunks.chunklen, *infile);

    // TODO: Check if fread was successful.
  }
}

int main(int argc, char *argv[]) {
  if (argc < 3) {
    fprintf(stderr, "Not enough arguments supplied.\n");
    return EXIT_FAILURE;
  }

  FILE *infile, *outfile;

  char *inpath = argv[1];
  char *outpath = argv[2];

  open_read_write_files(&infile, &outfile, inpath, outpath);

  section_file(&infile, 16);
  printf("\n");

  close_read_write_files(&infile, &outfile);

  return EXIT_SUCCESS;
}
