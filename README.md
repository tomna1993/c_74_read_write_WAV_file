# c_74_read_write_WAV_file

## DESCRIPTION

Read and write WAV audio file's information. Change the audio volume and save the new audio file.

[Informations about WAV file structure](https://en.wikipedia.org/wiki/WAV)

### IMPLEMENTATION DETAILS

- The program accepts three command-line arguments: 
  - `input` represents the name of the original audio file, 
  - `output` represents the name of the new audio file that should be generated,
  - `factor` is the amount by which the volume of the original audio file should be scaled. For example, if factor is 2.0, then your program should double the volume of the audio file in input and save the newly generated audio file in output.

- Make sure the file is a WAV audio file.

- Create a structure to save all the WAV header infromation.

- Read in all the WAV header information and print them on screen.

- Change the volume of the original audio file with factor.

- Save the audio file as `output.wav`.
