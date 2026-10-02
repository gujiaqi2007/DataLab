/*
 * CS:APP Data Lab
 *
 * <gujiaqi>
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
  4. Interprets integer expressions using the Data Lab 32-bit bit-vector
     model: results outside the signed range retain their low 32 bits.


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
#include "bits.h"

// P1
/*
 * signMask - return a mask with only the most significant bit set (0x80000000)
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 2
 *   Rating: 1
 */
int signMask(void) {
  /* 1 左移到符号位即得 0x80000000 */
  return 1 << 31;
}

// P2
/*
 * bitXor - x^y using only ~ and &
 *   Example: bitXor(4, 5) = 1, bitXor(7, 7) = 0
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 2
 */
int bitXor(int x, int y) {
  /* 异或 = 有一个是 0 且不是都是 0： ~(~x & ~y) 是"至少一个 1"，~(x & y) 是"不都是 1"，
     两者同时成立恰是恰有一个 1 */
  return ~(~x & ~y) & ~(x & y);
}

// P3
/*
 * negativePart - return -x if x < 0, otherwise return 0
 *   Examples: negativePart(-10) = 10, negativePart(5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 3
 */
int negativePart(int x){
  /* x>>31 得到全 1（负）或全 0（非负）掩码；-x = ~x + 1；掩码为 0 时结果归零 */
  return (x >> 31) & (~x + 1);
}


// P4
/*
 * copyByteWithin - copy byte src of x to byte dst, leaving all other bytes unchanged
 *   Bytes are numbered from 0 (least significant) to 3 (most significant).
 *   You can assume 0 <= src <= 3 and 0 <= dst <= 3.
 *   Example: copyByteWithin(0x11223344, 0, 2) = 0x11443344
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int copyByteWithin(int x, int src, int dst) {
  /* 取出第 src 字节（算术右移的符号位污染会被 0xff 掩掉），
     清掉目标字节位置后把该字节摆过去 */
  int b = (x >> (src << 3)) & 0xff;
  int s = dst << 3;
  return (x & ~(0xff << s)) | (b << s);
}

// P5
/*
 * logicalShift - shift x to the right by n bits, using a logical shift
 *   Can assume that 0 <= n <= 31
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int logicalShift(int x, int n) {
  /* 先算术右移，再用掩码清掉高 n 个符号位；
     掩码 = ~(((1<<31)>>n)<<1)，n=0 时恰好为全 1 */
  return (x >> n) & ~(((1 << 31) >> n) << 1);
}

// P6
/*
 * swapNibblePairs - swap the low and high 4 bits within each byte of x
 *   Examples: swapNibblePairs(0xAB) = 0xBA
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 18
 *   Rating: 4
 */
int swapNibblePairs(int x) {
  /* 用 0x0f0f0f0f 分出低/高半字节，交换后拼回；掩码由 0x0f 翻倍生成 */
  int m = 0x0f | (0x0f << 8);
  m = m | (m << 16);
  return ((x & m) << 4) | ((x >> 4) & m);
}

// P7
/*
 * secondLowestZeroBit - return a mask that marks the position of the second least significant 0 bit
 *   Examples: secondLowestZeroBit(0xFFFFFFFA) = 0x4, secondLowestZeroBit(0x7FFFFFFF) = 0
 *             secondLowestZeroBit(-1) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 4
 */
int secondLowestZeroBit(int x) {
  /* y = ~x 后 0 变 1；z = y & (y-1) 抹掉最低的 1；
     再取 z 的最低位 1（z & (~z+1)）即原数第二个最低 0 位 */
  int y = ~x;
  int z = y & (y + ~0);
  return z & (~z + 1);
}

// P8
/*
 * oddParity - return the odd parity bit of x, that is,
 *      when the number of 1s in the binary representation of x is even, then the return 1, otherwise return 0.
 *   Examples: oddParity(5) = 1, oddParity(7) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 56
 *   Rating: 5
 */
int oddParity(int x) {
  /* 折半异或：32 位两两异或后，所有位的信息集中到最低位（1 的个数的奇偶性）；
     偶数个 1 时最低位为 0，取非得 1 */
  x = x ^ (x >> 16);
  x = x ^ (x >> 8);
  x = x ^ (x >> 4);
  x = x ^ (x >> 2);
  x = x ^ (x >> 1);
  return !(x & 1);
}

// P9
/*
 * rotateRightBits - rotate x to right by n bits
 *   you can assume n >= 0
 *   Examples: rotateRightBits(0x12345678, 8) = 0x78123456
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 5
 */
