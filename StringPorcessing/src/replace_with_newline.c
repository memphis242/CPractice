/* **********************************************************************************************
 * PURPOSE: I want to use this program in the form: echo <env_variable> | replace_with_newline.exe
 *          and do something like replace all occurences of ';' /w a newline. This is
 *          helpful for printing $PATH for example, because by default, the lsit is only ';'
 *          separated instead of newline separated, making it very hard to read!
 *          Basically just like echo but replacing ';' with newlines.
 * 
 * AUTHOR: Abdullah Almosalami
 * *********************************************************************************************/

#include <stdio.h>


int main( int argc, char * argv[] )
{
    // Insert a newline just to put an extra space between command and output
    fputc('\n', stdout);

    char ch_input;

    while ( ( ch_input = fgetc(stdin) ) != EOF  )
    {
        if ( ch_input != ';' )  fputc(ch_input, stdout);
        else    fputc('\n', stdout);
    }
}	
