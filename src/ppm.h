#pragma once

void OutputTestPPMFile();

void WritePPMFile(const char* filename, const int width, const int height);
void WritePPMFile_without_gamma_correction(const char* filename, const int width,
                                         const int height);
