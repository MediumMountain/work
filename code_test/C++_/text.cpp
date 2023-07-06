/* 画面に何か表示するプログラム */
#include <stdio.h>
int main(void)
{
	// char text[] = {"aaaa\n"
	// 	"bbbb\n"
	// 	"cccc"};

    const char *text = R"(
        precision mediump float;
        void main() {
            gl_FragColor = vec4(0.3, 0.8, 0.3, 1.0);
        }
    )";

	printf("%s\n", text);
	// printf("%s\n", text);
	return 0;
}