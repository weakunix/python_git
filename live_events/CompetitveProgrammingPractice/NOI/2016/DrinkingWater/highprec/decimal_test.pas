// This is a test program with decimal lib

uses math;

// ---------- decimal lib start ----------

// Decimal_len = PREC div 9 + 1
const Decimal_len : longint = 2100 div 9 + 1;
const Decimal_mo : longint = 1000000000;

type Decimal = record
	is_neg : boolean;
	i : int64;
	data : array[0 .. 2100 div 9] of longint;
end;

function new_decimal() : Decimal;
begin
	new_decimal.is_neg := false;
	new_decimal.i := 0;
	fillchar(new_decimal.data, Decimal_len * 4, 0);
end;

operator := (x : longint) ret : Decimal;
begin
	ret := new_decimal();
	
	if x < 0 then begin
		ret.is_neg := true;
		x := -x;
	end;
	
	ret.i := x;
end;

operator := (x : int64) ret : Decimal;
begin
	ret := new_decimal();
	
	if x < 0 then begin
		ret.is_neg := true;
		x := -x;
	end;
	
	ret.i := x;
end;

operator := (x : double) ret : Decimal;
var
	i : longint;
begin
	ret := new_decimal();
	
	if x < 0 then begin
		ret.is_neg := true;
		x := -x;
	end;
	
	ret.i := floor(x);
	x := x - ret.i;
	
	for i := 0 to Decimal_len - 1 do begin
		x := x * Decimal_mo;
		if x < 0 then x := 0;
		ret.data[i] := floor(x);
		x := x - ret.data[i];
	end;
end;

// Note: ansistring is null-terminated
// see http://wiki.freepascal.org/Character_and_string_types#AnsiString
operator := (s : ansistring) ret : Decimal;
var
	i : longint;
	pos : longint;
	x : longint;
begin
	ret := new_decimal();
	
	// find the first digit or the negative sign
	i := 1;
	while s[i] <> '#0' do begin
		if s[i] = '-' then begin
			ret.is_neg := true;
			inc(i);
			break;
		end else if (s[i] >= '0') and (s[i] <= '9') then begin
			break;
		end;
		inc(i);
	end;
	
	// read the integer part
	while (s[i] >= '0') and (s[i] <= '9') do begin
		ret.i := ret.i * 10 + ord(s[i]) - 48;
		inc(i);
	end;
	
	// read the decimal part
	if s[i] = '.' then begin
		pos := 0;
		x := Decimal_mo div 10;
		
		inc(i);
		while (pos < Decimal_len) and (s[i] >= '0') and (s[i] <= '9') do begin
			ret.data[pos] := ret.data[pos] + (ord(s[i]) - 48) * x;
			inc(i);
			x := x div 10;
			if x = 0 then begin
				inc(pos);
				x := Decimal_mo div 10;
			end;
		end;
	end;
end;

function is_zero(a : Decimal) : boolean;
var
	i : longint;
begin
	if a.i <> 0 then exit(false);
	for i := 0 to Decimal_len - 1 do begin
		if a.data[i] <> 0 then exit(false);
	end;
	exit(true);
end;

function to_double(a : Decimal) : double;
var
	k : double;
	i : longint;
begin
	to_double := a.i;
	
	k := 1.0;
	for i := 0 to Decimal_len - 1 do begin
		k := k / Decimal_mo;
		to_double := to_double + k * a.data[i];
	end;
	
	if a.is_neg then begin
		to_double := -to_double;
	end;
end;

function to_string(a : Decimal; p : longint) : ansistring;
var
	s : ansistring;
	i : longint;
	x, tmp : longint;
