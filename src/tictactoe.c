#include <stdio.h>   //printf, scanf
#include <stdbool.h> //bool
/*
Einleitung koennten wir noch erweitern, z.B. die Namen der Spieler eingeben,
aussuchen wer X und wer O setzt, sowie wer anfaengt. Da dies aber nicht
gefordert war, hab ich zugunsten der Uebersichtlichkeit darauf verzichtet.

Hatte keine andere Idee, als bool in eine Funktion zu packen, eigentlich
kommen Funktionen im Heft GPI 22. Hab hier eine Ausnahme gemacht.
*/
bool checkWinner(char matrix[3][3], char player)
{
    // Pruefe Zeilen und Spalten
    for (int i = 0; i < 3; ++i)
    {
        if ((matrix[i][0] == player && matrix[i][1] == player && matrix[i][2] == player) ||
            (matrix[0][i] == player && matrix[1][i] == player && matrix[2][i] == player))
        {
            return true;
        }
    }
    // Pruefe Diagonalen
    if ((matrix[0][0] == player && matrix[1][1] == player && matrix[2][2] == player) ||
        (matrix[0][2] == player && matrix[1][1] == player && matrix[2][0] == player))
    {
        return true;
    }
    return false;
}
bool draw(char matrix[3][3])
{
    for (int z = 0; z < 3; ++z)
    {
        for (int s = 0; s < 3; ++s)
        {
            if (matrix[z][s] == '.')
                return false;
        }
    }
    return true;
}
int main()
{
    // Einleitung
    printf("Willkommen zum Spiel TicTacToe!\n"
           "Es gelten die allgemein bekannten Regeln.\n"
           "Nachfolgend einige Hinweise zur Steuerung:\n"
           "Spieler 1 setzt X und beginnt das Spiel.\n"
           "Spieler 2 setzt O.\n"
           "Koordinaten helfen bei der Eingabe.\n"
           "Geben Sie zuerst die Zeile, dann Leerzeichen, dann die Spalte an.\n"
           "Beispiel: '1 2' wuerde ein Feld in der Mitte der oberen Zeile fuellen.\n"
           "Spiel geht so lange, bis alle Felder voll sind, viel Spass!\n");
    char ticTacToe[3][3];
    char init = '.';
    // Array initialisieren
    for (int z = 0; z < 3; ++z)
    { // z steht fuer Zeile
        for (int s = 0; s < 3; ++s)
        { // s steht fuer Spalte
            ticTacToe[z][s] = init;
        }
    }
    int currentPlayer = 1; // 1 fuer X, 2 fuer O
    while (1)
    { // Spielschleife (unendlich, wird mit break; beendet)
        printf("\nDas aktuelle Spielfeld: \n");
        // Array ausgeben (das aktuelle Spielfeld)
        printf(" 123\n"); // Koordinaten fuer x-Achse
        for (int z = 0; z < 3; ++z)
        {
            printf("%d", z + 1); // Koordinaten fuer y-Achse
            for (int s = 0; s < 3; ++s)
            {
                printf("%c", ticTacToe[z][s]);
            }
            printf("\n");
        }
        // frage Spieler nach Input und validiere es
        printf("Spieler %d (%c) ist dran.\n", currentPlayer, (currentPlayer == 1) ? 'X' : 'O');
        printf("Geben Sie Koordinaten ein: ");
        int Z, S;
        scanf("%d %d", &Z, &S);
        if (Z >= 1 && Z <= 3 && S >= 1 && S <= 3 &&
            ticTacToe[Z - 1][S - 1] != 'X' && ticTacToe[Z - 1][S - 1] != 'O')
        {
            ticTacToe[Z - 1][S - 1] = (currentPlayer == 1) ? 'X' : 'O';
        }
        else
        {
            printf("Eingabe war ungueltig, lesen Sie noch mal die Einleitung.\n");
            while (getchar() != '\n')
                ;
            continue;
        }
        // Pruefe ob jemand gewonnen hat
        if (checkWinner(ticTacToe, (currentPlayer == 1) ? 'X' : 'O'))
        {
            printf("\nSpieler %d (%c) hat gewonnen, Glueckwunsch!\n", currentPlayer, (currentPlayer == 1) ? 'X' : 'O');
            printf("Hier sehen Sie den Endstand: \n");
            // Array ausgeben (das aktuelle Spielfeld)
            printf(" 123\n"); // Koordinaten fuer x-Achse
            for (int z = 0; z < 3; ++z)
            {
                printf("%d", z + 1); // Koordinaten fuer y-Achse
                for (int s = 0; s < 3; ++s)
                {
                    printf("%c", ticTacToe[z][s]);
                }
                printf("\n");
            }
            break;
        }
        else if (draw(ticTacToe))
        {
            printf("Alle Felder sind voll, es gab ein Unentschieden!\n");
            break;
        }
        currentPlayer = (currentPlayer == 1) ? 2 : 1; // Spielerwechsel
    }
    return 0;
}
