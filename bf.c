#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INS_INC_POINTER 62
#define INS_DEC_POINTER 60
#define INS_INC_CELL 43
#define INS_DEC_CELL 45
#define INS_OUTPUT_ASCII 46
#define INS_OUTPUT_DECIMAL 58
#define INS_INPUT 44
#define INS_JUMP_FORWARD 91
#define INS_JUMP_BACK 93

void executeProgram(unsigned char* program, unsigned long programSize) {
  unsigned int programCounter = 0;
  unsigned int pointer = 0;
  unsigned int tape[255] = {0};

  while (programCounter < programSize) {
    unsigned char instruction = program[programCounter];

    switch (instruction) {
    case INS_INC_POINTER: {
      pointer++;
      break;
    }

    case INS_DEC_POINTER: {
      pointer--;
      break;
    }

    case INS_INC_CELL: {
      tape[pointer]++;
      break;
    }

    case INS_DEC_CELL: {
      tape[pointer]--;
      break;
    }

    case INS_OUTPUT_ASCII: {
      fprintf(stdout, "%c", tape[pointer]);
      break;
    }

    case INS_OUTPUT_DECIMAL: {
      fprintf(stdout, "%d", tape[pointer]);
      break;
    }

    case INS_INPUT: {
      unsigned char input;
      fprintf(stdout, "BF Program Requests Input: ");
      fscanf(stdin, "%c", &input);
      tape[pointer] = input;
      break;
    }

    case INS_JUMP_FORWARD: {
      if (tape[pointer]) {
        break;
      }

      unsigned int opened = 0;
      while (1) {
        programCounter++;
        unsigned char instruction = program[programCounter];
        if (instruction == INS_JUMP_FORWARD) {
          opened++;
        } else if (instruction == INS_JUMP_BACK) {
          if (!opened) {
            break;
          }
          opened--;
        }
      }
      break;
    }

    case INS_JUMP_BACK: {
      if (!tape[pointer]) {
        break;
      }

      unsigned int closed = 0;
      while (1) {
        programCounter--;
        unsigned char instruction = program[programCounter];
        if (instruction == INS_JUMP_BACK) {
          closed++;
        } else if (instruction == INS_JUMP_FORWARD) {
          if (!closed) {
            break;
          }
          closed--;
        }
      }
      break;
    }
    }

    programCounter++;
  }
}

int main(int argc, char** argv) {
  if (argc < 2) {
    fprintf(stderr, "ERROR: Please provide a file path\n");
    exit(1);
  }

  char* filePath = argv[1];
  FILE* file = fopen(filePath, "rb");

  if (file == NULL) {
    fprintf(stderr, "ERROR: Cannot read file %s: %s\n", filePath, strerror(errno));
    exit(1);
  }

  unsigned char program[1024];
  unsigned long programSize = fread(program, sizeof(unsigned char), 1024, file);

  if (ferror(file)) {
    fprintf(stderr, "ERROR: Cannot read file %s: %s\n", filePath, strerror(errno));
    exit(1);
  }

  executeProgram(program, programSize);

  return 0;
}
