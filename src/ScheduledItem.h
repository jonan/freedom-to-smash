/**
File: ScheduledItem.h
*/


#pragma once


#include <list>
#include "ITask.h"

#include <boost/shared_ptr.hpp>


	//! Clase intermedia que representa a una Tarea programada.
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
