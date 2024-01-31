#include "global_fns.h"
// global functions implementation

int mod4(int number)
{
  while ( (number>= 4) || (number < 0)) 
    if (number>= 4) number -=4;
    else number +=4;

  return number;
}

int char_to_hex(char c)
{
  int i;
  if ( ('0' <= c)&&(c <= '9')) i = c - '0';
  else i = c - 'A' +10;
 // printf( " char_to_hex: char = %c, hex = %d \n", c, i );
  return i;
}

char hex_to_char(int i)
{
  char c;
  if ( i < 10) c = (char)i + '0';
  else c = ((char)i - 10) + 'A' ;
  return c;
}

//void int_to_string(int int_value, char* str)
void int_to_string24(int int_value, t_twentyfour_bit string)
{
  strcpy (string.s6, "000000");
  for (int j=0; j<6; j++)
    {
      string.s6[5-j] = hex_to_char(int_value & 15);
      int_value = int_value >> 4;
    }
  printf("GloFn: string = %s \n", string.s6);
}

int string_to_hex(char* str, int length)
{
  int i=0;
  int power=1;
  for (int j=length; j>0; j--)
    {
      i+=char_to_hex(str[j-1])*power;
      power = power*16;
    }
  return i;
}

int char_less_than_int(char c, int i)
{
  if ( char_to_hex(c) < i)
    return 1;
  else 
    return 0;
}

int char_grtr_than_int(char c, int i)
{
  if ( char_to_hex(c) > i)
    return 1;
  else 
    return 0;
}

void increment_char(char &c)
{
  //  if ( char_to_hex(c) != 10) c++; //no overflow check
  if ( char_to_hex(c) != 9) c++; //no overflow check
  else c = 'A';

}

//takes a hexadecimal number of length L and increments it.
void increment_hex_string(char *str, int L)
{
  if (char_less_than_int( str[L-1] , 15 )) 
    increment_char(str[L-1]); 
  else
    {
      str[L-1] = '0';
      if (L > 1)
	increment_hex_string(str, L-1);
    }
}

//takes a hexadecimal digit and returns its complement
char hex_complement(char c)
{
  int temp, value, new_value=0, power_of_2=1;
  value = char_to_hex(c);
  for (int i =1; i<4 ; i++)
    {
      temp = value % (power_of_2 *2);
      if (temp)
	value = value - power_of_2;
      else
	new_value = new_value + power_of_2;
      power_of_2= power_of_2*2;
    }
  if (value==0)
    new_value +=8;

  return hex_to_char(new_value);
}

//takes a 24-bit number in hexadecimal form and finds its complement
void a_complement(char* number)
{
    for (int i =0; i<6; i++)    // 6 digits
    {
        char value = number[i];
        number[i] = hex_complement(value);
    }
}

//takes a 64-bit number in hexadecimal form and finds its complement
void s_complement(char* number)
{
    for (int i =0; i<16; i++)      //16 digits
    {
        char value = number[i];
        number[i]= hex_complement(value);
    } 
}

int string_to_int(char* str, int length)
{
    size_t uSize = strlen( str );
    if( uSize == 0 )
    {
        printf( "Warning - string_to_int called with string of length zero!\n" );
        return 0;
    }
    if( uSize < length )
    {
        printf( "Warning - string_to_int called with shorter string than expected!\n" );
        length = (int)uSize;
    }
    int sign = 0;
    if (char_to_hex(str[0]) > 7)
    {
        a_complement(str);
        sign = 1;
    }
    int i = 0;
    int power = 1;
    for (int j=length; j>0; j--)
    {
        i += char_to_hex(str[j-1])*power;
        power = power*16;
    }
    if (sign == 1)
    {
        i = i + 1; // Add 1 because hex complement result is 1's complement
        i = -i;
        a_complement(str); // restore str to original value
    }
    return i;
}

