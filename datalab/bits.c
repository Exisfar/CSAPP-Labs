/*
 * CS:APP Data Lab
 *
 * <Please put your name and userid here>
 *
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code
  must conform to the following style:

  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>

  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.


  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 *
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce
 *      the correct answers.
 */

#endif
// 1
/*
 * bitXor - x^y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  /* Boolean Algebra is an algebra that captures the properties of propositional
   * logic. */
  // propositional logic in this problem:
  // neither both 1 nor both 0
  return ~(~x & ~y) & ~(x & y);
}
/*
 * tmin - return minimum two's complement integer
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  // 10...0 (31's 0): -2^31
  return 1 << 31;
}
// 2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
  // max two's complement: 0111...1 (31's 1)
  // x + 1 == ~x, exclude x=-1 (11...1)
  return !((x + 1) ^ (~x)) & !!~x;
}
/*
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  // construct mask 0xAAAAAAAA
  int mask = 0xAA;
  mask = (mask << 8) | mask;   // 0xAAAA
  mask = (mask << 16) | mask;  // 0xAAAAAAAA
  return !((x & mask) ^ mask);
}
/*
 * negate - return -x
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) { return ~x + 1; }
// 3
/*
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0'
 * to '9') Example: isAsciiDigit(0x35) = 1. isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
  // overflow does not matter in this solution
  int left = !((x + ~0x30 + 1) >> 31);
  int right = !((0x39 + ~x + 1) >> 31);
  return left & right;
}
/*
 * conditional - same as x ? y : z
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  // construct mask ~!x: 0 if x is true, -1 if x is false
  // -1 + 1 == ~(-1)
  int mask = ~(!x) + 1;
  return (~mask & y) | (mask & z);
}
/*
 * isLessOrEqual - if x <= y  then return 1, else return 0
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  // Subtracting y from x directly (x - y) can cause overflow if x is very large
  // and y is very small (or vice versa)
  int sign_x = x >> 31;
  int sign_y = y >> 31;

  int opposite_signs = sign_x ^ sign_y;
  int is_x_neg_y_pos = sign_x & !sign_y;

  int diff = y + ~x + 1;
  int diff_sign = diff >> 31;
  int same_sign_result = !opposite_signs & !diff_sign;
  return is_x_neg_y_pos | same_sign_result;
}
// 4
/*
 * logicalNeg - implement the ! operator, using all of
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int logicalNeg(int x) {
  // If x is 0, then ~x + 1 will also be 0.
  // If x is non-zero, then ~x + 1 will be non-zero.
  // The sign bit of x | (~x + 1) will be 1 if x is non-zero, and 0 if x is zero
  // In two's complement representation, shifting a negative number right (>>)
  // performs sign extension. This means the sign bit (most significant bit) is
  // copied into the new bits When x is non-zero, x | (~x + 1) has the sign bit
  // set to 1. Shifting this right by 31 bits fills all 32 bits with 1s,
  // resulting in -1 (in two's complement, 0xFFFFFFFF represents -1)
  int sign_bit = (x | (~x + 1)) >>
                 31;  // 000...0 if x is zero and 111...1 if x is non-zero
  return sign_bit + 1;
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
  int sign = x >> 31;
  // 当x为正时，设pos表示为1的最高的位置，答案是pos + 1。
  // 当x为负时，将x取反，设pos表示此时为1的最高的位置，答案也是idx + 1
  x = (~sign & x) |
      (sign &
       ~x);  // 这样，无论是正数还是负数，都可以用相同的方法找到最高有效位
  // 二分
  int one_in_high_16_bits =
      !!(x >> 16) << 4;       // get 16 if x has one in high 16 bits, else 0
  x >>= one_in_high_16_bits;  // right shift 16 bits if x has ...
  int one_in_high_8_bits = !!(x >> 8) << 3;
  x >>= one_in_high_8_bits;
  int one_in_high_4_bits = !!(x >> 4) << 2;
  x >>= one_in_high_4_bits;
  int one_in_high_2_bits = !!(x >> 2) << 1;
  x >>= one_in_high_2_bits;
  int one_in_high_1_bit = !!(x >> 1);
  x >>= one_in_high_1_bit;

  int total_bits = one_in_high_16_bits + one_in_high_8_bits +
                   one_in_high_4_bits + one_in_high_2_bits + one_in_high_1_bit +
                   x + 1;  // 1 for sign bit

  return total_bits;
}
// float
/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
  int exponent = uf >> 23 & 0xFF;
  // 1. Inifnity or NaN: exponent filed is all ones
  if (exponent == 0xFF) {
    return uf;
  }

  int msb = uf >> 31;
  int fraction = uf & 0x7FFFFF;

  // 2. denormalized values: exponent filed is all zeros
  if (exponent == 0) {
    fraction <<= 1;
    // check if the fraction overflows
    if (fraction & 0x800000) {
      // if it overflows, set the exponent to 1
      exponent = 1;
      fraction &= 0x7FFFFF;  // clear the overflow bit
    }
  } else {  // 3. normalized values
    exponent++;
    // check if the exponent overflows
    if (exponent == 0xFF) {
      // if it overflows, set the fraction to 0
      fraction = 0;
    }
  }

  return (msb << 31) | (exponent << 23) | fraction;
}

/*
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
  int exponent = uf >> 23 & 0xFF;
  // NaN or infinity
  if (exponent == 0xFF) {
    return 0x80000000u;
  }

  // denormalized values
  if (exponent == 0) {
    return 0;
  }

  // normalized values
  int msb = uf >> 31;
  int fraction = uf & 0x7FFFFF;
  int bias = 127;
  // In C: from float or double to int, the value will be rounded toward zero
  int shift = exponent - bias;
  if (shift < 0) {
    return 0;
  } else {
    // check if the result overflows
    if (shift > 31 || (shift == 31 && msb == 1)) {
      return 0x80000000u;
    }
    // shift the fraction to the left by 23 bits
    fraction = (fraction | 0x800000) >> (23 - shift);
  }

  return msb ? -fraction : fraction;
}
/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatPower2(int x) {
  // the result is to large
  if (x > 127) {
    return 0x7F800000;  // +INF
  }
  // the result is too small
  if (x < -126) {
    return 0;
  }
  // the result is normalized
  return (x + 127) << 23;
}
