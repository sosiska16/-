#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <limits.h>

struct listek {
    int znach;
    struct listek* next;
};

struct listek* start = NULL, * end = NULL;
int length = 0;


typedef struct listek sht;



void addtop(int num) {
    sht* pr = (sht*)malloc(sizeof(sht));
    pr->znach = num;
    pr->next = NULL;
    if (!start) start = pr;
    else end->next = pr;
    end = pr;
    length++;
}


void addbot(int num) {
    sht* pr = (sht*)malloc(sizeof(sht));
    pr->znach = num;
    pr->next = start;
    start = pr;
    length++;
}


void deltop() {
    if (length == 1) {
        free(start);
        start = NULL;
        end = NULL;
        return;
    }
    int i;
    struct listek* pr = start;
    for (i = 0; i < length - 2; i++) pr = pr->next;
    free(pr->next);
    pr->next = NULL;
    end = pr;
}


void delbot() {
    if (length == 1) {
        free(start);
        start = NULL;
        end = NULL;
        return;
    }
    sht* pr = start;
    start = pr->next, free(pr);
}



void addaft(int numb, int num) {
    if (numb == length - 1) {
        addtop(num);
        return;
    }
    int i;
    sht* pr2 = start;
    sht* pr3;
    sht* pr = (sht*)malloc(sizeof(sht));
    pr->znach = num;
    if (numb != 0) {
        for (i = 0; i < numb; i++) pr2 = pr2->next;
    }
    pr3 = pr2->next;
    pr2->next = pr;
    pr->next = pr3;
    length++;
}



void delaft(int numb) {
    if (numb == 0) {
        if (length == 1) {
            free(start);
            start = NULL;
            end = NULL;
            return;
        }
        delbot();
        return;
    }
    if (numb == length - 1) {
        deltop();
        return;
    }
    int i;
    sht* pr = start;
    sht* dl;
    for (i = 0; i < numb - 1; i++) {
        pr = pr->next;
    }
    dl = pr->next;
    pr->next = dl->next;
    free(dl);
}




void show() {
    sht* pr = start;
    printf("SpiSok\n::::::::::::::::::::\n");
    if (!pr) {
        printf("Sector Clear\n");
        return;
    }
    while (pr) {
        printf("%2d ", pr->znach);
        pr = pr->next;
    }
    printf("\nlength %d\n\n", length);
}

int v9() {
    int i, minimum = INT_MAX;
    struct listek* pr = start;
    if (start->znach < start->next->znach) minimum = start->znach;
    for (i = 0; i < length - 2; i++) {
        if ((pr->znach > pr->next->znach) && (pr->next->znach < pr->next->next->znach) && (pr->next->znach < minimum)) {
            minimum = pr->next->znach;
        }
        pr = pr->next;
    }
    if ((pr->znach > pr->next->znach) && (pr->next->znach < minimum)) minimum = pr->next->znach;
    return minimum;
}

void f5() {
    FILE* save;
    int err = fopen_s(&save, "savings.txt", "wt");
    if (err != 0) {
        puts("\n!3RR0R!\n");
        return;
    }
    sht* pr = start;
    fprintf(save, "%d ", length);
    while (pr) {
        fprintf(save, "%d ", pr->znach);
        pr = pr->next;
    }
    fclose(save);
}

void f9() {
    int n, i;
    FILE* save;
    int err = fopen_s(&save, "savings.txt", "rt");
    if (err != 0) {
        puts("\n!3RR0R!\n");
        return;
    }
    while (length) {
        deltop();
        length--;
    }
    fscanf_s(save, "%d", &length);
    for (i = 0; i < length; i++) {
        fscanf_s(save, "%d", &n);
        addtop(n);
        length--;
    }

    fclose(save);
}



int main() {
    printf("\nHi 0w0\n\n");
    int num, numb, action;
    show();
    printf("\n=.=Fill this LineList=.=\n");
    do {
        printf("Enter num (do 0 to end it)\n");
        scanf_s("%d", &num);
        if (!num) break;
        printf("=> %d\n", num);
        addtop(num);
    } while (1);
    show();

    do {
        printf("\nI can:\n");
        puts("\n1. Add to origin");
        puts("\n2. Add to TOP");
        puts("\n3. Add after given");
        puts("\n4. Delete from origin");
        puts("\n5. Delete from TOP");
        puts("\n6. Delete given");
        puts("\n7. If u want v10");
        puts("\n8. FastSave");
        puts("\n9. FastLoad");
        puts("\n0. Exit");
        printf("\nWhat do u want ?_?\n");
        scanf_s("%d", &action);
        if (action == 0) {
            puts("\nBye T_T\n");
            break;
        }
        switch (action) {
        case 1:
            printf("Enter num\n");
            scanf_s("%d", &num);
            addbot(num);
            show();
            break;
        case 2:
            printf("Enter num\n");
            scanf_s("%d", &num);
            addtop(num);
            show();
            break;
        case 3:
            printf("\nEnter num and index\n");
            scanf_s("%d %d", &num, &numb);
            addaft(numb, num);
            show();
            break;
        case 4:
            printf("\n");
            if (length == 0) {
                printf("Nothing 2 delete\n");
                break;
            }
            delbot();
            length--;
            show();
            break;
        case 5:
            printf("\n");
            if (length == 0) {
                printf("Nothing 2 delete\n");
                break;
            }
            deltop();
            length--;
            show();
            break;
        case 6:
            printf("\nEnter id\n");
            scanf_s("%d", &numb);
            if (numb > length - 1) {
                printf("\nNo Element\n");
                break;
            }
            delaft(numb);
            length--;
            show();
            break;
        case 7:
            show();
            printf("minimal minimum s %d\n", v9());
            break;
        case 8:
            f5();
            puts("\nSave\n");
            show();
            break;
        case 9:
            f9();
            puts("\nLoaded\n");
            show();
            break;
        default:
            printf("\nSorry, I can't do it :(\n\n");
            break;
        }
    } while (1);

    return 0;
}
