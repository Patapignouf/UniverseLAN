#include <TestCaseClientDetails.hxx>

#if GALAXY_BUILD_FEATURE_HAS_IGALAXY
#define GET_GALAXY_API(what) galaxy_api->Get ## what
#define GET_GALAXY_API_AS_IS(what) galaxy_api->what

galaxy::api::IGalaxy* galaxy_api = nullptr;
#else
#define GET_GALAXY_API(what) galaxy::api::what
#define GET_GALAXY_API_AS_IS(what) galaxy::api::what
#endif

#if !GALAXY_BUILD_FEATURE_SIGNIN_RENAMED_TO_SIGNINCREDENTIALS
#define SignInCredentials SignIn
#endif

bool has_access_token_refreshed = true;
bool has_signed_in = false;
bool has_connected = false;
bool has_operational_state_change = false;
bool has_person_data_unchanged = false;
bool performed_init = false;
bool user_data_received = true;
std::unique_ptr<tracer::Trace> trace{ nullptr };
DelayRunner delay_runner{};
GalaxyID my_lobby_id = 0;

void perform_test() {

	auto matchmaking_ptr = GET_GALAXY_API(Matchmaking());
	
	matchmaking_ptr->CreateLobby(LobbyType::LOBBY_TYPE_PUBLIC, 4, true, LobbyTopologyType::LOBBY_TOPOLOGY_TYPE_FCM_OWNERSHIP_TRANSITION);
}

long long GetTimeNow() {
	return std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

void TimerThread() {
	while (true) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));

		delay_runner.Add([]() {
			uint64_t time_now = GetTimeNow();

			tracer::Trace::write_all(
				std::format(
					"key: {} value: {}",
					"timer", time_now
				));


			auto matchmaking_ptr = GET_GALAXY_API(Matchmaking());

			char* time_now_c = (char*)&time_now;
			char data[] = {
				0x42, // 'B'inary
				0x54, // 'T'ime
				0x00,
				0x00,
				time_now_c[0],
				time_now_c[1],
				time_now_c[2],
				time_now_c[3],
				time_now_c[4],
				time_now_c[5],
				time_now_c[6],
				time_now_c[7],
				0x00,
				0x00,
				0x00,
				0x00,
				0x3F,
				0x3F,
				0x00,
				0x00,
				0xAA
			};

			matchmaking_ptr->SendLobbyMessage(my_lobby_id, data, sizeof(data));
			});
	}
}

void OnLobbyCreated(const GalaxyID& lobbyID, LobbyCreateResult result) 
{
	if (result != LobbyCreateResult::LOBBY_CREATE_RESULT_SUCCESS) {
		return;
	}

	my_lobby_id = lobbyID;

	auto matchmaking_ptr = GET_GALAXY_API(Matchmaking());

	for (auto& data_entry : LOBBY_TEST_DATA) {
		matchmaking_ptr->SetLobbyData(lobbyID, data_entry[0].data(), data_entry[1].data());
	}
	
	matchmaking_ptr->SetLobbyData(lobbyID, "timer", std::to_string(GetTimeNow()).c_str());

	std::thread{ TimerThread }.detach(); // !!! LEAK !!! (until thread exits)
}

void try_init() {
	if (!has_signed_in ||
		!has_connected ||
		!has_operational_state_change ||
		!has_person_data_unchanged ||
		!has_access_token_refreshed ||
		!user_data_received ||
		performed_init)
	{
		return;
	}

	performed_init = true;
}

