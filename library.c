/************************************************************************
 * LES10A110 Principles of C-programming
 * Name: S******o
 * Student number: 0******3
 * Email: S******o@student.lut.fi
 * Date: 1.5.2022
 * By submitting this work for evaluation, I certify that
 * 1) I myself wrote all the code in this file
 * 2) I have not given this code to anyone else
 *************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "library.h"

// in this function it just print the menu in every cycle
void printMenu() {
    printf("1)Read the file\n"
           "2)Analyze consumption\n"
           "3)Analyze production\n"
           "0)Stop\n"
           "Select an Item:\n");
}

/* this function accept the file name and the pointer of the list,
it use fopen to open file, and fgets to read the file line by line,
then the strtok will separate the data and store them into
a newly created node, and add the new node into the list,
the while loop repeat the steps above until last line is read
*/
void readFile(char fileName[], link *list) {
    int i, cont, col = 0, row[8];
    char *fild;
    char stmp[20], line[200];
    FILE *fp = fopen(fileName, "r");
    cont = 0;
    while(fgets(line, 200, fp)) {
        if(cont != 0) {
            col = 0;
            fild = strtok(line, ";");
            strcpy(stmp, fild);
            while(col < 8) {
                fild = strtok(NULL, ";");
                row[col] = atoi(fild);
                ++col;
            }
            link *node = malloc(sizeof(link));
            strcpy(node->time, stmp);
            for(i = 0; i < 8; ++i) {
                node->data[i] = row[i];
            }
            node->next = NULL;
            list->next = node;
            list = node;
        }
        ++cont;
    }
    fclose(fp);
}

/* this function accept the head pointer.
In every cycle it accumulate the total consumption,
and compare with the currently biggest and smallest,
if it's even bigger or smaller then replace the previous one,
and also there is a counter count the amount of data,
after doing those above it move to the next node,
repeat steps above until the last node is read.
Finally it print the result info into standard out and new file.
*/
void analyzeConsumption(link *head) {
    int cont = 0, bgst = 0, lest = 2147483647, ibSt[3], ilSt[3];
    double mean, csum = 0;
    char bStp[200], lStp[200];
    link *ptr = head->next;
    while(ptr) {
        ++cont;
        csum += ptr->data[1];
        if(ptr->data[1] > bgst) {
            bgst = ptr->data[1];
            strcpy(bStp, ptr->time);
        } else if(ptr->data[1] < lest) {
            lest = ptr->data[1];
            strcpy(lStp, ptr->time);
        }
        ptr = ptr->next;
    }
    mean = csum / cont;
    free(ptr);
    ibSt[0] = atoi(&bStp[0]);
    ibSt[1] = atoi(&bStp[3]);
    ibSt[2] = atoi(&bStp[10]);
    ilSt[0] = atoi(&lStp[0]);
    ilSt[1] = atoi(&lStp[3]);
    ilSt[2] = atoi(&lStp[10]);
    fprintf(stdout, "Statistics on %d measurements:\n"
        "Consumption totaled %.lf kWh, and averaged %.1lf kWh.\n"
        "The highest consumption, %d kWh, occurred on %d.%d.2020 %d:00.\n"
        "The lowest consumption, %d kWh, occurred on %d.%d.2020 %d:00.\n",
        cont, csum, mean, bgst, ibSt[0], ibSt[1], ibSt[2],
        lest, ilSt[0], ilSt[1], ilSt[2]);
    FILE *fp = fopen("consumption.txt", "w");
    fprintf(fp, "Statistics on %d measurements:\n"
        "Consumption totaled %.lf kWh, and averaged %.1lf kWh.\n"
        "The highest consumption, %d kWh, occurred on %d.%d.2020 %d:00.\n"
        "The lowest consumption, %d kWh, occurred on %d.%d.2020 %d:00.\n",
        cont, csum, mean, bgst, ibSt[0], ibSt[1], ibSt[2],
        lest, ilSt[0], ilSt[1], ilSt[2]);
    fclose(fp);
}

// this function accept parameter, parse the data, write file... and so on
// in the same way as the previous function.
void analyzeProduction(link *head) {
    int week;
    double solr = 0, wind = 0, hdro = 0,
          nclr = 0, chp = 0, thml = 0;
    FILE *fp = fopen("production.csv", "w");
    if(!fp) {
        return;
    }
    fprintf(fp, "Week;Solar power;Wind power;Hydropower;"
                "Nuclear power;CHP;Thermal power\n");
    link *ptr = head->next;
    week = ptr->data[0];
    while(ptr) {
        if (ptr->data[0] == week) {
            solr += ptr->data[2];
            wind += ptr->data[3];
            hdro += ptr->data[4];
            nclr += ptr->data[5];
            chp += ptr->data[6];
            thml += ptr->data[7];
        } else {
            solr = solr / 1000000;
            wind = wind / 1000000;
            hdro = hdro / 1000000;
            nclr = nclr / 1000000;
            chp = chp / 1000000;
            thml = thml / 1000000;
            fprintf(fp, "Week %d;%.2lf;%.2lf;%.2lf;%.2lf;%.2lf;%.2lf\n",
                    week, solr, wind, hdro, nclr, chp, thml);
            solr = wind = hdro = nclr = chp = thml = 0;
            week = ptr->data[0];
            solr += ptr->data[2];
            wind += ptr->data[3];
            hdro += ptr->data[4];
            nclr += ptr->data[5];
            chp += ptr->data[6];
            thml += ptr->data[7];
        }
        ptr = ptr->next;
    }
    solr = solr / 1000000;
    wind = wind / 1000000;
    hdro = hdro / 1000000;
    nclr = nclr / 1000000;
    chp = chp / 1000000;
    thml = thml / 1000000;
    fprintf(fp, "Week %d;%.2lf;%.2lf;%.2lf;%.2lf;%.2lf;%.2lf\n",
            week, solr, wind, hdro, nclr, chp, thml);
    fclose(fp);
    free(ptr);
}

// this function accept the head pointer,
// and free nodes one by one, until the last node is freed
void freeNodes(link* head) {
    link* node = head;
    while(node) {
        node = head;
        head = head->next;
        node->next = NULL;
        free(node);
    }
}