long int string_to_long(char* str, int length)
{
    size_t uSize = strlen( str );
    if( uSize == 0 )
    {
        printf( "Warning - string_to_long called with string of length zero!\n" );
        return 0;
    }
    if( uSize < length )
    {
        printf( "Warning - string_to_long called with shorter string than expected!\n" );
        length = (int)uSize;
    }
    int sign = 0;
    if (char_to_hex(str[0]) > 7)
    {
        s_complement(str);
        sign = 1;
    }
    long int i = 0;
    int power = 1;
    for (int j=length; j>0; j--)
    {
        i += char_to_hex(str[j-1])*power;
        power = power*16;
    }
    if (sign == 1)
    {
        i = i + 1; // Add 1 because hex complement result is 1's complement
        i = -i;
        s_complement(str); // restore str to original value
    }
    return i;
}

char add_hex_digits(char a, char b, int& overflow)
{
// adds a, b and overflow. Returns result and new overflow (if any)
  int temp = (char_to_hex(a) + char_to_hex(b)) + overflow;
  overflow = temp/16;
  return hex_to_char(temp%16);
}


void create_22bit( char* str24, char* str22)
{
  strcpy(str22, "000000");
   str22[5] = hex_to_char( char_to_hex(str24[5])%4 );
   for (int i =0; i<5; i++)
	str22[i]= hex_to_char( ( char_to_hex(str24[i])%4)*4 
				+ char_to_hex(str24[i+1])/4 );
}

void create_64bit( char* str24, char* str64)
{
  //   for (int i =0; i<10; i++)
  //	str64[i]= '0';

  strcpy(str64, "0000000000000000");
   for ( int i =10; i<16; i++)
	str64[i]= str24[i-10];

}

void increment_20bit( char* str20)
{
   if ( char_less_than_int( str20[4], 15))
	increment_char(str20[4]);
   else
   {
     str20[4]='0';
     if ( char_less_than_int( str20[3], 15))
	increment_char(str20[3]);	  
     else
     {
       str20[3]='0';
       if ( char_less_than_int( str20[2], 15))
	    increment_char(str20[2]);
       else
       {
	 str20[2]='0';
	 if ( char_less_than_int( str20[1], 15))
	      increment_char(str20[1]);
	 else
	 {
	   str20[1]='0';
	   increment_char(str20[0]); //no overflow
	 }
       }
     }
   }
}


void add_addresses( char* op2, char* op1)
{
   int overflow = 0;
   for (int i=4; i>=0; i--)
	op2[i]=add_hex_digits( op2[i], op1[i], overflow);
}

void add_strings( char* op2, char* op1, char* ans, int length)
{
   int overflow = 0;
  strcpy(ans, "0000000000000000");
   for (int i=(length-1); i>=0; i--)
	ans[i]=add_hex_digits( op2[i], op1[i], overflow);
}

void ones_mask(char* str64, int count)
{
  //generates a mask of 64-count ones from right to left
  int temp1=count/4;
  int temp2=count-(temp1*4);
  strcpy(str64, "0000000000000000");

  if (temp2==0)
    str64[temp1]= 'F';
  if (temp2==1)
    str64[temp1]= '7';
  if (temp2==2)
    str64[temp1]= '3';
  if (temp2==3)
    str64[temp1]= '1';

  for (int i = temp1+1; i<16; i++)
    str64[i] = 'F';

}

int Pop_count(char* str64)
{
  int ans=0;
  int hex_digit;
  for(int i=0; i<16; i++)
    {
      hex_digit = char_to_hex(str64[i]);
      for ( int j =0; j<4; j++)
	{
	  if (hex_digit%2 ==1)
	    ans++;
	  hex_digit = hex_digit/2;  
	}
    }
  return ans;
}

int ldg_0_count(char* str64)
{
  int count=0;
  int ans = 0;
  while ( str64[count] == '0')
    {
      count++;
    }
  ans=count*4;
  if ( char_less_than_int(str64[count], 8))
    {
      ans++;
      if ( char_less_than_int(str64[count], 4))
	{
	  ans++;
	  if ( char_less_than_int(str64[count], 2))
	    ans++;
	}
    }
  return ans;
}

