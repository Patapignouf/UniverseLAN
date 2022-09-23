#include "Peer.hxx"

#include <GalaxyApi.h>

#include <cstdint>
#include <chrono>

namespace universelan::server::peer {
	using namespace galaxy::api;

	Mapper::Mapper() : map{}, connected_peers{} {}

	ptr Mapper::Get(ENetPeer* peer) {
		assert(peer != nullptr);
		assert(peer->data != nullptr);

		return static_cast<ptr>(peer->data);
	}

	ptr Mapper::Get(const galaxy::api::GalaxyID& id) {
		auto it = map.find(id);
		if (it == map.end()) {
			return nullptr;
		}

		return Get(it->second);
	}

	ptr Mapper::Connect(ENetPeer* peer) {
		assert(peer != nullptr);
		ptr x = (ptr)peer->data;
		assert(peer->data == nullptr);

		connected_peers.insert(peer);
		return new Data(peer, this);
	}

	void Mapper::Disconnect(ENetPeer* peer) {
		assert(peer != nullptr);

		delete static_cast<ptr>(peer->data);
		connected_peers.erase(peer);
	}

	Data::Data(ENetPeer* peer, Mapper* mapper) :
		mapper{ mapper}, peer{ peer }, id{ 0ULL }, challenge{},
		connected_time{ std::chrono::system_clock::now() },
		chat_rooms{}, lobby{nullptr}
	{
		assert(peer != nullptr);
		assert(peer->data == nullptr);
		peer->data = static_cast<void*>(this);
	}

	Data::~Data() {
		mapper->map.erase(id);
		peer->data = nullptr;
	}

	bool Data::link(const GalaxyID& id) {
		if (peer->data == nullptr) {
			return false;
		}

		if (!id.IsValid()) {
			return false;
		}

		if (!mapper->map.emplace(id, peer).second) {
			return false;
		}

		mapper->Get(peer)->id = id;

		return true;
	}
}
