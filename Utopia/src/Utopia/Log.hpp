#pragma once

#include "Core.hpp"
#include <any>

namespace Utopia
{
	class LogImpl;

	class UTOPIA_API Logger
	{
	public:
		static void Init();
		static LogImpl* GetCoreLogger() { return s_CoreLogger.get(); }
		static LogImpl* GetClientLogger() { return s_ClientLogger.get(); }
	private:
		static std::unique_ptr<LogImpl> s_CoreLogger;
		static std::unique_ptr<LogImpl> s_ClientLogger;
	};

	namespace Log
	{
		// Core Log
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

		void error(std::any&& arg)
		{
			Logger::GetClientLogger()->error(std::forward<std::any>(arg));
		}

		// SandBox Log Macros
		/*
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
	}
}
