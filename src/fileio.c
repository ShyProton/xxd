#include "include/fileio.h"
#include <stdio.h>
#include <stdlib.h>

void open_read_write_files(FILE **p_infile, FILE **p_outfile, char *inpath,
                           char *outpath) {
  *p_infile = fopen(inpath, "r");

  if (*p_infile == NULL) {
    perror("Opening input file failed");
    exit(EXIT_FAILURE);
  }

  *p_outfile = fopen(outpath, "w");

  if (*p_outfile == NULL) {
    perror("Opening output file failed");
    fclose(*p_infile);
    exit(EXIT_FAILURE);
  }
}

void close_read_write_files(FILE **p_infile, FILE **p_outfile) {
  if (fclose(*p_infile) == EXIT_FAILURE) {
    perror("Closing input file failed");
  }

  if (fclose(*p_outfile) == EXIT_FAILURE) {
    perror("Closing output file failed");
  }
}
