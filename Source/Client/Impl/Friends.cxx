#include "Friends.hxx"

#include "UniverseLAN.hxx"

#include <ContainerGetByIndex.hxx>
#include <SafeStringCopy.hxx>

#include <algorithm>

namespace universelan::client {
	using namespace galaxy::api;
	FriendsImpl::FriendsImpl(InterfaceInstances* intf) :
		intf{ intf }, listeners{ intf->notification.get() },
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
		user_information_requests{},
		retrieve_rich_presence_requests{},
#endif
		rich_presence_change_requests{},
		avatar_criteria{ 0 }
	{
		tracer::Trace trace{  };
	}

	FriendsImpl::~FriendsImpl()
	{
		tracer::Trace trace{  };
	}

#if GALAXY_BUILD_FEATURE_HAS_CONNECTION_TYPE
	AvatarCriteriaImpl FriendsImpl::GetDefaultAvatarCriteria() {
		tracer::Trace trace{  };

		return avatar_criteria;
	}

	void FriendsImpl::SetDefaultAvatarCriteria(AvatarCriteriaImpl defaultAvatarCriteria) {
		tracer::Trace trace{  };

		avatar_criteria = defaultAvatarCriteria;
	}
#endif

	void FriendsImpl::RequestUserInformation(
		GalaxyID userID
		, AvatarCriteriaImpl avatarCriteria
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
		, IUserInformationRetrieveListener* const listener
#endif
	) {
		tracer::Trace trace{  };

		if (intf->config->IsSelfUserID(userID)) {
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			listeners->NotifyAll(listener, &IUserInformationRetrieveListener::OnUserInformationRetrieveSuccess, userID);
#endif
#if GALAXY_BUILD_FEATURE_IFRIENDS_ONPERSONADATACHANGED
			listeners->NotifyAll(&IPersonaDataChangedListener::OnPersonaDataChanged, userID, IPersonaDataChangedListener::PERSONA_CHANGE_NONE);
#endif
		}
		else {
			uint64_t request_id = MessageUniqueID::get();

#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			user_information_requests.emplace(request_id, listener);
#endif

			intf->client->GetConnection().SendAsync(RequestSpecificUserDataMessage{ RequestSpecificUserDataMessage::RequestTypeFriends, request_id, userID });
		}
	}

	void FriendsImpl::RequestUserInformationProcessed(const std::shared_ptr<RequestSpecificUserDataMessage>& data) {
		tracer::Trace trace{  };

#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
		IUserInformationRetrieveListener* listener = user_information_requests.pop(data->request_id);
#endif

		if (data->found) {
			auto entry = intf->user->GetGalaxyUserData(data->id);
			entry->stats = data->asuc;
			entry->nickname = data->nickname;
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			listeners->NotifyAll(listener, &IUserInformationRetrieveListener::OnUserInformationRetrieveSuccess, data->id);
#endif
		}
		else {
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			listeners->NotifyAll(listener, &IUserInformationRetrieveListener::OnUserInformationRetrieveFailure, data->id, IUserInformationRetrieveListener::FAILURE_REASON_UNDEFINED);
#endif
		}
#if GALAXY_BUILD_FEATURE_IFRIENDS_ONPERSONADATACHANGED
		listeners->NotifyAll(&IPersonaDataChangedListener::OnPersonaDataChanged, data->id, IPersonaDataChangedListener::PERSONA_CHANGE_NONE);
#endif
	}

#if GALAXY_BUILD_FEATURE_HAS_USERDATAINFOAVAILABLE
	bool FriendsImpl::IsUserInformationAvailable(GalaxyID userID) {
		tracer::Trace trace{  };

		return intf->user->IsUserDataAvailable(userID);
	}
#endif

	const char* FriendsImpl::GetPersonaName() {
		tracer::Trace trace{  };

		return intf_inst.config->GetCustomPersonaName().c_str();
	}

	void FriendsImpl::GetPersonaNameCopy(char* buffer, uint32_t bufferLength) {
		tracer::Trace trace{  };

		auto name = intf_inst.config->GetCustomPersonaName();

		universelan::util::safe_copy_str_n(name, buffer, bufferLength);
	}

	PersonaState FriendsImpl::GetPersonaState() {
		tracer::Trace trace{  };

		return intf->client->IsConnected() ?
			PERSONA_STATE_ONLINE :
			PERSONA_STATE_OFFLINE;
	}

