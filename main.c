#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Policy.h"



int main() {
    int pages = 0;
    char policy[5];

    /*Read the number of pages*/
    scanf("%d",&pages);

    /*Read Replacement Policy*/
    scanf("%s",policy);

    int Memory[pages], uses_count[pages];
    int references = 0,i,page_fault = 0, fault = 0;
    /*Initializing Memory to be EMPTY and control bits count*/
    for(i=0;i<pages;i++) {
        Memory[i] = EMPTY;
        uses_count[i] = 0;
    }

    /*Reading the first input*/

    scanf("%d",&references);
    printf("Replacement Policy = %s\n",policy);
    printf("-------------------------------------\n");
    printf("Page   Content of Frames\n");
    printf("----   -----------------\n");

    /*Looping till taking input*/
    while(references != -1)
    {
        /*Applying FIFO Replacement Policy to the input if required FIFO*/
        if(strcmp(policy, "FIFO") == 0)
        {
            fault = FIFO(Memory, references, pages);

            /*Incrementing page fault counter if happens*/
            page_fault += fault;

            /*Printing Snapshot of the input and memory*/
            NewInputPrint(fault, Memory,references, pages);
        }
        /*Applying LRU Replacement Policy to the input if required LRU*/
        else if (strcmp(policy, "LRU") == 0)
        {
            fault = LRU(Memory, references, pages, uses_count);

            /*Incrementing page fault counter if happens*/
            page_fault += fault;

            /*Printing Snapshot of the input and memory*/
            NewInputPrint(fault, Memory, references, pages);
        }
        /*Applying CLOCK Replacement Policy to the input if required CLOCK*/
        else if (strcmp(policy, "CLOCK") == 0)
        {
            fault = Clock(Memory, references, pages, uses_count);

            /*Incrementing page fault counter if happens*/
            page_fault += fault;

            /*Printing Snapshot of the input and memory*/
            NewInputPrint(fault, Memory, references, pages);
        }

        /*Reading New input*/
        scanf("%d",&references);
    }
    printf("-------------------------------------\n");
    printf("Number of page faults = %d\n",page_fault);
    return 0;
}

