/*
 * Host checks for the integer number primitives: luai_numpow (constant
 * folding and OP_POW) and luaA_strtol (lexer numerals and tonumber).
 *
 *   cc -I src -o numbers tests/numbers.c && ./numbers
 */

#define lobject_c
#include "luaconf.h"
#include "llibc.c"

#include <stdio.h>
#include <string.h>

static int failures = 0;

static void pow_case(long a, long b, long expected) {
  long got = luai_numpowimpl(a, b);
  if (got != expected) {
    printf("FAIL %ld^%ld = %ld, expected %ld\n", a, b, got, expected);
    failures++;
  }
}

static void strtol_case(const char *s, int base, long expected, int consumed) {
  char *end = (char *)0x1; /* anything but s, so an unset endptr shows */
  long got = luaA_strtol(s, &end, base);
  if ((got != expected) || (end != s + consumed)) {
    printf("FAIL strtol(\"%s\", %d) = %ld, end +%ld, expected %ld, end +%d\n",
           s, base, got, (long)(end - s), expected, consumed);
    failures++;
  }
}

int main(void) {
  pow_case(2, 10, 1024);
  pow_case(3, 0, 1);
  pow_case(0, 0, 1);
  pow_case(-3, 3, -27);
  pow_case(10, 9, 1000000000);
  pow_case(2, -1, 0);
  pow_case(1, -5, 1);
  pow_case(-1, -3, -1);
  pow_case(-1, -4, 1);
  pow_case(0, -1, 0);

  strtol_case("10", 10, 10, 2);
  strtol_case("010", 10, 10, 3);
  strtol_case("00", 10, 0, 2);
  strtol_case("0", 10, 0, 1);
  strtol_case("0.5", 10, 0, 1);
  strtol_case("-010", 10, -10, 4);
  strtol_case("  42 ", 10, 42, 4);
  strtol_case("", 10, 0, 0);
  strtol_case("   ", 10, 0, 0);
  strtol_case("-", 10, 0, 0);
  strtol_case("abc", 10, 0, 0);
  strtol_case("0x1F", 16, 31, 4);
  strtol_case("-0x10", 16, -16, 5);
  strtol_case("0x", 16, 0, 1);
  strtol_case("0x1F", 10, 0, 1);
  strtol_case("017", 0, 15, 3);
  strtol_case("0x1f", 0, 31, 4);
  strtol_case("17", 0, 17, 2);
  strtol_case("z", 36, 35, 1);
  strtol_case("1", 1, 0, 0);

  if (failures) {
    printf("%d failure(s)\n", failures);
    return 1;
  }
  printf("numbers: all checks passed\n");
  return 0;
}
