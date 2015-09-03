#pragma once

#include <queue>

namespace MOO
{
	namespace EventSystem
	{
		template<class EventEnum>
		class EventSystem
		{

		private: 

			std::queue<EventEnum> eventQueue;

		public:

			bool PollEvents( EventEnum& getEvent );

			void AddEvent( EventEnum& addEvent );
		};
	}
}

template<class EventEnum>
inline bool MOO::EventSystem::EventSystem<EventEnum>::PollEvents( EventEnum& getEvent )
{
	if( eventQueue.empty() == true )
	{
		return false;
	}

	else
	{
		getEvent = eventQueue.front();
		eventQueue.pop();

		return true;
	}
}

template<class EventEnum>
inline void MOO::EventSystem::EventSystem<EventEnum>::AddEvent( EventEnum& addEvent )
{
	eventQueue.push( addEvent );
}
