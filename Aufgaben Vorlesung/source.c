#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define _USE_MATH_DEFINES
#include <math.h>

#include "../../MenuLib/menu.h"

#define INPUT_LENGTH 50


void 
euklid(void), 
gerste(void), 
ostern(void),
ascii(void),
db(void),
mod11(void),
namen(void),
strHeader(void);


int main(void) {
	struct MenuItem items[] = {
		{"Euklidscher Algorithmus",	'1', (void*)&euklid},
		{"Gerstenkorn",				'2', (void*)&gerste},
		{"Osterdatum ausrechnen",	'3', (void*)&ostern},
		{"ASCII Tabelle",			'4', (void*)&ascii},
		{"DB-Pruefziffer",			'5', (void*)&db},
		{"Modulo 11",				'6', (void*)&mod11},
		{"BLANK",					NULL, (void*)NULL},
		{"Namen TEST",				'a', (void*)&namen},
		{"Strings",					'b', (void*)&strHeader},
		{"BLANK",					NULL, (void*)NULL},
		{"Exit",					'q', (void*)&exit}
	};
	show_menu(sizeof(items) / sizeof(struct MenuItem), items, "Vorlesungsaufgaben", true, true, NO_BORDER);
}

void euklid(void) {
	int x, y;
	printf("Zahl 1: ");
	scanf_s("%d", &x);

	fflush(stdin);

	printf("Zahl 2: ");
	scanf_s("%d", &y);

	fflush(stdin);

	while (x != y) {
		if (x > y) {
			x -= y;
		}
		else {
			y -= x;
		}
	}

	printf("Der groesste gemeinsame Zaehler betraegt %d!\n", x);
}

void gerste(void) {
	int height = 0;

	while (height <= 200) {
		double volume = height * M_PI * 2500;
		volume /= 1000000;
		printf("Bei einer Hoehe von %3d mm betraegt das Volumen %.3lf Liter!\n", height, volume);
		height += 10;
	}
}

void ostern(void) {
	unsigned int jahr = 0;
	int a, b, c, d, e, tag;

	jahr = 1990;
	while (jahr <= 2025) {
		if (jahr == 1954 || jahr == 1981) {
			printf("\nOstern kann %i nicht berechnet werden!\n", jahr);
		}
		else {
			a = jahr % 19;
			b = jahr % 4;
			c = jahr % 7;
			d = (19 * a + 24) % 30;
			e = (2 * b + 4 * c + 6 * d + 5) % 7;

			tag = 22 + d + e;

			if (tag > 31) {
				printf("Ostern faellt im Jahr %4i auf den %2d. April!", jahr, tag - 31);
			}
			else {
				printf("Ostern faellt im Jahr %4i auf den %2d. Maerz!", jahr, tag);
			}
		}
		printf("\n");
		jahr++;
	}
}

void ascii(void) {
	printf("------------------ ASCII - Tabelle -------------------\n\n");
	printf("	0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F\n");
	printf("	0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15");

	printf("\n%2X %3i", 0, 0);
	printf("\n%2X %3i ", 1, 16);

	for (int i = 32; i < 256; i++) {
		if (i % 16 == 0) {
			printf("\n%2X %3i ", i / 16, i);
		}
		printf(" %c ", i);
	}
}

void db(void) {
	char input[8];
	printf("Bitte gebe die Kennzeichnung ein: ");
	gets_s(input, 8);

	int numbers[7] = { 0 };

	for (int i = 0; i < 7; i++) {
		if (input[i] != '-') {
			numbers[i] = input[i] - 48;
		}
	}
	int sum = 0, tmp;;

	numbers[0] *= 1;

	numbers[1] *= 2;
	tmp = numbers[1] / 10;
	tmp > 0 ? numbers[1] = tmp + numbers[1] - 10 : 0;

	numbers[2] *= 1;

	numbers[4] *= 2;

	numbers[5] *= 1;

	numbers[6] *= 2;
	tmp = numbers[6] / 10;
	tmp > 0 ? numbers[6] = tmp + numbers[6] - 10: 0;

	for (int i = 0; i < 7; i++) {
		sum += numbers[i];
	}

	tmp = sum / 10 + 1;
	
	printf("Es ergibt sich folgende Kennzeichnung mit Pruefnummer %s-%d", input, tmp * 10 - sum);

}

void namen(void) {
	char namen[3][7 + 1];

	strcpy(namen[0], "Hannes");

	strcpy(namen[1], "Elisabeth");
	printf("Namen 1: %s\n", namen[1]);

	strcpy(namen[2], "Holger");
	printf("Namen 1 NEU: %s", namen[1]);
}


void 
mod11Calc(void),
mod11Test(void);
void mod11(void) {
	struct MenuItem items[] = {
		{"Nummer berechnen",	'1', (void*)&mod11Calc},
		{"Nummer ueberpruefen",	'2', (void*)&mod11Test},
		{"BLANK",		NULL, (void*)NULL},
		{"Zurueck",		'q', (void*)&main}
	};
	show_menu(sizeof(items) / sizeof(struct MenuItem), items, "Vorlesungsaufgaben", false, false, MODERN);
}

