/*
 * CS:APP Data Lab
 *
 * <Please put your name and userid here>
 *
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 */

/* Instructions to Students:

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code
  must conform to the following style:

  long Funct(long arg1, long arg2, ...) {
      // brief description of how your implementation works
      long var1 = Expr1;
      ...
      long varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. (Long) integer constants 0 through 255 (0xFFL), inclusive. You are
      not allowed to use big constants such as 0xffffffffL.
  3. Function arguments and local variables (no global variables).
  4. Local variables of type int and long
  5. Unary integer operations ! ~
     - Their arguments can have types int or long
     - Note that ! always returns int, even if the argument is long
  6. Binary integer operations & ^ | + << >>
     - Their arguments can have types int or long
  7. Casting from int to long and from long to int

  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting other than between int and long.
  7. Use any data type other than int or long.  This implies that you
     cannot use arrays, structs, or unions.

  You may assume that your machine:
  1. Uses 2s complement representations for int and long.
  2. Data type int is 32 bits, long is 64.
  3. Performs right shifts arithmetically.
  4. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31 (int) or 63 (long)

EXAMPLES OF ACCEPTABLE CODING STYLE:
  //
  // pow2plus1 - returns 2^x + 1, where 0 <= x <= 63
  //
  long pow2plus1(long x) {
     // exploit ability of shifts to compute powers of 2
     // Note that the 'L' indicates a long constant
     return (1L << x) + 1L;
  }

  //
  // pow2plus4 - returns 2^x + 4, where 0 <= x <= 63
  //
  long pow2plus4(long x) {
     // exploit ability of shifts to compute powers of 2
     long result = (1L << x);
     result += 4L;
     return result;
  }

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

CAUTION:
  Do not add an #include of <stdio.h> (or any other C library header)
  to this file.  C library headers almost always contain constructs
  that dlc does not understand.  For debugging, you can use printf,
  which is declared for you just below.  It is normally bad practice
  to declare C library functions by hand, but in this case it's less
  trouble than any alternative.

  dlc will consider each call to printf to be a violation of the
  coding style (function calls, after all, are not allowed) so you
  must remove all your debugging printf's again before submitting your
  code or testing it with dlc or the BDD checker.  */

extern int printf(const char *, ...);

/* Edit the functions below.  Good luck!  */
// 2
/*
 * copyLSB - set all bits of result to least significant bit of x
 *   Examples:
 *     copyLSB(5L) = 0xFFFFFFFFFFFFFFFFL
 *     copyLSB(6L) = 0x0000000000000000L
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
long copyLSB(long x) { // Checked.
    long least = x & 1;
    long result = ~0;
    return ~(result + least);
}
/*
 * dividePower2 - Compute x/(2^n), for 0 <= n <= 62
 *  Round toward zero
 *   Examples: dividePower2(15L,1L) = 7L, dividePower2(-33L,4L) = -2L
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
long dividePower2(long x, long n) { // Checked. see book p73
    // There should be (x < 0 ? x + (1 << n) - 1 : x) >> n
    // long t = (1L << n) - 1L;
    // Attention! There should be `1L` insted of `1`, otherwise it will be
    // considered as int32, which causes overflow.
    // printf("[Print] The t is : 0x%lx (%ld)\n", t, t);
    long bias = ((1L << n) + (~0)) & (x >> 63);
    // printf("[Print] The ((1L << n) - 1L) is : 0x%lx (%ld)\n",
    //(long)((1L << n) - 1L), (long)((1L << n) - 1L));
    // printf("[Print] The (x >> 63) is : 0x%lx (%ld)\n", (x >> 63), (x
    // >> 63)); printf("[Print] bias = 0x%lx (%ld)\n", bias, bias);
    return (x + bias) >> n;
}
/*
 * distinctNegation - returns 1 if x != -x.
 *     and 0 otherwise
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 5
 *   Rating: 2
 */
long distinctNegation(long x) { // Checked.
    return !(!(x ^ (~x + 1)));
    // return !(!((x ^ (~x + 1)) & 2));
}
/*
 * anyEvenBit - return 1 if any even-numbered bit in word set to 1
 *   where bits are numbered from 0 (least significant) to 63 (most significant)
 *   Examples anyEvenBit(0xAL) = 0L, anyEvenBit(0xEL) = 1L
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 14
 *   Rating: 2
 */