	const char* FriendsImpl::GetFriendPersonaName(GalaxyID userID) {
		tracer::Trace trace{  };

		return intf->user->GetGalaxyUserData(userID)->nickname.c_str();
	}

	void FriendsImpl::GetFriendPersonaNameCopy(GalaxyID userID, char* buffer, uint32_t bufferLength) {
		tracer::Trace trace{  };

		std::string nickname = intf->user->GetGalaxyUserData(userID)->nickname;
		universelan::util::safe_copy_str_n(nickname, buffer, bufferLength);
	}

	PersonaState FriendsImpl::GetFriendPersonaState(GalaxyID userID) {
		tracer::Trace trace{  };

		return intf->user->GetGalaxyUserData(userID)->online ?
			PERSONA_STATE_ONLINE :
			PERSONA_STATE_OFFLINE;
	}

	const char* FriendsImpl::GetFriendAvatarUrl(GalaxyID userID, AvatarType avatarType) {
		tracer::Trace trace{  };

		return "";
	}

	void FriendsImpl::GetFriendAvatarUrlCopy(GalaxyID userID, AvatarType avatarType, char* buffer, uint32_t bufferLength) {
		tracer::Trace trace{  };

		universelan::util::safe_copy_str_n(GetFriendAvatarUrl(userID, avatarType), buffer, bufferLength);
	}

	uint32_t FriendsImpl::GetFriendAvatarImageID(GalaxyID userID, AvatarType avatarType) {
		tracer::Trace trace{  };

		return 0;
	}

	void FriendsImpl::GetFriendAvatarImageRGBA(GalaxyID userID, AvatarType avatarType, GetImageRGBABufferType* buffer, uint32_t bufferLength) {
		tracer::Trace trace{  };


	}

	bool FriendsImpl::IsFriendAvatarImageRGBAAvailable(GalaxyID userID, AvatarType avatarType) {
		tracer::Trace trace{  };

		return false;
	}

	void FriendsImpl::RequestFriendList(
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
		IFriendListListener* const listener
#endif
	) {
		tracer::Trace trace{  };

		listeners->NotifyAll(
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			listener, 
#endif
			&IFriendListListener::OnFriendListRetrieveSuccess);
	}

#if GALAXY_BUILD_FEATURE_ADDED_RICH_PRESENCE_LISTENERS
	bool FriendsImpl::IsFriend(GalaxyID userID) {
		tracer::Trace trace{  };

		return false;
	}
#endif

	uint32_t FriendsImpl::GetFriendCount() {
		tracer::Trace trace{  };

		return 0;
	}

	GalaxyID FriendsImpl::GetFriendByIndex(uint32_t index) {
		tracer::Trace trace{  };

		return 0;
	}

#if GALAXY_BUILD_FEATURE_NEW_FRIEND_FEATURES_104_3

	void FriendsImpl::SendFriendInvitation(GalaxyID userID
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
		, IFriendInvitationSendListener* const listener
#endif
	) {
		tracer::Trace trace{  };

		listeners->NotifyAll(
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			listener,
#endif
			&IFriendInvitationSendListener::OnFriendInvitationSendSuccess, userID);
	}

	void FriendsImpl::RequestFriendInvitationList(
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
		IFriendInvitationListRetrieveListener* const listener
#endif
	) {
		tracer::Trace trace{  };

		listeners->NotifyAll(
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			listener,
#endif
			&IFriendInvitationListRetrieveListener::OnFriendInvitationListRetrieveSuccess);
	}

	void FriendsImpl::RequestSentFriendInvitationList(
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
		ISentFriendInvitationListRetrieveListener* const listener
#endif
	) {
		tracer::Trace trace{  };

		listeners->NotifyAll(
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			listener, 
#endif
			&ISentFriendInvitationListRetrieveListener::OnSentFriendInvitationListRetrieveSuccess);
	}

	uint32_t FriendsImpl::GetFriendInvitationCount() {
		tracer::Trace trace{  };

		return 0;
	}

	void FriendsImpl::GetFriendInvitationByIndex(uint32_t index, GalaxyID& userID, uint32_t& sendTime) {
		tracer::Trace trace{  };
	}

	void FriendsImpl::RespondToFriendInvitation(GalaxyID userID, bool accept
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
		, IFriendInvitationRespondToListener* const listener
#endif
	) {
		tracer::Trace trace{  };

		listeners->NotifyAll(
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			listener,
#endif
			&IFriendInvitationRespondToListener::OnFriendInvitationRespondToFailure, userID, IFriendInvitationRespondToListener::FAILURE_REASON_UNDEFINED);
	}

