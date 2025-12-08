#include <stdio.h>
#include <locale.h>
#include <math.h>
#include <time.h>


void main() {
	setlocale(LC_CTYPE, "RUS");
	struct tm* mytime;
	time_t t;
	t = time(NULL);
	mytime = localtime(&t);

	char buffer[256];
	sprintf(buffer, "Московское время %02d:%02d:%02d \n", mytime->tm_hour, mytime->tm_min, mytime->tm_sec);
	puts(buffer);

	sprintf(buffer, "День/Месяц/Год: %02d/%02d/%4d \n", mytime->tm_mday, mytime->tm_mon + 1, mytime->tm_year + 1900);
	puts(buffer);

	switch (mytime->tm_wday) {
	case 0: puts("Воскресенье\n");
		break;
	case 1: puts("Понедельник\n");
		break;
	case 2: puts("Вторник\n");
		break;
	case 3: puts("Среда\n");
		break;
	case 4: puts("Четверг\n");
		break;
	case 5: puts("Пятница\n");
		break;
	case 6: puts("Суббота\n");
		break;
	default: puts("Wrong number--"); 
		break;
	}

	sprintf(buffer, "%02d ", mytime->tm_mday);
	puts(buffer);
	switch (mytime->tm_mon) {
	case 0: puts("января"); break;
	case 1: puts("февраля"); break;
	case 2: puts("марта"); break;
	case 3: puts("апреля"); break;
	case 4: puts("мая"); break;
	case 5: puts("июня"); break;
	case 6: puts("июля"); break;
	case 7: puts("августа"); break;
	case 8: puts("сентября"); break;
	case 9: puts("октября"); break;
	case 10: puts("ноября"); break;
	case 11: puts("декабря"); break;
	default: puts("Wrong number--"); break;
	}
	puts("\n");

	sprintf(buffer, "сегодня %02d-й день %04d года \n", mytime->tm_yday + 1, mytime->tm_year + 1900);
	puts(buffer);

	sprintf(buffer, "до воскресенья %01d дней и %d часов \n", 6 - mytime->tm_wday, 23 - mytime->tm_hour);
	puts(buffer);

	int current_min = mytime->tm_hour * 60 + mytime->tm_min;
	int start_min = 8 * 60 + 30;
	if (current_min < start_min)
		puts("Пара ещё не началась! \n");
	else {
		sprintf(buffer, "с первой пары прошло %d часов %d минут \n", (current_min - start_min) / 60, (current_min - start_min) % 60);
		puts(buffer);
	}
	int days_in_month;
	switch (mytime->tm_mon) {
	case 0: case 2: case 4: case 6: case 7: case 9: case 11:
		days_in_month = 31; break;
	case 3: case 5: case 8: case 10:
		days_in_month = 30; break;
	case 1:
		days_in_month = 28; break;
	default: days_in_month = 30;
	}

	sprintf(buffer, "до Нового года осталось %d месяцев и %d дней \n", 11 - mytime->tm_mon, days_in_month - mytime->tm_mday);
	puts(buffer);

	int current_sec = current_min * 60 + mytime->tm_sec;
	if (current_min > 509 && current_min < 606) {
		sprintf(buffer, "до конца пары %d минут и %d секунд \n", (605 * 60 - current_sec) / 60, (605 * 60 - current_sec) % 60);
		puts(buffer);
	}
	else if (current_min > 614 && current_min < 711) {
		sprintf(buffer, "до конца пары %d минут и %d секунд \n", (710 * 60 - current_sec) / 60, (710 * 60 - current_sec) % 60);
		puts(buffer);
	}
	else if (current_min > 719 && current_min < 816) {
		sprintf(buffer, "до конца пары %d минут и %d секунд \n", (815 * 60 - current_sec) / 60, (815 * 60 - current_sec) % 60);
		puts(buffer);
	}
	else if (current_min > 859 && current_min < 956) {
		sprintf(buffer, "до конца пары %d минут и %d секунд \n", (955 * 60 - current_sec) / 60, (955 * 60 - current_sec) % 60);
		puts(buffer);
	}
	else if (current_min > 964 && current_min < 1061) {
		sprintf(buffer, "до конца пары %d минут и %d секунд \n", (1060 * 60 - current_sec) / 60, (1060 * 60 - current_sec) % 60);
		puts(buffer);
	}
	else if (current_min > 1069 && current_min < 1166) {
		sprintf(buffer, "до конца пары %d минут и %d секунд \n", (1165 * 60 - current_sec) / 60, (1165 * 60 - current_sec) % 60);
		puts(buffer);
	}
	else if (current_min > 1174 && current_min < 1271) {
		sprintf(buffer, "до конца пары %d минут и %d секунд \n", (1270 * 60 - current_sec) / 60, (1270 * 60 - current_sec) % 60);
		puts(buffer);
	}
	else puts("В данный момент пара не проводится. \n");

	sprintf(buffer, "до конца месяца %d дней, до конца года %d месяцев \n", days_in_month - mytime->tm_mday, 11 - mytime->tm_mon);
	puts(buffer);

	puts("month ");
	switch (mytime->tm_mon) {
	case 0: puts("\tI"); break;
	case 1: puts("\tII"); break;
	case 2: puts("\tIII"); break;
	case 3: puts("\tIV"); break;
	case 4: puts("\tV"); break;
	case 5: puts("\tVI"); break;
	case 6: puts("\tVII"); break;
	case 7: puts("\tVIII"); break;
	case 8: puts("\tIX"); break;
	case 9: puts("\tX"); break;
	case 10: puts("\tXI"); break;
	case 11: puts("\tXII"); break;
	default: puts("\twrong number!--"); break;
	}

	sprintf(buffer, "\t\tof the %d \n", mytime->tm_year + 1900);
	puts(buffer);

	if (mytime->tm_mon == 11 || mytime->tm_mon == 0 || mytime->tm_mon == 1) {
		puts("зима");
	}
	else if (mytime->tm_mon >= 2 && mytime->tm_mon <= 4) {
		puts("весна");
	}
	else if (mytime->tm_mon >= 5 && mytime->tm_mon <= 7) {
		puts("лето");
	}
	else if (mytime->tm_mon >= 8 && mytime->tm_mon <= 10) {
		puts("осень");
	}

	sprintf(buffer, "\t%d-го года\n", (mytime->tm_year + 1900) % 100);
	puts(buffer);

	if (mytime->tm_mon == 11 || mytime->tm_mon == 0 || mytime->tm_mon == 1) {
		if (mytime->tm_mon == 11) {
			sprintf(buffer, "идет %d день зимы", mytime->tm_mday);
			puts(buffer);
		}
		else if (mytime->tm_mon == 0) {
			sprintf(buffer, "идет %d день зимы", mytime->tm_mday + 31);
			puts(buffer);
		}
		else {
			sprintf(buffer, "идет %d день зимы", mytime->tm_mday + 62);
			puts(buffer);
		}
	}
	puts("\n");

	if (mytime->tm_mon >= 8 && mytime->tm_mon <= 10) {
		if (mytime->tm_mon == 8) {
			sprintf(buffer, "идет %d день осени", mytime->tm_mday);
			puts(buffer);
		}
		else if (mytime->tm_mon == 9) {
			sprintf(buffer, "идет %d день осени", mytime->tm_mday + 30);
			puts(buffer);
		}
		else {
			sprintf(buffer, "идет %d день осени", mytime->tm_mday + 61);
			puts(buffer);
		}
	}
	puts("\n");



	system("pause");


}