void shift_left(char* op, char* ans, int places)
{
   int shiftdigits, shift;
   int temp;
   strcpy(ans, "0000000000000000");

   places = places % 64;
   shiftdigits = places/4;
   for (int j=0; j< 16-shiftdigits; j++)
     {
       ans[j]= op[j+shiftdigits];
     }

   shift = places%4;
   while (shift)
     {
       for (int j=0; j< 16-shiftdigits; j++)
	 {
	   temp = ( char_to_hex(ans[j])*2 ) %16;
	   if ( j!=15)
	     if (char_grtr_than_int(ans[j+1], 7) )
	       temp = temp+1;
	   ans[j] = hex_to_char(temp);
	 }
       shift--;
     }
}

void shift_right(char* op, char* ans, int places)
{
   int shiftdigits, shift;
   int temp;
   strcpy(ans, "0000000000000000");

   places = places % 64;
   shiftdigits = places/4;
   for (int j=shiftdigits ; j< 16; j++)
     {
       ans[j]= op[j-shiftdigits];
     }

   shift = places%4;
   while (shift)
     {
       for (int j=15; j>=shiftdigits; j--)
	 {
	   temp = char_to_hex(ans[j])/2;
	   
	   if ( j!=0)
	       temp = temp + ( char_to_hex(ans[j-1])%2 )*8;
	   ans[j] = hex_to_char(temp);
	 }
       shift--;
     }
}

void shift_2_left(char* op1, char* op2, char* ans, int places)
{
   int shiftdigits, shift;
   int temp, next;
   char op[32];
   strcpy(ans, "0000000000000000");
   strcpy(op, op1);
   strcat(op, op2);

   places = places % 64;
   shiftdigits = places/4;
   for (int j=0; j< 16; j++)
     {
       ans[j]= op[j+shiftdigits];
     }
   next=char_to_hex(op[16+shiftdigits]);

   shift = places%4;
   while (shift)
     {
       for (int j=0; j< 16; j++)
	 {
	   temp = ( char_to_hex(ans[j])*2 ) %16;
	   if ( j!=15)
	     {
	     if (char_grtr_than_int(ans[j+1], 7) )
	       temp = temp+1;
	     }
	   else
	     if ( next> 7 )
	       temp = temp+1;
		
	   ans[j] = hex_to_char(temp);
	 }
       next = (next*2)%16;
       shift--;
     }
}
void shift_2_right(char* op1, char* op2, char* ans, int places)
{
   int shiftdigits, shift;
   int temp, next;
   char op[32];
   strcpy(ans, "0000000000000000");
   strcpy(op, op1);
   strcat(op, op2);

   places = places % 64;
   shiftdigits = places/4;
   for (int j=0 ; j< 16; j++)
     {
       ans[j]= op[j+16-shiftdigits];
     }

   next=char_to_hex(op[32-shiftdigits]);

   shift = places%4;
   while (shift)
     {
       for (int j=15; j>=0; j--)
	 {
	   temp = char_to_hex(ans[j])/2;
	   
	   if ( j!=0)
	     temp = temp + ( char_to_hex(ans[j-1])%2 )*8;
	   else
	     temp = temp + ( next %2 )*8;
	   ans[j] = hex_to_char(temp);
	 }
       next = next/2;
       shift--;
     }
}

void l_and(char* op1, char* op2, char* ans)
{
   int temp, digit1, digit2, factor;
   strcpy(ans, "0000000000000000");
   for (int i =0; i<16; i++)
     {
       temp = 0;
       digit1 = char_to_hex(op1[i]);
       digit2 = char_to_hex(op2[i]);
       factor=2;
       for (int j = 0; j<4; j++)
	 {
	   if ( (digit1 %factor >= factor/2) && (digit2 %factor >= factor/2) )
	     temp +=factor/2;
	   factor= factor*2;
	 }
       ans[i]= hex_to_char(temp);
     }
}

