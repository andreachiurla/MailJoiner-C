#include "funzioni.h"

/**
 * metodo di memorizzazione:
 * numeroPersona mailPersona
 *
 * 1. addMail
 * 2. aggiunge una mail in fondo al file che le contiene tutte
 * 3. void
 * 4. void
 */
void addMail(){
    char email[100] = "";
    int personID;
    char temp;

    printf(MAGENTA"\nPer non inserire più mail, inserisci \'exit\'\n"RESET);

    while(strcmp(email, "exit")) {
        // richiesta mail
        printf(BLUE"Inserisci mail [exit per uscire]:\n"RESET);
        strcpy(email, "");
        scanf("%c", &temp);    // '\n' problem
        fgets(email, 100, stdin);
        email[strcspn(email, "\n")] = 0;

        // se non ha inserito 'exit' chiede anche il numero corrispondente alla persona e li stampa su file
        if(strcmp(email, "exit")) {
            personID = getPersonID();
            temp = personID + '0';

            FILE *fp = fopen(FILENAME, "a");
            fprintf(fp, &temp);
            fprintf(fp, " ");
            fprintf(fp, email);
            fprintf(fp, "\n");
            fclose(fp);
        }
    }
}

int getPersonID() {
    int personID;

    while(1) {   // chiede finché inserisce un numero già inserito
        printf(BLUE"Inserisci il numero della persona: "RESET);
        scanf( " %d", &personID) ;

        if(isFree(personID) == false){
            printf(RED"Esiste una persona con lo stesso numero.\n"RESET);
        }else{
            break;
        }
    }
    return personID;
}

/**
 *
 * @param mailsString
 */
void toString(){
    FILE *fp = fopen(FILENAME, "r");
    char email[100];
    char toString[1000] = "";
    int personID = -1;
    int nSearch;
    bool isFound = false;

    printf(BOLDGREEN "Inserisci il numero di ogni presente. [per smettere inserisci '0']" RESET);
    for (int i = 1; personID != 0; ++i) {
        printf(CYAN "\nPresente %d" RESET": ", i);
        scanf("%d", &personID);
        if(personID == 0) break;

        fseek(fp, 0, SEEK_SET);
        while(!feof(fp)){
            fscanf(fp, "%d", &nSearch);
            if(nSearch == personID){
                isFound = true;
                break;
            }
            fseek(fp, +1, SEEK_CUR);
            if (nSearch == EOF) break;
        }
        if(!isFound){
            printf(RED "Nessuna corrispondenza" RESET);
        }else {
            printf("\n -- MAIL TROVATA: %s\n", email);
            fscanf(fp, "%s", email);     // salvo la mail corrispondente al numero richiesto dall'utente
            strcat(toString, email);    // concateno la mail estratta dal file nella stringa di tutte le mail
            strcat(toString, ", ");
        }
    }

    fclose(fp);
    printf("email concatenate:\n%s\n", toString);
}

/**
 *
 * @param fp
 * @param num
 * @return
 */
bool isFree(int num){
    char nSearch;
    num = abs(num);
    char charNum = num + '0';

    FILE *fp = fopen(FILENAME, "r+");
    if(fp == NULL){
        printf(RED "\nErrore nell'apertura del file\n" RESET);
    }else {
        fseek(fp, 0, SEEK_SET);
        while (!feof(fp)) {
            fscanf(fp, "%c", &nSearch);
            fseek(fp, +1, SEEK_CUR);
            if (nSearch == charNum) {
                return false;
            }
            char c = fgetc(fp);
            if (c == EOF) break;    // se finito il file esce
        }
        fclose(fp);
    }
    return true;
}