/************************************************************************
 * LES10A110 Principles of C-programming
 * Name: Shangqi Zhao
 * Student number: 000206163
 * Email: Shangqi.Zhao@student.lut.fi
 * Date: 1.5.2022
 * By submitting this work for evaluation, I certify that
 * 1) I myself wrote all the code in this file
 * 2) I have not given this code to anyone else
 *************************************************************************/
typedef struct link {
    char time[20];
    int data[8];
    struct link* next;
}link;

void printMenu();
void readFile(char fileName[], link* list);
void analyzeConsumption(link* head);
void analyzeProduction(link* head);
void freeNodes(link* head);