/**
File: ScheduledItem.cpp
*/

#include "ScheduledItem.h"



	ScheduledItem::ScheduledItem() : mExecutionsSoFar(0)
	{

	}

	bool ScheduledItem::LessThanFunctor::operator()( Ptr const & e1, Ptr const & e2 )
	{
		if(e1->mNextExecutionTime < e2->mNextExecutionTime)
		{
			return true;
		}
		else if(e1->mNextExecutionTime == e2->mNextExecutionTime)
		{
			if(e1->mPriority < e2->mPriority)
			{
				return true;
			}
			else if(e1->mPriority == e2->mPriority)
			{
				assert(e1->mID != e2->mID);

				if(e1->mID < e2->mID)
					return true;
				else return false;
			}
			else
			{
				return false;
			}

		}
		else 
		{
			return false;
		}
	}
