#include "utpch.hpp"
#include "Log.hpp"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace Utopia
{
	class LogImpl
	{
	public:
		LogImpl(std::shared_ptr<spdlog::logger> logger) : logger(std::move(logger)) {};

		void setLevelToTrace()
		{
			logger->set_level(spdlog::level::trace);
		}

		void error(std::any&& arg)
		{
			logger->error(std::forward<std::any>(arg));
		}

	private:
		std::shared_ptr<spdlog::logger> logger;
	};

	// spdlog::logger
	std::unique_ptr<LogImpl> Logger::s_CoreLogger;
	std::unique_ptr<LogImpl> Logger::s_ClientLogger;

	void Logger::Init()
	{
		spdlog::set_pattern("%^[%T](%l) %n: %v%$");

		s_CoreLogger = std::make_unique<LogImpl>(spdlog::stdout_color_mt("UTOPIA"));
		s_CoreLogger->setLevelToTrace();

		s_ClientLogger = std::make_unique<LogImpl>(spdlog::stdout_color_mt("APP"));
		s_ClientLogger->setLevelToTrace();
	}
}
