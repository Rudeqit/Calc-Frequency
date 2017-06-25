#ifndef PROCESS_H
#define PROCESS_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

enum {
	OUT,
	IN
};

typedef struct word {
	char name_word[50];
	int count;
} word;

uint32_t calc_bsize(FILE* in);

uint32_t calc_word(char *string);

char *buffer_init(FILE* in, uint32_t b_size);

void write_files(const char *out_file_name, uint32_t words_num, word *box);

char *open_files(const char *in_file_name);

void filling_box(word *box, char *buffer, uint32_t words_num);

int process(const char *in_file_name, const char *out_file_name);

#endif
