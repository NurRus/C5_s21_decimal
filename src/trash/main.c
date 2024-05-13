#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define EXP_MASK 0b00000000111111110000000000000000
#define HIGHT_MASK 0b10000000000000000000000000000000
#define LOW_MASK 0b00000000000000000000000000000001
#define EXPMAX 28

typedef struct {
  unsigned int bits[4];
} s21_decimal;

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_negate(s21_decimal value, s21_decimal *result);


int s21_EXPOFTEN (s21_decimal value);
void s21_NORMALIZATION(s21_decimal *value_1, s21_decimal *value_2);
int s21_ADDALGORITM(s21_decimal *value_1, s21_decimal *value_2, s21_decimal *result);
void s21_SUBALGORITM(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
void s21_SHIFTLEFT(s21_decimal *value, int n);
int s21_NUMBEROFDIGITS(s21_decimal value);
int s21_BITCOMPARISION(s21_decimal value_1, s21_decimal value_2);
int s21_MULTENEXP(s21_decimal *value, int exp);
int s21_DIVTENEXP(s21_decimal *value, int exp);
void s21_BANKROUND(s21_decimal *value, int remain);
void s21_TAKEBIT(s21_decimal *value, int digit);
int s21_CHECKINGFORZERO(s21_decimal value);
void s21_RESETDECIMAL(s21_decimal *value);
void s21_EQUALITYDECIMAL(s21_decimal *result, s21_decimal value);
int s21_MULALGORITM(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
void s21_SIGNANDEXPRECORDING(s21_decimal *value, int sign, int exp);
void s21_DIVALGORITM(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_FRACTIONALPART(s21_decimal value_1, s21_decimal value_2);
int s21_MANTISSAOPTIMIZATION(s21_decimal *value, int sign, int exp);

int main() {
    s21_decimal decimal_1;
    s21_decimal decimal_2;
    s21_decimal decimal_3;
    s21_RESETDECIMAL(&decimal_1);
    s21_RESETDECIMAL(&decimal_2);
    s21_RESETDECIMAL(&decimal_3);
    decimal_1.bits[3] = 0b00000000000000010000000000000000;
    decimal_2.bits[3] = 0b00000000000000110000000000000000;
    decimal_1.bits[0] = 0b00000000000000000000000000000001;
    decimal_2.bits[0] = 0b00000000000000000000000000000001;
  

    //0000000000000000000000000000000000000000000000000000000000000000
    int f = s21_add(decimal_1, decimal_2, &decimal_3);
    if (f == 1){
        printf("Очень большое число\n");
    } else if (f == 2) {
        printf("Очень маленькое число\n");
    } else {
        int sign = (decimal_3.bits[3] & HIGHT_MASK) >> 31;
        int exp = s21_EXPOFTEN(decimal_3);
        printf("Знак: %d; Степень: %d\n", sign, exp);
        printf("bits[2] = %u; bits[1] = %u; bits[0] = %u\n", decimal_3.bits[2],
                decimal_3.bits[1], decimal_3.bits[0]);
    }
    //00011001100110011001100110011001
    //10011001100110011001100110011001
    //10011001100110011001100110011010

    return 0;
}

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2){
    int result = 1;
    s21_decimal tempvalue_1, tempvalue_2;
    s21_EQUALITYDECIMAL(&tempvalue_1, value_1);
    s21_EQUALITYDECIMAL(&tempvalue_2, value_2);
    if ((value_1.bits[3] >> 31) == (value_2.bits[3] >> 31)) {
        s21_NORMALIZATION(&tempvalue_1, &tempvalue_2);
        if (s21_BITCOMPARISION(tempvalue_1, tempvalue_2) == 0) {
            result = 0;
        }
    }
    return result;
}

int s21_is_equal(s21_decimal value_1, s21_decimal value_2){
    int result = 0;
    s21_decimal tempvalue_1, tempvalue_2;
    for (int i = 0; i < 4; i++){
        tempvalue_1.bits[i] = value_1.bits[i];
        tempvalue_2.bits[i] = value_2.bits[i];
    }
    if ((value_1.bits[3] >> 31) == (value_2.bits[3] >> 31)) {
        s21_NORMALIZATION(&tempvalue_1, &tempvalue_2);
        if (s21_BITCOMPARISION(tempvalue_1, tempvalue_2) != 0) {
            result = 0;
        } else {
            result = 1;
        }
    }
    return result;
}

int s21_is_less(s21_decimal value_1, s21_decimal value_2){
    int result = 0;
    s21_decimal tempvalue_1, tempvalue_2;
    for (int i = 0; i < 4; i++){
        tempvalue_1.bits[i] = value_1.bits[i];
        tempvalue_2.bits[i] = value_2.bits[i];
    }
    if ((value_1.bits[3] >> 31) > (value_2.bits[3] >> 31)) {
        result = 1;
    }
    if ((value_1.bits[3] >> 31) == (value_2.bits[3] >> 31)) {
        s21_NORMALIZATION(&tempvalue_1, &tempvalue_2);
        if (s21_BITCOMPARISION(tempvalue_1, tempvalue_2) == 2 && (value_1.bits[3] >> 31) == 0) {
            result = 1;
        }
        if (s21_BITCOMPARISION(tempvalue_1, tempvalue_2) == 1 && (value_1.bits[3] >> 31) == 1) {
            result = 1;
        }
    }
    return result;
}

int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2){
    int result = 0;
    s21_decimal tempvalue_1, tempvalue_2;
    for (int i = 0; i < 4; i++){
        tempvalue_1.bits[i] = value_1.bits[i];
        tempvalue_2.bits[i] = value_2.bits[i];
    }
    if ((value_1.bits[3] >> 31) > (value_2.bits[3] >> 31)) {
        result = 1;
    }
    if ((value_1.bits[3] >> 31) == (value_2.bits[3] >> 31)) {
        s21_NORMALIZATION(&tempvalue_1, &tempvalue_2);
        int res = s21_BITCOMPARISION(tempvalue_1, tempvalue_2);
        if (res == 1 && (value_1.bits[3] >> 31) == 1) {
          result = 1;
        } else if (res == 2 && (value_1.bits[3] >> 31) == 0) {
          result = 1;
        } else if (res == 0) {
          result = 1;
        }
    }
    printf("sign1 = %d", value_1.bits[3] >> 31);
    printf("val1 = %u; exp1 = %d\n", tempvalue_1.bits[0], 
             s21_EXPOFTEN(tempvalue_1));
    printf("sign2 = %d", value_2.bits[3] >> 31);
    printf("val1 = %u; exp1 = %d\n", tempvalue_2.bits[0], 
             s21_EXPOFTEN(tempvalue_2));
    return result;
}

int s21_is_greater(s21_decimal value_1, s21_decimal value_2){
    int result = 0;
    s21_decimal tempvalue_1, tempvalue_2;
    for (int i = 0; i < 4; i++){
        tempvalue_1.bits[i] = value_1.bits[i];
        tempvalue_2.bits[i] = value_2.bits[i];
    }
    if ((value_1.bits[3] >> 31) < (value_2.bits[3] >> 31)) {
        result = 1;
    }
    if ((value_1.bits[3] >> 31) == (value_2.bits[3] >> 31)) {
        s21_NORMALIZATION(&tempvalue_1, &tempvalue_2);
        if (s21_BITCOMPARISION(tempvalue_1, tempvalue_2) == 1 && (value_1.bits[3] >> 31) == 0) {
            result = 1;
        }
        if (s21_BITCOMPARISION(tempvalue_1, tempvalue_2) == 2 && (value_1.bits[3] >> 31) == 1) {
            result = 1;
        }
    }
    return result;
}

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2){
    int result = 0;
    s21_decimal tempvalue_1, tempvalue_2;
    for (int i = 0; i < 4; i++){
        tempvalue_1.bits[i] = value_1.bits[i];
        tempvalue_2.bits[i] = value_2.bits[i];
    }
    if ((value_1.bits[3] >> 31) < (value_2.bits[3] >> 31)) {
        result = 1;
    }
    if ((value_1.bits[3] >> 31) == (value_2.bits[3] >> 31)) {
        s21_NORMALIZATION(&tempvalue_1, &tempvalue_2);
        int res = s21_BITCOMPARISION(tempvalue_1, tempvalue_2);
        if (res == 1 && (value_1.bits[3] >> 31) == 0){
            result = 1;
        }
        if (res == 2 && (value_1.bits[3] >> 31) == 1){
            result = 1;
        }
        if (res == 0) {
            result = 1;
        }
    }
    return result;
}

