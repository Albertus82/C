#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

typedef struct tm* Date;

struct utente {
	char username[20];
	char cognome[50];
	char nome[50];
	char email[100];
	Date dataNascita;
};
typedef struct utente* Utente;

char* formatDate(const Date date) {
	char* dateStr = malloc(11 * sizeof(char));
	sprintf(dateStr, "%.2d/%.2d/%4d", date->tm_mday, date->tm_mon + 1, date->tm_year + 1900);
	return dateStr;
}

Date newDate(const int day, const int month, const int year) {
	Date date = malloc(sizeof(struct tm));
	date->tm_mday = day;
	date->tm_mon = month - 1;
	date->tm_year = year - 1900;
	date->tm_hour = 0;
	date->tm_min = 0;
	date->tm_sec = 0;
	return date;
}

int main(void) {

	time_t timer;
	Date date;

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
	utente->dataNascita = newDate(12, 12, 1990);

	/* Modifica di una data */
	utente->dataNascita->tm_mday -= 3578;
	timer = mktime(utente->dataNascita); // Da "struct tm" a long
	date = localtime(&timer); // Da long a "struct tm"
	free(utente->dataNascita);
	utente->dataNascita = date; // Sovrascrive la vecchia data con la nuova

	printf("%s, %s, %s, %s, %s\n", utente->cognome, utente->nome, utente->email, utente->username,
			formatDate(utente->dataNascita));

	printf("Fine.\n");
	return 0;
}