void l_or(char* op1, char* op2, char* ans)
{
   int temp, digit1, digit2, factor;
   strcpy(ans, "0000000000000000");
   for (int i =0; i<16; i++)
     {
       temp = 0;
       digit1 = char_to_hex(op1[i]);
       digit2 = char_to_hex(op2[i]);
       factor=2;
       for (int j = 0; j<4; j++)
	 {
	   if ( (digit1 %factor >= factor/2) || (digit2 %factor >= factor/2) )
	     temp +=factor/2;
	   factor= factor*2;
	 }
       ans[i]= hex_to_char(temp);
     }
}

void l_xor(char* op1, char* op2, char* ans)
{
   int temp, digit1, digit2, factor;
   strcpy(ans, "0000000000000000");
   for (int i =0; i<16; i++)
     {
       temp = 0;
       digit1 = char_to_hex(op1[i]);
       digit2 = char_to_hex(op2[i]);
       factor=2;
       for (int j = 0; j<4; j++)
	 {
	   if ( (digit1 %factor >= factor/2) != (digit2 %factor >= factor/2) )
	     temp +=factor/2;
	   factor= factor*2;
	 }
       ans[i]= hex_to_char(temp);
     }
}

void equiv(char* op1, char* op2, char* ans)
{
   int temp, digit1, digit2, factor;
   strcpy(ans, "0000000000000000");
   for (int i =0; i<16; i++)
     {
       temp = 0;
       digit1 = char_to_hex(op1[i]);
       digit2 = char_to_hex(op2[i]);
       factor=2;
       for (int j = 0; j<4; j++)
	 {
	   if ( (digit1 %factor >= factor/2) == (digit2 %factor >= factor/2) )
	     temp +=factor/2;
	   factor= factor*2;
	 }
       ans[i]= hex_to_char(temp);
     }
}


void s_merge(char* op1, char* op2, char* sk, char* ans)
{
   int temp, si, sj, k, result, factor;

   strcpy(ans, "0000000000000000");
   for (int i =0; i<16; i++)
     {
       k = char_to_hex(sk[i]);
       si = char_to_hex(op1[i]);
       sj = char_to_hex(op2[i]);
       if (k==0)
	 ans[i]= hex_to_char(si);
       else
	 {
	   if (k==15)
	     ans[i]= hex_to_char(sj);
	   else
	     {
	       factor=1;
	       result =0;
	       for (int j = 0; j<4; j++)
		 {
		   if ( (k %(factor*2) >= factor) )
		     temp = (sj / factor)%2;
		   else
		     temp = (si / factor)%2;

		   result +=temp*factor;
		   factor = factor*2;
		 }
	 
	       ans[i]= hex_to_char(result);
	     }
	 }
     }

}

void add2_float(char* op1, char* op2, char* ans)
{
 double d1=0.0, d2=0.0;
 String_to_double( op1, d1);
 String_to_double( op2, d2);

 Double_to_string(d1+d2, ans);
}

int find_expon(char* exp)
{
  int ans, first;
  ans = string_to_hex(exp+1,3);
  first = char_to_hex(exp[0])%8; //ignore the sign
  
  if (first%2 ==1)
    {
      first = first-1;
      ans = ans + 4096;
    }
  if (first%4 ==2)
    {
      first = first-2;
      ans = ans + 8192;
    }
  if (first == 4)
    ans = ans - 16384 ;
 
  //   16384=2^14= bias
  return ans;

}

