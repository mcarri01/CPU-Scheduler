/* 
*
*	simulator.h
*
*	Header file for simulator module.
*
*	Defines create_scheduler method to initialize
*	waiting queue for whichever chosen scheduling algorithm
*	(between FCFS and CFS)
*
*   by 
*     	Justin Tze Tsun Lee
*     	Matthew Carrington-Fair
*     	Tomer Shapira
*
*
*
*/

#ifndef _SIMULATOR_H
#define _SIMULATOR_H

#include "CFS.h"
#include "FCFS.h"

void create_scheduler(FILE* file, char* algo);


#endif