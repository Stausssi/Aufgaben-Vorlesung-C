#include "linkedList.h"

int main(void) {
	mainMenu(NULL);
}

void mainMenu(ListContainer* c) {
	ListContainer* container = c;

	if (container == NULL) {
		container = malloc(sizeof(ListContainer));

		container->first = 0;
		container->current = 0;
		container->elementCount = 0;
		container->pointersShown = false;
		container->autosave = false;
	}

	struct MenuItem menu[] = {
		{"Datensatz anzeigen",			'1',	(void*)&submenu_show,	container},
		{"Element hinzuf" ü "gen",		'2',	(void*)&submenu_add,	container},
		{"Element entfernen",			'3',	(void*)&submenu_remove,	container},
		{"Element suchen",				'4',	(void*)&searchElement,	container},
		{"Elemente sortieren",			'5',	(void*)&submenu_sort,	container},
		{"BLANK",						NULL,	(void*)NULL},
		{"Datensatz speichern",			'a',	(void*)&submenu_save,	container},
		{"Datensatz wiederherstellen",	'b',	(void*)&submenu_get,	container},
		{"BLANK",						NULL,	(void*)NULL},
		{"Beenden",						'q',	(void*)&exit}
	};

	struct MenuPage pages[] = {
		{menu, sizeof(menu) / sizeof(struct MenuItem), "Verkettete Liste", true, true, &SOLID}
	};
	show_menu(pages, sizeof(pages) / sizeof(struct MenuPage), true);
}


/* -----[Show]----- */

void submenu_show(ListContainer* container) {
	if (firstElementCreated(container)) {
		struct MenuItem show[] = {
			{"Liste anzeigen",				'1',	(void*)&showList,		container},
			{"Seiten" ü "bersicht anzeigen",	'2',	(void*)&showPage,		container},
			{"BLANK",						NULL,	(void*)NULL},
			{"Zeigerdarstellung umstellen",	'a',	(void*)&pointersShown,	container},
			{"BLANK",						NULL,	(void*)NULL},
			{"Zur" ü "ck",						'b',	(void*)&mainMenu,		container}
		};
		struct MenuPage page[] = {
				{show, sizeof(show) / sizeof(struct MenuItem), "Datensatz anzeigen", false, false, &NO_BORDER}
		};
		show_menu(page, sizeof(page) / sizeof(struct MenuPage), false);
	}
	else
		printf("Die Liste ist aktuell leer!");
}

void showList(ListContainer* container) {
	int position = 1;
	ListElement* helpElement = container->first;

	printf("Die Liste enth" ä "lt folgende Elemente:\n\n");
	printf(
		"%8s %21s %10s %22s %25s",
		"Position",
		"Name der Person",
		"Postleitzahl",
		"Stadt",
		"Hobby"
	);

	if (container->pointersShown)
		printf(
			" | %8s %8s %8s", "Zeiger", "Davor", "Danach");

	putchar('\n');

	do {
		printf(
			" %3d %25s %9s %25s %25s",
			position++,
			helpElement->name,
			helpElement->postcode,
			helpElement->city,
			helpElement->hobby
		);

		if (container->pointersShown) printf(" | %p %p %p", helpElement, helpElement->previous, helpElement->next);

		putchar('\n');

		helpElement = helpElement->next;
	} while (helpElement != 0);
}

void showPage(ListContainer* container) {
	int pageIndex = 1;
	ListElement* helpElement = container->first;
	char input;

	do {
		system("cls");

		printf("Seiten wechseln mit 'a'/'d', beenden mit 'q'!\n\n");

		printf("Element %d:\n", pageIndex);

		printf("- %-7s %s\n- %-7s %s\n- %-7s %s\n- %-7s %s\n",
			"Name:", helpElement->name,
			"Hobby:", helpElement->hobby,
			"PLZ:", helpElement->postcode,
			"Stadt:", helpElement->city
		);

		if (container->pointersShown)
			printf(
				"\n- %-7s %p\n  - %-7s %p\n  - %-7s %p",
				"Zeiger:", helpElement,
				"Davor:", helpElement->previous,
				"Danach:", helpElement->next
			);

		putchar('\n');
		printf("> ");

		input = tolower(_getch());

		if (input == 'a' && pageIndex > 1) {
			pageIndex--;
			helpElement = helpElement->previous;
		}
		if (input == 'd' && pageIndex < container->elementCount) {
			pageIndex++;
			helpElement = helpElement->next;
		}

	} while (input != 'q');
}