int rotateRightBits(int x, int n) {
  /* 实际位移量 s = n & 31；逻辑右移 s 位（掩码清符号位）拼上左移 (32-s)&31 位；
     s=0 时左移量取 0，避免移 32 位的未定义行为 */
  int s = n & 31;
  int right = (x >> s) & ~(((1 << 31) >> s) << 1);
  int left = x << ((33 + ~s) & 31);
  return right | left;
}

// P10
/*
 * roundEvenPow2 - round nonnegative x to the nearest multiple of 2^n.
 *   If x is exactly halfway between two multiples, choose the multiple whose
 *   quotient by 2^n is even.
 *   You can assume 0 <= x <= 0x3fffffff and 1 <= n <= 16.
 *   Examples: roundEvenPow2(10, 2) = 8, roundEvenPow2(14, 2) = 16
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 5
 */
int roundEvenPow2(int x, int n) {
  /* rounded = (x + half) 再清低位 = 四舍五入；
     需要修正的只有"恰好半路且向上取整后商为奇数"的情形（此时应向下） */
  int block = 1 << n;
  int mask = block + ~0;          /* 2^n - 1 */
  int r = x & mask;               /* 余数 */
  int half = block >> 1;
  int rounded = (x + half) & ~mask;
  int tie = !(r ^ half);                  /* 恰好半路 */
  int oddUp = (rounded >> n) & 1;         /* 向上取整结果为奇数 */
  int adj = tie & oddUp;                  /* 需要减回一个 block */
  int neg = (adj << 31) >> 31;            /* 把 0/1 拉成全 0/全 1 */
  return rounded + (neg & (~block + 1));
}

// P11
/*
 * midpointTowardFirst - return the exact mathematical midpoint (x+y)/2
 *   without overflow. If the exact midpoint lies halfway between two
 *   integers, choose the adjacent integer that is closer to the first
 *   argument x.
 *   Examples: midpointTowardFirst(4, 7) = 5,
 *             midpointTowardFirst(7, 4) = 6
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 32
 *   Rating: 5
 */
int midpointTowardFirst(int x, int y) {
  /* floor((x+y)/2) = (x>>1) + (y>>1) + (x和y都为奇数时的1)，全程不溢出；
     若 x+y 为奇数（中点是 .5）且 x >= y（向 x 靠即向上取整），再 +1。
     x >= y 用差值的符号位判断，异号时直接看 x 的符号（避免减法溢出） */
  int floorMid = (x >> 1) + (y >> 1) + ((x & y) & 1);
  int sumOdd = (x ^ y) & 1;
  int diff = x + ~y + 1;
  int diffSign = (x ^ y) >> 31;
  int lessMask = (diffSign & (x >> 31)) | (~diffSign & (diff >> 31)); /* x < y */
  return floorMid + ((~lessMask & 1) & sumOdd);
}


// P12
/*
 * isBetweenEitherOrder - return 1 when x lies in the inclusive interval whose
 *   endpoints are a and b. The endpoints may be given in either order.
 *   Example: isBetweenEitherOrder(5, 8, 3) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 48
 *   Rating: 7
 */
int isBetweenEitherOrder(int x, int a, int b) {
  /* x 在区间外 <=> x 比两个端点都小，或比两个端点都大。
     比较用无溢出的 lt(u,v)：同号看 u-v 符号位，异号看 u 的符号位 */
  int sgA = (x ^ a) >> 31;
  int sgB = (x ^ b) >> 31;
  int dxa = x + ~a + 1;                    /* x - a */
  int dxb = x + ~b + 1;                    /* x - b */
  int ltxa = (sgA & (x >> 31)) | (~sgA & (dxa >> 31));
  int ltxb = (sgB & (x >> 31)) | (~sgB & (dxb >> 31));
  int dax = ~dxa + 1;                      /* a - x */
  int dbx = ~dxb + 1;                      /* b - x */
  int ltax = (sgA & (a >> 31)) | (~sgA & (dax >> 31));
  int ltbx = (sgB & (b >> 31)) | (~sgB & (dbx >> 31));
  return !((ltxa & ltxb) | (ltax & ltbx));
}

// P13
/*
 * mul5Sat - return x*5, and if x*5 overflow, change the result to
 *   INT_MAX(0x7fffffff) or INT_MIN(0x80000000) correspondingly
 *   Examples: mul5Sat(1) = 0x5, mul5Sat(0x40000000) = 0x7fffffff
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 30
 *   Rating: 7
 */