begin
	str(a.i, to_string);
	
	if a.is_neg and not is_zero(a) then begin
		to_string := '-' + to_string;
	end;
	
	to_string := to_string + '.';
	
	for i := 0 to Decimal_len - 1 do begin
		// append a.data[i] as "%09d"
		s := '';
		x := Decimal_mo div 10;
		tmp := a.data[i];
		while x <> 0 do begin
			s := s + chr(48 + tmp div x);
			tmp := tmp mod x;
			x := x div 10;
			dec(p);
			if p = 0 then begin
				break;
			end;
		end;
		to_string := to_string + s;
		if p = 0 then break;
	end;
	
	while p > 0 do begin
		to_string := to_string + '0';
		dec(p);
	end;
end;

operator < (a, b : Decimal) ret : boolean;
var
	i : longint;
begin
	if (a.is_neg <> b.is_neg) then begin
		exit(a.is_neg and (not is_zero(a) or not is_zero(b)));
	end else if not a.is_neg then begin
		// a, b >= 0
		if a.i <> b.i then begin
			exit(a.i < b.i);
		end;
		for i := 0 to Decimal_len - 1 do begin
			if a.data[i] <> b.data[i] then begin
				exit(a.data[i] < b.data[i]);
			end;
		end;
		exit(false);
	end else begin
		// a, b <= 0
		if a.i <> b.i then begin
			exit(a.i > b.i);
		end;
		for i := 0 to Decimal_len - 1 do begin
			if a.data[i] <> b.data[i] then begin
				exit(a.data[i] > b.data[i]);
			end;
		end;
		exit(false);
	end;
end;

operator > (a, b : Decimal) ret : boolean;
var
	i : longint;
begin
	if (a.is_neg <> b.is_neg) then begin
		exit(not a.is_neg and (not is_zero(a) or not is_zero(b)));
	end else if not a.is_neg then begin
		// a, b >= 0
		if a.i <> b.i then begin
			exit(a.i > b.i);
		end;
		for i := 0 to Decimal_len - 1 do begin
			if a.data[i] <> b.data[i] then begin
				exit(a.data[i] > b.data[i]);
			end;
		end;
		exit(false);
	end else begin
		// a, b <= 0
		if a.i <> b.i then begin
			exit(a.i < b.i);
		end;
		for i := 0 to Decimal_len - 1 do begin
			if a.data[i] <> b.data[i] then begin
				exit(a.data[i] < b.data[i]);
			end;
		end;
		exit(false);
	end;
end;

operator <= (a, b : Decimal) ret : boolean;
var
	i : longint;
begin
	if (a.is_neg <> b.is_neg) then begin
		exit(a.is_neg or (is_zero(a) and is_zero(b)));
	end else if not a.is_neg then begin
		// a, b >= 0
		if a.i <> b.i then begin
			exit(a.i < b.i);
		end;
		for i := 0 to Decimal_len - 1 do begin
			if a.data[i] <> b.data[i] then begin
				exit(a.data[i] < b.data[i]);
			end;
		end;
		exit(true);
	end else begin
		// a, b <= 0
		if a.i <> b.i then begin
			exit(a.i > b.i);
		end;
		for i := 0 to Decimal_len - 1 do begin
			if a.data[i] <> b.data[i] then begin
				exit(a.data[i] > b.data[i]);
			end;
		end;
		exit(true);
	end;
end;

operator >= (a, b : Decimal) ret : boolean;
var
	i : longint;
begin
	if (a.is_neg <> b.is_neg) then begin
		exit(not a.is_neg or (is_zero(a) and is_zero(b)));
	end else if not a.is_neg then begin
		// a, b >= 0
		if a.i <> b.i then begin
			exit(a.i > b.i);
		end;
		for i := 0 to Decimal_len - 1 do begin
			if a.data[i] <> b.data[i] then begin
				exit(a.data[i] > b.data[i]);
			end;
		end;
		exit(true);
	end else begin
		// a, b <= 0
		if a.i <> b.i then begin
			exit(a.i < b.i);
		end;
		for i := 0 to Decimal_len - 1 do begin
			if a.data[i] <> b.data[i] then begin
				exit(a.data[i] < b.data[i]);
			end;
		end;
		exit(true);
	end;
end;

operator = (a, b : Decimal) ret : boolean;
var
	i : longint;
