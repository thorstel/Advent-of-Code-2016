#include <stdio.h>
#include <stdlib.h>

void dragon_checksum(const char *init, int len)
{
	int i, j, n;
	int *data = malloc(len * sizeof(int));

	for (i = 0; init[i] != '\0'; ++i)
		data[i] = init[i] - '0';
	for (j = -1; i < len; ++i) {
		if (j < 0) {
			data[i] = 0;
			j = i - 1;
		} else {
			data[i] = !data[j--];
		}
	}

	for (i = 0, j = len; (j % 2) == 0; j /= 2, ++i);
	n = 1 << i;
	for (i = 0; i < len;) {
		int cnt = 0;
		for (j = 0; j < n; ++j, ++i)
			cnt += data[i];
		putchar(cnt % 2 == 0 ? '1' : '0');
	}
	putchar('\n');

	free(data);
}

int main(int argc, const char *argv[])
{
	const char *input = "00111101111101000";
	const char *init;
	if (argc > 1)
		init = argv[1];
	else
		init = input;
	dragon_checksum(init, 272);
	dragon_checksum(init, 35651584);
	return 0;
}
