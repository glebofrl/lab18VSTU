#include <locale.h>
#include <stdio.h>
#include <math.h>

struct point {
	float x;
	float y;
	char name;
};

typedef struct point Point;

void put_point(Point z) {
	printf("point %c (%.1f, %.1f)\n", z.name, z.x, z.y);
}

float dist(Point z, Point w) {
	float dist = sqrt(pow(w.x - z.x, 2) + pow(w.y - z.y, 2));
	return dist;
}

void put_check(Point z) {
	setlocale(LC_CTYPE, "RUS");

	if (z.x == 0 && z.y == 0)
		printf("point %c (%.1f, %.1f) - начало координат\n", z.name, z.x, z.y);
	if (z.x == 0 && z.y!=0)
		printf("point %c (%.1f, %.1f) - ось y\n", z.name, z.x, z.y);
	if (z.x != 0 && z.y == 0)
		printf("point %c (%.1f, %.1f) - ось x\n", z.name, z.x, z.y);
	if (z.x > 0 && z.y > 0)
		printf("point %c (%.1f, %.1f) - I четверть\n", z.name, z.x, z.y);
	if (z.x > 0 && z.y < 0)
		printf("point %c (%.1f, %.1f) - IV четверть\n", z.name, z.x, z.y);
	if (z.x < 0 && z.y < 0)
		printf("point %c (%.1f, %.1f) - III четверть\n", z.name, z.x, z.y);
	if (z.x < 0 && z.y > 0)
		printf("point %c (%.1f, %.1f) - II четверть\n", z.name, z.x, z.y);

}

Point M(Point z, Point w) {
	Point m;
	m.name = 'M';
	m.x = (z.x + w.x) / 2;
	m.y = (z.y + w.y) / 2;
	return m;
}

void main() {
	Point b, a;
	a = (Point){ 1.f, 2.f, 'A' };
	b.name = 'B'; b.x = 5; b.y = -3;

	printf("point %c (%.1f, %.1f)\n", a.name, a.x, a.y);
	printf("dist = %f\n", dist(a, b));
	put_point(b);
	Point m = M(a,b);
	printf("point %c (%.1f, %.1f)\n", m.name, m.x, m.y);
	put_check(m);
	system("pause");
	

}