int main()
{
	tracer::Trace::InitTracing(".", false, true, false, 0, true);
	tracer::Trace::SetLogToCout(true);
	tracer::Trace::SetTracingEnabled(false);

	galaxy::api::InitOptions options(galaxy::api::CLIENT_ID.data(), galaxy::api::CLIENT_SECRET.data());

#if GALAXY_BUILD_FEATURE_HAS_IGALAXY
	galaxy_api = galaxy::api::GalaxyFactory::CreateInstance();
#endif

	GET_GALAXY_API_AS_IS(Init(options));

	trace = std::make_unique<tracer::Trace>("", "main");

	AccessTokenListenerImplGlobal accesstokenlistener{ [&]() {
		has_access_token_refreshed = true;
		try_init();
		} };

	AchievementChangeListenerImplGlobal achievementchangelistener{};
	AuthListenerImplGlobal authlistener{ [&]() {
		has_signed_in = true;
		try_init();
		} };

#if GALAXY_BUILD_FEATURE_HAS_ICHAT 
	ChatRoomMessageSendListenerImplGlobal chatroommessagesendlistener{};
	ChatRoomMessagesListenerImplGlobal chatroommessageslistener{};
	ChatRoomMessagesRetrieveListenerImplGlobal chatroommessagesretrievelistener{};
	ChatRoomWithUserRetrieveListenerImplGlobal chatroomwithuserretrievelistener{};
#endif

	ConnectionCloseListenerImplGlobal connectioncloselistener{};
	ConnectionDataListenerImplGlobal connectiondatalistener{};
	ConnectionOpenListenerImplGlobal connectionopenlistener{};
	EncryptedAppTicketListenerImplGlobal encryptedappticketlistener{};
	FileShareListenerImplGlobal filesharelistener{};

#if GALAXY_BUILD_FEATURE_HAS_FRIENDADDLISTENER
	FriendAddListenerImplGlobal friendaddlistener{};
#endif

#if GALAXY_BUILD_FEATURE_NEW_FRIEND_FEATURES_104_3
	FriendDeleteListenerImplGlobal frienddeletelistener{};
	FriendInvitationListRetrieveListenerImplGlobal friendinvitationlistretrievelistener{};
	FriendInvitationListenerImplGlobal friendinvitationlistener{};
	FriendInvitationRespondToListenerImplGlobal friendinvitationrespondtolistener{};
	FriendInvitationSendListenerImplGlobal friendinvitationsendlistener{};
#endif

	FriendListListenerImplGlobal friendlistlistener{};
	GameInvitationReceivedListenerImplGlobal gameinvitationreceivedlistener{};
#if GALAXY_BUILD_FEATURE_HAS_GAMEJOINREQUESTEDLISTENER
	GameJoinRequestedListenerImplGlobal gamejoinrequestedlistener{};
#endif

#if GALAXY_BUILD_FEATURE_HAS_GOGSERVICECONNECTIONSTATELISTENER
	GogServicesConnectionStateListenerImplGlobal gogservicesconnectionstatelistener{ [&](GogServicesConnectionState state) {
		if (state != GOG_SERVICES_CONNECTION_STATE_CONNECTED) {
			return;
		}
		has_connected = true;
		try_init();
		} };
#endif

	LeaderboardEntriesRetrieveListenerImplGlobal leaderboardentriesretrievelistener{};
	LeaderboardRetrieveListenerImplGlobal leaderboardretrievelistener{};
	LeaderboardScoreUpdateListenerImplGlobal leaderboardscoreupdatelistener{};
	LeaderboardsRetrieveListenerImplGlobal leaderboardsretrievelistener{};
	LobbyCreatedListenerImplGlobal lobbycreatedlistener{ OnLobbyCreated };
	LobbyDataListenerImplGlobal lobbydatalistener{};
	LobbyDataRetrieveListenerImplGlobal lobbydataretrievelistener{};
	LobbyEnteredListenerImplGlobal lobbyenteredlistener{};
	LobbyLeftListenerImplGlobal lobbyleftlistener{};
	LobbyListListenerImplGlobal lobbylistlistener{};
	LobbyMemberStateListenerImplGlobal lobbymemberstatelistener{};
	LobbyMessageListenerImplGlobal lobbymessagelistener{};
	LobbyOwnerChangeListenerImplGlobal lobbyownerchangelistener{};

#if GALAXY_BUILD_FEATURE_HAS_NAT_FUNCTIONALITY
	NatTypeDetectionListenerImplGlobal nattypedetectionlistener{};
#endif

	NetworkingListenerImplGlobal networkinglistener{};
	NotificationListenerImplGlobal notificationlistener{};
	OperationalStateChangeListenerImplGlobal operationalstatechangelistener{ [&](uint32_t operationalState) {
		if (!(operationalState & IOperationalStateChangeListener::OperationalState::OPERATIONAL_STATE_SIGNED_IN &&
			operationalState & IOperationalStateChangeListener::OperationalState::OPERATIONAL_STATE_LOGGED_ON)) {
			return;
		}
		has_operational_state_change = true;
		try_init();
		} };

	OtherSessionStartListenerImplGlobal othersessionstartlistener{};

#if GALAXY_BUILD_FEATURE_OVERLAYSTATE_ENUM
	OverlayInitializationStateChangeListenerImplGlobal overlayinitializationstatechangelistener{};
	OverlayVisibilityChangeListenerImplGlobal overlayvisibilitychangelistener{};
#endif

	PersonaDataChangedListenerImplGlobal personadatachangedlistener{ [&](GalaxyID userID, uint32_t personaStateChange) {
		if (personaStateChange != 0 || userID != GET_GALAXY_API(User())->GetGalaxyID()) {
			return;
		}
		has_person_data_unchanged = true;
		try_init();
		}
	};
	//RichPresenceChangeListenerImplGlobal richpresencechangelistener{};

#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
	//RichPresenceListenerImplGlobal richpresencelistener{};
#endif

#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
	//RichPresenceRetrieveListenerImplGlobal richpresenceretrievelistener{};
#endif

#if GALAXY_BUILD_FEATURE_HAS_ISENTFRIENDINVITATIONLISTRETRIEVELISTENER
	SendInvitationListenerImplGlobal sendinvitationlistener{};
#endif

#if GALAXY_BUILD_FEATURE_HAS_ISENTFRIENDINVITATIONLISTRETRIEVELISTENER
	SentFriendInvitationListRetrieveListenerImplGlobal sentfriendinvitationlistretrievelistener{};
#endif

	SharedFileDownloadListenerImplGlobal sharedfiledownloadlistener{};
	SpecificUserDataListenerImplGlobal specificuserdatalistener{
		[&](GalaxyID userID) {
		user_data_received = true;
		try_init();
		}
	};
	StatsAndAchievementsStoreListenerImplGlobal statsandachievementsstorelistener{};

#if GALAXY_BUILD_FEATURE_HAS_ITELEMETRY
	TelemetryEventSendListenerImplGlobal telemetryeventsendlistener{};
#endif

	UserDataListenerImplGlobal userdatalistener{ [&]() {
		user_data_received = true;
		try_init();
		}
	};

#if GALAXY_BUILD_FEATURE_HAS_IUSERFINDLISTENER
	UserFindListenerImplGlobal userfindlistener{};
#endif

#if GALAXY_BUILD_FEATURE_IFRIENDS_INFORMATIONLISTENERS
	UserInformationRetrieveListenerImplGlobal userinformationretrievelistener{};
	UserStatsAndAchievementsRetrieveListenerImplGlobal userstatsandachievementsretrievelistener{};
#endif

#if GALAXY_BUILD_FEATURE_HAS_IUSERTIMEPLAYEDRETRIEVELISTENER
	UserTimePlayedRetrieveListenerImplGlobal usertimeplayedretrievelistener{};
#endif

#if GALAXY_BUILD_FEATURE_HAS_ISERVERNETWORKINGLISTENER
	ServerNetworkingListenerImplGlobal servernetworkinglistener{};
#endif

#if GALAXY_BUILD_FEATURE_HAS_IOVERLAYSTATECHANGELISTENER
	OverlayStateChangeListenerImplGlobal overlaystatechangelistener{};
#endif

	auto credentials = USER_CREDENTIALS[0];

	GET_GALAXY_API(User())->SignInCredentials(credentials[0].data(), credentials[1].data());
	bool sub_init_done = false;

	while (true)
	{
		GET_GALAXY_API_AS_IS(ProcessData());
		if (performed_init && !sub_init_done) {
			sub_init_done = true;

			tracer::Trace::SetTracingEnabled(true);
			trace = std::make_unique<tracer::Trace>("::INIT", "main");

			perform_test();
		}

		delay_runner.Run();
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}

	return 0;
}
