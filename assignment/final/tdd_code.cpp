//======== Copyright (c) 2021, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Test Driven Development - priority queue code
//
// $NoKeywords: $ivs_project_1 $tdd_code.cpp
// $Author:     ROMAN POLIACIK <xpolia05@stud.fit.vutbr.cz>
// $Date:       $2022-02-22
//============================================================================//
/**
 * @file tdd_code.cpp
 * @author ROMAN POLIACIK
 * 
 * @brief Implementace metod tridy prioritni fronty.
 */

#include <stdlib.h>
#include <stdio.h>

#include "tdd_code.h"

//============================================================================//
// ** ZDE DOPLNTE IMPLEMENTACI **
//
// Zde doplnte implementaci verejneho rozhrani prioritni fronty (Priority Queue)
// 1. Verejne rozhrani fronty specifikovane v: tdd_code.h (sekce "public:")
//    - Konstruktor (PriorityQueue()), Destruktor (~PriorityQueue())
//    - Metody Insert/Remove/Find/GetHead ...
//    - Pripadne vase metody definovane v tdd_code.h (sekce "protected:")
//
// Cilem je dosahnout plne funkcni implementace prioritni fronty implementovane
// pomoci tzv. "singly linked list", ktera bude splnovat dodane testy
// (tdd_tests.cpp).
//============================================================================//

PriorityQueue::PriorityQueue(){
    m_pHead = NULL;
}

PriorityQueue::~PriorityQueue(){
    Element_t *next_head;
    while(m_pHead != NULL){
        next_head = m_pHead->pNext;
        delete m_pHead;
        m_pHead = next_head;
    }
}

void PriorityQueue::Insert(int value){
    Element_t *item = new Element_t;
    item->pNext = NULL;
    item->value = value;

    if (GetHead() == NULL){
        m_pHead = item;
        return;
    }
    if (m_pHead->value <= value){
        //item<->mphead switch (use temp -> xor switch na pointre nefunguje)
        Element_t *temp_head;
        temp_head = m_pHead;
        m_pHead = item;
        item->pNext = temp_head;
        return;
    }
    Element_t *temp_item = GetHead();
    while(temp_item->pNext != NULL && temp_item->pNext->value > value){
        temp_item = temp_item->pNext;
    }
    if(temp_item->pNext == NULL){
        temp_item->pNext = item;
        return;
    }
    Element_t *next = temp_item->pNext;
    temp_item->pNext = item;
    item->pNext = next;
}

bool PriorityQueue::Remove(int value)
{
    Element_t *temp = GetHead();
    if (GetHead() == NULL){
        return false;
    }
    if (m_pHead->value == value){
        Element_t *next_head = m_pHead->pNext;
        delete m_pHead;
        m_pHead = next_head;
        return true;
    }

    if(m_pHead->pNext == NULL){
        return false;
    }
    
    for(temp; temp->pNext->pNext != NULL && temp->pNext->value != value;){
        temp = temp->pNext;
    }
    
    if(temp->pNext->pNext != NULL){
        Element_t *next_item = temp->pNext->pNext;
        delete temp->pNext;
        temp->pNext = next_item;
        return true;
    }
    
    if(temp->pNext->pNext == NULL){
        if(temp->pNext->value == value){
            delete temp->pNext;
            temp->pNext = NULL;
            return true;
        }
    }
    return false;

}

PriorityQueue::Element_t *PriorityQueue::Find(int value)
{ 
    Element_t *item = GetHead();
    while(item != NULL){
        if (item->value == value)
            return item;
        item = item->pNext;
    }
    return item;
}


size_t PriorityQueue::Length()
{
	size_t len = 0;
    for (Element_t *temp_head = GetHead(); temp_head != NULL;){
        len++;
        temp_head = temp_head->pNext;
    }
    return len;
}

PriorityQueue::Element_t *PriorityQueue::GetHead()
{
    return m_pHead;
}

/*** Konec souboru tdd_code.cpp ***/