int s21_EXPOFTEN (s21_decimal value){
    int result = 0;
    result = (value.bits[3] & EXP_MASK) >> 16;
    return result;
}

void s21_NORMALIZATION(s21_decimal *value_1, s21_decimal *value_2) {
  int exp1 = s21_EXPOFTEN(*value_1);
  int exp2 = s21_EXPOFTEN(*value_2);
  if (exp1 > exp2) {
    int deltaexp = exp1 - exp2;
    while ((s21_NUMBEROFDIGITS(*value_2) + 4) <= 96 && deltaexp > 0) {
      s21_MULTENEXP(value_2, 1);
      deltaexp--;
      value_2->bits[3] = value_2->bits[3] + (1 << 16);
    }
    if (deltaexp > 0) {
      s21_DIVTENEXP(value_1, deltaexp);
      value_1->bits[3] = value_1->bits[3] - (deltaexp << 16);
    }
  }
  if (exp2 > exp1) {
    int deltaexp = exp2 - exp1;
    while ((s21_NUMBEROFDIGITS(*value_1) + 4) <= 96 && deltaexp > 0) {
      s21_MULTENEXP(value_1, 1);
      deltaexp--;
      value_1->bits[3] = value_1->bits[3] + (1 << 16);
    }
    if (deltaexp > 0) {
      s21_DIVTENEXP(value_2, deltaexp);
      value_2->bits[3] = value_2->bits[3] - (deltaexp << 16);
    }
  }
}