void pointersShown(ListContainer* container) {
	container->pointersShown = !container->pointersShown;

	char info[13];
	switch (container->pointersShown) {
	case 0:
		strcpy(info, "deaktiviert");
		break;
	case 1:
		strcpy(info, "aktiviert");
		break;
	}
	printf("Zeigerdarstellung wurde erfolgreich %s!", info);
}


/* -----[Add]----- */

void submenu_add(ListContainer* container) {
	struct MenuItem add[] = {
		{"Einzelnes Element hinzuf" ü "gen",				'1',	(void*)&addElement,				container},
		{"An einer bestimmten Stelle einf" ü "gen",			'2',	(void*)&addElementAt,			container},
		{"Bestimmte Anzahl an Elementen hinzuf" ü "gen",	'3',	(void*)&addMultipleElements,	container},
		{"Existierenden Datensatz kopieren und bearbeiten",	'4',	(void*)&cloneElement,			container},
		{"BLANK",											NULL,	(void*)NULL},
		{"Zur" ü "ck",										'b',	(void*)&mainMenu,				container}
	};
	struct MenuPage page[] = {
			{add, sizeof(add) / sizeof(struct MenuItem), "Element hinzuf" ü "gen", false, false, &NO_BORDER}
	};
	show_menu(page, sizeof(page) / sizeof(struct MenuPage), false);
};

void addElement(ListContainer* container) {
	linkElement(container, fillElement(container), container->elementCount + 1);

	printf("Neues Element wurde hinzugef" ü "gt!");
}

void addElementAt(ListContainer* container) {
	int pos = 0;

	getPosition(&pos, "An welcher Stelle soll das Element hinzugef" ü "gt werden", false, container);

	if (pos >= 1 && pos <= container->elementCount + 1)
		linkElement(container, fillElement(container), pos);
	else
		printf("Die angegebene Position %d ist ung" ü "ltig!", pos);
}

void addMultipleElements(ListContainer* container) {
	int count;

	getPosition(&count, "Wie viele Elemente sollen hintereinander hinzugef" ü "gt werden", false, container);

	if (count <= 10)
		for (int i = 0; i < count; i++) {
			system("cls");
			addElement(container);
		}
	else
		printf("Es k" ö "nnen maximal 10 Elemente nacheinander eingef" ü "gt werden");
}

void cloneElement(ListContainer* container) {
	int pos;

	if (getPosition(&pos, "Welche Position soll dupliziert werden", true, container)) {
		ListElement
			* clonedElement = malloc(sizeof(ListElement)),
			* toBeCloned = getElementAt(container, pos);

		if (yesNoDialog("Soll dieses Element dupliziert werden", toBeCloned, true)) {
			strcpy(clonedElement->name, toBeCloned->name);
			strcpy(clonedElement->hobby, toBeCloned->hobby);
			strcpy(clonedElement->postcode, toBeCloned->postcode);
			strcpy(clonedElement->city, toBeCloned->city);

			clonedElement->next = NULL;
			clonedElement->previous = NULL;

			if (yesNoDialog("Soll dieses Element noch bearbeitet werden", clonedElement, false)) notSupported();

			getPosition(&pos, "An welcher Stelle soll das Element eingef" ü "gt werden", false, container);

			if (pos >= 1 && pos <= container->elementCount + 1) {
				linkElement(container, clonedElement, pos);

				printf("Das Element wurde erfolgreich dupliziert und an der Stelle %d eingef" ü "gt!", pos);
			}
			else
				printf("Die angegebene Position %d ist ung" ü "ltig!", pos);
		}
		else
			printf("Vorgang abgebrochen!");
	}
	else
		printf("Die angegebene Position %d existiert nicht!", pos);
}

void linkElement(ListContainer* container, ListElement* item, int position) {
	container->current = item;

	if (position == 1) {
		if (firstElementCreated(container)) {
			container->first->previous = container->current;
			container->current->next = container->first;
		}

		container->first = container->current;
	}
	else {
		container->current->next = getElementAt(container, position);
		container->current->previous = getElementAt(container, position - 1);

		if (container->current->previous != NULL)
			container->current->previous->next = container->current;

		if (container->current->next != NULL)
			container->current->next->previous = container->current;
	}

	if (container->autosave) writeFile(DEFAULT_PATH_AUTOSAVE, container);

	container->elementCount++;
}

