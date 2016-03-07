#include "config.h"
#include "sysclock.h"
#include "task.h"

/************************************************************************
 * Task module internal data types
 ************************************************************************/
typedef struct tagTask
{
	time star_time;      //start time of interval
	bool active;				 //if the task is active
	bool repeat;	       //if the task should repeat
	time interval;       //interval between repeats (in milliseconds)
	void (*task)();			 //function to run for this task
} Task;

/************************************************************************
 * Variables in the static scope of task module (i.e. this .c file)
 ************************************************************************/
Task task_list[TASK_MAX_TASKS];
unsigned char num_tasks = 0;

/************************************************************************
 * Initializes a task structure with the given parameters. Returns true
 * if the task was successfully created, false otherwise.
 ************************************************************************/
bool task_create(void (*task)(), time interval, bool repeat)
{
	Task* new_task = task_list + num_tasks;

	//Check if the task list is full...
	if(num_tasks >= TASK_MAX_TASKS) return false;

	//Create the new task
	new_task->star_time = sysclock_ticks();
	new_task->interval  = interval;
	new_task->repeat    = repeat;
	new_task->task      = task;
	new_task->active    = true;

	num_tasks++;
	return true;
}

/************************************************************************
 * Checks each of the created tasks and executes any of them with an
 * expired interval.
 ************************************************************************/
void task_update_all()
{
	int i;
	time delta;
	Task* current_task;

	//For every task in the task list...
	for(i=0, current_task=task_list; i<num_tasks; i++, current_task++)
	{
		delta = SYSCLOCK_TICKS_TO_MS(sysclock_ticks() - current_task->star_time);

		//If the current task is active and enough time has passed since its start time...
		if( current_task->active &&  delta >= current_task->interval )
		{
			//Run the task function
			current_task->task();

			//Reset the task for repeat or deactivate it if it doesn't repeat
			if(current_task->repeat) current_task->star_time = sysclock_ticks();
			else current_task->active = false;
		}
	}
}
