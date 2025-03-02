// This is a test program with decimal lib

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// ---------- decimal lib start ----------

#define PREC 2100
#define Decimal_len (PREC / 9 + 1)

const int Decimal_mo = 1000000000;

typedef struct {
	bool is_neg;
	long long integer;
	int data[Decimal_len];
} Decimal;

Decimal new_decimal();
Decimal new_decimal_s(const char *s);
Decimal new_decimal_i(int x);
Decimal new_decimal_l(long long x);
Decimal new_decimal_f(double x);

bool is_zero_d(Decimal a);

// p (p > 0) is the number of digits after the decimal point
void to_string_d(Decimal a, char *s, int p);
double to_double_d(Decimal a);

Decimal add_dd(Decimal a, Decimal b);
Decimal add_di(Decimal a, int x);
Decimal add_id(int x, Decimal a);
Decimal add_dl(Decimal a, long long x);
Decimal add_ld(long long x, Decimal a);
Decimal add_df(Decimal a, double x);
Decimal add_fd(double x, Decimal a);

Decimal sub_dd(Decimal a, Decimal b);
Decimal sub_di(Decimal a, int x);
Decimal sub_id(int x, Decimal a);
Decimal sub_dl(Decimal a, long long x);
Decimal sub_ld(long long x, Decimal a);
Decimal sub_df(Decimal a, double x);
Decimal sub_fd(double x, Decimal a);

Decimal mul_di(Decimal a, int x);
Decimal mul_id(int x, Decimal a);

Decimal div_di(Decimal a, int x);

Decimal neg_d(Decimal a);

// <
bool cmp_lt(Decimal a, Decimal b);
// >
bool cmp_gt(Decimal a, Decimal b);
// <=
bool cmp_le(Decimal a, Decimal b);
// >=
bool cmp_ge(Decimal a, Decimal b);
// ==
bool cmp_eq(Decimal a, Decimal b);
// !=
bool cmp_ne(Decimal a, Decimal b);


// implementations

Decimal new_decimal() {
	Decimal ret;
	ret.is_neg = false;
	ret.integer = 0;
	memset(ret.data, 0, Decimal_len * sizeof(int));
	return ret;
}

Decimal new_decimal_s(const char *s) {
	Decimal ret = new_decimal();
	
	// find the first digit or the negative sign
	while (*s != 0) {
		if (*s == '-') {
			ret.is_neg = true;
			++s;
			break;
		} else if (*s >= 48 && *s <= 57) {
			break;
		}
		++s;
	}
	
	// read the integer part
	while (*s >= 48 && *s <= 57) {
		ret.integer = ret.integer * 10 + *s - 48;
		++s;
	}
	
	// read the decimal part
	if (*s == '.') {
		int pos = 0;
		int x = Decimal_mo / 10;
		
		++s;
		while (pos < Decimal_len && *s >= 48 && *s <= 57) {
			ret.data[pos] += (*s - 48) * x;
			++s;
			x /= 10;
			if (x == 0) {
				++pos;
				x = Decimal_mo / 10;
			}
		}
	}
	
	return ret;
}

Decimal new_decimal_i(int x) {
	Decimal ret = new_decimal();
	
	if (x < 0) {
		ret.is_neg = true;
		x = -x;
	}
	
	ret.integer = x;
	
	return ret;
}

Decimal new_decimal_l(long long x) {
	Decimal ret = new_decimal();
	
	if (x < 0) {
		ret.is_neg = true;
		x = -x;
	}
	
	ret.integer = x;
	
	return ret;
}

Decimal new_decimal_f(double x) {
	Decimal ret = new_decimal();
	
	if (x < 0) {
		ret.is_neg = true;
		x = -x;
	}
	
	ret.integer = (long long)x;
	x -= ret.integer;
	
	int i;
	for (i = 0; i < Decimal_len; i++) {
		x *= Decimal_mo;
		if (x < 0) x = 0;
		ret.data[i] = (int)x;
		x -= ret.data[i];
	}
	
	return ret;
}

