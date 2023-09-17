#pragma once
#include <cstdint>
#include <iostream>
#include <syncstream>
#include <source_location>

namespace universelan::tracer {
	template<uint64_t N>
	static constexpr uint64_t bit() { return 1 << N; }

	class Trace
	{
	private:
		const bool enabled;
		const char* const func;
		const char* const extra;
		const void* return_address;
	public:
		enum MASK: uint64_t {
			INFORMATIONAL = 0,
			HIGH_FREQUENCY_CALLS = bit<0>(),
			ARGUMENTS = bit<1>(),
			RETURN_VALUES = bit<2>(),
			API_IMPL = bit<3>()
		};

		static bool InitTracing(const char* const log_directory, 
			bool in_unhandled_exception_logging, bool in_tracing_enabled, 
			bool in_mindump_on_unhandled_exception, int minidump_verbosity_level,
			bool in_should_always_flush_tracing, uint64_t mask = INFORMATIONAL);

		static void SetUnhandledExceptionLogging(bool enabled);
		static void SetTracingEnabled(bool enabled);

		Trace(const char* const extra = nullptr, MASK mask = INFORMATIONAL, const char* const func = std::source_location::current().function_name());
		Trace(MASK mask, const char* const extra = nullptr, const char* const func = std::source_location::current().function_name());

		~Trace();

		explicit operator bool() const;
		bool operator!() const;
		bool has_flags(MASK mask) const;

		static std::ofstream& thread_logger();
		static std::osyncstream global_logger();
	};
}