	void FriendsImpl::DeleteFriend(GalaxyID userID
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
		, IFriendDeleteListener* const listener
#endif
	) {
		tracer::Trace trace{  };

		listeners->NotifyAll(
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			listener, 
#endif
			&IFriendDeleteListener::OnFriendDeleteFailure, userID, IFriendDeleteListener::FAILURE_REASON_UNDEFINED);
	}

#endif

	void FriendsImpl::SetRichPresence(const char* key, const char* value
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
		, IRichPresenceChangeListener* const listener
#endif
	) {
		tracer::Trace trace{  };

		intf->config->GetLocalUserData()->stats.SetRichPresence(key, value);

		uint64_t request_id = MessageUniqueID::get();

#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
		rich_presence_change_requests.emplace(request_id, listener);
#endif

		intf->client->GetConnection().SendAsync(RichPresenceChangeMessage{ request_id, 0, RichPresenceChangeMessage::ACTION_SET, key, value });
	}

	void FriendsImpl::DeleteRichPresence(const char* key
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
		, IRichPresenceChangeListener* const listener
#endif
	) {
		tracer::Trace trace{  };

		intf->config->GetLocalUserData()->stats.EraseRichPresence(key);

		uint64_t request_id = MessageUniqueID::get();

#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
		rich_presence_change_requests.emplace(request_id, listener);
#endif

		intf->client->GetConnection().SendAsync(RichPresenceChangeMessage{ request_id, 0, RichPresenceChangeMessage::ACTION_DELETE, key });
	}

	void FriendsImpl::ClearRichPresence(
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
		IRichPresenceChangeListener* const listener
#endif
	) {
		tracer::Trace trace{  };

		intf->config->GetLocalUserData()->stats.ClearRichPresence();

		uint64_t request_id = MessageUniqueID::get();

#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
		rich_presence_change_requests.emplace(request_id, listener);
#endif

		intf->client->GetConnection().SendAsync(RichPresenceChangeMessage{ request_id, 0, RichPresenceChangeMessage::ACTION_CLEAR });
	}

	void FriendsImpl::RichPresenceChangeMessageProcessed(const std::shared_ptr<RichPresenceChangeMessage>& data) {
		tracer::Trace trace{  };

		if (intf->config->IsSelfUserID(data->id)) {
			IRichPresenceChangeListener* listener = rich_presence_change_requests.pop(data->request_id);

			if (data->success) {
				listeners->NotifyAll(listener, &IRichPresenceChangeListener::OnRichPresenceChangeSuccess);
#if GALAXY_BUILD_FEATURE_ADDED_RICH_PRESENCE_LISTENERS
				listeners->NotifyAll(&IRichPresenceListener::OnRichPresenceUpdated, intf->config->GetApiGalaxyID());
#endif
			}
			else {
				listeners->NotifyAll(listener, &IRichPresenceChangeListener::OnRichPresenceChangeFailure, IRichPresenceChangeListener::FAILURE_REASON_UNDEFINED);
			}
			return;
		}
		else if (data->success) {
			auto entry = intf->user->GetGalaxyUserData(data->id);
			switch (data->action) {
			case RichPresenceChangeMessage::ACTION_SET:
				entry->stats.SetRichPresence(data->key, data->value);
				break;

			case RichPresenceChangeMessage::ACTION_DELETE:
				entry->stats.EraseRichPresence(data->key);
				break;

			case RichPresenceChangeMessage::ACTION_CLEAR:
				entry->stats.ClearRichPresence();
				break;

			case RichPresenceChangeMessage::ACTION_NONE:
				break;
			}
		}
	}

#if GALAXY_BUILD_FEATURE_ADDED_RICH_PRESENCE_LISTENERS
	void FriendsImpl::RequestRichPresence(GalaxyID userID
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
		, IRichPresenceRetrieveListener* const listener
#endif
	) {
		tracer::Trace trace{  };

		if (intf->config->IsSelfUserID(userID)) {
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			listeners->NotifyAll(listener, &IRichPresenceRetrieveListener::OnRichPresenceRetrieveSuccess, userID);
#endif
#if GALAXY_BUILD_FEATURE_ADDED_RICH_PRESENCE_LISTENERS
			listeners->NotifyAll(&IRichPresenceListener::OnRichPresenceUpdated, userID);
#endif
		}
		else {
			uint64_t request_id = MessageUniqueID::get();
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			retrieve_rich_presence_requests.emplace(request_id, listener);
#endif

			intf->client->GetConnection().SendAsync(RequestSpecificUserDataMessage{ RequestSpecificUserDataMessage::RequestTypeRichPresence, request_id, userID });
		}
	}

