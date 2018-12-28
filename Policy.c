//
// Created by ahmed-essam100 on 27/12/18.
//
#include "Policy.h"
#include <stdlib.h>
#include <stdio.h>

/*Policies pointers*/
int FIFO_ptr=0, LRU_time=0, Clock_ptr=0;

int FIFO(int *Memory, int reference, int pages)
{
    int i, found=0, empty=0;

    /*Looping over the pages to found EMPTY slot or page equal to the reference input page*/
    for(i=0;i<pages;i++) {
        if (Memory[i] == reference)
        {
            found = 1;
            break;
        }
        else if (Memory[i] == EMPTY)
        {
            found = 0;
            empty = 1;
            break;
        }
    }

    /*If referenced page not found*/
    if(!found)
    {
        /*Replace the next page with the referenced*/
        Memory[FIFO_ptr] = reference;
        FIFO_ptr++;

        /*If Policy pointer reached to the end of memory*/
        if(FIFO_ptr == pages)
            FIFO_ptr = 0;

        /*If the page was empty -> No page Fault*/
        if(empty)
            return 0;
        /*If the page was empty -> Page Fault*/
        else
            return 1;
    }
    /*If referenced page found*/
    else
    {
        /*No page fault*/
        return 0;
    }
}

int LRU(int *Memory, int reference, int pages, int *uses_count)
{
    int i, found=0, empty=0, idx=0;

    /*Looping over the pages to found EMPTY slot or page equal to the reference input page*/
    for(i=0;i<pages;i++) {
        if (Memory[i] == reference)
        {
            found = 1;
            idx = i;
            break;
        }
        else if (Memory[i] == EMPTY)
        {
            found = 0;
            empty = 1;
            idx = i;
            break;
        }
    }

    /*If referenced page not found and there is empty slot*/
    if(!found && empty)
    {
        /*Update the page usage time*/
        uses_count[idx] = LRU_time;
        LRU_time++;

        /*Put The referenced page to the empty slot*/
        Memory[idx] = reference;

        /*No page fault*/
        return 0;
    }
    /*If referenced page not found and there is no empty slot*/
    else if(!found && !empty)
    {
        /*Get the index of the page to be replaced*/
        idx = GetLRU(pages, uses_count);

        /*Put the page referenced time with the current time*/
        uses_count[idx] = LRU_time;
        LRU_time++;

        /*Put the referenced page the returned slot index*/
        Memory[idx] = reference;

        /*Return page fault*/
        return 1;
    }
    /*If the page referenced already exists*/
    else
    {
        /*Update usage time of the page referenced*/
        uses_count[idx] = LRU_time;
        LRU_time++;

        /*No page fault*/
        return 0;
    }
}

int GetLRU(int pages, int uses_count[])
{
    int i, min=uses_count[0], idx=0;
    /*Find the Least recently used page*/
    for(i=1;i<pages;i++)
    {
        if(uses_count[i] < min)
        {
            min = uses_count[i];
            idx = i;
        }
    }
    /*Returning LRU page index*/
    return idx;
}

int Clock(int *Memory, int reference, int pages, int *uses_count)
{
    int i, found=0, empty=0, idx=0;

    /*Looping over the pages to found EMPTY slot or page equal to the reference input page*/
    for(i=0;i<pages;i++) {
        if (Memory[i] == reference)
        {
            found = 1;
            idx = i;
            break;
        }
        else if (Memory[i] == EMPTY)
        {
            found = 0;
            idx = i;
            empty = 1;
            break;
        }
    }

    /*If referenced page not found and there is empty slot*/
    if(!found && empty)
    {
        /*Set use bit of that page*/
        uses_count[idx] = 1;

        /*Put the page referenced to that empty slot*/
        Memory[idx] = reference;

        /*Advance the policy pointer*/
        Clock_ptr++;
        if(Clock_ptr == pages)
            Clock_ptr = 0;
        /*No page fault occurs*/
        return 0;
    }
    /*If referenced page found*/
    else if(found && !empty)
    {
        /*Set use bit of that page*/
        if(!uses_count[idx])
            uses_count[idx] = 1;

        /*No page fault occurs*/
        return 0;
    }
    /*If referenced page not found and there is no empty slot*/
    else
    {
        /*Apply the Clock Replacement*/
        Get_Clock_Replacement(Memory, pages, uses_count, reference);

        /*Page fault occurs*/
        return 1;
    }
}

void Get_Clock_Replacement(int *Memory, int pages, int *uses_count, int reference)
{
    int i, all_use=1, idx;
    /*Use bit is set and Memory slot the pointer points to is not equal the referenced page*/
    if(uses_count[Clock_ptr] == 1 && Memory[Clock_ptr] != reference)
    {
        /*Finds the page with use bit = 0*/
        for (i=Clock_ptr;i<pages;i++) {
            if(uses_count[i]==0)
            {
                idx = i;
                all_use = 0;
                break;
            }
            /*Clear the use bit*/
            uses_count[i] = 0;
        }
    }
    /*All pages use bit are set*/
    if(all_use)
    {
        /*Replace with the slot the pointer points to*/
        uses_count[Clock_ptr] = 1;
        Memory[Clock_ptr] = reference;
        Clock_ptr++;
    }
    /*There is page with use bit equals zero*/
    else
    {
        /*Replace that slot with the page referenced*/
        uses_count[idx] = 1;
        Memory[idx] = reference;
        Clock_ptr = idx+1;
    }
    if(Clock_ptr >= pages)
    {
        Clock_ptr = 0;
    }
}

void NewInputPrint(int fault, int Memory[], int reference, int pages)
{
    int i;
    if(fault)
    {
        printf("%02d F   ",reference);
        for (i=0;i<pages;i++) {
            if (Memory[i] == EMPTY)
            {
                break;
            }
            else
            {
                printf("%02d ",Memory[i]);
            }
        }
        printf("\n");
    }
    else
    {
        printf("%02d     ",reference);
        for (i=0;i<pages;i++) {
            if (Memory[i] == EMPTY)
            {
                break;
            }
            else
            {
                printf("%02d ",Memory[i]);
            }
        }
        printf("\n");
    }
}
