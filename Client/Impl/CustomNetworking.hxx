#ifndef LSFDRMFG_IMPL_CUSTOM_NETWORKING_H
#define LSFDRMFG_IMPL_CUSTOM_NETWORKING_H

/**
 * @file
 * Contains data structures and interfaces related to communicating with custom endpoints.
 * @warning This API is experimental and can be changed or removed in following releases.
 */

#include <ICustomNetworking.h>
#include <IListenerRegistrar.h>

namespace galaxy
{
	namespace api
	{
		/**
		 * @addtogroup api
		 * @{
		 */

		/**
		 * The interface for communicating with a custom endpoint.
		 */
		class CustomNetworking : public ICustomNetworking
		{
		public:

			virtual ~CustomNetworking();

			/**
			 * Open a connection with a specific endpoint.
			 *
			 * This call is asynchronous. Responses come to the IConnectionOpenListener.
			 *
			 * @remark Currently only supported connection string is a WebSocket URL (e.g. ws://example.com:8000/path/to/ws).
			 *
			 * @param [in] connectionString The string which contains connection info.
			 * @param [in] listener The listener for specific operation.
			 */
			virtual void OpenConnection(const char* connectionString, IConnectionOpenListener* const listener = NULL) override;

			/**
			 * Close a connection.
			 *
			 * This call is asynchronous. Responses come to the IConnectionCloseListener.
			 *
			 * @param [in] connectionID The ID of the connection.
			 * @param [in] listener The listener for specific operation.
			 */
			virtual void CloseConnection(ConnectionID connectionID, IConnectionCloseListener* const listener = NULL) override;

			/**
			 * Send binary data over a specific connection.
			 *
			 * @param [in] connectionID The ID of the connection.
			 * @param [in] data The data to send.
			 * @param [in] dataSize The size of the data.
			 */
			virtual void SendData(ConnectionID connectionID, const void* data, uint32_t dataSize) override;

			/**
			 * Returns the number of bytes in a specific connection incoming buffer.
			 *
			 * @param [in] connectionID The ID of the connection.
			 * @return The number of bytes in the connection incomming buffer.
			 */
			virtual uint32_t GetAvailableDataSize(ConnectionID connectionID) override;

			/**
			 * Reads binary data received from a specific connection.
			 * The data that was read this way is left in the connection incomming buffer.
			 *
			 * @param [in] connectionID The ID of the connection.
			 * @param [in, out] dest The buffer to pass the data to.
			 * @param [in] dataSize The size of the data.
			 */
			virtual void PeekData(ConnectionID connectionID, void* dest, uint32_t dataSize) override;

			/**
			 * Reads binary data received from a specific connection.
			 * The data that was read this way is removed from the connection incomming buffer.
			 *
			 * @param [in] connectionID The ID of the connection.
			 * @param [in, out] dest The buffer to pass the data to.
			 * @param [in] dataSize The size of the data.
			 */
			virtual void ReadData(ConnectionID connectionID, void* dest, uint32_t dataSize) override;

			/**
			 * Removes a given number of bytes from a specific connection incomming buffer.
			 *
			 * @param [in] connectionID The ID of the connection.
			 * @param [in] dataSize The numbers of bytes to be removed from the buffer.
			 */
			virtual void PopData(ConnectionID connectionID, uint32_t dataSize) override;
		};

		/** @} */
	}
}



#endif
