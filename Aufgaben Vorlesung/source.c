#include "includes.h"
#include "linkedList.h"


// Other
void
euklid(void),
gerste(void),
ostern(void),
ascii(void),
db(void),
mod11(void),
namen(void),
decToFloat(void);

//Rekursion
void
fak(void),
tvh(void);

int
fakREK(int x),
tvhREK(int count, int from, int to);

// String
void
strcatEx(void),
strlenEx(void),
strncpyEx(void),
strchrEx(void),
strstrEx(void),
strtokEx(void),
replace(void),
strcatOWN(void),
strlenOWN(void),
strcpyOWN(void),
strcmpOWN(void),
strrevOWN(void);

// Sortieren
void
swap(int* first, int* second),
init(int* toSort),
print(int* content),
sort(char key[]),
bubble(int* toSort),
quickSort(int* toSort, int left, int right);

//Annuität
void annu(void);


//int main(void) {
//	struct MenuItem other[] = {
//		{"Euklidscher Algorithmus",	'1',	(void*)&euklid},
//		{"Gerstenkorn",				'2',	(void*)&gerste},
//		{"Osterdatum ausrechnen",	'3',	(void*)&ostern},
//		{"ASCII Tabelle",			'4',	(void*)&ascii},
//		{"DB-Pruefziffer",			'5',	(void*)&db},
//		{"Modulo 11",				'6',	(void*)&mod11},
//		{"Umwandlung Gleitkomma",	'7',	(void*)&decToFloat},
//		{"Annuitaetsdarlehen",'8',(void*)&annu},
//		{"BLANK",					NULL,	(void*)NULL},
//		{"Verkettete Liste",		'a',	(void*)&mainMenu, NULL},
//		{"BLANK",					NULL,	(void*)NULL},
//		{"Exit",					'q',	(void*)&exit}
//	};
//
//	struct MenuItem recursion[] = {
//		{"Fakultaet",			'1', (void*)&fak},		
//		{"Tuerme von Hanoi",	'2', (void*)&tvh}
//	};
//
//	struct MenuItem stringsEX[] = {
//		{"strcat()",	'1',	(void*)&strcatEx},
//		{"strlen()",	'2',	(void*)&strlenEx},
//		{"strncpy()",	'3',	(void*)&strncpyEx},
//		{"strchr()",	'4',	(void*)&strchrEx},
//		{"strstr()",	'5',	(void*)&strstrEx},
//		{"strtok()",	'6',	(void*)&strtokEx},
//		{"BLANK",		NULL,	(void*)NULL},
//		{"Ersetzen",	'7',	(void*)&replace}
//	};
//
//	struct MenuItem stringsOWN[] = {
//		{"strcat()",	'1', (void*)&strcatOWN},
//		{"strlen()",	'2', (void*)&strlenOWN},
//		{"strcpy()",	'3', (void*)&strcpyOWN},
//		{"strcmp()",	'4', (void*)&strcmpOWN},
//		{"strrev()",	'5', (void*)&strrevOWN}
//	};
//
//	struct MenuItem sorting[] = {
//		{"Bubblesort",	'1', (void*)&sort,	"Bubblesort"},
//		{"Quicksort",	'2', (void*)&sort,	"Quicksort"}
//	};
//
//	struct MenuPage pages[] = {
//		{other,			sizeof(other) / sizeof(struct MenuItem),		"Vorlesungsaufgaben",	true, true, &SOLID},
//		{sorting,		sizeof(sorting) / sizeof(struct MenuItem),		"Sortieralgorithmen",	true, true, &SOLID},
//		{recursion,		sizeof(recursion) / sizeof(struct MenuItem),	"Rekursion",			true, true, &MODERN},
//		{stringsEX,		sizeof(stringsEX) / sizeof(struct MenuItem),	"String - Beispiele",	true, true, &NO_BORDER},
//		{stringsOWN,	sizeof(stringsOWN) / sizeof(struct MenuItem),	"String - Eigene",		true, true, &NO_BORDER}
//	};
//	show_menu(pages, sizeof(pages) / sizeof(struct MenuPage), true);
//}

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


