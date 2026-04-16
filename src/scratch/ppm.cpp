#include <cstdio>
#include <filesystem>

#include "color.h"
#include "filepath.h"

const int max_color_value = 255;

void output_ppm_file() {}

static std::filesystem::path ResolveOutputPath(const char *filename) {
  std::filesystem::path output_path = IMAGE_PATH;

  if (filename != nullptr && filename[0] != '\0') {
    output_path /= filename;
  } else {
    output_path /= "default.ppm";
  }

  const std::filesystem::path parent_dir = output_path.parent_path();
  if (parent_dir.empty()) {
    std::filesystem::create_directories(IMAGE_PATH);
  } else {
    std::filesystem::create_directories(parent_dir);
  }

  return output_path;
}

void OutputTestPPMFile() {
  static const int width = 256;
  static const int height = 256;

  const std::filesystem::path output_path = IMAGE_PATH / "output.ppm";
  std::filesystem::create_directories(IMAGE_PATH);

  // open file named output.ppm for writing
  FILE *fp = fopen(output_path.string().c_str(), "wb");
  if (fp == nullptr) {
    std::perror("Failed to open file");
    return;
  }

  // write ppm file, red goes from 0 to 255, green goes from 0 to 255, blue is
  // always 128
  fprintf(fp, "P3\n%d %d\n%d\n", width, height, max_color_value);

  // TODO 写成并行逻辑
  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      double normalized_x = static_cast<double>(x) / (width - 1);
      double normalized_y = static_cast<double>(y) / (height - 1);
      int r = static_cast<int>(normalized_x *
                               max_color_value); // red goes from 0 to 255
      int g = static_cast<int>(normalized_y *
                               max_color_value); // green goes from 0 to 255
      int b = 128;                               // blue is always 128
      fprintf(fp, "%d %d %d \n", r, g, b);
    }
    fprintf(fp, "\n");
  }

  fclose(fp);
}

void WritePPMFile(const char *filename, const int width, const int height) {
  const std::filesystem::path output_path = ResolveOutputPath(filename);

  // open file named output.ppm for writing
  FILE *fp = fopen(output_path.string().c_str(), "wb");
  if (fp == nullptr) {
    std::perror("Failed to open file");
    return;
  }

  // write ppm file, red goes from 0 to 255, green goes from 0 to 255, blue is
  // always 128
  fprintf(fp, "P3\n%d %d\n%d\n", width, height, max_color_value);

  // TODO 写成并行逻辑
  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      double normalized_x = static_cast<double>(x) / (width - 1);
      double normalized_y = static_cast<double>(y) / (height - 1);
      auto pixel_color = color3(normalized_x, normalized_y, 0.5);
      WriteColor2File(fp, pixel_color);
    }
    fprintf(fp, "\n");
  }

  fclose(fp);
}

void WritePPMFile_without_gamma_correction(const char *filename,
                                           const int width, const int height) {
  const std::filesystem::path output_path = ResolveOutputPath(filename);

  // open file named output.ppm for writing
  FILE *fp = fopen(output_path.string().c_str(), "wb");
  if (fp == nullptr) {
    std::perror("Failed to open file");
    return;
  }

  // write ppm file, red goes from 0 to 255, green goes from 0 to 255, blue is
  // always 128
  fprintf(fp, "P3\n%d %d\n%d\n", width, height, max_color_value);

  // TODO 写成并行逻辑
  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      double normalized_x = static_cast<double>(x) / (width - 1);
      double normalized_y = static_cast<double>(y) / (height - 1);
      auto pixel_color = color3(normalized_x, normalized_y, 0.5);
      WriteColor2File_without_gamma_correction(fp, pixel_color);
    }
    fprintf(fp, "\n");
  }

  fclose(fp);
}