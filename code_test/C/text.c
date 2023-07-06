/* 画面に何か表示するプログラム */
#include <stdio.h>
int main(void)
{
	int size=0;
	char text[] = {"aaaa    \n"
		"bbbb\n"
		"cccc"};

	printf("%s\n", text);

	size = sizeof(text);

	printf("size = %d\n", size);
	return 0;
}