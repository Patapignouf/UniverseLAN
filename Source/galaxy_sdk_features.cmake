cmake_minimum_required(VERSION 3.12)

# these are prefixed with GALAXY_BUILD_FEATURE_
function(add_feature_definitions_to_target TARGET MAJOR MINOR PATCH)
  set(UVV "${MAJOR}.${MINOR}.${PATCH}")

  afvd(NEAR_FILTER_ENUM 				9.999.0) # disabled because it's not really present? bug in SDK?
  afvd(HAS_ICHAT 						1.104.3)
  afvd(LOBBY_LISTENERS 					1.124.1)
  afvd(MATCHMAKING_RESULT_COUNT 		1.124.1)
  afvd(MATCHMAKING_RET_TYPE_VOID 		1.124.1)
  afvd(USER_SIGNIN_LISTENERS 			1.121.3)
  afvd(USER_DATA_LISTENERS 				1.124.1)
  afvd(USER_SIGNIN_CROSSPLATFORM 		1.124.1)
  afvd(USER_ACCESS_TOKEN_INFO 			1.124.1)
  afvd(GALAXYID_HAS_IDTYPE 				1.106.0)
  afvd(GetImageRGBA_CHAR_TO_VOID 		1.114.0)
  afvd(OVERLAYSTATE_ENUM 				1.103.0)
  afvd(HAS_DISABLEOVERLAYPOPUPS 		1.109.0)
  afvd(HAS_NAT_FUNCTIONALITY 			1.113.0)
  afvd(HAS_CONNECTION_TYPE 				1.114.0)
  afvd(HAS_USERDATAINFOAVAILABLE 		1.113.2)
  afvd(HAS_INITOPTIONS 					1.82.0 )
  afvd(HAS_INITOPTIONS_MODERN 			1.120.0)
  afvd(ALLOCATOR 						1.120.0)
  afvd(EXCEPTION_HELPER 				1.120.0)
  afvd(GAME_SERVER_API 					1.120.0)
  afvd(ENCRYPTED_APP_TICKET 			1.67.0 )
  afvd(ENCRYPTED_APP_TICKET_CONST 		1.102.0)
  afvd(SEND_LOBBY_MESSAGE_CHAR_TO_VOID 	1.113.3)
  afvd(FIND_USER 						1.109.0)
  afvd(NEW_FRIEND_FEATURES_104_3		1.104.3)

endfunction()