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

#include <boost/shared_ptr.hpp>

	//! Represents a task. That is, an action to run at a specified time.
	//! That action is meant to be specified by overriding the Execute function.
	class ITask
	{

	public:

		//! Constructs a task.
		//!
		ITask()
		{
		}

		enum { PRIORITY_LOW = -1, PRIORITY_NORMAL, PRIORITY_HIGH };
		enum { EXEC_FOREVER = -1, EXEC_NONE, EXEC_ONCE };
		enum { FREQ_ASWAIT = -1 };

		typedef boost::shared_ptr<ITask> Ptr;

		//! Member function called automatically by the Scheduler when
		//! the time is right. If it returns false, the task will be
		//! automatically removed from the scheduler, whether it was
		//! originally meant to repeat itself or not.
		//!
		virtual bool Execute() = 0;

	};

