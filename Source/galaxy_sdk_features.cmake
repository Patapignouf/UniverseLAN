cmake_minimum_required(VERSION 3.12)

# these are prefixed with GALAXY_BUILD_FEATURE_
function(add_feature_definitions_to_target TARGET MAJOR MINOR PATCH)
  set(UVV "${MAJOR}.${MINOR}.${PATCH}")

  #		NAME							START_VERSION END_VERSION
  afvd(HAS_IGALAXY	 							0.0.0 		1.114.9		)

  afvd(IFRIENDS_HAS_PERSONANAME_AND_AVATARURL	1.59.0					)

  afvd(IFRIENDS_ONPERSONADATACHANGED			1.61.0					)
  afvd(IFRIENDS_SET_DEL_CLR_RICHPRESENCE		1.61.0					)

  afvd(HAS_IERRORMANAGER						1.62.0					)
  afvd(FACTORY_RESET_RENAMED_TO_RESETINSTANCE	1.62.0					)
  afvd(LEADERBOARDENTRY_REASON_NOT_FOUND		1.62.0					)
  afvd(IUSER_HAS_ISLOGGEDON						1.62.0					)

  afvd(HAS_GAMEJOINREQUESTEDLISTENER			1.65.0					)
  afvd(HAS_OPERATIONALSTATECHANGELISTENER		1.65.0					)

  afvd(ENCRYPTED_APP_TICKET 					1.67.0 					)
  afvd(HAS_FRIENDLISTLISTENER 					1.67.0 					)
  afvd(HAS_IOVERLAYSTATECHANGELISTENER  		1.67.0 					)

  afvd(HAS_GETLEADERBORDENTRYCOUNT				1.68.0 					)

  afvd(HAS_LEADERBOARD_WITH_DETAILS	    		1.68.0 					)

  afvd(HAS_ILEADERBOARDRETRIEVELISTENER    		1.70.0 					)
  afvd(HAS_IACCESSTOKENLISTENER         		1.70.0 					)
  afvd(HAS_SIGNIN_WITH_SERVERKEY         		1.70.0 					)

  afvd(HAS_GALAXYID_GETREALID            		1.71.0 					)
  afvd(IFRIENDS_GET_FRIEND_PERSONA_AVATAR_COPY  1.71.0 					)
  afvd(IMATCHMAKING_GET_DATA_MEMBER_COPY        1.71.0 					)
  afvd(ISTATS_LEADERBORDSORTMETHOD1_71_ARG_CHANGE 1.71.0 				)
  afvd(ISTATS_GET_ACHIEVEMENT_COPY              1.71.0 			    	)
  afvd(IUSER_GET_DATA_ACCESSTOKEN_COPY          1.71.0 			    	)

  # up to here it's up-to-date
  
  afvd(API_HAS_UTILS                            1.73.0 			    	)
  afvd(API_HAS_IAPPS                            1.73.0 			    	)

  afvd(ADDED_RICH_PRESENCE_LISTENERS			1.74.0					)

  afvd(HAS_INITOPTIONS 							1.82.0 					)

  afvd(ENCRYPTED_APP_TICKET_CONST 				1.102.0					)

  afvd(OVERLAYSTATE_ENUM 						1.103.0					)

  afvd(HAS_ICHAT 								1.104.3					)
  afvd(NEW_FRIEND_FEATURES_104_3				1.104.3					)

  afvd(GALAXYID_HAS_IDTYPE 						1.106.0					)

  afvd(HAS_DISABLEOVERLAYPOPUPS 				1.109.0					)
  afvd(FIND_USER 								1.109.0					)

  afvd(HAS_NAT_FUNCTIONALITY 					1.113.0					)
  afvd(HAS_USERDATAINFOAVAILABLE 				1.113.2					)
  afvd(SEND_LOBBY_MESSAGE_CHAR_TO_VOID 			1.113.3					)

  afvd(HAS_CONNECTION_TYPE 						1.114.0					)
  afvd(GetImageRGBA_CHAR_TO_VOID 				1.114.0					)

  afvd(HAS_INITOPTIONS_MODERN 					1.120.0					)
  afvd(ALLOCATOR 								1.120.0					)
  afvd(EXCEPTION_HELPER 						1.120.0					)
  afvd(GAME_SERVER_API 							1.120.0					)
  afvd(NEEDS_DLL_IMPL 							1.120.0					)

  afvd(USER_SIGNIN_LISTENERS 					1.121.3					)

  afvd(LOBBY_LISTENERS 							1.124.1					)
  afvd(MATCHMAKING_RESULT_COUNT 				1.124.1					)
  afvd(MATCHMAKING_RET_TYPE_VOID 				1.124.1					)
  afvd(USER_DATA_LISTENERS 						1.124.1					)
  afvd(USER_SIGNIN_CROSSPLATFORM 				1.124.1					)
  afvd(USER_ACCESS_TOKEN_INFO 					1.124.1					)

  afvd(IFRIENDS_INFORMATIONLISTENERS			1.126.0					)

  afvd(IFRIENDS_ISTATS_UPDATE_1_127_0			1.127.0					)

  afvd(HAS_GAMESERVER_UTILS						1.133.0					)
  afvd(HAS_GOGSERVICECONNECTIONSTATELISTENER	1.133.0					)
  afvd(HAS_IMATCHMAKING_LOBBY_LEAVE_REASON		1.133.0					)
  afvd(SIGNIN_RENAMED_TO_SIGNINCREDENTIALS		1.133.0					)
  afvd(SIGNIN_RENAMED_TO_SIGNINSTEAM			1.133.0					)
  afvd(SIGNIN_RENAMED_TO_SIGNINGALAXY			1.133.0					)
  afvd(SIGNIN_RENAMED_TO_SIGNINPS4	    		1.133.0					)
  afvd(SIGNIN_RENAMED_TO_SIGNINXB1	    		1.133.0					)
  afvd(SIGNIN_RENAMED_TO_SIGNINSERVERKEY		1.133.0					)
  afvd(HAS_SIGNINTOKEN							1.133.0					)
  afvd(HAS_SIGNINUWP							1.133.0					)

  afvd(HAS_ITELEMETRY			 				1.134.0					) 

  afvd(IUSER_SIGNINEPIC							1.139.5					)

  afvd(ITELEMETRY_1_139_6_UPDATE				1.139.6					)

  afvd(ITELEMETRY_1_139_7_UPDATE				1.139.7					)

  afvd(HAS_IGALAXYTHREADFACTORY 				1.140.0					)

  afvd(HAS_ITELEMETRY_SAMPLING_CLASS			1.141.0					)
  afvd(IGALAXYTHREAD_JOINABLE_DETACH			1.141.0					)

  afvd(IUSER_SIGNINXBLIVE						1.143.0					)

  afvd(IUSER_SIGNINLAUNCHER						1.146.0					)

  afvd(HAS_RED_PREFIX							1.149.12	1.149.16	)

  afvd(NEAR_FILTER_ENUM 						9.999.0					) # disabled because it's not really present? bug in SDK?
  
endfunction()

# INCLUSIVE MIN_VERSION and INCLUSIVE MAX_VERSION
function(afvd FEATURE_NAME FEATURE_MIN_VERSION)
  set(RESULT 0)

  if(${UVV} VERSION_GREATER_EQUAL ${FEATURE_MIN_VERSION})
    set(RESULT 1)
  endif()

  if(ARGN)
    list (GET ARGN 0 FEATURE_MAX_VERSION)
    if(NOT "${FEATURE_MAX_VERSION}" STREQUAL "")
      if(${UVV} VERSION_GREATER ${FEATURE_MAX_VERSION})
        set(RESULT 0)
      endif()
    endif()
  endif()

  target_compile_definitions(${TARGET} PUBLIC 
    "GALAXY_BUILD_FEATURE_${FEATURE_NAME}=${RESULT}"
  )

  set_property(GLOBAL PROPERTY "GALAXY_${UVV}_BUILD_FEATURE_${FEATURE_NAME}" "${RESULT}")
endfunction()