begin
	if is_zero(a) and is_zero(b) then exit(true);
	if a.is_neg <> b.is_neg then exit(false);
	if a.i <> b.i then exit(false);
	for i := 0 to Decimal_len - 1 do begin
		if a.data[i] <> b.data[i] then exit(false);
	end;
	exit(true);
end;

operator <> (a, b : Decimal) ret : boolean;
begin
	exit(not (a = b));
end;

operator - (a : Decimal) ret : Decimal;
var
	i : longint;
begin
	ret := a;
	// -0 = 0
	if not ret.is_neg and (ret.i = 0) then begin
		for i := 0 to Decimal_len - 1 do begin
			if ret.data[i] <> 0 then break;
		end;
		if i < Decimal_len then begin
			ret.is_neg := true;
		end;
	end else begin
		ret.is_neg := not ret.is_neg;
	end;
end;

function _decimal_add(a, b : Decimal) : Decimal;
var
	last : boolean;
	i : longint;
	ret : Decimal;
begin
	ret := a;
	last := false;
	for i := Decimal_len - 1 downto 0 do begin
		ret.data[i] := ret.data[i] + b.data[i] + longint(last);
		if ret.data[i] >= Decimal_mo then begin
			ret.data[i] := ret.data[i] - Decimal_mo;
			last := true;
		end else begin
			last := false;
		end;
	end;
	ret.i := ret.i + b.i + longint(last);
	exit(ret);
end;

operator - (a, b : Decimal) ret : Decimal;
var
	last : boolean;
	i : longint;
begin
	if not a.is_neg and not b.is_neg then begin
		if a >= b then begin
			ret := a;
			last := false;
			for i := Decimal_len - 1 downto 0 do begin
				ret.data[i] := ret.data[i] - b.data[i] - longint(last);
				if ret.data[i] < 0 then begin
					ret.data[i] := ret.data[i] + Decimal_mo;
					last := true;
				end else begin
					last := false;
				end;
			end;
			ret.i := ret.i - b.i - longint(last);
		end else begin
			ret := b;
			last := false;
			for i := Decimal_len - 1 downto 0 do begin
				ret.data[i] := ret.data[i] - a.data[i] - longint(last);
				if ret.data[i] < 0 then begin
					ret.data[i] := ret.data[i] + Decimal_mo;
					last := true;
				end else begin
					last := false;
				end;
			end;
			ret.i := ret.i - a.i - longint(last);
			ret.is_neg := true;
		end;
	end else if a.is_neg and b.is_neg then begin
		// a - b = (-b) - (-a)
		exit(-b - -a);
	end else if a.is_neg then begin
		// -|a| - b
		exit(-_decimal_add(-a, b));
	end else begin
		// a - -|b|
		exit(_decimal_add(a, -b));
	end;
end;

operator + (a, b : Decimal) ret : Decimal;
begin
	if a.is_neg = b.is_neg then begin
		exit(_decimal_add(a, b));
	end else if not a.is_neg then begin
		// a - |b|
		exit(a - -b);
	end else begin
		// b - |a|
		exit(b - -a);
	end;
end;

operator + (a : Decimal; x : int64) ret : Decimal;
var
	last : boolean;
	i : longint;
begin
	if not a.is_neg then begin
		if a.i + x >= 0 then begin
			a.i := a.i + x;
		end else begin
			last := false;
			for i := Decimal_len - 1 downto 0 do begin
				if last or (a.data[i] <> 0) then begin
					a.data[i] := Decimal_mo - a.data[i] - longint(last);
					last := true;
				end else begin
					last := false;
				end;
			end;
			a.i := -x - a.i - longint(last);
			a.is_neg := true;
		end;
	end else begin
		if a.i - x >= 0 then begin
			a.i := a.i - x;
		end else begin
			last := false;
			for i := Decimal_len - 1 downto 0 do begin
				if last or (a.data[i] <> 0) then begin
					a.data[i] := Decimal_mo - a.data[i] - longint(last);
					last := true;
				end else begin
					last := false;
				end;
			end;
			a.i := x - a.i - longint(last);
			a.is_neg := false;
		end;
	end;
	exit(a);
