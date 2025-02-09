#include "include/chunk.h"
#include <stdio.h>
#include <string.h>

static void whitespace_convert(char *p_char) {
  switch (*p_char) {
  case '\n':
    *p_char = '.';
  }
}

static void get_chunk(Chunk *chunk, char **p_str, size_t nth_chunk,
                      size_t chunk_size) {
  // Allocating chunk size + 1 for the null terminator.
  chunk->text = calloc(chunk_size + 1, sizeof(char));

  if (chunk->text == NULL) {
    perror("Out of memory");
    free(*p_str);
    exit(EXIT_FAILURE);
  }

  char strchar;
  size_t strchar_idx = nth_chunk * chunk_size;

  for (size_t i = 0; i < chunk_size; i++) {
    strchar = (*p_str)[strchar_idx];
    whitespace_convert(&strchar); // So we can see whitespace characters.

    chunk->text[i] = strchar;
    strchar_idx++;
  }

  // Null-terminate the text.
  chunk->text[chunk_size] = '\0';
}

size_t chunk_str(Chunk *p_chunks[], char *str, size_t chunk_size) {
  size_t num_chunks = (strlen(str) / chunk_size) + 1;

  *p_chunks = calloc(num_chunks, sizeof(Chunk));

  if (*p_chunks == NULL) {
    perror("Out of memory");
    free(str);
    exit(EXIT_FAILURE);
  }

  for (size_t i = 0; i < num_chunks; i++) {
    get_chunk(&(*p_chunks)[i], &str, i, chunk_size);
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
