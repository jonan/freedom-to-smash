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


#include <list>
#include "ITask.h"

#include <boost/shared_ptr.hpp>


    //! Intermediary class which represents a scheduled task.
    //!
    struct ScheduledItem
    {
        typedef boost::shared_ptr<ScheduledItem> Ptr;


        ScheduledItem();


        ITask::Ptr mTaskPtr;
        unsigned long mNextExecutionTime;
        unsigned long mID;
        long mRemainingExecutions;
        unsigned long mExecutionsSoFar;
        long mFrequency;
        int mPriority;


        struct LessThanFunctor
        {
            bool operator()(Ptr const & e1, Ptr const & e2);
        };

    };
