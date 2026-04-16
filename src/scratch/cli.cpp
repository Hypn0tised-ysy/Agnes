#include "cli.h"
#include <iostream>

/*
错误处理：
对于output/width/height未提供参数则提示用户使用默认配置
对于output/width/height提供了参数但参数无效则提示用户，并退出
*/

const std::string DEFAULT_OUTPUT_FILE_NAME = "default.ppm";
const int DEFAULT_WIDTH = 256;
const int DEFAULT_HEIGHT = 256;

void ParseOutput(const char *arg, RenderOptions &options) {
  if (arg == nullptr) {
    std::cerr << "Warning: Output file name is not provided. Using default: "
              << options.output_file_name << std::endl;
  } else {
    options.output_file_name = arg;
  }
}

void ParseWidth(const char *arg, RenderOptions &options) {
  if (arg == nullptr) {
    std::cerr << "Warning: Width is not provided. Using default: "
              << options.width << std::endl;
  } else {
    try {
      options.width = std::stoi(arg);
    } catch (const std::exception &) {
      std::cerr << "Error: Invalid width." << std::endl;
      exit(1);
    }
  }
}

void ParseHeight(const char *arg, RenderOptions &options) {
  if (arg == nullptr) {
    std::cerr << "Warning: Height is not provided. Using default: "
              << options.height << std::endl;
  } else {
    try {
      options.height = std::stoi(arg);
    } catch (const std::exception &) {
      std::cerr << "Error: Invalid height." << std::endl;
      exit(1);
    }
  }
}

RenderOptions ParseCommandLineArguments(int argc, char *argv[]) {
  RenderOptions options;
  options.output_file_name = DEFAULT_OUTPUT_FILE_NAME;
  options.width = DEFAULT_WIDTH;
  options.height = DEFAULT_HEIGHT;

  for (int i = 1; i < argc; ++i) {
    std::string arg = argv[i];
    // user should provide --output, --width, and --height
    // 如果output后面的参数未空则ParseOutput会提示用户并退出
    if (arg == "--output") {
      ParseOutput(i + 1 < argc ? argv[i + 1] : nullptr, options);
      ++i;
    } else if (arg == "--width") {
      ParseWidth(i + 1 < argc ? argv[i + 1] : nullptr, options);
      ++i;
    } else if (arg == "--height") {
      ParseHeight(i + 1 < argc ? argv[i + 1] : nullptr, options);
      ++i;
    } else {
      std::cerr << "Error: Unknown argument: " << arg << std::endl;
      exit(1);
    }
  }
  return options;
}