bool is_zero_d(Decimal a) {
	if (a.integer) return false;
	int i;
	for (i = 0; i < Decimal_len; i++) {
		if (a.data[i]) return false;
	}
	return true;
}

void to_string_d(Decimal a, char *s, int p) {
	if (a.is_neg && !is_zero_d(a)) {
		*s++ = '-';
	}
	
	// append the integer part to s
	long long x = a.integer;
	if (x == 0) {
		*s++ = 48;
	} else {
		char _[30];
		int cnt = 0;
		while (x) {
			_[cnt++] = x % 10;
			x /= 10;
		}
		while (cnt--) {
			*s++ = _[cnt] + 48;
		}
	}
	
	// append the decimal part to s
	*s++ = '.';
	int i;
	for (i = 0; i < Decimal_len; i++) {
		// append a.data[i] as "%09d"
		int x = Decimal_mo / 10;
		int tmp = a.data[i];
		while (x) {
			*s++ = 48 + tmp / x;
			tmp %= x;
			x /= 10;
			if (--p == 0) {
				break;
			}
		}
		if (p == 0) break;
	}
	if (p > 0) {
		while (p--) {
			*s++ = '0';
		}
	}
	
	*s++ = '\0';
}

double to_double_d(Decimal a) {
	double ret = a.integer;
	
	double k = 1.0;
	int i;
	for (i = 0; i < Decimal_len; i++) {
		k /= Decimal_mo;
		ret += k * a.data[i];
	}
	
	if (a.is_neg) {
		ret = -ret;
	}
	
	return ret;
}

bool cmp_lt(Decimal a, Decimal b) {
	if (a.is_neg != b.is_neg) {
		return a.is_neg && (!is_zero_d(a) || !is_zero_d(b));
	} else if (!a.is_neg) {
		// a, b >= 0
		if (a.integer != b.integer) {
			return a.integer < b.integer;
		}
		int i;
		for (i = 0; i < Decimal_len; i++) {
			if (a.data[i] != b.data[i]) {
				return a.data[i] < b.data[i];
			}
		}
		return false;
	} else {
		// a, b <= 0
		if (a.integer != b.integer) {
			return a.integer > b.integer;
		}
		int i;
		for (i = 0; i < Decimal_len; i++) {
			if (a.data[i] != b.data[i]) {
				return a.data[i] > b.data[i];
			}
		}
		return false;
	}
}

bool cmp_gt(Decimal a, Decimal b) {
	if (a.is_neg != b.is_neg) {
		return !a.is_neg && (!is_zero_d(a) || !is_zero_d(b));
	} else if (!a.is_neg) {
		// a, b >= 0
		if (a.integer != b.integer) {
			return a.integer > b.integer;
		}
		int i;
		for (i = 0; i < Decimal_len; i++) {
			if (a.data[i] != b.data[i]) {
				return a.data[i] > b.data[i];
			}
		}
		return false;
	} else {
		// a, b <= 0
		if (a.integer != b.integer) {
			return a.integer < b.integer;
		}
		int i;
		for (i = 0; i < Decimal_len; i++) {
			if (a.data[i] != b.data[i]) {
				return a.data[i] < b.data[i];
			}
		}
		return false;
	}
}

bool cmp_le(Decimal a, Decimal b) {
	if (a.is_neg != b.is_neg) {
		return a.is_neg || (is_zero_d(a) && is_zero_d(b));
	} else if (!a.is_neg) {
		// a, b >= 0
		if (a.integer != b.integer) {
			return a.integer < b.integer;
		}
		int i;
		for (i = 0; i < Decimal_len; i++) {
			if (a.data[i] != b.data[i]) {
				return a.data[i] < b.data[i];
			}
		}
		return true;
	} else {
		// a, b <= 0
		if (a.integer != b.integer) {
			return a.integer > b.integer;
		}
		int i;
		for (i = 0; i < Decimal_len; i++) {
			if (a.data[i] != b.data[i]) {
				return a.data[i] > b.data[i];
			}
		}
		return true;
	}
}