int s21_ADDALGORITM(s21_decimal *value_1, s21_decimal *value_2,
                    s21_decimal *result) {
  s21_RESETDECIMAL(result);
  result->bits[3] = value_1->bits[3];
  int stec = 0;
  int n = 0;
  int j = 0;
  int i = 0;
  int bit_v1 = 0;
  int bit_v2 = 0;
  int max_digit = s21_NUMBEROFDIGITS(*value_1);
  int digit2 = s21_NUMBEROFDIGITS(*value_2);
  if (digit2 > max_digit) {
    max_digit = digit2;
  }
  while(i <= max_digit && i < 96){
    if (i == 32 || i == 64) {
      j = 0;
      n++;
    }
    bit_v1 = ((value_1->bits[n] & (LOW_MASK << j))) >> j;
    bit_v2 = ((value_2->bits[n] & (LOW_MASK << j))) >> j;
    if ((bit_v1 + bit_v2 + stec) == 2) {
      stec = 1;
    } else if ((bit_v1 + bit_v2 + stec) == 3) {
      stec = 1;
      result->bits[n] = result->bits[n] | (LOW_MASK << j);
    } else if ((bit_v1 + bit_v2 + stec) == 1) {
      stec = 0;
      result->bits[n] = result->bits[n] | (LOW_MASK << j);
    } else if ((bit_v1 + bit_v2 + stec) == 0) {
      stec = 0;
    }
    j++;
    i++;
  }
  if (stec == 1 && s21_EXPOFTEN(*value_1) > 0) {
    s21_DIVTENEXP(value_1, 1);
    s21_DIVTENEXP(value_2, 1);
    value_1->bits[3] = value_1->bits[3] - (1 << 16);
    value_2->bits[3] = value_2->bits[3] - (1 << 16);
    stec = s21_ADDALGORITM(value_1, value_2, result);
  }
  return stec;
}

void s21_SUBALGORITM(s21_decimal value_1, s21_decimal value_2,
                     s21_decimal *result) {
  s21_decimal tempvalue_1, tempvalue_2;
  for (int i = 0; i < 3; i++) {
    tempvalue_1.bits[i] = value_1.bits[i];
    tempvalue_2.bits[i] = value_2.bits[i];
  }
  int max_digit = s21_NUMBEROFDIGITS(value_1);
  int i = 0;
  int k = 0;
  int bit_v1 = 0;
  int bit_v2 = 0;
  for (int j = 0; j < max_digit; j++) {
    if (j == 32 || j == 64) {
      i = 0;
      k++;
    }
    bit_v1 = (tempvalue_1.bits[k] & (LOW_MASK << i)) >> i;
    bit_v2 = (tempvalue_2.bits[k] & (LOW_MASK << i)) >> i;
    if (bit_v1 == 1 && bit_v2 == 0) {
      result->bits[k] = result->bits[k] | (LOW_MASK << i);
    }
    if (bit_v1 == 0 && bit_v2 == 1) {
      result->bits[k] = result->bits[k] | (LOW_MASK << i);
      s21_TAKEBIT(&tempvalue_1, j);
    }
    i++;
  }
  result->bits[3] = value_1.bits[3];
}