end;

operator + (a : Decimal; x : longint) ret : Decimal;
begin
	ret := a + int64(x);
end;

operator + (x : longint; a : Decimal) ret : Decimal;
begin
	ret := a + int64(x);
end;

operator + (x : int64; a : Decimal) ret : Decimal;
begin
	ret := a + x;
end;

operator + (a : Decimal; x : double) ret : Decimal;
begin
	ret := a + Decimal(x);
end;

operator + (x : double; a : Decimal) ret : Decimal;
begin
	ret := Decimal(x) + a;
end;

operator - (a : Decimal; x : longint) ret : Decimal;
begin
	ret := a + int64(-x);
end;

operator - (x : longint; a : Decimal) ret : Decimal;
begin
	ret := -(a + int64(-x));
end;

operator - (a : Decimal; x : int64) ret : Decimal;
begin
	ret := a + -x;
end;

operator - (x : int64; a : Decimal) ret : Decimal;
begin
	ret := -(a + -x);
end;

operator - (a : Decimal; x : double) ret : Decimal;
begin
	ret := a - Decimal(x);
end;

operator - (x : double; a : Decimal) ret : Decimal;
begin
	ret := Decimal(x) - a;
end;

operator * (a : Decimal; x : longint) ret : Decimal;
var
	last, i : longint;
	tmp : int64;
begin
	if x < 0 then begin
		a.is_neg := not a.is_neg;
		x := -x;
	end else if x = 0 then begin
		exit(new_decimal());
	end;
	
	last := 0;
	for i := Decimal_len - 1 downto 0 do begin
		tmp := int64(a.data[i]) * x + last;
		last := tmp div Decimal_mo;
		a.data[i] := tmp - int64(last) * Decimal_mo;
	end;
	a.i := a.i * x + last;
	
	exit(a);
end;

operator * (x : longint; a : Decimal) ret : Decimal;
begin
	exit(a * x);
end;

operator / (a : Decimal; x : longint) ret : Decimal;
var
	last, i : longint;
	tmp : int64;
begin
	if x < 0 then begin
		a.is_neg := not a.is_neg;
		x := -x;
	end;
	
	last := a.i mod x;
	a.i := a.i div x;
	
	for i := 0 to Decimal_len - 1 do begin
		tmp := int64(last) * Decimal_mo + a.data[i];
		a.data[i] := tmp div x;
		last := tmp - int64(a.data[i]) * x;
	end;
	
	if a.is_neg and (a.i = 0) then begin
		for i := 0 to Decimal_len - 1 do begin
			if a.data[i] <> 0 then begin
				break;
			end;
		end;
		if i = Decimal_len then begin
			a.is_neg := false;
		end;
	end;
	
	exit(a);
end;

// ---------- decimal lib end ----------

function to_TF(x : boolean) : ansistring;
begin
	if x then begin
		exit('true');
	end else begin
		exit('false');
	end;
end;

var
	a : Decimal;
	ans, tmp : Decimal;
	i : longint;