bool cmp_ge(Decimal a, Decimal b) {
	if (a.is_neg != b.is_neg) {
		return !a.is_neg || (is_zero_d(a) && is_zero_d(b));
	} else if (!a.is_neg) {
		// a, b >= 0
		if (a.integer != b.integer) {
			return a.integer > b.integer;
		}
		int i;
		for (i = 0; i < Decimal_len; i++) {
			if (a.data[i] != b.data[i]) {
				return a.data[i] > b.data[i];
			}
		}
		return true;
	} else {
		// a, b <= 0
		if (a.integer != b.integer) {
			return a.integer < b.integer;
		}
		int i;
		for (i = 0; i < Decimal_len; i++) {
			if (a.data[i] != b.data[i]) {
				return a.data[i] < b.data[i];
			}
		}
		return true;
	}
}

bool cmp_eq(Decimal a, Decimal b) {
	if (is_zero_d(a) && is_zero_d(b)) return true;
	if (a.is_neg != b.is_neg) return false;
	if (a.integer != b.integer) return false;
	int i;
	for (i = 0; i < Decimal_len; i++) {
		if (a.data[i] != b.data[i]) return false;
	}
	return true;
}

bool cmp_ne(Decimal a, Decimal b) {
	return !cmp_eq(a, b);
}

Decimal neg_d(Decimal a) {
	Decimal ret = a;
	// -0 = 0
	if (!ret.is_neg && ret.integer == 0) {
		int i;
		for (i = 0; i < Decimal_len; i++) {
			if (ret.data[i] != 0) break;
		}
		if (i < Decimal_len) {
			ret.is_neg = true;
		}
	} else {
		ret.is_neg ^= 1;
	}
	return ret;
}

Decimal add_dd(Decimal a, Decimal b) {
	if (a.is_neg == b.is_neg) {
		Decimal ret = a;
		bool last = true;
		int i;
		for (i = Decimal_len - 1; i >= 0; i--) {
			ret.data[i] += b.data[i] + last;
			if (ret.data[i] >= Decimal_mo) {
				ret.data[i] -= Decimal_mo;
				last = true;
			} else {
				last = false;
			}
		}
		ret.integer += b.integer + last;
		return ret;
	} else if (!a.is_neg) {
		// a - |b|
		return sub_dd(a, neg_d(b));
	} else {
		// b - |a|
		return sub_dd(b, neg_d(a));
	}
}

Decimal sub_dd(Decimal a, Decimal b) {
	if (!a.is_neg && !b.is_neg) {
		if (cmp_ge(a, b)) {
			Decimal ret = a;
			bool last = false;
			int i;
			for (i = Decimal_len - 1; i >= 0; i--) {
				ret.data[i] -= b.data[i] + last;
				if (ret.data[i] < 0) {
					ret.data[i] += Decimal_mo;
					last = true;
				} else {
					last = false;
				}
			}
			ret.integer -= b.integer + last;
			return ret;
		} else {
			Decimal ret = b;
			bool last = false;
			int i;
			for (i = Decimal_len - 1; i >= 0; i--) {
				ret.data[i] -= a.data[i] + last;
				if (ret.data[i] < 0) {
					ret.data[i] += Decimal_mo;
					last = true;
				} else {
					last = false;
				}
			}
			ret.integer -= a.integer + last;
			ret.is_neg = true;
			return ret;
		}
	} else if (a.is_neg && b.is_neg) {
		// a - b = (-b) - (-a)
		return sub_dd(neg_d(b), neg_d(a));
	} else if (a.is_neg) {
		// -|a| - b
		return neg_d(add_dd(neg_d(a), b));
	} else {
		// a - -|b|
		return add_dd(a, neg_d(b));
	}
}

