#include "funzioni.h"

int main() {
    int userRequest = -1;
    char mailsString[10000];
    FILE *fp = fopen("listaEmail.txt", "r+"); // creazione file
    fclose(fp);

    while(userRequest != 3) {
        // richiesta comando
        printf(RED "\n---- COMANDI ----" RESET);
        printf("\n-Richiedi stringa mail dei presenti " BLUE "[1] \n" RESET
               "-Aggiungi mail " BLUE "[2]\n" RESET
               "-Esci dal programma " BLUE "[3]\n" RESET);
        printf("\n");
        printf(BLUE "Inserisci comando: " RESET);
        scanf("%d", &userRequest);

        // chiamata funzione relativa al comando
        if (userRequest == 1) toString(mailsString);
        else if(userRequest == 2) addMail();
        else if(userRequest == 3){
            printf(RED "Uscendo dal programma..." RESET);
        }
        else{
            printf("Input inserito non valido");
        }

        printf("\n");
    }

    return 0;
}
