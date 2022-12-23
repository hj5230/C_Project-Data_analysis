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

int main() {
    int i, b = 1;
    char fileName[20];
    link *head = malloc(sizeof(link));
    head->next = NULL;
    link *list = head;
    while (b) {
        printMenu();
        scanf("%d", &i);
        switch (i) {
        case 1:
            printf("Please enter the file name\n");
            scanf("%s", fileName);
            readFile(fileName, list);
            break;
        case 2:
            analyzeConsumption(head);
            break;
        case 3:
            analyzeProduction(head);
            break;
        default:
            b = 0;
            break;
        }
    }
    freeNodes(head);
    return 0;
}
