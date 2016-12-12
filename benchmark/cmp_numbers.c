#include <stdlib.h>
#include <stdio.h>

main(int argc, char *argv[]) {
	if(argc != 3)
		return EXIT_FAILURE;
	FILE
		*first = fopen(argv[1], "r"),
		*second = fopen(argv[2], "r");
	if(first == NULL || second == NULL) {
		if(first == NULL)
			fprintf(stderr, "error: could not open file %s\n", argv[1]);
		else if(second == NULL)
			fprintf(stderr, "error: could not open file %s\n", argv[2]);

		if(first != NULL)
			fclose(first);
		if(second != NULL)
			fclose(second);

		return EXIT_FAILURE;
	}

	char f, s;
	size_t len = 0;
	while((f = fgetc(first)) != EOF && (s = fgetc(second)) != EOF)
		if(f == s) {
			fputc(f, stdout);
			++len;
		}
		else
			break;
	printf("%lu\n", len);

	fclose(first);
	fclose(second);
}
