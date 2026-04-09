#include "ppm.h"

const char *output_file_name = "output_without_gamma_correction.ppm";
const int WIDTH = 1024;
const int HEIGHT = 1024;

int main() {

  WritePPMFile_without_gamma_correction(output_file_name, WIDTH, HEIGHT);
  return 0;
}