void add_float(char* op1, char* op2, char* ans)
{
  int sign1, sign2, sign_res;
  int exp1, exp2, exp_res;
  int coeff1[48], coeff2[48], coeff_res[48];
  //  long int two_to_the_48 = 16*16*16*16;
  int count=0, element1, element2, temp;
  int overflow;

   strcpy(ans, "0000000000000000");
  if (char_grtr_than_int(op1[0], 7))
    sign1=1;
  else
    sign1=0;
  if (char_grtr_than_int(op2[0], 7))
    sign2=1;
  else
    sign2=0;
  sign_res = sign1;

  exp1 =  find_expon(op1); 
  exp2 =  find_expon(op2); 
  for (int i = 0; i<12; i++)
    {
      count = 16;
      element1 = char_to_hex(op1[4+i]);
      element2 = char_to_hex(op2[4+i]);
      for (int j = 0; j<4; j++)
	{
	  count = count/2;
	  coeff1[4*i+j] =  element1/count;
	  coeff2[4*i+j] =  element2/count;
	  element1 = element1%count;
	  element2 = element2%count;
	}
    }
  //decide which to shift down
  if (exp1>=exp2)
    {
      exp_res = exp1;
      while (exp2<exp1)
	{
	  exp2++;
	  for (int i = 1; i<48; i++)
	    coeff2[i] = coeff2[i-1]; 
	  coeff2[0] = 0; 
	}
    }
  else
    {
      exp_res = exp2;
      while (exp1<exp2)
	{
	  exp1++;
	  for (int i = 1; i<48; i++)
	    coeff1[i] = coeff1[i-1]; 
	  coeff1[0] = 0; 
	}
    }

  overflow = 0;
  for (int i =47; i>=0; i--)
    {
      coeff_res[i] = (coeff1[i] + coeff2[i] + overflow)%2;
      overflow = (coeff1[i] + coeff2[i] + overflow)/2;
    }
  if (overflow >0)
    {
      for (int i = 1; i<48; i++)
	{
	  coeff_res[i] = coeff_res[i-1];
	  coeff_res[0] = 1;
	}
      exp_res++;
    }
  count = 4096;
  temp = 8*sign_res + (16384+ exp_res)/count;
  ans[0]=hex_to_char(temp);
  exp_res = (16384+ exp_res)%count;
  for (int i=1; i<4; i++)
    {
      count = count/16;
      temp =  exp_res/count;
      ans[i]=hex_to_char(temp);
      exp_res = exp_res%count;
    }

  for (int i=0; i<12; i++)
    {
      temp = coeff_res[4*i]*8 + coeff_res[4*i+1]*4 +
	     coeff_res[4*i+2]*1 +coeff_res[4*i+3] ;
      ans[i+4]=hex_to_char(temp);
    }
}

void recip_float(char* op1, char* ans)
{
  int sign1, sign_res;
  int exp1, exp_res;
  double coeff1;
  double coeff_res;
  double two_to_the_48 = 16.0*16.0*16.0*16.0;

  if (char_grtr_than_int(op1[0], 7))
    sign1=1;
  else
    sign1=0;
  sign_res=sign1; 

  exp1 = string_to_long(op1,4) - (32768*sign1) - 16384; // 32768=2^15, sign
                                                        // 16384=2^14, bias
  
  exp_res = (-exp1) -48;

  coeff1 = (double) string_to_long(op1+4,12);  

  coeff_res = two_to_the_48 * (two_to_the_48 / coeff1);   //does this work?
  create_float(sign_res, (long int) coeff_res, exp_res, ans);
}

void mult_float(char* op1, char* op2, char* ans)
{
 double d1=0.0, d2=0.0;
 String_to_double( op1, d1);
 String_to_double( op2, d2);

 Double_to_string(d1+d2, ans);
}

