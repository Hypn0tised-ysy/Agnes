#include "cli.h"
#include "filepath.h"
#include "ppm.h"

int main(int argc, char *argv[]) {
  // command line arguments
  // initialize
  // render
  // clean up resource

  RenderOptions options = ParseCommandLineArguments(argc, argv);
  WritePPMFile(options.output_file_name.c_str(), options.width, options.height);
  return 0;
}