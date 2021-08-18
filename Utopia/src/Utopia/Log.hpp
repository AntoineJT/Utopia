#pragma once

#include "Core.hpp"

#include <any>
#include <memory>

namespace Utopia
{
	class UTOPIA_API Logger
	{
	public:
		static void Init();
		static void* GetCoreLogger() { return s_CoreLogger.get(); }
		static void* GetClientLogger() { return s_ClientLogger.get(); }
	private:
		static std::shared_ptr<void> s_CoreLogger;
		static std::shared_ptr<void> s_ClientLogger;
	};

	struct Log
	{
		static void _coreError(const std::any& msg);
		static void _error(const std::any& msg);
		static void _info(const std::any& msg);

		template<typename... Args>
		static constexpr void coreError(Args&&... args)
		{
			std::vector<std::any> vec = { std::forward<std::any>(args)... };
			for (auto elem : vec)
			{
				_coreError(elem);
			}
		}

		template<typename... Args>
		static constexpr void error(Args&&... args)
		{
			std::vector<std::any> vec = { std::forward<std::any>(args)... };
			for (auto elem : vec)
			{
				_error(elem);
			}
		}

		template<typename... Args>
		static constexpr void info(Args&&... args)
		{
			std::vector<std::any> vec = { std::forward<std::any>(args)... };
			for (auto elem : vec)
			{
				_info(std::reference_wrapper(elem));
			}
		}
	};
}
