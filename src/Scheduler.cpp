/**
File: Scheduler.cpp
*/

#include "Scheduler.h"
#include <iostream>


	unsigned long Scheduler::GenerateNewID()
	{
		++lastID;
		return lastID;
	}

	void Scheduler::RunDueTasks()
	{
		std::set< ScheduledItem::Ptr, ScheduledItem::LessThanFunctor>::iterator it =
			mSet.begin();

		while( it != mSet.end() && mCurrentTime >= (*it)->mNextExecutionTime )
		{

			ScheduledItem & item = **it;

			// Execute the task, unless remaining executions is 0, or until Execute returns false.
			// This will only happen if the execution time was explicitly set to 0.
			if(item.mRemainingExecutions)
			{
				bool b = item.mTaskPtr->Execute();

				if(!b) 
					item.mRemainingExecutions = 0;
				else if(item.mRemainingExecutions > 0)
					item.mRemainingExecutions--;

				item.mExecutionsSoFar++;

				// REMARK: Using the last execution time instead of the current time
				//			as a base means that executions will happen at more
				//			accurate times. However, if the machine cannot dispatch
				//			all the tasks in time and suffers a delay, this scheme
				//			will not compensate.
				item.mNextExecutionTime += item.mFrequency;

			}

			// Now, we might have to remove the task and insert it again
			// so that the order is the right one.
			// We also have to increase the iterator.
			// If we still have executions remaining: 
			if(item.mRemainingExecutions)
			{
				// Delete old item and insert the updated one.
				ScheduledItem::Ptr pitem = *it;
				std::set< ScheduledItem::Ptr, ScheduledItem::LessThanFunctor>::iterator 
					tempit = it;
				++it;
				mSet.erase(tempit);
				mSet.insert(pitem);
			}
			else // This will be called if initially it was zero, or if it now is zero.
			{

				// Delete the item, no more executions left.
				std::set< ScheduledItem::Ptr, ScheduledItem::LessThanFunctor>::iterator 
					tempit = it;
				++it;
				mSet.erase(tempit);
			}
		} // !while
	}

	Scheduler::TaskID Scheduler::AddTask( ITask::Ptr const & task, unsigned long wait, long times /*= 1*/, long frequency /*= -1*/, int priority /*= ITask::PRIORITY_NORMAL */ )
	{
		// Create the scheduled item.
		ScheduledItem::Ptr item(new ScheduledItem);
		item->mRemainingExecutions = times;
		item->mPriority = priority;
		item->mID = GenerateNewID();
		item->mNextExecutionTime = mCurrentTime + wait;
		item->mFrequency = (frequency < 0 ? wait : frequency);
		item->mTaskPtr = task;

		// Insert it into the set
		mSet.insert(item);

		return item->mID;
	}

	void Scheduler::Initialize(unsigned long const & time )
	{
		mCurrentTime = time;
	}

	Scheduler::Scheduler( unsigned long curtime ) : lastID(0), mCurrentTime(curtime)
	{
		Initialize(curtime);
	}

	void Scheduler::SetInternalTime( unsigned long curtime )
	{
		mCurrentTime = curtime;
	}

	void Scheduler::Update(unsigned long const & delta )
	{
		mCurrentTime += delta;
		RunDueTasks();
	}

	void Scheduler::RunPendingTasksOnly()
	{
		RunDueTasks();
	}

	void Scheduler::UpdateOnly(unsigned long const & delta )
	{
		mCurrentTime += delta;
	}

	void Scheduler::RemoveTask( TaskID taskID )
	{
		std::set< ScheduledItem::Ptr, ScheduledItem::LessThanFunctor>::iterator it =
			mSet.begin();
		for( ; it != mSet.end() ; ++it)
		{
			if((*it)->mID == taskID)
			{
				mSet.erase(it);
				return;
			}
		}
	}

