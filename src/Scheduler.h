/*
Copyright (C) 2007-2010 Luis Rodríguez Gil <zstars@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License version 3 as
published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>
*/

#pragma once


#include <set>
#include <stdexcept>
#include "ITask.h"
#include "ScheduledItem.h"


    //! Lets the user program Tasks easily, which will be executed after a
    //! certain amount of time has elapsed, and optionally repeat themselves
    //! periodically. Time units used by the class are relative. The class
    //! is optimized for task execution and insertion.
    class Scheduler
    {
        unsigned long lastID;

        unsigned long mCurrentTime;
        std::set< ScheduledItem::Ptr, ScheduledItem::LessThanFunctor> mSet;

        //! Generates a new Task ID. IDs should be unique within the same
        //! Scheduler. One of their purposes is to be able to tell apart
        //! ScheduledItems with the same execution time and the same priority,
        //! allowing strict ordering.
        unsigned long GenerateNewID();

        //! Runs pending tasks.
        //!
        void RunDueTasks();

    public:

        typedef int TaskID;


        class Exception : public std::runtime_error
        {
        public:
            Exception(std::string const & msg) : std::runtime_error(msg) { }
        };


        //! Starts the scheduler, optionally, with a given time.
        //!
        //! @param curtime Current time. Can be any time unit, as long
        //! as there is consistency.
        Scheduler(unsigned long curtime = 0);

        //! Assigns a value to the internal time.
        //!
        void SetInternalTime(unsigned long curtime);


        //! Adds a new task to the scheduler. Tasks must inherit from ITask.
        //! The first execution will take place after the amount of time units
        //! specified by the wait parameter elapses.
        //!
        //! @param task Smart pointer to the task to execute.
        //!
        //! @param wait Time to wait before executing the task for the first time.
        //!
        //! @param times Number of times to execute the task, waiting the first time
        //! "wait" time units, and from then on, "frequency" time units.
        //!
        //! @param frequency Time to wait after each run for the next.
        //! If it takes the value ITask::FREQ_ASWAIT the frequency will be the
        //! same as "wait".
        //!
        //! @param priority Priority may be PRIORITY_LOW, PRIORITY_NORMAL,
        //! PRIORITY_HIGH, or any number, being negative priorities the lowest.
        //!
        //! @return TaskID which identifies the Task.
        //!
        //! @remark A task is never run more than once per cycle (Update).
        //! Should the delta exceed the frequency, the task would be run
        //! on the next cycle, or the next ones, until the appropiate number
        //! of times is reached.
        TaskID AddTask(ITask::Ptr const & task, unsigned long wait, long times = 1,
            long frequency = ITask::FREQ_ASWAIT, int priority = ITask::PRIORITY_NORMAL );


        //! Removes a Task from the Scheduler, using its TaskID.
        //!
        //! @param taskID TaskID which was returned when adding the task to the
        //! Scheduler.
        void RemoveTask(TaskID taskID);


        //! Initializes the time as specified.
        //!
        //! @param time Time, in any unit.
        void Initialize(unsigned long const & time);

        //! Updates the scheduler, running every pending tasks and updating
        //! the internal timer according to the delta.
        //!
        //! @param delta Un incremento de tiempo, generalmente el incremento de
        //! tiempo pasado desde la �ltima llamada a este mismo Update.
        //!
        //! @remark Una tarea no se ejecuta nunca m�s de una vez por ciclo (Update).
        //! En caso de que el delta exceda la frecuencia, la Tarea se ejecutar�
        //! al siguiente ciclo, o a los siguientes, hasta llegar al n�mero de veces
        //! apropiado.
        void Update(unsigned long const & delta);


        //! Runs pending tasks without updating the internal timer.
        //!
        void RunPendingTasksOnly();


        //! Updates the internal timer, without running any pending task.
        //!
        void UpdateOnly(unsigned long const & delta);

    };
