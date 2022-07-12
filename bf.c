#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void executeProgram(unsigned char* program, unsigned long programSize) {
  int programCounter = 0;
  unsigned char pointer = 0;
  unsigned char tape[255] = {0};

  while (programCounter < programSize) {
    unsigned char instruction = program[programCounter];

    switch (instruction) {
    case '>': {
      pointer++;
      break;
    }

    case '<': {
      pointer--;
      break;
    }

    case '+': {
      tape[pointer]++;
      break;
    }

    case '-': {
      tape[pointer]--;
      break;
    }

    case '.': {
      printf("%c", tape[pointer]);
      break;
    }

    case ':': {
      printf("%d", tape[pointer]);
      break;
    }

    case ',': {
      printf("BF Program Requests Input: ");
      scanf("%c", &tape[pointer]);
      break;
    }

    case '[': {
      if (tape[pointer])
        break;

      int opened = 0;

      while (1) {
        programCounter++;

        unsigned char instruction = program[programCounter];

        if (instruction == '[') {
          opened++;
        } else if (instruction == ']') {
          if (opened == 0)
            break;

          opened--;
        }
      }

      break;
    }

    case ']': {
      if (!tape[pointer])
        break;

      int opened = 0;

      while (1) {
        programCounter--;

        unsigned char instruction = program[programCounter];

        if (instruction == ']') {
          opened++;
        } else if (instruction == '[') {
          if (opened == 0)
            break;

          opened--;
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
  unsigned long programSize = fread(program, sizeof(char), 1024, file);

  if (ferror(file)) {
    fprintf(stderr, "ERROR: Cannot read file %s: %s\n", filePath, strerror(errno));
    exit(1);
  }

  executeProgram(program, programSize);

  return 0;
}
