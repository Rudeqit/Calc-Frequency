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
		if (string[i] == ' ' || string[i] == '\n' || string[i] == '\r') {
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

	fread(buffer, 1, b_size, in);
	buffer[b_size] = 0;

	return buffer;
}

int write_files(const char *out_file_name, uint32_t words_num, word *box)
{
	FILE *out = fopen(out_file_name, "w+");

	for(int i = 0; i <= words_num - 1; i++) {
		if(box[i].count >= 2) {
			fputs(box[i].name_word, out);
			fprintf(out, " - %d\n", box[i].count);
		}
	}

	if(calc_bsize(out) == 0) {
		return 1;
	}

	fclose(out);
	return 0;
}

char *open_files(const char *in_file_name)
{
	FILE *in = fopen(in_file_name, "rt");

	if(in == NULL) {
		return '\0';
	}

	uint32_t b_size = calc_bsize(in);
	char* buffer = buffer_init(in, b_size);

	fclose(in);

	return buffer;
}

void sort_box(word *box, uint32_t box_count)
{
	int flag = 0;
	while(!flag) {
		flag = 1;
		for(int j = 0; j < box_count - 1; j++) {
			if (box[j].count < box[j + 1].count) {
				word tmp_word;
				strcpy(tmp_word.name_word, box[j].name_word);
				tmp_word.count = box[j].count;
				strcpy(box[j].name_word, box[j + 1].name_word);
				box[j].count = box[j + 1].count;
				strcpy(box[j + 1].name_word, tmp_word.name_word);
				box[j + 1].count = tmp_word.count;
				flag = 0;
			}
		}
	}
}

void filling_box(word *box, char *buffer)
{
	char *pointer_to_word = strtok(buffer, " \n,.");
	uint32_t box_count = 0;

	while(pointer_to_word != NULL) {
		int flag = 1;
		for(int j = 0; j < box_count; j++ ) {
			if (strcmp(box[j].name_word, pointer_to_word) == 0) {
				box[j].count++;
				flag = 0;
				break;
			}
		}
		if (flag) {
			strcpy(box[box_count].name_word, pointer_to_word);
			box[box_count].count = 1;
			box_count++;
		}
		pointer_to_word = strtok(NULL, " \n,.");
	}

	sort_box(box, box_count);
}

int process(const char *in_file_name, const char *out_file_name)
{
	char *buffer = open_files(in_file_name);
	if(buffer[0] == '\0') {
		printf("Ошибка! Входной файл пуст.\n");
		return -1;
	}

	uint32_t words_num = calc_word(buffer);
	word *box = (word*)malloc(sizeof(word) * words_num);
	memset(box, 0, sizeof(word) * words_num);

	filling_box(box, buffer);

	write_files(out_file_name, words_num, box);
	if(write_files(out_file_name, words_num, box)) {
		printf("Повторяющихся слов не найдно.\n");
		return -1;
	}

	printf("Запись прошла успешно.\n");

	free(buffer);
	free(box);

	return 0;
}
