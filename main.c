/*
 * main.c
 * Copyright (C) 2023 rzavalet <rzavalet@noemail.com>
 *
 * Distributed under terms of the MIT license.
 */

#include <stdio.h>
#include <assert.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

const char *shift_arg(int *argc, char ***argv)
{
  const char *arg = **argv;
  assert(argc > 0);
  (*argc) --;
  (*argv) ++;
  return arg;
}

int main(int argc, char *argv[])
{
  int img_width;
  int img_height;
  int channels_in_file;
  //const char c[] = "@%#*+=-:. ";
  const char c[] = " .:-=+*#%@";
  const int levels = sizeof(c)/sizeof(c[0]) - 1;

  const char *program = shift_arg(&argc, &argv);
  if (argc <= 0) {
    fprintf(stderr, "No image file provided.\n");
    fprintf(stderr, "Usage: %s <path_to_image_file>\n", program);
    return 1;
  }

  const char *filename = shift_arg(&argc, &argv);
  if (filename == NULL || *filename == 0) {
    fprintf(stderr, "Please provide a valid file name.\n");
    fprintf(stderr, "Usage: %s <path_to_image_file>\n", program);
    return 1;
  }

  stbi_uc *image = stbi_load(filename, &img_width, &img_height, &channels_in_file, 0);
  fprintf(stdout, "Image is of size %dx%d, channels: %d\n", img_width, img_height, channels_in_file);

  for (int i = 0; i < img_height; i++) {
    for (int j = 0; j < img_width; j++) {
      int avg = (image[i * channels_in_file * img_width + channels_in_file * j  + 0] + 
                 image[i * channels_in_file * img_width + channels_in_file * j  + 1] + 
                 image[i * channels_in_file * img_width + channels_in_file * j  + 2]) / 3;
      int val = avg * (levels-1) / 255.0;
      char x = c[val];
      fprintf(stdout, "%c", x);
    }
    fprintf(stdout, "\n");
  }

  return 0;
}