void s21_SHIFTLEFT(s21_decimal *value, int n){
    int f[3];
    for (int i = 0; i < n; i++) {
        f[0] = 0; f[1] = 0; f[2] = 0;
        if((value->bits[2] >> 31) == 1) f[2] = 1;
        if((value->bits[1] >> 31) == 1) f[1] = 1;
        if((value->bits[0] >> 31) == 1) f[0] = 1;
        value->bits[0] = value->bits[0] << 1;
        value->bits[1] = value->bits[1] << 1;
        value->bits[2] = value->bits[2] << 1;
        if (f[0] == 1) {
            value->bits[1] = value->bits[1] | LOW_MASK;
        }
        if (f[1] == 1) {
            value->bits[2] = value->bits[2] | LOW_MASK; 
        }
        if (f[2] == 1) {
            value->bits[2] = value->bits[2] | HIGHT_MASK;
        }
    }
}

int s21_NUMBEROFDIGITS(s21_decimal value){
    int count = 0;
    int i = 0;
    while(i < 32 && (value.bits[2] & (HIGHT_MASK >> i)) == 0){
        count++;
        i++;
    }
    if (count == 32) {
        i = 0;
        while(i < 32 && (value.bits[1] & (HIGHT_MASK >> i)) == 0){
            count++;
            i++;
        }
    }
    if (count == 64) {
        i = 0;
        while(i < 32 && (value.bits[0] & (HIGHT_MASK >> i)) == 0){
            count++;
            i++;
        }
    }
    return 96 - count;
}

int s21_BITCOMPARISION(s21_decimal value_1, s21_decimal value_2){
    int result = 0;
    int n = 95;
    int k = 0;
    int i = 31;
    while (n > 0 && result == 0) {
        if(n >= 64) {
            k = 2;
        } else if (n < 64 && n >= 32){
            k = 1;
        } else if (n < 32){
            k = 0;
        }
        if (n == 63 || n == 31){
            i = 31;
        }
        if ((value_1.bits[k] & (LOW_MASK << i)) > (value_2.bits[k] & (LOW_MASK << i))) {
            result = 1;
        }
        if ((value_1.bits[k] & (LOW_MASK << i)) < (value_2.bits[k] & (LOW_MASK << i))) {
            result = 2;
        }
        i--;
        n--;
    }
    return result;
}

void s21_BANKROUND(s21_decimal *value, int remain) {
    int j = 0;
    int i = 0;
    int k = 0;
    int bit_v = value->bits[0] & LOW_MASK;
    if (bit_v == 0 && remain > 5) {
        value->bits[k] = value->bits[k] | (LOW_MASK << i);
    } 
    if (bit_v == 1 && remain >= 5) {
        while (bit_v == 1) {
            value->bits[k] = value->bits[k] & (~(LOW_MASK << i));
            j++;
            i++;
            if (j == 32 || j == 64) {
                i = 0;
                k++;
            }
            bit_v = (value->bits[k] & (LOW_MASK << i)) >> i;
        }
        value->bits[k] = value->bits[k] | (LOW_MASK << i);
    }
}

int s21_DIVTENEXP(s21_decimal *value, int exp) {
  int result = 0;
  s21_decimal devider, dividend, subvalue;
  s21_RESETDECIMAL(&devider);
  int compar = 0;
  int translation;
  for (int i = 0; i < exp; i++) {
    translation = s21_NUMBEROFDIGITS(*value) - 4;
    for (int i = 0; i < 3; i++) {
      dividend.bits[i] = value->bits[i];
      value->bits[i] = 0;
    }
    while (translation >= 0) {
      s21_SHIFTLEFT(value, 1);
      s21_RESETDECIMAL(&subvalue);
      s21_RESETDECIMAL(&devider);
      devider.bits[0] = 10;
      s21_SHIFTLEFT(&devider, translation);
      compar = s21_BITCOMPARISION(dividend, devider);
      if (compar == 0 || compar == 1) {
        s21_SUBALGORITM(dividend, devider, &subvalue);
        dividend.bits[2] = subvalue.bits[2];
        dividend.bits[1] = subvalue.bits[1];
        dividend.bits[0] = subvalue.bits[0];
        value->bits[0] = value->bits[0] | LOW_MASK;
      }
      translation--;
    }
    int remainder = 0;
    remainder = dividend.bits[0];
    if (remainder > 0) {
      result = 1;
      s21_BANKROUND(value, remainder);
    }
  }
  return result;
}

