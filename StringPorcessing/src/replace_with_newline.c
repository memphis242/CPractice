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
#include <stdint.h>


enum Shell_Type_E
{
    WINDOWS_CMD,
    CYGWIN,
    GIT_BASH
};


int main( int argc, char * argv[] )
{
    // Insert a newline just to put an extra space between command and output
    fputc('\n', stdout);

    // Check whether type of bash is passed in as an argument in argv
    enum Shell_Type_E type_of_shell = WINDOWS_CMD; 
    // Now depending on the type of shell, the character used to delimit entries
    // in the env variable differ I believe. For cmd, it's ';', while for cygwin,
    // it's ':'. Let's designate that type at runtime.
    char delimiter = ';';
    if ( argc >= 2 )
    {
        switch ( argv[1][0] )
        {
            case 'w':
                type_of_shell = WINDOWS_CMD;
                delimiter = ';';
                break;

            case 'c':
                type_of_shell = CYGWIN;
                delimiter = ':';
                break;

            case 'g':
                type_of_shell = GIT_BASH;
                delimiter = ':';
                break;

            default:
                type_of_shell = WINDOWS_CMD;
                delimiter = ';';
        }
    }


    // Now get the standard input!
    char ch_input;
    while ( ( ch_input = fgetc(stdin) ) != EOF  )
    {
        if ( ch_input != delimiter )  fputc(ch_input, stdout);
        else    fputc('\n', stdout);
    }
}	