int mul5Sat(int x) {
  /* 溢出阈值：正数 x >= 0x1999999A(=floor(TMax/5)+1)，负数 x <= 0xE6666666。
     用加常数看符号位实现无溢出比较：x+0x66666666 的 bit31 恰好在正溢出区
     （以及比 0x99999999 更小的负数）置位，x+0x19999999 的 bit31 覆盖剩余
     溢出区，两者并集正好等于全部溢出输入且无误报。c2 = c1 >> 2 */
  int c1 = 0x66 | (0x66 << 8);
  int five = (x << 2) + x;
  int c2, ovf, sat;
  c1 = c1 | (c1 << 16);            /* 0x66666666 */
  c2 = c1 >> 2;                    /* 0x19999999 */
  ovf = ((x + c1) >> 31) | ((x + c2) >> 31);
  sat = (x >> 31) ^ ~(1 << 31);
  return (ovf & sat) | (~ovf & five);
}

// P14
/*
 * classifyAdd3 - classify the exact mathematical sum x+y+z.
 *   Return 1 if the sum is greater than INT_MAX, -1 if it is less than
 *   INT_MIN, and 0 otherwise. You may not use a wider integer type.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 52
 *   Rating: 7
 */
int classifyAdd3(int x, int y, int z) {
  /* 分两步加，每步记录是否溢出及方向（+1/-1）。
     精确和 = s2 + k*2^32（k 为两次溢出方向之和，只能取 -1/0/1），
     且 k=1 必然超出 INT_MAX、k=-1 必然低于 INT_MIN，故返回 k 即可 */
  int s1 = x + y;
  int ovf1 = (~(x ^ y) & (s1 ^ x)) >> 31;      /* x+y 溢出（同号相加符号翻转） */
  int d1 = ovf1 & ((x >> 31) | 1);             /* 溢出方向：+1 或 -1 */
  int s2 = s1 + z;
  int ovf2 = (~(s1 ^ z) & (s2 ^ s1)) >> 31;
  int d2 = ovf2 & ((s1 >> 31) | 1);
  return d1 + d2;
}

// P15
/*
 * floatScaleThreeHalves - Return bit-level equivalent of expression f*3/2 for
 *   floating point argument f.
 *   Both the argument and return value are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   Use round-to-nearest-even. Preserve the sign of both +0 and -0.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 60
 *   Rating: 7
 */
unsigned floatScaleThreeHalves(unsigned uf) {
  /* 对有效数字（含隐含 1）乘 3 得 T，再把 T 缩小 1~2 位并重新对齐指数，
     右移时按 RNE 舍入；非规格数结果 < 2^24，sign|r 的编码同时覆盖
     结果仍为非规格数和恰好进位成最小规格数两种情况 */
  unsigned sign = uf & 0x80000000u;
  unsigned exp = (uf >> 23) & 0xFFu;
  unsigned frac = uf & 0x7FFFFFu;
  unsigned M, T, q, up, e2, f2;
  if (exp == 0xFFu)
    return uf;                       /* NaN / Inf 原样返回 */
  if (exp == 0u) {
    if (frac == 0u)
      return uf;                     /* ±0 */
    T = frac + (frac << 1);          /* 3*frac */
    q = T >> 1;
    up = (T & 1u) & (q & 1u);        /* 恰半路且向下取整为奇数时进位 */
    return sign | (q + up);
  }
  M = frac | 0x800000u;
  T = M + (M << 1);                  /* 3M ∈ [1.5*2^24, 1.5*2^25) */
  if (T >> 25) {                     /* 需右移 2 位，指数 +1 */
    q = T >> 2;
    up = (((T & 3u) + (q & 1u) + 1u) >> 2) & 1u;
    e2 = exp + 1u;
  } else {                           /* 右移 1 位，指数不变 */
    q = T >> 1;
    up = (T & 1u) & (q & 1u);
    e2 = exp;
  }
  f2 = (q + up) - 0x800000u;         /* 若为 0x800000 会自然进位到指数域 */
  if (e2 >= 0xFFu)
    return sign | 0x7F800000u;       /* 溢出为无穷 */
  return sign + (e2 << 23) + f2;
}

// P16
/*
 * floatRoundEven - round the floating-point value represented by uf to the
 *   nearest integer, with halfway cases rounded to the even integer. Return
 *   the bit-level representation of that integer as a single-precision float.
 *   If rounding produces zero, preserve the input sign; thus a negative
 *   value that rounds to zero returns -0. When uf is NaN or infinity,
 *   return uf unchanged.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 65
 *   Rating: 10
 */
