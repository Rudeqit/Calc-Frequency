#include "process.h"

void print_usage()
{
	printf("Используйте следующую форму:\n"
		"./calcFrequency <in-file-name> <out-file-name>\n");
}

int main(int argc, char *argv[])
{
	if (argc != 3) {
		print_usage();
		return -1;
	} else {
		process(argv[1], argv[2]);
	}

	return 0;
}
