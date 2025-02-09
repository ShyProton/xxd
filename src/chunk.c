#include "include/chunk.h"
#include <stdio.h>
#include <string.h>

static void whitespace_convert(char *c) {
  switch (*c) {
  case '\n':
    *c = '.';
  }
}

static void get_chunk(Chunk *chunk, char **str, size_t nth_chunk,
                      size_t chunk_size) {
  chunk->text = calloc(chunk_size + 1, sizeof(char));

  if (chunk->text == NULL) {
    perror("Out of memory");
    free(*str);
    exit(EXIT_FAILURE);
  }

  char strchar;
  size_t strchar_idx = nth_chunk * chunk_size;

  for (size_t i = 0; i < chunk_size; i++) {
    strchar = (*str)[strchar_idx];
    whitespace_convert(&strchar); // So we can see whitespace characters.

    chunk->text[i] = strchar;
    strchar_idx++;
  }

  chunk->text[chunk_size] = '\0';
}

size_t chunk_str(Chunk *chunks[], char *str, size_t chunk_size) {
  size_t num_chunks = (strlen(str) / chunk_size) + 1;

  *chunks = calloc(num_chunks, sizeof(Chunk));

  if (*chunks == NULL) {
    perror("Out of memory");
    free(str);
    exit(EXIT_FAILURE);
  }

  for (size_t i = 0; i < num_chunks; i++) {
    get_chunk(&(*chunks)[i], &str, i, chunk_size);
  }

  free(str);

  return num_chunks;
}

void deallocate_chunks(Chunk *chunks[], size_t num_chunks) {
  for (size_t i = 0; i < num_chunks; i++) {
    free((*chunks)[i].text);
    free((*chunks)[i].hex);
  }

  free(*chunks);
}