unsigned floatRoundEven(unsigned uf) {
  /* 按指数分档：e<=125 |v|<0.5 舍到 ±0；e=126 |v|∈[0.5,1)，仅 0.5 处取 0；
     e>=150 本身就是整数；中间档把 1.frac 右移 s=150-e 位并按 RNE 舍入，
     (I<<s)-0x800000 恰好同时完成尾数编码和进位到指数域 */
  unsigned sign = uf & 0x80000000u;
  unsigned e = (uf >> 23) & 0xFFu;
  unsigned frac = uf & 0x7FFFFFu;
  unsigned s, M, q, rem, half, I;
  if (e == 0xFFu)
    return uf;                       /* NaN / Inf */
  if (e <= 125u)
    return sign;                     /* |v| < 0.5，保留符号的 0 */
  if (e == 126u) {
    if (frac == 0u)
      return sign;                   /* ±0.5 半路取偶（0），保留符号 */
    return sign | 0x3F800000u;       /* (0.5,1) 舍到 ±1 */
  }
  if (e >= 150u)
    return uf;                       /* 已是整数 */
  s = 150u - e;                      /* 需要舍弃的尾数位数 1..23 */
  M = frac | 0x800000u;
  q = M >> s;
  rem = M & ((1u << s) - 1u);
  half = 1u << (s - 1u);
  I = q + ((rem > half) || ((rem == half) && (q & 1u)));  /* RNE */
  return sign + (e << 23) + ((I << s) - 0x800000u);
}

// P17
/*
 * float_i2f - Return bit-level equivalent of expression (float) x.
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of
 *   a single-precision floating point values.
 *   Legal ops: Any integer / unsigned operations incl. ||, &&. also if, while
 *   Max ops: 40
 *   Rating: 10
 */
unsigned float_i2f(int x) {
  /* 取绝对值后左移规格化（最高位到 bit31），指数 = 剩余位数 + 127；
     尾数取接下来 23 位，低 8 位按 RNE 舍入（恰 0x80 时向偶数对齐），
     进位覆盖到指数时指数 +1。INT_MIN 的绝对值利用回绕得到 0x80000000 */
  unsigned sign = 0u;
  unsigned ux;
  unsigned e = 31u;
  unsigned frac, rem;
  if (x == 0)
    return 0u;
  if (x < 0) {
    sign = 0x80000000u;
    ux = -x;                         /* INT_MIN 时回绕，位型仍正确 */
  } else {
    ux = x;
  }
  while (!(ux & 0x80000000u)) {
    ux <<= 1;
    e--;
  }
  frac = (ux >> 8) & 0x7FFFFFu;
  rem = ux & 0xFFu;
  if (rem > 0x80u || (rem == 0x80u && (frac & 1u)))
    frac++;
  if (frac == 0x800000u) {           /* 舍入进位 */
    frac = 0u;
    e++;
  }
  return sign | ((e + 127u) << 23) | frac;
}



// P18
/*
 * bitCount - return count of number of 1's in the binary representation of x
 *   Examples: bitCount(5) = 2, bitCount(7) = 3
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 40
 *   Rating: 10
 */
int bitCount(int x) {
  /* 分治：相邻 2 位、4 位、8 位分组求和，最后字节折叠；
     掩码 0x55555555/0x33333333/0x0f0f0f0f 由小常量翻倍生成 */
  int m1 = 0x55 | (0x55 << 8);
  int m2 = 0x33 | (0x33 << 8);
  int m4 = 0x0F | (0x0F << 8);
  m1 = m1 | (m1 << 16);
  m2 = m2 | (m2 << 16);
  m4 = m4 | (m4 << 16);
  x = (x & m1) + ((x >> 1) & m1);
  x = (x & m2) + ((x >> 2) & m2);
  x = (x & m4) + ((x >> 4) & m4);
  x = x + (x >> 8);
  x = x + (x >> 16);
  return x & 0x3F;
}

// P19
/*
 * bitReverse - Reverse bits in an 32-bit integer
 *   Examples: bitReverse(0x80000004) = 0x20000001
 *             bitReverse(0x7FFFFFFF) = 0xFFFFFFFE
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 34
 *   Rating: 10
 */
int bitReverse(int x)
{
  /* 先整体反转字节顺序，再在字节内做 4/2/1 位粒度的分治交换；
     掩码互相推导省操作数：m4=0x0f0f0f0f，m2=m4^(m4<<2)，m1=m2^(m2<<1)，m3=0xff00 */
  int m4 = 0x0F | (0x0F << 8);
  int m3 = 0xFF << 8;
  int m2, m1;
  m4 = m4 | (m4 << 16);
  m2 = m4 ^ (m4 << 2);
  m1 = m2 ^ (m2 << 1);
  x = (x << 24) | ((x & m3) << 8) | ((x >> 8) & m3) | ((x >> 24) & 0xFF);
  x = ((x & m4) << 4) | ((x >> 4) & m4);
  x = ((x & m2) << 2) | ((x >> 2) & m2);
  x = ((x & m1) << 1) | ((x >> 1) & m1);
  return x;
}
