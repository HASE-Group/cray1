// Project Cray 1
// global functions header file
#include <ctype.h>
#include <string.h>
#include <stdio.h>

class memory;
class a_registers;
class b_registers;
class s_registers;
class t_registers;
class v_registers;
class p_register;
class s_pop_u;
class cip;
class nip;
class lip;
class scoreboard;

int mod4(int number);

int char_to_hex(char c);

char hex_to_char(int i);

void int_to_string24(int i, t_twentyfour_bit string);

int string_to_hex(char* str, int length);

long int string_to_long(char* str, int length);

int char_less_than_int(char c, int i);

int char_grtr_than_int(char c, int i);

void increment_char(char &c);

void increment_hex_string(char *str, int i);

char hex_complement(char c);

void a_complement(char* number);

void s_complement(char* number);

int string_to_int(char* str, int length);

char add_hex_digits(char a, char b, int& overflow);

void create_22bit( char* str24, char* str22);
  
void create_64bit( char* str24, char* str64);

void increment_20bit( char* str20);

void add_addresses( char* op2, char* op1);     // adds 2nd address to first.

void add_strings( char* op2, char* op1, char* ans, int length);

void ones_mask(char* str64, int count);

int Pop_count(char* str64);

int ldg_0_count(char* str64);

void shift_left(char* op, char* ans, int places);

void shift_right(char* op, char* ans, int places);

void shift_2_left(char* op1, char* op2, char* ans, int places);

void shift_2_right(char* op1, char* op2, char* ans, int places);
/*
void and(char* op1, char* op2, char* ans);

void or(char* op1, char* op2, char* ans);

void xor(char* op1, char* op2, char* ans);
*/
void l_and(char* op1, char* op2, char* ans);

void l_or(char* op1, char* op2, char* ans);

void l_xor(char* op1, char* op2, char* ans);

void s_merge(char* si, char* sj,char* sk, char* ans);

void add_float(char* op1, char* op2, char* ans);

int find_expon(char* exp);

void sub_float(char* op1, char* op2, char* ans);

void recip_float(char* op1, char* ans);

void mult_float(char* op1, char* op2, char* ans);

void create_float(int sign, long int coeff, int exp, char* ans);

void Double_to_string(double f, char* ans);

void String_to_double(char* str, double d);
