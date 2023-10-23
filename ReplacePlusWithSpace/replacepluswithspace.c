#include <stdio.h>
#include <stdbool.h>

#define STRING_MAX_SIZE 150
 
int main(int argc, char *argv[])
{
   char * myFileName;
   bool isIndexAPlus[STRING_MAX_SIZE] =   { 
                                          false, false, false, false, false, false, false, false, false, false,
                                          false, false, false, false, false, false, false, false, false, false,
                                          false, false, false, false, false, false, false, false, false, false,
                                          false, false, false, false, false, false, false, false, false, false,
                                          false, false, false, false, false, false, false, false, false, false,
                                          false, false, false, false, false, false, false, false, false, false,
                                          false, false, false, false, false, false, false, false, false, false,
                                          false, false, false, false, false, false, false, false, false, false,
                                          false, false, false, false, false, false, false, false, false, false,
                                          false, false, false, false, false, false, false, false, false, false,
                                          false, false, false, false, false, false, false, false, false, false,
                                          false, false, false, false, false, false, false, false, false, false,
                                          false, false, false, false, false, false, false, false, false, false,
                                          false, false, false, false, false, false, false, false, false, false,
                                          false, false, false, false, false, false, false, false, false, false,
                                          };
   char newFileName[STRING_MAX_SIZE + 1];
   int ret = 1;

   // Read in file-name argument
   myFileName = argv[1];

   // Find all the pluses
   for ( unsigned int i=0; i<STRING_MAX_SIZE; i++ )
   {
      if ( myFileName[i] == '+' )
      {
         isIndexAPlus[i] = true;
      }
   }

   // Create new string with pluses replaced by spaces
   for ( unsigned int i=0; i<STRING_MAX_SIZE; i++ )
   {
      if ( isIndexAPlus[i] == true )
      {
         newFileName[i] = ' ';
      }
      else
      {
         newFileName[i] = myFileName[i];
      }
   }
   newFileName[STRING_MAX_SIZE + 1] = '\0';

   // Replace filename
   ret = rename( myFileName, newFileName );
   if ( ret == 0 )
   {
      printf("File name changed successfully.");
   }
   else
   {
      printf("FAILED to rename file.");
   }
}