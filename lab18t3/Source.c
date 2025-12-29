#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct train {
	int num_of_train;
	int arrival_time;
	int departure_time;
	char direction[256];
	int distance;
}Train;

int input_file(char* filename, Train* arr);
int output_file(char* filename, Train* arr, int  n);
float train_speed(int arrival_time, int departure_time, int distance);
void getRandomDirection(char* direction);
void fillTrainArray(Train trains[], int size);
int getRandomNumber(int min, int max);
void fill_array(Train trains[], int size);
void print_array(Train trains[], int size);
Train* search_trains(Train* trains, int size, char* comp_direction);
int compare(const void* a, const void* b);
int output_file(char* fname, Train* trains, int size);



int main(void) {
	setlocale(LC_CTYPE, "RUS");

	char fname[20] = "trains.txt";
	Train* trains;
	Train* copy_trains;
	char copy_name[] = "copy.txt";
	int SIZE;
	int copy_size;
	char comp_direction[20];

	//print_array(trains, SIZE);

	Train* checker;

	printf("Введите количество записей: ");
	scanf("%d", &SIZE);


	printf("Выберите действие: \n"
		"1. Заполнить массив случайными числами\n"
		"2. Заполнить массив с клавиатуры\n");

	while (getchar() != '\n');
	char a = getchar();
	switch (a)
	{
	case '1':
		trains = (Train*)malloc(SIZE * sizeof(Train));
		fillTrainArray(trains, SIZE);
		print_array(trains, SIZE);
		break;
	case '2':
		trains = (Train*)malloc(SIZE * sizeof(Train));
		fill_array(trains, SIZE);
		print_array(trains, SIZE);
		break;
	default:
		puts("Ошибка ввода");
		return 1;
	}
	while (getchar() != '\n');

	printf("Выберите действие: \n"
		"1. Найти элемент массива по направлению\n"
		"2. Отсортировать массив\n"
		"3. Выгрузить массив в файл\n"
		"4. Загрузить массив из файла\n");
	a = getchar();
	switch (a) {
	case '1':
		printf("Введите направление: ");
		scanf("%s", comp_direction);
		checker = search_trains(trains, SIZE, comp_direction);
		if (checker != NULL) {
			printf("Найден поезд %d\n", checker->num_of_train);
			printf("Направление: %s\n", checker->direction);
		}
		else
			puts("Поезд не найден!");
		print_array(trains, SIZE);
		break;
	case '2':
		qsort(trains, SIZE, sizeof(Train), compare);
		print_array(trains, SIZE);
		break;
	case '3':
		if (output_file(fname, trains, SIZE) == 0)
			printf("Данные успешно записаны в файл");
		break;
	case '4':
		copy_size = 4;
		copy_trains = (Train*)malloc(copy_size * sizeof(Train));
		input_file(copy_name, copy_trains);
		break;
	default:
		puts("Ошибка ввода");
		return 1;
	}
	while (getchar() != '\n');

	return 0;

}

float train_speed(int arrival_time, int departure_time, int distance) {
	float train_speed;
	if (arrival_time > departure_time)
		train_speed = distance / ((arrival_time - departure_time) / 60.f);
	else
		train_speed = distance / ((1440 - departure_time + arrival_time) / 60.f);

	if (train_speed < -0)
		return -999.f;
	return train_speed;
}

void getRandomDirection(char* direction) {
	char* titles[] =
	{ "Москва-СПб", "СПб-Москва", "Москва-Казань",
	"Екатеринбург-Новосибирск", "Сочи-Москва",
	"Владивосток-Хабаровск", "Минск-Москва",
	"Киев-Львов", "Астана-Алматы" };

	int index = rand() % (sizeof(titles) / sizeof(titles[0]));
	strcpy(direction, titles[index]);
}

