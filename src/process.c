#include "process.h"

uint32_t calc_bsize(FILE* in)
{
	fseek(in, 0, SEEK_END);
	uint32_t b_size = ftell(in);
	rewind(in);

	return b_size;
}

uint32_t calc_word(char* string)
{
	int state = OUT;
	uint32_t words_num = 0;

	for (int i = 0; string[i] != '\0'; i++) {
		if (string[i] == ' ' || string[i] == '\n'
			/*|| string[i] == '-'*/ || string[i] == '\r') {
			state = OUT;
		} else if (state == OUT) {
			state = IN;
			++words_num;
		}
	}

	return words_num;
}

char *buffer_init(FILE* in, uint32_t b_size)
{
	char *buffer = (char*)malloc(sizeof(char) * b_size);

	if (buffer == NULL) {
		printf("ERROR 2");
//		return -1;
	}

	fread(buffer, 1, b_size, in);

//	puts(buffer);
	printf("THE NUMBER BYTE: %u\n", b_size);

	return buffer;
}

void write_files(const char *out_file_name, uint32_t words_num, word *box)
{
	FILE *out = fopen(out_file_name, "w+");

	if (out == NULL) {
		printf("ERROR 3");
//		return -1;
	}

	for(int i = 0; i <= words_num - 1; i++) {
		if(box[i].count >= 2) {
			fputs(box[i].name_word, out);
			fprintf(out, " - %d\n", box[i].count);
		}
	}

	fclose(out);
}

char *open_files(const char *in_file_name)
{
	FILE *in = fopen(in_file_name, "rt");

	if (in == NULL) {
		printf("ERROR 1");
//		return -1;
	}

	uint32_t b_size = calc_bsize(in);
	char* buffer = buffer_init(in, b_size);

	fclose(in);

	return buffer;
}
/*
void filling_box(word *box, char *buffer, uint32_t words_num)
{
	uint32_t words_count;
	int i = 0;

	while(buffer[i] != '\0') {
		if(buffer[i] != ' ' || buffer[i] != '\n' || buffer[i] != ',' || buffer[i] != '.') {	
		
}
*/
int process(const char *in_file_name, const char *out_file_name)
{
	char *buffer = open_files(in_file_name);

	uint32_t words_num = calc_word(buffer);
	word *box = (word*)malloc(sizeof(word) * words_num);
	memset(box, 0, sizeof(word) * words_num);

	printf("THE NUMBER WORDS: %u\n", words_num);

//	filling_box(box, buffer, words_num);

	write_files(out_file_name, words_num, box);

	free(buffer);

	return 0;
}