	const char* FriendsImpl::GetRichPresence(const char* key, GalaxyID userID) {
		tracer::Trace trace{  };

		return intf->user->GetGalaxyUserData(userID)->stats.GetRichPresence(key).c_str();
	}

	void FriendsImpl::GetRichPresenceCopy(const char* key, char* buffer, uint32_t bufferLength, GalaxyID userID) {
		tracer::Trace trace{  };

		std::string value = intf->user->GetGalaxyUserData(userID)->stats.GetRichPresence(key);
		universelan::util::safe_copy_str_n(value, buffer, bufferLength);
	}

	uint32_t FriendsImpl::GetRichPresenceCount(GalaxyID userID) {
		tracer::Trace trace{  };

		auto entry = intf->user->GetGalaxyUserData(userID);
		return entry->stats.run_locked_richpresence<uint32_t>([&](auto& map) -> uint32_t {
			return (uint32_t)map.size();
			});
	}

	GetRichPresenceReturnT::type FriendsImpl::GetRichPresenceByIndex(uint32_t index, char* key, uint32_t keyLength, char* value, uint32_t valueLength, GalaxyID userID) {
		tracer::Trace trace{  };

		auto entry = intf->user->GetGalaxyUserData(userID);
		return entry->stats.run_locked_richpresence<GetRichPresenceReturnT::type>([&](auto& map) -> GetRichPresenceReturnT::type {
			if (map.size() < index) {
				return GetRichPresenceReturnT::value_false();
			}

			auto ref = container_get_by_index(map, index);
			universelan::util::safe_copy_str_n(ref.first, key, keyLength);
			universelan::util::safe_copy_str_n(ref.second, value, valueLength);

			return GetRichPresenceReturnT::value_true();
			});
	}
#endif

	void FriendsImpl::RequestRichPresenceProcessed(const std::shared_ptr<RequestSpecificUserDataMessage>& data) {
		tracer::Trace trace{  };

#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
		IRichPresenceRetrieveListener* listener = retrieve_rich_presence_requests.pop(data->request_id);
#endif

		if (data->found) {
			auto entry = intf->user->GetGalaxyUserData(data->id);
			entry->stats = data->asuc;
			entry->nickname = data->nickname;

#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			listeners->NotifyAll(listener, &IRichPresenceRetrieveListener::OnRichPresenceRetrieveSuccess, data->id);
#endif
#if GALAXY_BUILD_FEATURE_ADDED_RICH_PRESENCE_LISTENERS
			listeners->NotifyAll(&IRichPresenceListener::OnRichPresenceUpdated, data->id);
#endif

		}
		else {
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			listeners->NotifyAll(listener, &IRichPresenceRetrieveListener::OnRichPresenceRetrieveFailure, data->id, IRichPresenceRetrieveListener::FAILURE_REASON_UNDEFINED);
#endif
		}
	}


	void FriendsImpl::ShowOverlayInviteDialog(const char* connectionString) {
		tracer::Trace trace{  };

		std::cout << "ShowOverlayInviteDialog\n\t" << connectionString << std::endl;
	}

	void FriendsImpl::SendInvitation(GalaxyID userID, const char* connectionString
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
		, ISendInvitationListener* const listener
#endif
	) {
		tracer::Trace trace{  };

		// TODO: implement this sometime

		listeners->NotifyAll(
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			listener,
#endif
			&ISendInvitationListener::OnInvitationSendFailure, userID, connectionString, ISendInvitationListener::FAILURE_REASON_RECEIVER_DOES_NOT_ALLOW_INVITING);
	}

#if GALAXY_BUILD_FEATURE_FIND_USER
	void FriendsImpl::FindUser(const char* userSpecifier
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
		, IUserFindListener* const listener
#endif
	) {
		tracer::Trace trace{  };

		listeners->NotifyAll(
#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
			listener, 
#endif
			&IUserFindListener::OnUserFindFailure, userSpecifier, IUserFindListener::FAILURE_REASON_UNDEFINED);
	}
#endif

#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
	bool FriendsImpl::IsUserInTheSameGame(GalaxyID userID) const {
		tracer::Trace trace{  };

		return intf->user->GetGalaxyUserData(userID)->online;
	}
#endif
}
