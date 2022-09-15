#include "ListenerRegistrar.hxx"

#include <iostream>
#include <mutex>
#include <stdexcept>

namespace galaxy
{
	namespace api
	{
		ListenerRegistrarImpl* ListenerRegistrarImpl::get_local()
		{
			return dynamic_cast<ListenerRegistrarImpl*>(ListenerRegistrar());
		}

		ListenerRegistrarImpl* ListenerRegistrarImpl::get_game_server()
		{
			return dynamic_cast<ListenerRegistrarImpl*>(GameServerListenerRegistrar());
		}

		ListenerRegistrarImpl::ListenerRegistrarImpl() :
			listeners{}
		{ }

		ListenerRegistrarImpl::~ListenerRegistrarImpl()
		{
			for (int t = LISTENER_TYPE_BEGIN; t < LISTENER_TYPE_END; ++t) {
				if (listeners[t].set.size()) {
					std::cerr << "Listeners have not been unregistered: " << t << '\n';
				}
			}
		}

		void ListenerRegistrarImpl::Register(ListenerType listenerType, IGalaxyListener* listener) {
			std::scoped_lock<mutex_t> lock(listeners[listenerType].mtx);
			listeners[listenerType].set.insert(listener);
		}

		void ListenerRegistrarImpl::Unregister(ListenerType listenerType, IGalaxyListener* listener) {
			std::scoped_lock<mutex_t> lock(listeners[listenerType].mtx);
			listeners[listenerType].set.erase(listener);
		}

		void ListenerRegistrarImpl::ExecuteForListenerType(ListenerType listenerType, std::function<void(const std::set<IGalaxyListener*>& listeners)> code)
		{
			std::scoped_lock<mutex_t> lock(listeners[listenerType].mtx);
			code(listeners[listenerType].set);
		}

		void ListenerRegistrarImpl::ExecuteForListenerTypePerEntry(ListenerType listenerType, std::function<void(IGalaxyListener* listeners)> code)
		{
			std::scoped_lock<mutex_t> lock(listeners[listenerType].mtx);
			for (auto& entry : listeners[listenerType].set) {
				code(entry);
			}
		}
	}
}