begin
	// input output test
	writeln('Testing IO ...');
	a := '-233.123454270204572407233464200700';
	writeln(to_string(a, 50));
	a := Decimal('-0');
	writeln(to_string(a, 50));
	
	// + - * / < test
	writeln('Testing + - * / < ...');
	a := 100;
	writeln('a = ', to_string(a, 50));
	a := a / 24;
	writeln('a/24 = ', to_string(a, 50));
	a := a + 123;
	writeln('a/24+123 = ', to_string(a, 50));
	a := a * 234;
	writeln('(a/24+123)*234 = ', to_string(a, 50));
	
	write('(a/24+123)*234 < 29756.9999999999999999 : ');
	writeln(to_TF(a < '29756.9999999999999999'));
	
	// double <-> decimal test
	writeln('Testing double <-> decimal ...\n');
	writeln('to_double(a) = ', to_double(a) : 0 : 15);
	
	a := 0.123456789;
	writeln('0.123456789 = ', to_double(a) : 0 : 15);
	writeln('0.123456789 = ', to_string(a, 50));
	a := a * 23333333;
	writeln('0.123456789*23333333 = ', to_double(a) : 0 : 15);
	writeln('0.123456789*23333333 = ', to_string(a, 50));
	
	// < > <= >= = <> test
	writeln('Testing < > <= >= = <> ...');
	writeln('1234.567 < 1234.568 : ', to_TF(Decimal('1234.567') < Decimal('1234.568')));
	writeln('1234.567 < -1234.568 : ', to_TF(Decimal('1234.567') < Decimal('-1234.568')));
	writeln('-1234.567 < 1234.568 : ', to_TF(Decimal('-1234.567') < Decimal('1234.568')));
	writeln('-1234.567 < -1234.568 : ', to_TF(Decimal('-1234.567') < Decimal('-1234.568')));
	
	writeln('1234.567 < 1234.567 : ', to_TF(Decimal('1234.567') < Decimal('1234.567')));
	writeln('1234.567 <= 1234.567 : ', to_TF(Decimal('1234.567') <= Decimal('1234.567')));
	writeln('1234.567 > 1234.567 : ', to_TF(Decimal('1234.567') > Decimal('1234.567')));
	writeln('1234.567 >= 1234.567 : ', to_TF(Decimal('1234.567') >= Decimal('1234.567')));
	
	writeln('-1234.567 < -1234.567 : ', to_TF(Decimal('-1234.567') < Decimal('-1234.567')));
	writeln('-1234.567 <= -1234.567 : ', to_TF(Decimal('-1234.567') <= Decimal('-1234.567')));
	writeln('-1234.567 > -1234.567 : ', to_TF(Decimal('-1234.567') > Decimal('-1234.567')));
	writeln('-1234.567 >= -1234.567 : ', to_TF(Decimal('-1234.567') >= Decimal('-1234.567')));
	
	writeln('1234.567 = 1234.567 : ', to_TF(Decimal('1234.567') = Decimal('1234.567')));
	writeln('1234.567 = 1234.568 : ', to_TF(Decimal('1234.567') = Decimal('1234.568')));
	writeln('1234.567 = -1234.567 : ', to_TF(Decimal('1234.567') = Decimal('-1234.567')));
	
	writeln('1234.567 <> 1234.567 : ', to_TF(Decimal('1234.567') <> Decimal('1234.567')));
	writeln('1234.567 <> 1234.568 : ', to_TF(Decimal('1234.567') <> Decimal('1234.568')));
	writeln('1234.567 <> -1234.567 : ', to_TF(Decimal('1234.567') <> Decimal('-1234.567')));
	
	writeln('-0 = 0 : ', to_TF(Decimal('-0') = Decimal('0')));
	writeln('-0 <> 0 : ', to_TF(Decimal('-0') <> Decimal('0')));
	writeln('-0 < 0 : ', to_TF(Decimal('-0') < Decimal('0')));
	writeln('-0 > 0 : ', to_TF(Decimal('-0') > Decimal('0')));
	writeln('-0 <= 0 : ', to_TF(Decimal('-0') <= Decimal('0')));
	writeln('-0 >= 0 : ', to_TF(Decimal('-0') >= Decimal('0')));
	
	// + - test
	writeln('Testing + - ...');
	a := 1.0 / 3.0;
	writeln('1/3 = ', to_string(a, 50));
	
	a := a + 233;
	writeln('1/3+233 = ', to_string(a, 50));
	
	a := a - 235;
	writeln('1/3-2 = ', to_string(a, 50));
	
	a := a + 1;
	writeln('1/3-1 = ', to_string(a, 50));
	
	a := a + 1;
	writeln('1/3 = ', to_string(a, 50));
	
	writeln('-1/3 = ', to_string(-a, 50));
	
	a := 0.0;
	writeln('-0 = ', to_string(-a, 50));
	
	a := a - 10;
	writeln('0 - 10 = ', to_string(a, 50));
	
	// * / negative test
	writeln('Testing * / with negative numbers ...');
	a := -1.0 / 6.0;
	writeln('-1/6 = ', to_string(a, 50));
	a := a * 7;
	writeln('-1/6*7 = ', to_string(a, 50));
	a := a * -3;
	writeln('-1/6*7*(-3) = ', to_string(a, 50));
	a := a / -6;
	writeln('-1/6*7*(-3)/(-6) = ', to_string(a, 50));
	a := a * 0;
	writeln('-1/6*7*(-3)/(-6)*0 = ', to_string(a, 50));
	
	// + - * / test
	writeln('Testing + - * / ...');
	writeln('1/3+2 = ', to_string(Decimal(1.0 / 3.0) + 2, 50));
	writeln('1/3+2 = ', to_string(Decimal(1.0) / 3 + 2, 50));
	writeln('1/3+2 = ', to_string(Decimal(1.0) / 3 + Decimal(2.0), 50));
	
	writeln('1/3+(-2) = ', to_string(Decimal(1.0 / 3.0) + -2, 50));
	writeln('1/3+(-2) = ', to_string(Decimal(1.0) / 3 + -2, 50));
	writeln('1/3+(-2) = ', to_string(Decimal(1.0) / 3 + Decimal(-2.0), 50));
	
	writeln('-1/3+2 = ', to_string(Decimal(-1.0 / 3.0) + 2, 50));
	writeln('-1/3+2 = ', to_string(Decimal(-1.0) / 3 + 2, 50));
	writeln('-1/3+2 = ', to_string(Decimal(-1.0) / 3 + Decimal(2.0), 50));
	
	writeln('1/3-2 = ', to_string(Decimal(1.0 / 3.0) - 2, 50));
	writeln('1/3-2 = ', to_string(Decimal(1.0) / 3 - 2, 50));
	writeln('1/3-2 = ', to_string(Decimal(1.0) / 3 - Decimal(2.0), 50));
	
	writeln('-1/3-2 = ', to_string(-Decimal(1.0 / 3.0) - 2, 50));
	writeln('-1/3-2 = ', to_string(-Decimal(1.0) / 3 - 2, 50));
	writeln('-1/3-2 = ', to_string(-Decimal(1.0) / 3 - Decimal(2.0), 50));
	
	writeln('1/-3+2 = ', to_string(Decimal(1.0 / -3.0) + 2, 50));
	writeln('1/-3+2 = ', to_string(Decimal(1.0) / -3 + 2, 50));
	writeln('1/-3+2 = ', to_string(Decimal(1.0) / -3 + Decimal(2.0), 50));
	
	writeln('-1/-3+2 = ', to_string(Decimal(-1.0 / -3.0) + 2, 50));
	writeln('-1/-3+2 = ', to_string(Decimal(-1.0) / -3 + 2, 50));
	writeln('-1/-3+2 = ', to_string(Decimal(-1.0) / -3 + Decimal(2.0), 50));
	
	writeln('1/6*11 = ', to_string(Decimal(1.0) / 6 * 11, 50));
	writeln('1/6*-11 = ', to_string(Decimal(1.0) / 6 * -11, 50));
	writeln('1/-6*-11 = ', to_string(Decimal(1.0) / -6 * -11, 50));
	// writeln('[can''t compile 1/1.5 = ', to_string(Decimal(1.0) / 1.5), 50);
	
	writeln('1/7-1/6 = ', to_string(Decimal(1.0) / 7 - Decimal(1.0) / 6, 50));
	
	// Calculate e = 1 / 0! + 1 / 1! + 1 / 2! + ...
	ans := 0;
	tmp := 1;
	for i := 1 to 1000 do begin
		ans := ans + tmp;
		tmp := tmp / i;
	end;
	writeln('e = ', to_string(ans, 2000));
end.