ListElement* fillElement(ListContainer* container) {
	ListElement* helpElement = malloc(sizeof(ListElement));

	printf("Bitte gebe den Namen ein: ");
	gets_s(helpElement->name, INPUT_LENGTH);

	printf("Bitte gebe deren Hobby an: ");
	gets_s(helpElement->hobby, INPUT_LENGTH);

	printf("Bitte gebe die Postleitzahl ein: ");
	gets_s(helpElement->postcode, 10);

	printf("Bitte gebe die entsprechende Stadt ein: ");
	gets_s(helpElement->city, INPUT_LENGTH);

	helpElement->next = NULL;
	helpElement->previous = NULL;

	return helpElement;
}


/* -----[Remove]----- */

void submenu_remove(ListContainer* container) {
	if (firstElementCreated(container)) {
		struct MenuItem remove[] = {
		{"Element an beliebiger Stelle entfernen",	'1',	(void*)&removeElementAt,		container},
		{"Bestimmten Bereich entfernen",			'2',	(void*)&removeElementsInRange,	container},
		{"Gesamte Liste l" ö "schen",			'3',	(void*)&removeAllElements,		container},
		{"BLANK",									NULL,	(void*)NULL},
		{"Zur" ü "ck",							'b',	(void*)&mainMenu,				container}
		};
		struct MenuPage page[] = {
			{remove, sizeof(remove) / sizeof(struct MenuItem), "Element entfernen", false, false, &NO_BORDER}
		};
		show_menu(page, sizeof(page) / sizeof(struct MenuPage), false);
	}
	else
		printf("Es gibt keine Elemente zum Entfernen!");
}

void removeElement(ListElement* toBeDeleted, ListContainer* container) {
	ListElement
		* helpElementNext,
		* helpElementPrevious;

	if (hasNextElement(toBeDeleted) && hasPreviousElement(toBeDeleted)) {
		helpElementNext = toBeDeleted->next;
		helpElementPrevious = toBeDeleted->previous;

		helpElementNext->previous = helpElementPrevious;
		helpElementPrevious->next = helpElementNext;
	}
	else if (hasNextElement(toBeDeleted)) {
		helpElementNext = toBeDeleted->next;
		helpElementNext->previous = 0;

		container->first = helpElementNext;
	}
	else if (hasPreviousElement(toBeDeleted)) {
		helpElementPrevious = toBeDeleted->previous;
		helpElementPrevious->next = 0;

		container->current = helpElementPrevious;
	}
	else {
		container->first = 0;
		container->current = 0;
	}

	free(toBeDeleted);

	if (container->autosave) writeFile(DEFAULT_PATH_AUTOSAVE, container);

	container->elementCount--;
}

void removeElementAt(ListContainer* container) {
	int pos, ctr = 0;

	if (getPosition(&pos, "An welcher Stelle soll das Element entfernt werden", true, container)) {
		ListElement* toBeDeleted = getElementAt(container, pos);

		if (yesNoDialog("Soll folgendes Element entfernt werden", toBeDeleted, true)) {
			printf("Entferne Element an der Stelle %d...\n", pos);

			removeElement(toBeDeleted, container);

			printf("Das Element wurde erfolgreich entfernt!");
		}
		else
			printf("Vorgang abgebrochen!");
	}
	else
		printf("Die angegebene Position %d existiert nicht!", pos);
}

void removeElementsInRange(ListContainer* container) {
	int lower, upper;

	if (getPosition(&lower, "Wie lautet der Startpunkt des Bereiches", true, container)) {
		if (getPosition(&upper, "Wie lautet der Endpunkt des Bereiches", true, container)) {
			if (upper > lower) {
				printf("Entferne alle Elemente im Bereich %d-%d...\n", lower, upper);

				for (int i = lower; i <= upper; i++) removeElement(getElementAt(container, lower), container);

				printf("Alle Elemente im Bereich %d-%d wurden entfernt!", lower, upper);
			}
			else
				printf("Der angegebene Bereich ist ung" ü "ltig!");
		}
		else
			printf("Die angegebene Position %d exisitert nicht!", upper);
	}
	else
		printf("Die angegebene Position %d exisitert nicht!", lower);
}

void removeAllElements(ListContainer* container) {
	printf("Entferne alle Elemente der Liste...\n");

	for (int i = 0; i <= container->elementCount + i; i++) removeElement(getElementAt(container, 1), container);

	printf("Alle Elemente wurden erfolgreich entfernt!");
}


/* -----[Search]----- */

