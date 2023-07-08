#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARGV_LENGTH 100
#define MAX_CHARS_LENGTH 10

typedef struct wav_header
{
    // “RIFF” (4 byte) - Marks the file as a riff file. 
    // Characters are each 1 byte long.
    char RIFF[MAX_CHARS_LENGTH];
    
    // File size in bytes (32-bit integer). 
    // Typically, you’d fill this in after creation.
    __int32 File_size;

    // “WAVE” (4 bytes) - File Type Header. For our purposes, it always equals “WAVE”.
    char File_type_header[MAX_CHARS_LENGTH];

    // “fmt " (4 bytes) - Format chunk marker. Includes trailing null
    char fmt[MAX_CHARS_LENGTH];

    // Length of format data / Chunk size: 16, 18 or 40
    __int32 Format_data_length;

    // Type of format (1 is PCM) - 2 byte integer
    __int16 Format_type;

    // Number of Channels - 2 byte integer 
    __int16 Num_of_channels;

    // Sample Rate - 32 byte integer. Common values are 44100 (CD), 48000 (DAT). 
    //Sample Rate = Number of Samples per second, or Hertz.
    __int32 Sample_rate;

    // Data rate = (Sample Rate * BitsPerSample * Channels) / 8; AvgBytesPerSec
    __int32 Data_rate;

    // Data block size (bytes) = (BitsPerSample * Channels) / 8
    __int16 Data_block_size;

    // Bits per sample
    __int16 Bits_per_sample;

    // “data” (4 bytes) chunk header. Marks the beginning of the data section.
    char Data[MAX_CHARS_LENGTH];

    // Size of the data section.
    __int32 Data_size;

    // Valid header - not in WAV header
    bool Is_Valid_WAV_header;
} 
wav_header;  


wav_header func_read_WAV_header(char file_name[MAX_ARGV_LENGTH]);
void func_print_WAV_header(wav_header WAV_head);


int main(int argc, char **argv)
{
    if (argc != 4)
    {
        printf ("Usage: <program> <input> <output> <factor>\n");
        return EXIT_FAILURE;
    }

    char input[MAX_ARGV_LENGTH] = { "" };
    char output[MAX_ARGV_LENGTH] = { "" };
    char factor[MAX_ARGV_LENGTH] = { "" };

    strcpy_s (input, MAX_ARGV_LENGTH, argv[1]);
    strcpy_s (output, MAX_ARGV_LENGTH, argv[2]);
    strcpy_s (factor, MAX_ARGV_LENGTH, argv[3]);

    wav_header WAV_head = func_read_WAV_header(input);

    if (WAV_head.Is_Valid_WAV_header == false)
    {
        printf ("Can't read WAV file's header!\n");
        return EXIT_FAILURE;
    }

    func_print_WAV_header(WAV_head);

    return EXIT_SUCCESS;
}


wav_header func_read_WAV_header(char file_name[MAX_ARGV_LENGTH])
{
    wav_header WAV_head = { 0 };

    // Open audio file
    FILE *fp = fopen(file_name, "rb");

    if (fp == NULL)
    {
        printf ("File cannot be opened!\n");
        WAV_head.Is_Valid_WAV_header = false;
        return WAV_head;
    }

    // “RIFF” (4 byte) - Marks the file as a riff file.
    fread (&WAV_head.RIFF, sizeof(char), 4, fp);

    // File size in bytes (32-bit integer).
    fread (&WAV_head.File_size, sizeof(__int32), 1, fp);

    // “WAVE” (4 bytes) - File Type Header. 
    // For our purposes, it always equals “WAVE”.
    fread (&WAV_head.File_type_header, sizeof(char), 4, fp);

    // “fmt " (4 bytes) - Format chunk marker. Includes trailing null
    fread (&WAV_head.fmt, sizeof(char), 4, fp);

    // Length of format data / Chunk size: 16, 18 or 40
    fread (&WAV_head.Format_data_length, sizeof(__int32), 1, fp);

    // Type of format (1 is PCM) - 2 byte integer
    fread (&WAV_head.Format_type, sizeof(__int16), 1, fp);

    // Number of Channels - 2 byte integer 
    fread (&WAV_head.Num_of_channels, sizeof(__int16), 1, fp);

    // Sample Rate - 32 byte integer. Common values are 44100 (CD), 48000 (DAT). 
    //Sample Rate = Number of Samples per second, or Hertz.
    fread (&WAV_head.Sample_rate, sizeof(__int32), 1, fp);

    // Data rate = (Sample Rate * BitsPerSample * Channels) / 8; AvgBytesPerSec
    fread (&WAV_head.Data_rate, sizeof(__int32), 1, fp);

    // Data block size (bytes) = (BitsPerSample * Channels) / 8
    fread (&WAV_head.Data_block_size, sizeof(__int16), 1, fp);

    // Bits per sample
    fread (&WAV_head.Bits_per_sample, sizeof(__int16), 1, fp);

    // “data” (4 bytes) chunk header. Marks the beginning of the data section.
    fread (&WAV_head.Data, sizeof(char), 4, fp);

    // Size of the data section.
    fread (&WAV_head.Data_size, sizeof(__int32), 1, fp);

    fclose(fp);

    WAV_head.Is_Valid_WAV_header = true;

    return WAV_head;
}

void func_print_WAV_header(wav_header WAV_head)
{
    // “RIFF” (4 byte) - Marks the file as a riff file.
    printf ("File format is %s\n", WAV_head.RIFF);

    // File size in bytes (32-bit integer).
    printf ("File size: %i\n", WAV_head.File_size);

    // “WAVE” (4 bytes) - File Type Header. 
    // For our purposes, it always equals “WAVE”.
    printf ("File type is %s\n", WAV_head.File_type_header);

    // “fmt " (4 bytes) - Format chunk marker. Includes trailing null
    printf ("Format chunk marker: %s\n", WAV_head.fmt);

    // Length of format data / Chunk size: 16, 18 or 40
    printf ("Length of format data: %i\n", WAV_head.Format_data_length);

    // Type of format (1 is PCM) - 2 byte integer
    printf ("Type of format: %i\n", WAV_head.Format_type);

    // Number of Channels - 2 byte integer 
    printf ("Number of Channels: %i\n", WAV_head.Num_of_channels);

    // Sample Rate - 32 byte integer. Common values are 44100 (CD), 48000 (DAT). 
    //Sample Rate = Number of Samples per second, or Hertz.
    printf ("Sample Rate: %i\n", WAV_head.Sample_rate);

    // Data rate = (Sample Rate * BitsPerSample * Channels) / 8; AvgBytesPerSec
    printf ("Data rate: %i\n", WAV_head.Data_rate);

    // Data block size (bytes) = (BitsPerSample * Channels) / 8
    printf ("Data block size: %i\n", WAV_head.Data_block_size);

    // Bits per sample
    printf ("Bits per sample: %i\n", WAV_head.Bits_per_sample);

    // “data” (4 bytes) chunk header. Marks the beginning of the data section.
    printf ("Data chunk header: %s\n", WAV_head.Data);

    // Size of the data section.
    printf ("Size of the data section: %i\n", WAV_head.Data_size);
}