int calcPruef(char* ptr) {
	int multi = 2, sum = 0;

	while (*ptr != 0)
	{
		sum += (*ptr - 48) * multi;

		ptr++;
		multi % 7 == 0 ? multi = 2 : multi++;
	}

	int pruef = 0;
	pruef = 11 - sum % 11;
	pruef == 10 ? pruef = 0 : pruef;
}
void mod11Calc(void) {
	char number[30 + 1], reverseNumber[30 + 1];

	printf("Gebe eine Nummer ein (max 30 Zeichen): ");
	gets_s(number, 30);

	strcpy(reverseNumber, number);
	_strrev(reverseNumber);

	printf("Die Nummer inklusive Pruefziffer ist: %s%d", number, calcPruef(reverseNumber));
}
void mod11Test(void) {
	char number[30 + 1];

	printf("Bitte gebe die Nummer inklusive Pruefziffer ein: ");
	gets_s(number, 30);

	char* ptr = number;
	while (*ptr != 0) ptr++;

	ptr--;
	int specPruef = *ptr - 48;
	*ptr = 0;

	specPruef == 10 ? specPruef = 0 : specPruef;

	_strrev(number);

	specPruef == calcPruef(number) ? printf("Die eingegebene Nummer ist korrekt!") : printf("Die eingegebene Nummer ist inkorrekt!");
}


// Funktionsprototypen für strHeader()
void
strcatEx(void),
strlenEx(void),
strncpyEx(void),
strchrEx(void),
strstrEx(void),
strtokEx(void),
replace(void);

void strHeader(void) {
	struct MenuItem items[] = {
		{"strcat()",	'1', (void*)&strcatEx},
		{"strlen()",	'2', (void*)&strlenEx},
		{"strncpy()",	'3', (void*)&strncpyEx},
		{"strchr()",	'4', (void*)&strchrEx},
		{"strstr()",	'5', (void*)&strstrEx},
		{"strtok()",	'6', (void*)&strtokEx},
		{"BLANK",		NULL, (void*)NULL},
		{"Ersetzen",	'a', (void*)&replace},
		{"BLANK",		NULL, (void*)NULL},
		{"Zurueck",		'q', (void*)&main}
	};
	show_menu(sizeof(items) / sizeof(struct MenuItem), items, "Waehle die String-Funktion aus", false, false, MODERN);
}

void strcatEx(void) {
	char first[INPUT_LENGTH + 1], second[INPUT_LENGTH + 1];
	printf("Gebe einen String ein: ");
	gets_s(first, INPUT_LENGTH);

	printf("Gebe einen weiteren String ein: ");
	gets_s(second, INPUT_LENGTH);

	printf("Zusammengefuegt: %s", strcat(first, second));
}
void strlenEx(void) {
	char input[INPUT_LENGTH + 1];
	printf("Gebe einen String ein: ");
	gets_s(input, INPUT_LENGTH);

	printf("Der String hat eine Laenge von %d", strlen(input));
}
void strncpyEx(void) {
	char input[INPUT_LENGTH + 1], dest[INPUT_LENGTH + 1];
	printf("Gebe einen String ein: ");
	gets_s(input, INPUT_LENGTH);

	int n;
	printf("Wie viele Zeichen möchtest du kopieren? ");
	scanf_s("%d", &n);

	fflush(stdin);

	dest[n] = '\0';
	printf("Die ersten %d Zeichen: %s", n, strncpy(dest, input, n));
}
void strchrEx(void) {
	char input[INPUT_LENGTH + 1], c;
	printf("Gebe einen String ein: ");
	gets_s(input, INPUT_LENGTH);

	printf("Gebe einen char ein: ");
	scanf_s("%c", &c, 1);

	fflush(stdin);

	printf("Auf den char '%c' folgt: %s", c, strchr(input, c));
}
void strstrEx(void) {
	char string[INPUT_LENGTH + 1], substring[INPUT_LENGTH + 1];
	printf("Gebe einen String ein: ");
	gets_s(string, INPUT_LENGTH);

	printf("Gebe einen Substring ein: ");
	gets_s(substring, INPUT_LENGTH);

	printf("Der Substring '%s' und die darauffolgenden Zeichen: %s", substring, strstr(string, substring));
}
void strtokEx(void) {
	char input[INPUT_LENGTH + 1], delim[10 + 1];
	printf("Gebe einen String ein: ");
	gets_s(input, INPUT_LENGTH);

	printf("Gebe einen Token ein: ");
	gets_s(delim, 10);

	printf("Folgende Tokens wurde gefunden: ");

	char* token = strtok(input, delim);
	while (token != NULL) {
		printf("\n- %s", token);

		token = strtok(NULL, delim);
	}
}

void replace(void) {
	char input[INPUT_LENGTH + 1], replaceMe, replaceWith;
	char* ptr;
	printf("Gebe einen Text ein: ");
	gets_s(input, INPUT_LENGTH);

	printf("Welchen Buchstaben willst du ersetzen? ");
	scanf_s("%c", &replaceMe, 1);

	while (getchar() != '\n');

	printf("Durch welchen Buchstaben soll '%c' ersetzt werden? ", toupper(replaceMe));
	scanf_s("%c", &replaceWith, 1);

	while (getchar() != '\n');
	
	ptr = input;
	while (*ptr != 0) {
		if (tolower(*ptr) == tolower(replaceMe)) {
			*ptr = isupper(*ptr) ? toupper(replaceWith) : tolower(replaceWith);
		}
		ptr++;
	}

	printf("Neuer Text: %s", input);
}