void searchElement(ListContainer* container) {
	if (!firstElementCreated(container))
		printf("Es befinden sich noch keine Elemente in der Liste!");
	else {
		printf("Die Suche funktioniert wie folgt:\n");
		printf("'PARAM:Wert'\n");
		printf("Korrekte Parameter sind 'NAME', 'PLZ', 'STADT', 'HOBBY'.\n\n");

		char input[INPUT_LENGTH * 2 + 1];
		printf("Nach was m\x94\chtest du suchen? ");
		gets_s(input, INPUT_LENGTH * 2);

		char* token = strtok(input, ":");

		if (token != NULL && (strcmp(token, "NAME") == 0 || strcmp(token, "PLZ") == 0 || strcmp(token, "STADT") == 0 || strcmp(token, "HOBBY") == 0)) {
			char* value = strtok(NULL, ":");
			if (value != NULL) {
				printf("Es wird nach %s gesucht...\n", value);
				searchFor(token, value, container);
			}
		}
		else {
			printf("Es konnte kein Parameter gefunden werden!");
		}
	}
}
void searchFor(char* token, char* value, ListContainer* container) {
	container->current = container->first;
	int pos = 1;
	bool entryFound;
	while (container->current != NULL) {
		entryFound = false;

		if (strcmp(token, "NAME") == 0) {
			if (strcmp(container->current->name, value) == 0) {
				entryFound = true;
			}
		}
		else if (strcmp(token, "PLZ") == 0) {
			if (strcmp(container->current->postcode, value) == 0) {
				entryFound = true;
			}
		}
		else if (strcmp(token, "STADT") == 0) {
			if (strcmp(container->current->city, value) == 0) {
				entryFound = true;
			}
		}
		else if (strcmp(token, "HOBBY") == 0) {
			if (strcmp(container->current->hobby, value) == 0) {
				entryFound = true;
			}
		}

		if (entryFound)
			printf(
				"\nPosition %d:\n- Name:  %s\n- PLZ:   %s\n- Stadt: %s\n- Hobby: %s",
				pos,
				container->current->name,
				container->current->postcode,
				container->current->city,
				container->current->hobby
			);

		pos++;
		container->current = container->current->next;
	}

	printf("\n\nDie Suche ist abgeschlossen!");
}


/* -----[Sort]----- */

void submenu_sort(ListContainer* container) {
	if (firstElementCreated(container)) {
		struct MenuItem sort[] = {
			{"Nach Namen sortieren",			'1',	(void*)&sortName,	container},
			{"Nach Hobby sortieren",			'2',	(void*)&sortHobby,	container},
			{"Nach Postleitzahl sortieren",		'3',	(void*)&sortPLZ,	container},
			{"Nach Stadt sortieren",			'4',	(void*)&sortCity,	container},
			{"BLANK",							NULL,	(void*)NULL},
			{"Zur" ü "ck",						'b',	(void*)&mainMenu,	container}
		};
		struct MenuPage page[] = {
			{sort, sizeof(sort) / sizeof(struct MenuItem), "Datensatz sortieren", false, false, &NO_BORDER}
		};
		show_menu(page, sizeof(page) / sizeof(struct MenuPage), false);
	}
	else
		printf("Es gibt keine Elemente zum Sortieren!");
}

void sortName(ListContainer* container) {
	sort(container, SORT_NAME);
}
void sortHobby(ListContainer* container) {
	sort(container, SORT_HOBBY);
}
void sortPLZ(ListContainer* container) {
	sort(container, SORT_PLZ);
}
void sortCity(ListContainer* container) {
	sort(container, SORT_CITY);
}

void sort(ListContainer* container, char* criteria) {
	sortElements(container, 0, container->elementCount, criteria);
	printf("Die Liste wurde erfolgreich nach %s sortiert!", criteria);

	if (container->autosave) writeFile(DEFAULT_PATH_AUTOSAVE, container);
}