void s21_TAKEBIT(s21_decimal *value, int digit){
    int bit = 0;
    int n = digit + 1;
    int k = 0;
    int i = 0;
    while (n < 96 && bit == 0) {
        if(n < 32) {
            k = 0;
            i = n;
        } else if (n >= 32 && n < 64) {
            k = 1;
            i = n - 32;
        } else if (n >= 64 && n < 96) {
            k = 2;
            i = n - 64;
        }
        bit = (value->bits[k] & (LOW_MASK << i)) >> i;
        if (bit == 1) {
            value->bits[k] = value->bits[k] & (~(LOW_MASK << i));
        } else {
            value->bits[k] = value->bits[k] | (LOW_MASK << i);
        }
        n++;
    }
}

int s21_MULTENEXP(s21_decimal *value, int exp) {
  int result = 0;
  int i = 0;
  s21_decimal addvalue_1, addvalue_2, tempvalue;
  s21_EQUALITYDECIMAL(&tempvalue, *value);
  while (i < exp && result == 0) {
    s21_EQUALITYDECIMAL(&addvalue_1, *value);
    s21_EQUALITYDECIMAL(&addvalue_2, *value);
    s21_RESETDECIMAL(value);
    s21_SHIFTLEFT(&addvalue_1, 1);
    s21_SHIFTLEFT(&addvalue_2, 3);
    result = s21_ADDALGORITM(&addvalue_1, &addvalue_2, value);
    s21_RESETDECIMAL(&addvalue_1);
    s21_RESETDECIMAL(&addvalue_2);
    i++;
  }
  if (result != 0) {
    s21_EQUALITYDECIMAL(value, tempvalue);
  }
  return result;
}

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int flag = 0;
  int zero1 = s21_CHECKINGFORZERO(value_1);
  int zero2 = s21_CHECKINGFORZERO(value_2);
  s21_decimal tempvalue_1, tempvalue_2;
  s21_EQUALITYDECIMAL(&tempvalue_1, value_1);
  s21_EQUALITYDECIMAL(&tempvalue_2, value_2);
  s21_NORMALIZATION(&tempvalue_1, &tempvalue_2);
  int sign1 = value_1.bits[3] >> 31;
  int sign2 = value_2.bits[3] >> 31;
  int paramter1 = sign1 - sign2;
  int paramter2 = s21_BITCOMPARISION(tempvalue_1, tempvalue_2);
  switch (paramter1) {
    case 0:
      flag = s21_ADDALGORITM(&tempvalue_1, &tempvalue_2, result);
      break;
    case -1:
    case 1: {
      if (paramter2 == 0) {
        s21_RESETDECIMAL(result);
      } else if (paramter2 == 2) {
        s21_SUBALGORITM(tempvalue_2, tempvalue_1, result);
      } else if (paramter2 == 1) {
        s21_SUBALGORITM(tempvalue_1, tempvalue_2, result);
      }
      break;
    }
  }
  if (zero1 == 1) {
    s21_EQUALITYDECIMAL(result, value_2);
  } else if (zero2 == 1) {
    s21_EQUALITYDECIMAL(result, value_1);
  }
  int sign = result->bits[3] >> 31;
  if (flag == 1 && sign == 1) {
    flag = 2;
  }
  if (flag == 0 && s21_NUMBEROFDIGITS(*result) >0) {
    int exp = s21_EXPOFTEN(tempvalue_1);
    int sign = result->bits[3] >> 31;
    s21_MANTISSAOPTIMIZATION(result, sign, exp);
  }
  return flag;
}

int s21_CHECKINGFORZERO(s21_decimal value){
    int result = 1;
    for (int i = 0; i < 3; i++){
        if(value.bits[i] != 0) {
            result = 0;
        }
    }
    return result;
}

int s21_negate(s21_decimal value, s21_decimal *result){
    int res = 0;
    int exp = s21_EXPOFTEN(value);
    if (exp > 28) {
        res = 1;
    }
    for (int i = 0; i < 3; i++){
        result->bits[i] = value.bits[i];
    }
    int bit = value.bits[3] >> 31;
    if (bit == 1) {
        result->bits[3] = value.bits[3] & (~HIGHT_MASK);
    } else if (bit == 0){
        result->bits[3] = value.bits[3] | HIGHT_MASK;
    }
    if (exp > 28) {
        res = 1;
    }
    return res;
}

