#include "Utils.hxx"
#include "UniverseLAN.hxx"

namespace universelan::client {
	using namespace galaxy::api;
	UtilsImpl::UtilsImpl(InterfaceInstances* intf) :
		intf{ intf }, listeners{ intf->notification.get() }
	{
		tracer::Trace trace{  };
	}

	UtilsImpl::~UtilsImpl()
	{
		tracer::Trace trace{  };
	}

	void UtilsImpl::GetImageSize(uint32_t imageID, int32_t& width, int32_t& height) {
		tracer::Trace trace{  };

		width = 0;
		height = 0;
	}

	void UtilsImpl::GetImageRGBA(uint32_t imageID, GetImageRGBABufferType* buffer, uint32_t bufferLength) {
		tracer::Trace trace{  };
	}

	void UtilsImpl::RegisterForNotification(const char* type) {
		tracer::Trace trace{  };
	}

	uint32_t UtilsImpl::GetNotification(NotificationID notificationID
#if (GALAXY_VERSION) > 11240
		, bool& consumable
#endif
		, char* type, uint32_t typeLength, void* content, uint32_t contentSize) {
		tracer::Trace trace{  };

		return 0;
	}

	void UtilsImpl::ShowOverlayWithWebPage(const char* url) {
		tracer::Trace trace{  };

		std::cout << "ShowOverlayWithWebPage:\n\t";
		std::cout << url << std::endl;
	}

#if GALAXY_BUILD_FEATURE_OVERLAYSTATE_ENUM
	bool UtilsImpl::IsOverlayVisible() {
		tracer::Trace trace{  };

		return false;
	}

	OverlayState UtilsImpl::GetOverlayState() {
		tracer::Trace trace{  };

		return OVERLAY_STATE_DISABLED;
	}

#endif
#if GALAXY_BUILD_FEATURE_HAS_DISABLEOVERLAYPOPUPS
	void UtilsImpl::DisableOverlayPopups(const char* popupGroup) {
		tracer::Trace trace{  };
	}
#endif
#if (GALAXY_VERSION) > 11240
	GogServicesConnectionState UtilsImpl::GetGogServicesConnectionState() {
		tracer::Trace trace{  };

		return intf->client->IsConnected() ?
			GOG_SERVICES_CONNECTION_STATE_CONNECTED :
			GOG_SERVICES_CONNECTION_STATE_DISCONNECTED;
	}
#endif

	void UtilsImpl::ConnectionStateChangeReceived(bool connected) {
		tracer::Trace trace{  };
#if (GALAXY_VERSION) > 11240
		listeners->NotifyAll(&IGogServicesConnectionStateListener::OnConnectionStateChange,
			(connected ?
				GOG_SERVICES_CONNECTION_STATE_CONNECTED :
				GOG_SERVICES_CONNECTION_STATE_DISCONNECTED)
		);
#endif
	}
}
