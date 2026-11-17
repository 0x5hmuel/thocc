#include "linux/input_headers.h"
#include <cstdio>
#include <fcntl.h>
#include <miniaudio.h>
#include <stdlib.h>

void play_audio(void) {
  const char *audio_file =
      "/home/_5hmuel/Downloads/apex-pro-tkl-v2_Akira/key1.wav";

  FILE *file;
  size_t bytes_read;
  long size;

  file = fopen(audio_file, "rb");

  if (file == NULL) {
    perror("Failed to read audio file");
    return;
  }

  if (fseek(file, 0, SEEK_END) == -1) {
    perror("Error while reading audio file.");
  }

  size = ftell(file); // Get the size of the file
  rewind(file);       // Move the pointer to the start of the file

  unsigned char *buf = malloc(bytes_read);

  if (buf == NULL) {
    perror("Unable to allocate buffer");
    return;
  }

  bytes_read = fread(buf, 1, size, file);
  fclose(file);

  // I have not allocate memory for it??
  // Seek till the end to know the full number of bytes
}