void s21_RESETDECIMAL(s21_decimal *value){
    for (int i = 0; i < 4; i++) {
        value->bits[i] = 0;
    }
}

void s21_EQUALITYDECIMAL(s21_decimal *result, s21_decimal value){
    for (int i = 0; i < 4; i++) {
        result->bits[i] = value.bits[i];
    }
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int flag = 0;
  int zero1 = s21_CHECKINGFORZERO(value_1);
  int zero2 = s21_CHECKINGFORZERO(value_2);
  s21_decimal tempvalue_1, tempvalue_2;
  s21_EQUALITYDECIMAL(&tempvalue_1, value_1);
  s21_EQUALITYDECIMAL(&tempvalue_2, value_2);
  s21_NORMALIZATION(&tempvalue_1, &tempvalue_2);
  int sign1 = value_1.bits[3] >> 31;
  int sign2 = value_2.bits[3] >> 31;
  int paramter1 = sign1 - sign2;
  int paramter2 = s21_BITCOMPARISION(tempvalue_1, tempvalue_2);
  switch (paramter1) {
    case 0: {
      if (paramter2 == 0) {
        s21_RESETDECIMAL(result);
      } else if (paramter2 == 2) {
        s21_SUBALGORITM(tempvalue_2, tempvalue_1, result);
        flag = s21_negate(*result, result);
      } else if (paramter2 == 1) {
        s21_SUBALGORITM(tempvalue_1, tempvalue_2, result);
      }
      break;
    }
    case -1:
    case 1:
      flag = s21_ADDALGORITM(&tempvalue_1, &tempvalue_2, result);
      break;
  }
  if (zero1 == 1) {
    s21_EQUALITYDECIMAL(result, value_2);
    flag = s21_negate(*result, result);
  } else if (zero2 == 1) {
    s21_EQUALITYDECIMAL(result, value_1);
  }
  int sign = result->bits[3] >> 31;
  if (flag == 1 && sign == 1) {
    flag = 2;
  }
  if (flag == 0 && s21_NUMBEROFDIGITS(*result) > 0) {
    int exp = s21_EXPOFTEN(tempvalue_1);
    int sign = result->bits[3] >> 31;
    s21_MANTISSAOPTIMIZATION(result, sign, exp);
  }
  return flag;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_decimal tempvalue_1, tempvalue_2;
  s21_EQUALITYDECIMAL(&tempvalue_1, value_1);
  s21_EQUALITYDECIMAL(&tempvalue_2, value_2);
  int flag = 0;
  int digit1 = s21_NUMBEROFDIGITS(value_1);
  int digit2 = s21_NUMBEROFDIGITS(value_2);
  int exp = s21_EXPOFTEN(value_1) + s21_EXPOFTEN(value_2);
  int digit = digit1 + digit2;
  int sign = 0;
  if ((value_1.bits[3] >> 31) != (value_2.bits[3] >> 31)) {
    sign = 1;
  }
  while (digit > 96) {
    if (digit1 >= digit2) {
      s21_DIVTENEXP(&tempvalue_1, 1);
      exp--;
      digit1 = s21_NUMBEROFDIGITS(tempvalue_1);
    } else {
      s21_DIVTENEXP(&tempvalue_2, 1);
      exp--;
      digit2 = s21_NUMBEROFDIGITS(tempvalue_2);
    }
    digit = digit1 + digit2;
  }
  flag = s21_MULALGORITM(tempvalue_1, tempvalue_2, result);
  if (flag == 0) {
    flag = s21_MANTISSAOPTIMIZATION(result, sign, exp);
  }
  if (flag != 0) {
    s21_RESETDECIMAL(result);
  }
  return flag;
}

