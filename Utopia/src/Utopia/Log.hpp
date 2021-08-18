#pragma once

#include "Core.hpp"

#include <any>

namespace Utopia
{
	class UTOPIA_API Logger
	{
	public:
		static void Init();
	private:
		class Impl;
		// static Impl* GetCoreLogger() { return s_CoreLogger.get(); }
		// static Impl* GetClientLogger() { return s_ClientLogger.get(); }

		static void error(bool core, std::any&& msg)
		{
			(core ? s_CoreLogger : s_ClientLogger)->error(std::forward<std::any>(msg));
		}

		static std::unique_ptr<Impl> s_CoreLogger;
		static std::unique_ptr<Impl> s_ClientLogger;

		friend class Log;
	};

	class Log 
	{
	public:

		// Core Log
		/*
		template<typename... Args>
		constexpr void coreTrace(Args&&... args)
		{
			Logger::GetCoreLogger()->trace(std::forward<Args>(args)...);
		}

		template<typename... Args>
		constexpr void coreInfo(Args&&... args)
		{
			Logger::GetCoreLogger()->info(std::forward<Args>(args)...);
		}

		template<typename... Args>
		constexpr void coreWarn(Args&&... args)
		{
			Logger::GetCoreLogger()->warn(std::forward<Args>(args)...);
		}

		template<typename... Args>
		constexpr void coreError(Args&&... args)
		{
			Logger::GetCoreLogger()->error(std::forward<Args>(args)...);
		}

		// SandBox Log Macros
		template<typename... Args>
		constexpr void trace(Args&&... args)
		{
			Logger::GetClientLogger()->trace(std::forward<Args>(args)...);
		}

		template<typename... Args>
		constexpr void info(Args&&... args)
		{
			Logger::GetClientLogger()->info(std::forward<Args>(args)...);
		}

		template<typename... Args>
		constexpr void warn(Args&&... args)
		{
			Logger::GetClientLogger()->warn(std::forward<Args>(args)...);
		}

		template<typename... Args>
		constexpr void error(Args&&... args)
		{
			Logger::GetClientLogger()->error(std::forward<Args>(args)...);
		}
		*/
	};
}
