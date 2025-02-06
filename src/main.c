#include "include/fileio.h"
#include <stdio.h>
#include <stdlib.h>

int print_bytes(FILE **infile, FILE **outfile) {
  char byte;

  while ((byte = fgetc(*infile)) != EOF) {
    printf("%02x ", byte);
  }

  return 0;
}

int *thing(void) {
  int x = 10;

  return &x;
}

int main(int argc, char **argv) {
  if (argc < 3) {
    fprintf(stderr, "Not enough arguments supplied.\n");
    return EXIT_FAILURE;
  }

  FILE *infile, *outfile;

  char *inpath = argv[1];
  char *outpath = argv[2];

  open_read_write_files(&infile, &outfile, inpath, outpath);

  print_bytes(&infile, &outfile);
  printf("\n");

  close_read_write_files(&infile, &outfile);

  return EXIT_SUCCESS;
}