int s21_MULALGORITM(s21_decimal value_1, s21_decimal value_2,
                    s21_decimal *result) {
  int flag = 0;
  s21_RESETDECIMAL(result);
  int digit1 = s21_NUMBEROFDIGITS(value_1);
  int digit2 = s21_NUMBEROFDIGITS(value_2);
  s21_decimal tempvalue_1, tempvalue_2, tempvalue_3, tempresult;
  if (digit1 >= digit2) {
    s21_EQUALITYDECIMAL(&tempvalue_1, value_1);
    s21_EQUALITYDECIMAL(&tempvalue_2, value_2);
  } else {
    s21_EQUALITYDECIMAL(&tempvalue_2, value_1);
    s21_EQUALITYDECIMAL(&tempvalue_1, value_2);
    digit2 = digit1;
    digit1 = s21_NUMBEROFDIGITS(value_2);
  }
  int j = 0;
  int k = 0;
  int i = 0;
  int bit_v;
  for (; j < digit2; j++) {
    if (j == 32 || j == 64) {
      k++;
      i = 0;
    }
    bit_v = (tempvalue_2.bits[k] & (LOW_MASK << i)) >> i;
    if (bit_v == 1) {
      s21_EQUALITYDECIMAL(&tempvalue_3, tempvalue_1);
      s21_EQUALITYDECIMAL(&tempresult, *result);
      s21_SHIFTLEFT(&tempvalue_3, j);
      s21_RESETDECIMAL(result);
      flag = s21_ADDALGORITM(&tempresult, &tempvalue_3, result);
    }
    i++;
  }
  return flag;
}

void s21_SIGNANDEXPRECORDING(s21_decimal *value, int sign, int exp){
    value->bits[3] = 0;
    value->bits[3] = (value->bits[3] + exp) << 16;
    if (sign == 1) {
        value->bits[3] = value->bits[3] | HIGHT_MASK;
    }
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int flag = 0;
  s21_decimal tempvalue_1, tempvalue_2;
  s21_EQUALITYDECIMAL(&tempvalue_1, value_1);
  s21_EQUALITYDECIMAL(&tempvalue_2, value_2);
  int sign;
  if ((value_1.bits[3] >> 31) != (value_2.bits[3] >> 31)) {
    sign = 1;
  }
  int digit2 = s21_NUMBEROFDIGITS(value_2);
  int digit1 = s21_NUMBEROFDIGITS(value_1);
  int exp = s21_EXPOFTEN(value_1) - s21_EXPOFTEN(value_2);
  printf("exp = %d\n", exp);
  s21_RESETDECIMAL(result);
  if (digit2 == 0) {
    flag = 3;
  } else if (digit1 > 0) {
    while (digit1 < 93) {
      s21_MULTENEXP(&tempvalue_1, 1);
      digit1 = s21_NUMBEROFDIGITS(tempvalue_1);
      exp++;
    }
    while (digit2 >= digit1) {
      s21_DIVTENEXP(&tempvalue_2, 1);
      exp++;
      digit2 = s21_NUMBEROFDIGITS(tempvalue_2);
    }
    s21_DIVALGORITM(tempvalue_1, tempvalue_2, result);
  }
  if (flag == 0 && s21_NUMBEROFDIGITS(*result) > 0) {
    s21_SIGNANDEXPRECORDING(result, sign, exp);
    flag = s21_MANTISSAOPTIMIZATION(result, sign, exp);
  }
  return flag;
}

void s21_DIVALGORITM(s21_decimal value_1, s21_decimal value_2,
                     s21_decimal *result) {
  s21_decimal devider, dividend, subvalue;
  s21_RESETDECIMAL(&devider);
  int compar = 0;
  int translation;
  int remainder = 0;
  translation = s21_NUMBEROFDIGITS(value_1) - s21_NUMBEROFDIGITS(value_2);
  s21_EQUALITYDECIMAL(&dividend, value_1);
  while (translation >= 0) {
    s21_SHIFTLEFT(result, 1);
    s21_RESETDECIMAL(&subvalue);
    s21_RESETDECIMAL(&devider);
    s21_EQUALITYDECIMAL(&devider, value_2);
    s21_SHIFTLEFT(&devider, translation);
    compar = s21_BITCOMPARISION(dividend, devider);
    if (compar == 0 || compar == 1) {
      s21_SUBALGORITM(dividend, devider, &subvalue);
      s21_EQUALITYDECIMAL(&dividend, subvalue);
      result->bits[0] = result->bits[0] | LOW_MASK;
    }
    translation--;
  }
  if (s21_NUMBEROFDIGITS(dividend) != 0) {
    remainder = s21_FRACTIONALPART(dividend, value_2);
    s21_BANKROUND(result, remainder);
  }
}

