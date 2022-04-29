#include <stdio.h>

#define MSG "I am a symbolic string constant."
#define MAXLENGTH 81

int main(void) {

    char words[MAXLENGTH] = "I am a string in an array.";
    const char * pt1 = "Something is pointing at me.";

    /* puts()
     * Just like printf(), this belongs to the stdio.h family of input/output functions. It only displays strings,
     * and unlike printf(), it automatically appends a newline to the string it displays.
     */
    puts("Here are some strings:");
    puts(MSG);
    puts(words);
    puts(pt1);
    words[8] = 'p';
    puts(words);

    return 0;
}
