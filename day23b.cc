#include <iostream>

int a, b, c, d, e, f, g, h;

int
main() {
	a = 1;

	b = 93;
	c = b;
	if (a) goto l5;
	goto l9;
l5:	b *= 100;
	b -= -100000;
	c = b;
	c -= -17000;
l9:	f = 1;  std::cout << a << " " << b << " " << c << " " << h << std::endl;
	d = 2;
l11:	e = 2;
l12:	g = d;
	g *= e;
	g -= b;
	if (g) goto l17;
	f = 0;
#ifndef ORIGINAL
	goto fix;
#endif
l17:	e -= -1;
	g = e;
	g -= b;
	if (g) goto l12;
	d -= -1;
	g = d;
#ifdef ORIGINAL
	g -= b;
#else
	g -= 350;
#endif
	if (g) goto l11;
fix:	if (f) goto l27;
	h -= -1;
l27:	g = b;
	g -= c;
	if (g) goto l31;
	goto l33;
l31:	b -= -17;
	goto l9;
l33:    std::cout << h << std::endl;
}
