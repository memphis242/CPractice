#ifndef CH11_H_INCLUDED
#define CH11_H_INCLUDED

char* get_string_input(char* str, int size_of_str);

//char* trim_string(char* str);     //NEEDS WORK

void trim_string_to_size(char* str, int desired_size);

char* str_safe_conc(char* str1, const char* str2, int size_of_1);

void sort_str_alph(char* strings[], int num_of_strings);    //Uses array of pointers to strings because that is much easier to sort; if one element needs to be switched, just reassign pointers.

#endif // CH11_H_INCLUDED