void fillTrainArray(Train trains[], int size) {
	srand(time(NULL));
	//trains[0] = { 1, 510, 400, 1, 300 };
	for (int i = 0; i < size; i++) {
		trains[i].num_of_train = i + 1;
		trains[i].arrival_time = getRandomNumber(0, 1135);
		trains[i].departure_time = getRandomNumber(200, 1410);
		getRandomDirection(trains[i].direction);
		trains[i].distance = getRandomNumber(100, 1000);
	}

}

int getRandomNumber(int min, int max) {
	return min + rand() % (max - min + 1);
}

void fill_array(Train trains[], int size) {

	int min, hour;
	for (int i = 0; i < size; i++) {
		printf("Заполнение строки номер %d\n", i);
		printf("Введите номер поезда: ");
		scanf("%d", &trains[i].num_of_train);

		printf("Введите время прибытия в формате \"чч мм\": ");
		scanf("%d %d", &hour, &min);
		trains[i].arrival_time = hour * 60 + min;

		printf("Введите время отбытия в формате \"чч мм\": ");
		scanf("%d %d", &hour, &min);
		trains[i].departure_time = hour * 60 + min;

		printf("Введите направление: ");
		scanf("%s", &trains[i].direction);

		printf("Введите расстояние в километрах: ");
		scanf("%d", &trains[i].distance);
	}
}

void print_array(Train trains[], int size) {
	char buffer[256];
	char* info = "| %2d  ||     %02d:%02d      ||     %02d:%02d     || %25s || %10d%5c || %14.2f%9c |";

	printf("|  N  || Время прибытия || Время отбытия || %6c Направление %6c || Расстояние (км) || Средняя скорость (км/ч) | \n", ' ', ' ');
	printf("_____________________________________________________________________________________________________________________\n");
	for (int i = 0; i < size; i++) {
		sprintf(buffer, info,
			trains[i].num_of_train,
			trains[i].arrival_time / 60, trains[i].arrival_time % 60,
			trains[i].departure_time / 60, trains[i].departure_time % 60,
			trains[i].direction,
			trains[i].distance, ' ',
			train_speed(trains[i].arrival_time, trains[i].departure_time, trains[i].distance), ' ');

		puts(buffer);
	}
}

Train* search_trains(Train* trains, int size, char* comp_direction) {

	for (int i = 0; i < size; i++) {

		if (strcmp(trains[i].direction, comp_direction) == 0)
			return (trains + i);
	}

	return NULL;

}

int compare(const void* a, const void* b) {

	const Train* trainA = (const Train*)a;
	const Train* traneB = (const Train*)b;

	int distanceA = trainA->distance;
	int distanceB = traneB->distance;

	if (distanceA < distanceB)
		return -1;
	else if (distanceA > distanceB)
		return 1;

	return 0;

}

int output_file(char* fname, Train* trains, int size) {
	FILE* out;
	if ((out = fopen(fname, "wt")) == NULL) {
		printf("Ошибка открытия файла для записи");
		return 1;
	}


	for (int i = 0; i < size; i++)
	{
		fprintf(out, " Номер:%2d ; Время прибытия: %02d:%02d ; Время отбытия: %02d:%02d ; Направление: %s ; Расстояние (км): %d ; Средняя скорость (км/ч): %f \n",
			trains[i].num_of_train,
			trains[i].arrival_time / 60, trains[i].arrival_time % 60,
			trains[i].departure_time / 60, trains[i].departure_time % 60,
			trains[i].direction,
			trains[i].distance,
			train_speed(trains[i].arrival_time, trains[i].departure_time, trains[i].distance));
	}
	fclose(out);
	return 0;
}

int input_file(char* filename, Train* arr) {

	char buffer[256];
	int count = 0;
	Train temp;
	FILE* in;
	if ((in = fopen(filename, "r")) == NULL) {
		printf("Ошибка открытия файла для записи");
		return 1;
	}

	for (int i = 0; !feof(in); i++) {
		fgets(buffer, sizeof(buffer), in);
		puts(buffer);
	}



	fclose(in);

	return count;;
}
