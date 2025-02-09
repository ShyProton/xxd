#include "include/chunk.h"
#include "include/fileio.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  if (argc < 3) {
    fprintf(stderr, "Not enough arguments supplied.\n");
    return EXIT_FAILURE;
  }

  char *inpath = argv[1];
  char *outpath = argv[2];

  Chunk *chunks;
  size_t num_chunks;
  char *file_content;

  fread_to_buf(inpath, &file_content);

  num_chunks = chunk_str(&chunks, file_content, 16);

  for (size_t i = 0; i < num_chunks; i++) {
    fputs(chunks[i].text, stdout);
    printf("\n");
  }

  printf("Number of chunks: %zu\n", num_chunks);

  deallocate_chunks(&chunks, num_chunks);

  return EXIT_SUCCESS;
}
