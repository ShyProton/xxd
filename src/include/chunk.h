#include <stdlib.h>

typedef struct {
  char *hex;
  char *text;
} Chunk;

size_t chunk_str(Chunk *p_chunks[], char *str, size_t chunk_size);

void deallocate_chunks(Chunk *p_chunks[], size_t num_chunks);
