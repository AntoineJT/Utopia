#include "utpch.hpp"
#include "Log.hpp"

#include <any>
#include <utility>

#include <spdlog/spdlog.h>
#include <spdlog/logger.h>
#include <spdlog/sinks/stdout_color_sinks.h>

struct Utopia::Logger::Impl
{
	Impl(std::shared_ptr<spdlog::logger> logger) : logger(std::move(logger)) {};
	/*
	~Impl()
	{
		logger.reset();
	}
	*/

	void set_level(spdlog::level::level_enum log_level)
	{
		logger->set_level(log_level);
	}

	void error(std::any&& msg)
	{
		logger->error(std::forward<std::any>(msg));
	}
private:
	std::shared_ptr<spdlog::logger> logger;
};

void Utopia::Logger::Init()
{
	spdlog::set_pattern("%^[%T](%l) %n: %v%$");

	Utopia::Logger::s_CoreLogger = std::make_unique<Utopia::Logger::Impl>(spdlog::stdout_color_mt("UTOPIA"));
	Utopia::Logger::s_CoreLogger->set_level(spdlog::level::trace);

	Utopia::Logger::s_ClientLogger = std::make_unique<Utopia::Logger::Impl>(spdlog::stdout_color_mt("APP"));
	Utopia::Logger::s_ClientLogger->set_level(spdlog::level::trace);
}
