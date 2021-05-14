/*
 * string_operations.h
 *
 *  Created on: 30-Oct-2020
 *      Author: rakshita.parihar
 */

#ifndef STRING_OPERATIONS_H_
#define STRING_OPERATIONS_H_

int convert_integer_to_char(int num, char *str);
int convert_negative_int_to_char(int num, char *str, int length);
int convert_char_to_integer_buff(char* string, int* ptr, int length);
int convert_char_to_integer(char* string, int* ptr, int length);

int str_comp_count(char* Sorce_Ram_address, char* Destination_Ram_address,int length);
//int str_comp_dilimetr(char* Source_Ram_address,char* Destination_Ram_address,char dili,int length);
void str_copy_delmt(char* Source_Ram_address, char* Destination_Ram_address,char dili);
int str_comp_dilli_n_len(char* Source_Ram_address, char* Destination_Ram_address,char dili, int length);
int str_comp_dilimetr(char* Source_Ram_address,char* Destination_Ram_address,char dili);
int count_intlength(int num);

#endif /* STRING_OPERATIONS_H_ */