Decimal add_dl(Decimal a, long long x) {
	if (!a.is_neg) {
		if (a.integer + x >= 0) {
			a.integer += x;
		} else {
			bool last = false;
			int i;
			for (i = Decimal_len - 1; i >= 0; i--) {
				if (last || a.data[i]) {
					a.data[i] = Decimal_mo - a.data[i] - last;
					last = true;
				} else {
					last = false;
				}
			}
			a.integer = -x - a.integer - last;
			a.is_neg = true;
		}
	} else {
		if (a.integer - x >= 0) {
			a.integer -= x;
		} else {
			bool last = false;
			int i;
			for (i = Decimal_len - 1; i >= 0; i--) {
				if (last || a.data[i]) {
					a.data[i] = Decimal_mo - a.data[i] - last;
					last = true;
				} else {
					last = false;
				}
			}
			a.integer = x - a.integer - last;
			a.is_neg = false;
		}
	}
	return a;
}

Decimal add_ld(long long x, Decimal a) {
	return add_dl(a, x);
}

Decimal add_di(Decimal a, int x) {
	return add_dl(a, x);
}

Decimal add_id(int x, Decimal a) {
	return add_dl(a, x);
}

Decimal sub_dl(Decimal a, long long x) {
	return add_dl(a, -x);
}

Decimal sub_ld(long long x, Decimal a) {
	return neg_d(add_dl(a, -x));
}

Decimal sub_di(Decimal a, int x) {
	return add_dl(a, -x);
}

Decimal sub_id(int x, Decimal a) {
	return neg_d(add_dl(a, -x));
}

Decimal add_df(Decimal a, double x) {
	return add_dd(a, new_decimal_f(x));
}

Decimal add_fd(double x, Decimal a) {
	return add_dd(new_decimal_f(x), a);
}

Decimal sub_df(Decimal a, double x) {
	return add_dd(a, new_decimal_f(-x));
}

Decimal sub_fd(double x, Decimal a) {
	return neg_d(add_dd(a, new_decimal_f(-x)));
}

Decimal mul_di(Decimal a, int x) {
	if (x < 0) {
		a.is_neg ^= 1;
		x = -x;
	} else if (x == 0) {
		return new_decimal();
	}
	
	int last = 0;
	int i;
	for (i = Decimal_len - 1; i >= 0; i--) {
		long long tmp = 1LL * a.data[i] * x + last;
		last = tmp / Decimal_mo;
		a.data[i] = tmp - 1LL * last * Decimal_mo;
	}
	a.integer = a.integer * x + last;
	
	return a;
}

Decimal mul_id(int x, Decimal a) {
	return mul_di(a, x);
}

Decimal div_di(Decimal a, int x) {
	if (x < 0) {
		a.is_neg ^= 1;
		x = -x;
	}
	
	int last = a.integer % x;
	a.integer /= x;
	
	int i;
	for (i = 0; i < Decimal_len; i++) {
		long long tmp = 1LL * last * Decimal_mo + a.data[i];
		a.data[i] = tmp / x;
		last = tmp - 1LL * a.data[i] * x;
	}
	
	if (a.is_neg && a.integer == 0) {
		for (i = 0; i < Decimal_len; i++) {
			if (a.data[i] != 0) {
				break;
			}
		}
		if (i == Decimal_len) {
			a.is_neg = false;
		}
	}
	
	return a;
}

// ---------- decimal lib end ----------

#include <stdio.h>

const char * to_TF(bool x) {
	return x ? "true" : "false";
}

