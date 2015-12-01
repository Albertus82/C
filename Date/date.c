#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

struct utente {
	char username[20];
	char cognome[50];
	char nome[50];
	char email[100];
	time_t dataNascita;
};
typedef struct utente* Utente;

char* formatDate(const time_t mytime) {
	char* dateStr = malloc(11 * sizeof(char));
	struct tm date = *localtime(&mytime);
	sprintf(dateStr, "%.2d/%.2d/%4d", date.tm_mday, date.tm_mon + 1, date.tm_year + 1900);
	return dateStr;
}

char* formatDateTime(const time_t mytime) {
	char* dateTimeStr = malloc(20 * sizeof(char));
	struct tm date = *localtime(&mytime);
	sprintf(dateTimeStr, "%.2d/%.2d/%4d %.2d:%.2d:%.2d", date.tm_mday, date.tm_mon + 1, date.tm_year + 1900,
			date.tm_hour, date.tm_min, date.tm_sec);
	return dateTimeStr;
}

time_t newDateTime(const int year, const int month, const int date, const int hrs, const int min, const int sec) {
	time_t mytime;
	struct tm myDate = { 0 };
	myDate.tm_mday = date;
	myDate.tm_mon = month - 1;
	myDate.tm_year = year - 1900;
	myDate.tm_hour = hrs;
	myDate.tm_min = min;
	myDate.tm_sec = sec;
	mytime = mktime(&myDate);
	return mytime;
}

time_t newDate(const int year, const int month, const int date) {
	return newDateTime(year, month, date, 0, 0, 0);
}

void dataStruct() {
	Utente utente = malloc(sizeof(struct utente));
	if (utente == NULL) {
		printf("Memoria insufficiente.\n");
		exit(1);
	}
	else {
		printf("Utente@0x%p\n", utente);
	}
	strcpy(utente->cognome, "Rossi");
	strcpy(utente->nome, "Mario");
	strcpy(utente->email, "mario.rossi@azienda.com");
	strcpy(utente->username, "mario.rossi");
	utente->dataNascita = newDate(1980, 6, 1);
	printf("%s, %s, %s, %s, %s\n", utente->cognome, utente->nome, utente->email, utente->username,
			formatDate(utente->dataNascita));
}

void modificaData() {
	struct tm mydate;
	time_t dataDaModificare;
	time_t dataModificata;

	dataDaModificare = newDateTime(1990, 11, 12, 14, 10, 55);
	printf("Data da modificare: %s\n", formatDateTime(dataDaModificare));

	mydate = *localtime(&dataDaModificare);
	mydate.tm_mon += 14;
	dataModificata = mktime(&mydate);
	printf("Data modificata: %s\n", formatDateTime(dataModificata));
}

int main(void) {
	dataStruct();
	modificaData();
	printf("Fine.\n");
	return 0;
}
