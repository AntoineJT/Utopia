#include "utpch.hpp"
#include "Log.hpp"

#include <any>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

void Utopia::Logger::Init()
{
	spdlog::set_pattern("%^[%T](%l) %n: %v%$");

	std::shared_ptr<spdlog::logger> coreLogger = spdlog::stdout_color_mt("UTOPIA");
	coreLogger->set_level(spdlog::level::trace);
	Utopia::Logger::s_CoreLogger = coreLogger;

	std::shared_ptr<spdlog::logger> clientLogger = spdlog::stdout_color_mt("APP");
	clientLogger->set_level(spdlog::level::trace);
	Utopia::Logger::s_CoreLogger = clientLogger;
}

void Utopia::Log::_coreError(const std::any& msg)
{
	static_cast<spdlog::logger*>(Utopia::Logger::GetCoreLogger())->error<std::any>(msg);
}

void Utopia::Log::_error(const std::any& msg)
{
	static_cast<spdlog::logger*>(Utopia::Logger::GetCoreLogger())->error<std::any>(msg);
}

void Utopia::Log::_info(const std::any& msg)
{
	static_cast<spdlog::logger*>(Utopia::Logger::GetCoreLogger())->info<std::any>(msg);
}
