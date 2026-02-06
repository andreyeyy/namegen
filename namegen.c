#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <stdbool.h>

// ======== CONFIGURATION ==========

const unsigned int MIN_LENGTH = 5;
const unsigned int MAX_LENGTH = 5;
const unsigned int MAX_CONSECUTIVE_LETTERS = 2;
const unsigned int MAX_CONSECUTIVE_NUMBERS = 1;


/* ==== NAME GENERATION RULE SET ==== 

1. The name consists of only lowercase letters and numbers
2. The first character is a letter
3. At most 2 letters can be next to each other
4. No two numbers can be next to each other

==================================== */

// returns a random lowercase letter
static inline char rand_letter() {
  return (rand() % 26) + 97;
}

// returns a random number 0-9
static inline char rand_number() {
  return (rand() % 10) + 48;
}

void gen_name() {

  putchar(rand_letter());

  unsigned int length_left = MIN_LENGTH + (rand() % (MAX_LENGTH - MIN_LENGTH + 1)) - 1;
  
  unsigned int consec_nums = 0;
  unsigned int consec_letters = 1;

  while (length_left != 0) {

    bool coin_toss = rand() % 2;

    if (consec_nums >= MAX_CONSECUTIVE_NUMBERS) {
      putchar(rand_letter());
      consec_letters = 1;
      consec_nums = 0;
    }
    else if (consec_letters >= MAX_CONSECUTIVE_LETTERS) {
      putchar(rand_number());
      consec_nums = 1;
      consec_letters = 0;
    }
    else if (coin_toss) {
      putchar(rand_letter());
      consec_letters += 1;
      consec_nums = 0;
    }
    else {
      putchar(rand_number());
      consec_nums += 1;
      consec_letters = 0;
    }

    length_left -= 1;
  }

  putchar('\n');
  fflush(stdout);
}

int main(int argc, char *argv[]) {
  int x;
  srand((unsigned)(time(NULL) ^ clock() ^ (uintptr_t)&x)); // random seed

  int num_names = 1;

  if (argc > 2) {
    fprintf(stderr, "Too many arguments. Usage:\nnamegen\t\tgenerates one random name\nnamegen n\tgenerates n random names\n");
    return 1;
  }
  if (argc > 1) {
    num_names = atoi(argv[1]);
    if (num_names < 1) {
      fprintf(stderr, "Invalid argument: %s\n", argv[1]);
      return 1;
    } 
  }

  for (int i = 0; i < num_names; i++)
  gen_name();
}