void sortElements(ListContainer* container, int left, int right, char* sortType) {
	int index_l, index_r, med;
	index_l = left;
	index_r = right;
	med = (index_l + index_r) / 2;

	while (index_l < index_r) {
		ListElement
			* elLeft = getElementAt(container, index_l),
			* elRight = getElementAt(container, index_r),
			* elMed = getElementAt(container, med);

		if (strcmp(sortType, SORT_NAME) == 0) {
			while (strcmp(elLeft->name, elMed->name) < 0) {
				elLeft = elLeft->next;
				index_l++;
			}

			while (strcmp(elRight->name, elMed->name) > 0) {
				elRight = elRight->previous;
				index_r--;
			}
		}
		else if (strcmp(sortType, SORT_HOBBY) == 0) {
			while (strcmp(elLeft->hobby, elMed->hobby) < 0) {
				elLeft = elLeft->next;
				index_l++;
			}

			while (strcmp(elRight->hobby, elMed->hobby) > 0) {
				elRight = elRight->previous;
				index_r--;
			}
		}
		else if (strcmp(sortType, SORT_PLZ) == 0) {
			while (strcmp(elLeft->postcode, elMed->postcode) < 0) {
				elLeft = elLeft->next;
				index_l++;
			}

			while (strcmp(elRight->postcode, elMed->postcode) > 0) {
				elRight = elRight->previous;
				index_r--;
			}
		}
		else if (strcmp(sortType, SORT_CITY) == 0) {
			while (strcmp(elLeft->city, elMed->city) < 0) {
				elLeft = elLeft->next;
				index_l++;
			}

			while (strcmp(elRight->city, elMed->city) > 0) {
				elRight = elRight->previous;
				index_r--;
			}
		}

		if(elLeft != elRight) swapElements(elLeft, elRight, container);

		if (index_l == med) med = index_r;
		else if (index_r == med) med = index_l;

		if (index_l < med) index_l++;
		if (index_r > med) index_r--;
	}

	if (left < med - 1) sortElements(container, left, med - 1, sortType);
	if (right > med + 1) sortElements(container, med + 1, right, sortType);
}

void swapElements(ListElement* element1, ListElement* element2) {
	char temp[INPUT_LENGTH + 1];

	strcpy(temp, element1->name);
	strcpy(element1->name, element2->name);
	strcpy(element2->name , temp);

	strcpy(temp, element1->hobby);
	strcpy(element1->hobby, element2->hobby);
	strcpy(element2->hobby, temp);

	strcpy(temp, element1->postcode);
	strcpy(element1->postcode, element2->postcode);
	strcpy(element2->postcode, temp);

	strcpy(temp, element1->city);
	strcpy(element1->city, element2->city);
	strcpy(element2->city, temp);
}

/* -----[File Handling]----- */

void submenu_save(ListContainer* container) {
	if (firstElementCreated(container)) {
		struct MenuItem save[] = {
			{"Standarddatei verwenden",				'1',	(void*)&saveContent,	container},
			{"Benutzerdefinierte Datei verwenden",	'2',	(void*)&saveContentTo,	container},
			{"BLANK",								NULL,	(void*)NULL},
			{"Automatisches Speichern umschalten",	'a',	(void*)&switchAutosave,	container},
			{"BLANK",								NULL,	(void*)NULL},
			{"Zur" ü "ck",							'b',	(void*)&mainMenu,		container}
		};
		struct MenuPage page[] = {
			{save, sizeof(save) / sizeof(struct MenuItem), "Datensatz speichern", false, false, &NO_BORDER}
		};
		show_menu(page, sizeof(page) / sizeof(struct MenuPage), false);
	}
	else
		printf("Es exisiteren keine Elemente zum Speichern!");
}

void saveContent(ListContainer* container) {
	writeFile(DEFAULT_PATH, container);
}

void saveContentTo(ListContainer* container) {
	char path[MAX_PATH_SIZE + 1];
	printf("In welcher Datei sollen die Eintr" ä "ge gespeichert werden?\n");
	printf("> ");

	gets_s(path, MAX_PATH_SIZE);

	writeFile(path, container);
}

void writeFile(char* path, ListContainer* container) {
	if (strcmp(path, DEFAULT_PATH_AUTOSAVE) != 0) printf("Elemente werden in '%s' gespeichert...\n", path);

	ListElement* helpElement = container->first;
	FILE* file = fopen(path, "w");

	do {
		fprintf(file,
			"%s,%s,%s,%s;\n",
			helpElement->name,
			helpElement->postcode,
			helpElement->city,
			helpElement->hobby
		);

		helpElement = helpElement->next;
	} while (helpElement != 0);

	fclose(file);

	if (strcmp(path, DEFAULT_PATH_AUTOSAVE) != 0) printf("Erfolgreich gespeichert!");
}

void switchAutosave(ListContainer* container) {
	container->autosave = !container->autosave;

	char info[13];
	switch (container->autosave) {
	case 0:
		strcpy(info, "deaktiviert");
		break;
	case 1:
		strcpy(info, "aktiviert");
		break;
	}
	printf("Automatisches Speichern wurde erfolgreich %s!", info);
}