int main() {
	static char buf[3000];
	
	// input output test
	printf("Testing IO ...\n");
	Decimal a = new_decimal_s("-233.123454270204572407233464200700");
	to_string_d(a, buf, 50);
	printf("%s\n", buf);
	
	a = new_decimal("-0");
	to_string_d(a, buf, 50);
	printf("%s\n", buf);
	
	// + - * / < test
	printf("Testing + - * / < ...\n");
	a = new_decimal_i(100);
	printf("a = %s\n", (to_string_d(a, buf, 50), buf));
	a = div_di(a, 24);
	printf("a/24 = %s\n", (to_string_d(a, buf, 50), buf));
	a = add_di(a, 123);
	printf("a/24+123 = %s\n", (to_string_d(a, buf, 50), buf));
	a = mul_di(a, 234);
	printf("(a/24+123)*234 = %s\n", (to_string_d(a, buf, 50), buf));
	
	printf("(a/24+123)*234 < 29756.9999999999999999 : ");
	printf("%s\n", to_TF(cmp_lt(a, new_decimal("29756.9999999999999999"))));
	
	// double <-> decimal test
	printf("Testing double <-> Decimal ...\n");
	printf("to_double_d(a) = %.15lf\n", to_double_d(a));
	
	a = new_decimal_f(0.123456789);
	printf("0.123456789 = %.15lf\n", to_double_d(a));
	printf("0.123456789 = %s\n", (to_string_d(a, buf, 50), buf));
	a = mul_di(a, 23333333);
	printf("0.123456789*23333333 = %.15lf\n", to_double_d(a));
	printf("0.123456789*23333333 = %s\n", (to_string_d(a, buf, 50), buf));
	
	// < > <= >= == != test
	printf("Testing < > <= >= == != ...\n");
	printf("1234.567 < 1234.568 : ");
	printf("%s\n", to_TF(cmp_lt(new_decimal_s("1234.567"), new_decimal_s("1234.568"))));
	
	printf("1234.567 < -1234.568 : ");
	printf("%s\n", to_TF(cmp_lt(new_decimal_s("1234.567"), new_decimal_s("-1234.568"))));
	
	printf("-1234.567 < 1234.568 : ");
	printf("%s\n", to_TF(cmp_lt(new_decimal_s("-1234.567"), new_decimal_s("1234.568"))));
	
	printf("-1234.567 < -1234.568 : ");
	printf("%s\n", to_TF(cmp_lt(new_decimal_s("-1234.567"), new_decimal_s("-1234.568"))));
	
	
	printf("1234.567 < 1234.567 : ");
	printf("%s\n", to_TF(cmp_lt(new_decimal_s("1234.567"), new_decimal_s("1234.567"))));
	
	printf("1234.567 <= 1234.567 : ");
	printf("%s\n", to_TF(cmp_le(new_decimal_s("1234.567"), new_decimal_s("1234.567"))));
	
	printf("1234.567 > 1234.567 : ");
	printf("%s\n", to_TF(cmp_gt(new_decimal_s("1234.567"), new_decimal_s("1234.567"))));
	
	printf("1234.567 >= 1234.567 : ");
	printf("%s\n", to_TF(cmp_ge(new_decimal_s("1234.567"), new_decimal_s("1234.567"))));
	
	
	printf("-1234.567 < -1234.567 : ");
	printf("%s\n", to_TF(cmp_lt(new_decimal_s("-1234.567"), new_decimal_s("-1234.567"))));
	
	printf("-1234.567 <= -1234.567 : ");
	printf("%s\n", to_TF(cmp_le(new_decimal_s("-1234.567"), new_decimal_s("-1234.567"))));
	
	printf("-1234.567 > -1234.567 : ");
	printf("%s\n", to_TF(cmp_gt(new_decimal_s("-1234.567"), new_decimal_s("-1234.567"))));
	
	printf("-1234.567 >= -1234.567 : ");
	printf("%s\n", to_TF(cmp_ge(new_decimal_s("-1234.567"), new_decimal_s("-1234.567"))));
	
	
	printf("1234.567 == 1234.567 : ");
	printf("%s\n", to_TF(cmp_eq(new_decimal_s("1234.567"), new_decimal_s("1234.567"))));
	
	printf("1234.567 == 1234.568 : ");
	printf("%s\n", to_TF(cmp_eq(new_decimal_s("1234.567"), new_decimal_s("1234.568"))));
	
	printf("1234.567 == -1234.567 : ");
	printf("%s\n", to_TF(cmp_eq(new_decimal_s("1234.567"), new_decimal_s("-1234.567"))));
	
	
	printf("1234.567 != 1234.567 : ");
	printf("%s\n", to_TF(cmp_ne(new_decimal_s("1234.567"), new_decimal_s("1234.567"))));
	
	printf("1234.567 != 1234.568 : ");
	printf("%s\n", to_TF(cmp_ne(new_decimal_s("1234.567"), new_decimal_s("1234.568"))));
	
	printf("1234.567 != -1234.567 : ");
	printf("%s\n", to_TF(cmp_ne(new_decimal_s("1234.567"), new_decimal_s("-1234.567"))));
	
	
	printf("-0 == 0 : ");
	printf("%s\n", to_TF(cmp_eq(new_decimal_s("-0"), new_decimal_s("0"))));
	
	printf("-0 != 0 : ");
	printf("%s\n", to_TF(cmp_ne(new_decimal_s("-0"), new_decimal_s("0"))));
	
	printf("-0 < 0 : ");
	printf("%s\n", to_TF(cmp_lt(new_decimal_s("-0"), new_decimal_s("0"))));
	
	printf("-0 > 0 : ");
	printf("%s\n", to_TF(cmp_gt(new_decimal_s("-0"), new_decimal_s("0"))));
	
	printf("-0 <= 0 : ");
	printf("%s\n", to_TF(cmp_le(new_decimal_s("-0"), new_decimal_s("0"))));
	
	printf("-0 >= 0 : ");
	printf("%s\n", to_TF(cmp_ge(new_decimal_s("-0"), new_decimal_s("0"))));
	
	// + -(unary) test
	printf("Testing + -(unary) ...\n");
	a = new_decimal_f(1.0 / 3.0);
	printf("1/3 = %s\n", (to_string_d(a, buf, 50), buf));
	
	a = add_di(a, 233);
	printf("1/3+233 = %s\n", (to_string_d(a, buf, 50), buf));
	
	a = sub_di(a, 235);
	printf("1/3-2 = %s\n", (to_string_d(a, buf, 50), buf));
	
	a = add_di(a, 1);
	printf("1/3-1 = %s\n", (to_string_d(a, buf, 50), buf));
	
	a = add_di(a, 1);
	printf("1/3 = %s\n", (to_string_d(a, buf, 50), buf));
	
	printf("-1/3 = %s\n", (to_string_d(neg_d(a), buf, 50), buf));
	
	a = new_decimal_f(0.0);
	printf("-0 = %s\n", (to_string_d(neg_d(a), buf, 50), buf));
	
	a = sub_di(a, 10);
	printf("-10 = %s\n", (to_string_d(a, buf, 50), buf));
	
	// * / negative test
	printf("Testing * / with negative numbers ...\n");
	a = new_decimal_f(-1.0 / 6.0);
	printf("-1/6 = %s\n", (to_string_d(a, buf, 50), buf));
	a = mul_di(a, 7);
	printf("-1/6*7 = %s\n", (to_string_d(a, buf, 50), buf));
	a = mul_di(a, -3);
	printf("-1/6*7*(-3) = %s\n", (to_string_d(a, buf, 50), buf));
	a = div_di(a, -6);
	printf("-1/6*7*(-3)/(-6) = %s\n", (to_string_d(a, buf, 50), buf));
	a = mul_di(a, 0);
	printf("-1/6*7*(-3)/(-6)*0 = %s\n", (to_string_d(a, buf, 50), buf));
	
	// + - * / test
	printf("Testing + - * / ...\n");
	printf("1/3+2 = %s\n", (to_string_d(add_di(new_decimal_f(1.0 / 3.0), 2), buf, 50), buf));
	printf("1/3+2 = %s\n", (to_string_d(add_di(div_di(new_decimal_f(1.0), 3), 2), buf, 50), buf));
	printf("1/3+2 = %s\n", (to_string_d(add_dd(div_di(new_decimal_f(1.0), 3), new_decimal_f(2.0)), buf, 50), buf));
	
	printf("1/3+(-2) = %s\n", (to_string_d(add_di(new_decimal_f(1.0 / 3.0), -2), buf, 50), buf));
	printf("1/3+(-2) = %s\n", (to_string_d(add_di(div_di(new_decimal_f(1.0), 3), -2), buf, 50), buf));
	printf("1/3+(-2) = %s\n", (to_string_d(add_dd(div_di(new_decimal_f(1.0), 3), new_decimal_f(-2.0)), buf, 50), buf));
	
	printf("-1/3+2 = %s\n", (to_string_d(add_di(new_decimal_f(-1.0 / 3.0), 2), buf, 50), buf));
	printf("-1/3+2 = %s\n", (to_string_d(add_di(div_di(new_decimal_f(-1.0), 3), 2), buf, 50), buf));
	printf("-1/3+2 = %s\n", (to_string_d(add_dd(div_di(new_decimal_f(-1.0), 3), new_decimal_f(2.0)), buf, 50), buf));
	
	printf("1/3-2 = %s\n", (to_string_d(sub_di(new_decimal_f(1.0 / 3.0), 2), buf, 50), buf));
	printf("1/3-2 = %s\n", (to_string_d(sub_di(div_di(new_decimal_f(1.0), 3), 2), buf, 50), buf));
	printf("1/3-2 = %s\n", (to_string_d(sub_dd(div_di(new_decimal_f(1.0), 3), new_decimal_f(2.0)), buf, 50), buf));
	
	printf("-1/3-2 = %s\n", (to_string_d(sub_di(neg_d(new_decimal_f(1.0 / 3.0)), 2), buf, 50), buf));
	printf("-1/3-2 = %s\n", (to_string_d(sub_di(div_di(neg_d(new_decimal_f(1.0)), 3), 2), buf, 50), buf));
	printf("-1/3-2 = %s\n", (to_string_d(sub_dd(div_di(neg_d(new_decimal_f(1.0)), 3), new_decimal_f(2.0)), buf, 50), buf));
	
	printf("1/-3+2 = %s\n", (to_string_d(add_di(new_decimal_f(1.0 / -3.0), 2), buf, 50), buf));
	printf("1/-3+2 = %s\n", (to_string_d(add_di(div_di(new_decimal_f(1.0), -3), 2), buf, 50), buf));
	printf("1/-3+2 = %s\n", (to_string_d(add_dd(div_di(new_decimal_f(1.0), -3), new_decimal_f(2.0)), buf, 50), buf));
	
	printf("-1/-3+2 = %s\n", (to_string_d(add_di(new_decimal_f(-1.0 / -3.0), 2), buf, 50), buf));
	printf("-1/-3+2 = %s\n", (to_string_d(add_di(div_di(new_decimal_f(-1.0), -3), 2), buf, 50), buf));
	printf("-1/-3+2 = %s\n", (to_string_d(add_dd(div_di(new_decimal_f(-1.0), -3), new_decimal_f(2.0)), buf, 50), buf));
	
	printf("1/6*11 = %s\n", (to_string_d(mul_di(div_di(new_decimal_f(1.0), 6), 11), buf, 50), buf));
	printf("1/6*-11 = %s\n", (to_string_d(mul_di(div_di(new_decimal_f(1.0), 6), -11), buf, 50), buf));
	printf("1/-6*-11 = %s\n", (to_string_d(mul_di(div_di(new_decimal_f(1.0), -6), -11), buf, 50), buf));
	
	printf("1/7-1/6 = %s\n", (to_string_d(sub_dd(div_di(new_decimal_f(1.0), 7), div_di(new_decimal_f(1.0), 6)), buf, 50), buf));
	
	// Calculate e = 1 / 0! + 1 / 1! + 1 / 2! + ...
	Decimal ans = new_decimal_i(0);
	Decimal tmp = new_decimal_i(1);
	int i;
	for (i = 1; i <= 1000; i++) {
		ans = add_dd(ans, tmp);
		tmp = div_di(tmp, i);
	}
	printf("e = %s\n", (to_string_d(ans, buf, 2000), buf));
	
	return 0;
}
