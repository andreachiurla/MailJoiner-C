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
    char strPersonID[10];
    char personID;
    printf(MAGENTA"\nPer non inserire più mail, inserisci \'exit\'\n"RESET);
    bool validNumber = false;

    char trash[10];

    while(strcmp(email, "exit")) {
        // richiesta mail
        printf(BLUE"Inserisci mail [exit per uscire]:\n"RESET);
        strcpy(email, "");
        fgets(email, 100, stdin);

        // se non ha inserito 'exit' chiede anche il numero corrispondente alla persona e li stampa su file
        if(strcmp(email, "exit")) {
            while(1) {   // chiede finché inserisce un numero già inserito
                printf(BLUE"Inserisci il numero della persona: "RESET);
                scanf("%s", trash);     // bug - trash
                fgets(&strPersonID, 3, stdin);
                personID = atoi(strPersonID);
                printf("-- ---  --HO LETTO: %c\n", personID);

                if(isFree(personID) == false){
                    printf(RED"Esiste una persona con lo stesso numero.\n"RESET);
                }else{
                    break;
                }
            }

            FILE *fp = fopen(FILENAME, "a");
            fprintf(fp, &personID);
            fprintf(fp, " ");
            fprintf(fp, email);
            fclose(fp);
        }
    }
}

/**
 *
 * @param mailsString
 */
void toString(char mailsString[]){
    FILE *fp = fopen(FILENAME, "r");
    char email[100];
    char toString[1000] = "";
    int personID = -1;
    int nSearch;
    bool isFound = false;

    printf(BOLDGREEN "Per favore, inserisci i numeri dei presenti. [per smettere inserisci '0']" RESET);
    for (int i = 1; personID != 0; ++i) {
        printf(CYAN "\nPresente %d" RESET": ", i);
        scanf("%d", &personID);
        if(personID == 0) break;

        fseek(fp, 0, SEEK_SET);
        while(!feof(fp)){
            fscanf(fp, "%d", &nSearch);
            fseek(fp, +1, SEEK_CUR);
            if(nSearch == personID){
                isFound = true;
                break;
            }
        }
        if(!isFound){
            printf(RED "Nessuna corrispondenza" RESET);
        }else {
            fscanf(fp, "%s", email);     // salvo la mail corrispondente al numero richiesto dall'utente
            printf("\n -- MAIL TROVATA: %s\n", email);
            strcat(toString, email);    // concateno la mail estratta dal file nella stringa di tutte le mail
            strcat(toString, ", ");
        }
    }


    printf("email concatenate: %s\n", toString);
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

    FILE *fp = fopen(FILENAME, "r");
    fseek(fp, 0, SEEK_SET);
    while(!feof(fp)){
        fscanf(fp, "%c", &nSearch);
        fseek(fp, +1, SEEK_CUR);
        if(nSearch == charNum){
            return false;
        }
        char c=fgetc(fp);
        if (c==EOF) break;
    }
    fclose(fp);
    return true;
}