void mult2_float(char* op1, char* op2, char* ans)
{
  int sign1, sign2, sign_res;
  int exp1, exp2, exp_res;
  double coeff1, coeff2, coeff_res;
  double two_to_the_48 = 16.0*16.0*16.0*16.0;

  if (char_grtr_than_int(op1[0], 7))
    sign1=1;
  else
    sign1=0;
  if (char_grtr_than_int(op2[0], 7))
    sign2=1;
  else
    sign2=0;

  sign_res = (sign1+sign2)%2;

  exp1 = string_to_long(op1,4) - (32768*sign1) - 16384; // 32768=2^15, sign
  exp2 = string_to_long(op2,4) - (32768*sign2) - 16384; // 16384=2^14, bias
  
  exp_res = exp1 + exp2;

  coeff1 = (double) string_to_long(op1+4,12);
  coeff2 = (double) string_to_long(op2+4,12);

  coeff_res = (coeff1 * coeff2) / two_to_the_48;
  create_float(sign_res, (long int) coeff_res, exp_res, ans);
}

void create_float(int sign, long int coeff, int exp, char* ans)
{
  long int two_to_the_48 = 16*16*16*16;
  strcpy(ans, "0000000000000000");

   exp = exp + (32768*sign) + 16384; //create biassed exponent

   // normalise 
   while ( coeff >= two_to_the_48)
     {
       exp++;
       coeff=coeff/2;
     }

   while ( coeff < (two_to_the_48/2) )
     {
       exp--;
       coeff=coeff*2;
     }

   for (int i = 3; i>=0; i--)
     {
       ans[i] = hex_to_char( exp%16);
       exp = exp/16;
     }
   for (int i = 11; i>=0; i--)
     {
       ans[i+4] = hex_to_char(( ( int) coeff)%16);
       coeff = coeff/16;
     }
   //  strcat(ans, coeffstr);
   
}


void String_to_double(char* str, double d)
{
  int sign;
  long int exp;
  double coeff, power;

  if (strcmp(str , "0000000000000000") ==0)
    d = 0.0;
  else
    {
      if (char_grtr_than_int(str[0], 7))
	sign=1;
      else
	sign=0;
      exp = string_to_long(str,4) - (32768*sign) - 16384; // 32768=2^15, sign
                                                     // 16384=2^14, bias
      power=1.0;
      coeff =0.0;
      for (int i =15; i>3; i++)
	{
      coeff = coeff + (char_to_hex(str[i]) * power);
      power = power*16.0;
	}
      
      d=1.0; // find  d = 2^exp
  
      while (exp<0)
	{
	  d = d/2.0;
	  exp++;
	}
      while (exp > 0 )
	{
	  d = d*2.0;
	  exp--;
	}

      d = d/coeff;
      if (sign==1)
	d = -d;
    }
}

void Double_to_string(double f, char* ans)
{
  int sign = 0;
  int coeff[48];
  long int exp =0, maxexp;
  double sixteen_12 = 16.0*16.0*16.0*16.0*16.0*16.0*16.0*16.0
                     *16.0*16.0*16.0*16.0;
  double power_of_16;
  int temp;
  maxexp=2*16*16*16;
  strcpy(ans, "0000000000000000");

  if (f<0.0)
    {
      sign = 1;
      f = -f;
    }

  while (( f > 1.0)&&(exp < maxexp))
    {
      f = f/2;
      exp++;
    }
  while ( (f < (1.0/16.0) ) && (exp > (-maxexp) ) )
    {
      f = f*2;
      exp--;
    }

  exp = exp + (32768*sign) + 16384; //create biassed exponent

  f = f*sixteen_12;
  power_of_16 = sixteen_12/2.0;
  for (int i =0; i<=48; i++)
    {
      if ( f >= power_of_16)
	{
	  f = f-power_of_16;
	  coeff[i]=1;
	}
      else 
	coeff[i]=0;
      power_of_16 = power_of_16/2.0;
    }

  temp =0;
  for (int i =0; i<12; i++) 
    {
      temp = i*4;
      ans[i+4]= hex_to_char(coeff[temp]*8 + coeff[temp+1]*4 + coeff[temp+2]*2
			  + coeff[temp+3] );
    }
  for (int i =3; i>=0; i--)
    {
      ans[i]= hex_to_char(exp%16);
      exp = exp/16;
    }

}
