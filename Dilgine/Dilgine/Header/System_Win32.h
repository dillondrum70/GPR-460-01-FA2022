#ifndef SYSTEM_WIN32_H
#define SYSTEM_WIN32_H

#ifdef _WIN32
// THIS IS WINDOWS-ONLY
#define _CRT_SECURE_NO_WARNINGS
#define _CRTDBG_MAP_ALLOC

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <crtdbg.h>

#include "System_Common.h"

namespace gpr460
{
	const gpr460::string ERROR_FILENAME = L"GameErrors.txt";

	//error constants
	const gpr460::string ERROR_PRESSED_K = L"Error: User pressed 'k'";

	class System_Win32 : public System
	{
		~System_Win32() override {}

		void Init() override;

		void Shutdown() override;

		void ErrorMessage(const gpr460::string& message) override;

		void LogToErrorFile(const gpr460::string& message) override;

		HANDLE errorFile;
	};

}
#endif

#endif