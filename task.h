#ifndef TASK_H
#define TASK_H

/************************************************************************
 * Task module configuration settings: alter to match needs
 ************************************************************************/
#define TASK_MAX_TASKS 10

/************************************************************************
 * Task module 'public' data types
 ************************************************************************/
typedef long long time;

/************************************************************************
 * Initializes a task structure with the given parameters. Returns true
 * if the task was successfully created, false otherwise.
 ************************************************************************/
bool task_create(void (*task)(), time interval, bool repeat);

/************************************************************************
 * Checks each of the created tasks and executes any of them with an
 * expired interval.
 ************************************************************************/
void task_update_all();

#endif
