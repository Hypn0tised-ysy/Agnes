#pragma once 
#include <string>

struct RenderOptions
{
    std::string output_file_name;
    int width;
    int height;
};

RenderOptions ParseCommandLineArguments(int argc, char *argv[]);