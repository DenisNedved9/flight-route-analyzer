#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

struct Waypoint
{
    char jmeno_in[30];
    float x;
    float y;
};

int main()
{

    FILE *pRoute = fopen("route.txt", "r"); // otevření složek
    FILE *pOutput = fopen("output.txt", "w");

    if (pRoute == NULL)
    { // kontrola zda není složka prázdna
        return 1;
    }

    char jmeno[30] = "";
    char x[50] = "";
    char y[50] = "";
    int output;
    float output_let;

    float nejdelsi = 0;

    float celkova_vzdalenost_letu = 0;
    float full_distance = 0;
    int type_of_waypoint = 0;
    int jmeno_promenna = 0;
    int x_promenna = 0;
    int y_promenna = 0;
    int let = 1;

    int pocet = 0;
    int typ = 0;

    char buffer[1024] = "0";

    int size = atoi(fgets(buffer, sizeof(buffer), pRoute));              // převedení str na int
    struct Waypoint *Waypoints = malloc(size * sizeof(struct Waypoint)); // vytvoření mallocu pro strc
    if (Waypoints == NULL)
    {
        fclose(pRoute);
        fclose(pOutput);
        return 1;
    }

    rewind(pRoute);

    while (fgets(buffer, sizeof(buffer), pRoute) != NULL) // opakuje se dokud je něco ve složce
    {
        buffer[strcspn(buffer, "\n")] = '\0'; // ostraníme konec řadku pokud tam je
        y_promenna = 0;
        x_promenna = 0;
        jmeno_promenna = 0;

        if (typ == 0) // pro 1. řádek kde je číslo na malloc jdeme jenom continue
        {
            typ++;
            continue;
        }
        for (int i = 0; i < strlen(buffer); i++) // pro každé písmeno/znak/číslo projdeme tento list
        {

            if (buffer[i] == ',') /*věci v route jsou odděleny čárkami takže až narazíme na čárku jdeme na další část
            jméno letu -> první lokace -> druhá lokace
            */
            {

                typ++;
                continue;
            }
            if (typ == 1)
            {

                jmeno[jmeno_promenna] = buffer[i];
                jmeno_promenna++;
            }
            else if (typ == 2)
            {

                x[x_promenna] = buffer[i];
                x_promenna++;
            }
            else if (typ == 3)
            {

                y[y_promenna] = buffer[i];
                y_promenna++;
            }
        }

        strcpy(Waypoints[type_of_waypoint].jmeno_in, jmeno); // přidání věcí do struct
        Waypoints[type_of_waypoint].x = atof(x);
        Waypoints[type_of_waypoint].y = atof(y);

        let++;
        type_of_waypoint++;
        typ = 1;
    }

    fprintf(pOutput, "ROUTE ANALYSIS:\n----------------------------------------\n");
    for (int i = 0; i < type_of_waypoint - 1; i++)
    {
        celkova_vzdalenost_letu = sqrt(pow((Waypoints[i + 1].x - Waypoints[i].x), 2) + pow((Waypoints[i + 1].y - Waypoints[i].y), 2));
        full_distance += celkova_vzdalenost_letu;
        if (celkova_vzdalenost_letu > nejdelsi)
        {
            output = i;
            output_let = celkova_vzdalenost_letu;
        }

        fprintf(pOutput, "%d. ", i + 1);
        fprintf(pOutput, "%s ", Waypoints[i].jmeno_in);
        fprintf(pOutput, "(%.2f, ", Waypoints[i].x);
        fprintf(pOutput, "%.2f) -> ", Waypoints[i].y);

        fprintf(pOutput, "%s ", Waypoints[i + 1].jmeno_in);
        fprintf(pOutput, "(%.2f, ", Waypoints[i + 1].x);
        fprintf(pOutput, "%.2f) : ", Waypoints[i + 1].y);
        fprintf(pOutput, "%.2f km", celkova_vzdalenost_letu);

        fprintf(pOutput, "\n");
    }
    fprintf(pOutput, "----------------------------------------\nTotal route length: %.1f km\n", full_distance);
    fprintf(pOutput, "Longest leg: %s -> %s (%.2f km)", Waypoints[output].jmeno_in, Waypoints[output + 1].jmeno_in, output_let);

    printf("Output was saved to 'output.txt'");

    free(Waypoints); // uzavření složek a uvolnění memory
    fclose(pRoute);
    fclose(pOutput);
    return 0;
}