void submenu_get(ListContainer* container) {
	struct MenuItem get[] = {
		{"Standarddatei verwenden",				'1',	(void*)&getContent,			container},
		{"Autosave wiederherstellen",			'2',	(void*)&restoreAutosave,	container},
		{"Benutzerdefinierte Datei verwenden",	'3',	(void*)&getContentFrom,		container},
		{"BLANK",								NULL,	(void*)NULL},
		{"Zur" ü "ck",							'b',	(void*)&mainMenu,			container}
	};
	struct MenuPage page[] = {
		{get, sizeof(get) / sizeof(struct MenuItem), "Datensatz wiedererstellen", false, false, &NO_BORDER}
	};
	show_menu(page, sizeof(page) / sizeof(struct MenuPage), false);
}

void getContent(ListContainer* container) {
	readFile(DEFAULT_PATH, container);
}

void restoreAutosave(ListContainer* container) {
	readFile(DEFAULT_PATH_AUTOSAVE, container);
}

void getContentFrom(ListContainer* container) {
	char path[MAX_PATH_SIZE];
	printf("Von welcher Datei soll der Datensatz wiederhergestellt werden?\n");
	printf("> ");

	gets_s(path, MAX_PATH_SIZE);

	readFile(path, container);
}

bool readFile(char* path, ListContainer* container) {
	FILE* file;
	file = fopen(path, "r");

	if (file != NULL) {
		printf("Elemente werden aus '%s' widerhergestellt...\n", path);
		char temp[INPUT_LENGTH * 3 + 15 + 1];

		fgets(temp, INPUT_LENGTH * 3 + 15, file);
		while (!feof(file)) {
			ListElement* helpElement = malloc(sizeof(ListElement));

			if (strncmp(temp, "***", 3) != 0 && strcmp(temp, "\n") != 0) {
				char* token = strtok(temp, ",;\n");
				int x = 0;
				while (token != NULL) {
					switch (x++) {
					case 0:
						strcpy(helpElement->name, token);
						break;
					case 1:
						strcpy(helpElement->postcode, token);
						break;
					case 2:
						strcpy(helpElement->city, token);
						break;
					case 3:
						strcpy(helpElement->hobby, token);
						break;
					}
					token = strtok(NULL, ",;\n");
				}

				helpElement->next = NULL;
				helpElement->previous = NULL;

				linkElement(container, helpElement, container->elementCount + 1);
			}

			fgets(temp, INPUT_LENGTH * 3 + 15, file);
		}
		fclose(file);

		printf("Der Datensatz wurde erfolgreich aus '%s' widerhergestellt!", path);
	}
	else
		printf("Die Textdatei '%s' konnte nicht gefunden werden!", path);
}


/* -----[Utility]----- */

bool getPosition(int* toWrite, char* message, bool performCheck, ListContainer* container) {
	system("cls");

	printf("%s? ", message);
	scanf_s("%d", toWrite);

	clearBuffer();

	if (performCheck)
		return isElementAt(container, *toWrite);
	else
		return true;
}

ListElement* getElementAt(ListContainer* container, int position) {
	ListElement* helpElement = container->first;

	for (int i = 1; i < position; i++) helpElement = helpElement->next;

 	return helpElement;
}

bool firstElementCreated(ListContainer* container) {
	return container->first != 0;
}

bool isElementAt(ListContainer* container, unsigned int position) {
	return position <= container->elementCount && position > 0;
}

bool yesNoDialog(char* message, ListElement* element, bool printInfo) {
	char input;
	do {
		system("cls");

		printf("%s? [y/n]\n", message);
		if (printInfo)
			printf(
				"Name: %s\nStadt: %s %s\nHobby: %s\n",
				element->name,
				element->postcode,
				element->city,
				element->hobby
			);

		putchar('>');
		putchar(' ');

		scanf_s("%c", &input, 1);

		clearBuffer();

		input = tolower(input);
	} while (input != 'y' && input != 'n');

	return input == 'y';
}

bool hasNextElement(ListElement* element) {
	return element != NULL ? element->next != NULL : false;
}

bool hasPreviousElement(ListElement* element) {
	return element != NULL ? element->previous != NULL : false;
}

void clearBuffer(void) {
	while (getchar() != '\n');
}


void notSupported(void) {
	printf("Diese Funktion wird derzeit noch nicht unterst" ü "tzt!");
}