// Modulo 11
void 
mod11Calc(void),
mod11Test(void);
void mod11(void) {
	struct MenuItem items[] = {
		{"Nummer berechnen",	'1', (void*)&mod11Calc},
		{"Nummer ueberpruefen",	'2', (void*)&mod11Test},
		{"BLANK",				NULL, (void*)NULL},
		//{"Zurueck",				'q', (void*)&main}
	};
	struct MenuPage pages[] = {
		{items, sizeof(items) / sizeof(struct MenuItem), "Modulo 11", true, true, &SOLID}
	};
	show_menu(pages, sizeof(pages) / sizeof(struct MenuPage), true);
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

	return pruef;
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


void iToA(int zahl, char* text, int basis) {
	int i = 0;
	do{
			text[i] = zahl % basis + 48;
			i++;
	} while (zahl /= basis);
	text[i] = 0;
	_strrev(text);
}
void decToFloat(void) {
	union {
		float f;
		unsigned char c[4];
	}u;

	printf("Gebe eine Gleitkommazahl ein: ");
	scanf_s("%f", &u.f);

	for (int i = 1; i < 5; i++) 
		printf(" Byte %d ||", i);
	
	putchar('\n');
	
	char text[9];

	for (int i = 3; i >= 0; i--) {
		if (u.c[i] != 0) {
			//iToA(u.c[i], text, 2);
			_itoa(u.c[i], text, 2);

			if (strlen(text) < 8) {
				for (int n = 0; n < 8 - strlen(text); n++) {
					putchar('0');
				}
			}
				
			int x = 0;
			while (text[x] != 0) {
				putchar(text[x]);
				text[x] = 0;
				x++;
			}	
		}
		else {
			for (int n = 0; n < 8; n++) printf("0");
		}
		printf("||");
	}
}


// String
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

void strcatOWN(void) {
	char first[INPUT_LENGTH + 1], second[INPUT_LENGTH + 1];
	printf("Gebe einen String ein: ");
	gets_s(first, INPUT_LENGTH);

	printf("Gebe einen weiteren String ein: ");
	gets_s(second, INPUT_LENGTH);

	char output[2 * INPUT_LENGTH + 1];
	int i = 0, i2 = 0;
	while (output[i] = first[i++]);
	i--;
	while (output[i++] = second[i2++]);

	printf("Zusammengefuegt: %s", output);

}
void strlenOWN(void) {
	char text[INPUT_LENGTH + 1], *ptr;
	printf("Gebe einen String ein (max. 80 Zeichen): ");
	gets_s(text, INPUT_LENGTH);
	ptr = text;

	int length = 0;

	while (*ptr++)length++;

	printf("Der eingegebene String hat die Laenge %d!", length);
}
void strcpyOWN(void) {
	char origin[INPUT_LENGTH + 1], copy[INPUT_LENGTH + 1];
	printf("Gebe einen String ein (max. 80 Zeichen): ");
	gets_s(origin, INPUT_LENGTH);

	int i = 0;
	while (copy[i] = origin[i++]);

	printf("Der String wurde kopiert: %s", copy);
}
void strcmpOWN(void) {
	char first[INPUT_LENGTH + 1], second[INPUT_LENGTH + 1];
	printf("Gebe einen String ein: ");
	gets_s(first, INPUT_LENGTH);

	printf("Gebe einen weiteren String ein: ");
	gets_s(second, INPUT_LENGTH);
	
	char lowerUpper;
	printf("Soll auf Gross- / Kleinschreibung geachtet werden [Y/N]? ");
	scanf_s("%c", &lowerUpper, 1);

	while (getchar() != '\n');

	if (tolower(lowerUpper) == 'n') {
		int i = 0;

		while (first[i])
			if (first[i] >= 65 && first[i] <= 90 && first[i] != 0)
				first[i++] += 32;
			else
				i++;
			
		i = 0;

		while (second[i])
			if (second[i] >= 65 && second[i] <= 90 && second[i] != 0)
				second[i++] += 32;
			else
				i++;
	}
	
	int i = 0, cmp = 0;
	if (strlen(first) <= strlen(second)) {
		while (first[i++]) cmp -= first[i] - second[i];
	}
	else {
		while (second[i++]) cmp -= second[i] - first[i];
	}

	printf("Das Ergebebnis ist: %d", cmp);
}
void strrevOWN(void) {
	char input[INPUT_LENGTH + 1], output[INPUT_LENGTH + 1] = { 0 };
	printf("Gebe einen String ein: ");
	gets_s(input, INPUT_LENGTH);

	int len = strlen(input) - 1, 
		i = 0;

	while (input[i] != 0) {
		output[i] = input[len - i];
		i++;
	}

	printf("Umgedreht: %s", output);
}


// Rekursion
void fak(void) {
	int nr;
	printf("Von welche Zahl soll die Fakultaet berechnet werden? ");
	scanf_s("%d", &nr);

	printf("Das Ergebnis betraegt %d", fakREK(nr));
}
int fakREK(int x) {
	if (x > 1)
		return x * fakREK(x - 1);
	else
		return 1;
}

void tvh(void) {
	int count, from = 1, to = 3;
	printf("Gebe die Anzahl von Scheiben an: ");
	scanf_s("%d", &count);

	tvhREK(count, from, to);
}
int tvhREK(int x, int y, int z) {
	int between;
	if (x > 1) {
		between = 6 - y - z;
		tvhREK(x - 1, y, between);
		printf("Scheibe %2d von %2d nach %2d\n", x, y, z);
		tvhREK(x - 1, between, z);
		
	}
	else
		printf("Scheibe %2d von %2d nach %2d\n", x, y, z);
}


// Sortieren
void swap(int* first, int* second) {
	int temp;
	temp = *first;
	*first = *second;
	*second = temp;
}

void init(int* toSort) {
	for (int i = 0; i < ELEMENTS; i++) {
		toSort[i] = rand();
	}
}

void print(int* content) {
	for (int i = 0; i <= 10; i++) printf("%d, ", content[i]);

	if (ELEMENTS > 10)
	{
		printf(" ... ");

		for (int i = ELEMENTS - 10; i < ELEMENTS; i++) printf("%d, ", content[i]);
	}
}

void sort(char key[]) {
	long t1 = 0, t2;

	int* toSort = malloc(sizeof(int) * ELEMENTS);

	init(toSort);

	printf("Sortieren mit %s:\n", key);

	printf("Unsortiert:\n");
	print(toSort);

	if (strcmp(key, "Bubblesort") == 0) {
		t1 = time(NULL);
		bubble(toSort);
	}
	else if (strcmp(key, "Quicksort") == 0) {
		t1 = time(NULL);
		quickSort(toSort, 0, ELEMENTS - 1);
	}

	t2 = time(NULL);
	
	printf("\n\nSortiert:\n");
	print(toSort);

	printf("\n\nDifferenz: %ld", t2 - t1);
}

void bubble(int* toSort) {
	int i = 0, j;
	bool getauscht;

	while (i < ELEMENTS) {
		getauscht = false;
		j = 0;
		while (j < ELEMENTS - 1 - i) {
			if (toSort[j] > toSort[j + 1]) {
				swap(&toSort[j], &toSort[j + 1]);
				getauscht = true;
			}
			j++;
		}
		i++;

		if (!getauscht)
			i = ELEMENTS;
	}
}

void quickSort(int* toSort, int left, int right) {
	int index_l, index_r, med;
	index_l = left;
	index_r = right;

	med = (index_l + index_r) / 2;

	while (index_l < index_r) {
		while (toSort[index_l] < toSort[med]) index_l++;
		while (toSort[index_r] > toSort[med]) index_r--;

		swap(&toSort[index_l], &toSort[index_r]);

		if (index_l == med) med = index_r;
		else if (index_r == med) med = index_l;

		if (index_l < med) index_l++;
		if (index_r > med) index_r--;
	}

	if (left < med - 1) quickSort(toSort, left, med - 1);
	if (right > med + 1) quickSort(toSort, med + 1, right);
}

/* Ignore me

void quickInternet(int* toSort, int left, int right) {
	int index_l, index_r, med;

	if (left < right) {
		med = left;
		index_l = left;
		index_r = right;

		while (index_l < index_r) {
			while (toSort[index_l] <= toSort[med] && index_l < right) index_l++;
			while (toSort[index_r] > toSort[med]) index_r--;

			if (index_l < index_r) {
				swap(&toSort[index_l], &toSort[index_r]);
			}
		}

		swap(&toSort[index_r], &toSort[med]);

		quickInternet(toSort, left, index_r - 1);
		quickInternet(toSort, index_r + 1, right);
	}
}
*/

//Annuität
void annu(void) {
	double darlehen, zins, anfTilg, mZins, mTilg, bezZins = 0, mAnnu, rest;
	int monat = 0;

	printf("Gebe das Darlehen ein: ");
	scanf_s("%lf", &darlehen);

	clearBuffer();

	printf("Gebe den Zinssatz ein: ");
	scanf_s("%lf", &zins);

	clearBuffer();

	printf("Gebe die Tilgung ein: ");
	scanf_s("%lf", &anfTilg);

	clearBuffer();

	FILE* file = fopen("annu.txt", "w");
	fprintf(file, "Darlehen: %.2lf\nZinssatz: %.2lf\nTilgung: %.2lf\n\n", darlehen, zins, anfTilg);


	mAnnu = darlehen * (zins + anfTilg) / 1200;

	rest = darlehen;

	while (rest > 0) {
		mZins = rest * zins / 1200;

		mTilg = mAnnu - mZins;

		if (monat % 12 == 0) {
			printf("%2d. Jahr\n- Restschuld: %.2lf\n- monatlicher Zins: %.2lf\n- monatliche Tilgung: %.2lf\n\n", 
				monat / 12 + 1, 
				rest, 
				mZins,
				mTilg
			);
			fprintf(file, "%2d. Jahr\n- Restschuld: %.2lf\n- monatlicher Zins: %.2lf\n- monatliche Tilgung: %.2lf\n\n",
				monat / 12 + 1, 
				rest, 
				mZins,
				mTilg
				);
		}
		rest -= mTilg;
		monat++;
		bezZins += mZins;

		if ((rest + (rest * zins / 1200)) < mAnnu) {
			mZins = rest * zins / 1200;
			bezZins += mZins;
			rest = 0;
			monat++;
		}
	}

	printf("\nNach %d Jahren und %d Monaten wurden insgesamt %.2lf Zinsen bezahlt!", 
		monat / 12,
		monat % 12, 
		bezZins
	);
	fprintf(file, "\nNach %d Jahren und %d Monaten wurden insgesamt %.2lf Zinsen bezahlt!",
		monat / 12,
		monat % 12,
		bezZins
	);

	fclose(file);
}