int s21_FRACTIONALPART(s21_decimal value_1, s21_decimal value_2) {
  int result = 0;
  s21_decimal tempvalue_1, tempvalue_2;
  s21_RESETDECIMAL(&tempvalue_1);
  s21_RESETDECIMAL(&tempvalue_2);
  s21_ADDALGORITM(&value_1, &value_1, &tempvalue_1);
  int compare = s21_BITCOMPARISION(tempvalue_1, value_2);
  if (compare == 1) {
    s21_SUBALGORITM(tempvalue_1, value_2, &tempvalue_2);
    s21_MULTENEXP(&tempvalue_2, 1);
    compare = s21_BITCOMPARISION(tempvalue_2, value_2);
    if (compare == 1 || compare == 0) {
      result = 7;
    }
  } else if (compare == 0) {
    result = 5;
  } else {
    result = 3;
  }
  return result;
}

int s21_MANTISSAOPTIMIZATION(s21_decimal *value, int sign, int exp) {
  int result = 0;
  s21_decimal tempvalue;
  s21_EQUALITYDECIMAL(&tempvalue, *value);
  int flag = 0;
  int digit = s21_NUMBEROFDIGITS(*value);
  while (exp > 0 && flag == 0 && digit > 0) {
    flag = s21_DIVTENEXP(&tempvalue, 1);
    exp--;
    if (flag == 1) {
      exp++;
    } else {
      s21_EQUALITYDECIMAL(value, tempvalue);
    }
  }
  digit = s21_NUMBEROFDIGITS(*value); 
  while (exp < 0 && digit < 93) {
    s21_MULTENEXP(value, 1);
    exp++;
    digit = s21_NUMBEROFDIGITS(*value);
  }
  while (exp > EXPMAX && digit > 0) {
    s21_DIVTENEXP(value, 1);
    exp--;
    digit = s21_NUMBEROFDIGITS(*value);
    if (digit == 0) {
      result = 2;
    }
  }
  s21_SIGNANDEXPRECORDING(value, sign, exp);
  if (exp < 0 && sign == 0) {
      result = 1;
  } else if (exp < 0 && sign == 1){
      result = 2;
  }
  if (result != 0) {
    s21_RESETDECIMAL(value);
  }
  return result;
}

int ss21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_decimal tempvalue_1, tempvalue_2;
  s21_EQUALITYDECIMAL(&tempvalue_1, value_1);
  s21_EQUALITYDECIMAL(&tempvalue_2, value_2);
  int flag = 0;
  int digit1 = s21_NUMBEROFDIGITS(value_1);
  int digit2 = s21_NUMBEROFDIGITS(value_2);
  int digit = digit1 + digit2;
  int exp = s21_EXPOFTEN(value_1) + s21_EXPOFTEN(value_2);
  int sign = 0;
  if ((value_1.bits[3] >> 31) != (value_2.bits[3] >> 31)) {
    sign = 1;
  }
  flag = s21_MULALGORITM(tempvalue_1, tempvalue_2, result);
  if (flag == 0) {
    flag = s21_MANTISSAOPTIMIZATION(result, sign, exp);
  }
  if (flag != 0) {
    s21_RESETDECIMAL(result);
  }
  return flag;
}

int s21_MULALGORITM(s21_decimal value_1, s21_decimal value_2,
                    s21_decimal *result) {
  s21_decimal bufer;
  int flag = 0;
  s21_RESETDECIMAL(result);
  s21_RESETDECIMAL(&bufer);
  int digit1 = s21_NUMBEROFDIGITS(value_1);
  int digit2 = s21_NUMBEROFDIGITS(value_2);
  s21_decimal tempvalue_1, tempvalue_2, tempvalue_3, tempresult;
  int j = 0;
  int k = 0;
  int i = 0;
  int bit_v;
  for (; j < digit2; j++) {
    if (j == 32 || j == 64) {
      k++;
      i = 0;
    }
    bit_v = (tempvalue_2.bits[k] & (LOW_MASK << i)) >> i;
    if (bit_v == 1) {
      s21_EQUALITYDECIMAL(&tempvalue_3, tempvalue_1);
      s21_EQUALITYDECIMAL(&tempresult, *result);
      s21_SHIFTLEFT(&tempvalue_3, j);
      s21_RESETDECIMAL(result);
      flag = s21_ADDALGORITM(&tempresult, &tempvalue_3, result);
    }
    i++;
  }
  return flag;
}