long anyEvenBit(long x) {    // Checked.
    long t = 85L;            // 0x55
    long y = (85L << 8) + t; // 0x5555
    t = y;                   // 0x5555
    y = (y << 16) + t;       // 0x55555555
    t = y;
    y = (y << 32) + t;
    return (long)!(!(x & y));
}
// 3
/*
 * isLessOrEqual - if x <= y  then return 1, else return 0
 *   Example: isLessOrEqual(4L,5L) = 1L.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
long isLessOrEqual(long x, long y) {
    long diff = x + (~y + 1);
    long sign = (diff >> 63) & 1L;
    long x_sign = (x >> 63) & 1L;
    long y_sign = (y >> 63) & 1L;
    long same = (~(x_sign ^ y_sign)) & 1L;
    return (same & sign) | ((!same) & x_sign) | (same & (!diff));
}
/*
 * replaceByte(x,n,c) - Replace byte n in x with c
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: replaceByte(0x12345678,1,0xab) = 0x1234ab78
 *   You can assume 0 <= n <= 7 and 0 <= c <= 255
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 3
 */
long replaceByte(long x, long n, long c) { // Checked.
    long mask = 255;
    mask = ~(mask << (n << 3));
    x = x & mask;
    return x | (c << (n << 3));
}
/*
 * conditional - same as x ? y : z
 *   Example: conditional(2,4L,5L) = 4L
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
long conditional(long x, long y, long z) { // Checked.
    long mask = y ^ z;
    long con = ~(~0 + !(!x));
    long a = ~(con ^ mask);
    long part1 = a & y;
    long b = ~((~con) ^ mask);
    long part2 = b & z;
    // printf(
    //     "[Print] mask = %lx, con = %lx, a = %lx, b = %lx, part1 = %lx, part2
    //     "
    //     "= %lx\n",
    //     mask, con, a, b, part1, part2);
    return part1 | part2;
}
/*
 * bitMask - Generate a mask consisting of all 1's
 *   between lowbit and highbit
 *   Examples: bitMask(5L,3L) = 0x38L
 *   Assume 0 <= lowbit < 64, and 0 <= highbit < 64
 *   If lowbit > highbit, then mask should be all 0's
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
long bitMask(long highbit, long lowbit) {
    long len = highbit + (~lowbit+1);
    long sign = (len >> 63) & 1;
    len = 
    long mask = (1L << (len + 1)) + (~0);
    mask << lowbit;
    return 2L;
}
// 4
/*
 * isPalindrome - Return 1 if bit pattern in x is equal to its mirror image
 *   Example: isPalindrome(0x6F0F0123c480F0F6L) = 1L
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 70
 *   Rating: 4
 */
long isPalindrome(long x) { //Checked.
    // construct 0x00000000ffffffffL
    long tmp2 = (0xffL << 8) | 0xffL; // t = 0xffffL
    long t = (tmp2 << 16) | tmp2;
    long x2 = (x >> 32) & t;
    x = t & x;

    // 0x0000ffffL t
    // 0x00ff00ffL
    long tmp3 = (0xffL << 16) | 0xffL;
    // 0x0f0f0f0fL
    long tmp4 = (0x0fL << 8) | 0x0fL;
    tmp4 = (tmp4 << 16) | tmp4;
    // 0x33333333L
    long tmp5 = (0x33L << 8) | 0x33L;
    tmp5 = (tmp5 << 16) | tmp5;
    // 0x55555555L
    long tmp6 = (0x55L << 8) | 0x55L;
    tmp6 = (tmp6 << 16) | tmp6;

    x = ((x & tmp2) << 16) | (((x & (tmp2 << 16)) >> 16) & tmp2);
    // printf("[print] %lx\n", x);
    x = ((x & tmp3) << 8) | (((x & (tmp3 << 8)) >> 8) & tmp3);
    // printf("[print] %lx\n", x);
    x = ((x & tmp4) << 4) | (((x & (tmp4 << 4)) >> 4) & tmp4);
    // printf("[print] %lx\n", x);
    x = ((x & tmp5) << 2) | (((x & (tmp5 << 2)) >> 2) & tmp5);
    // printf("[print] %lx\n", x);
    x = ((x & tmp6) << 1) | (((x & (tmp6 << 1)) >> 1) & tmp6);
    // printf("[print] %lx\n", x);
    return !(x ^ x2);
}
/*
 * trueFiveEighths - multiplies by 5/8 rounding toward 0,
 *  avoiding errors due to overflow
 *  Examples:
 *    trueFiveEighths(11L) = 6L
 *    trueFiveEighths(-9L) = -5L
 *    trueFiveEighths(0x3000000000000000L) = 0x1E00000000000000L (no overflow)
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 20
 *  Rating: 4
 */
long trueFiveEighths(long x) {
    return 2L;
}
/*
 * logicalNeg - implement the ! operator, using all of
 *              the legal operators except !
 *   Examples: logicalNeg(3L) = 0L, logicalNeg(0L) = 1L
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
long logicalNeg(long x) { // Checked.
    return ((x | (~x + 1)) >> 63) + 1;
}
