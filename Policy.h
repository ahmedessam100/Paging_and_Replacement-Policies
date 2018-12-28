//
// Created by ahmed-essam100 on 27/12/18.
//

#ifndef PAGING_AND_REPLACEMENT_POLICY_H
#define PAGING_AND_REPLACEMENT_POLICY_H
#define EMPTY -2


/*First In First out replacement policy*/
int FIFO(int *Memory, int reference, int pages);

/*Least Recently Used replacement policy*/
int LRU(int *Memory, int reference, int pages, int *uses_count);

/*Clock replacement policy*/
int Clock(int *Memory, int reference, int pages, int *uses_count);

/*Printing State after new input*/
void NewInputPrint(int fault, int Memory[], int reference, int pages);

/*Get the index of the page to be replaced*/
int GetLRU(int pages, int uses_count[]);

/*Get the index of the page to be replaced and replace it*/
void Get_Clock_Replacement(int *Memory, int pages, int *uses_count, int reference);

#endif //PAGING_AND_REPLACEMENT_POLICY_H
