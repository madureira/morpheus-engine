#pragma once

#include <string>
#ifdef _WIN32
#include <windows.h>
#include <intrin.h>
#elif MACOS
#include <sys/param.h>
#include <sys/sysctl.h>
#else
#include <cpuid.h>
#include <unistd.h>
#endif

namespace Morpheus {

	class HardwareUtil final
	{
	public:
		static std::string GetCPUInfo()
		{
#ifdef WIN32
			int CPUInfo[4] = { -1 };
			unsigned   nExIds, i = 0;
			char CPUBrandString[0x40];
			// Get the information associated with each extended ID.
			__cpuid(CPUInfo, 0x80000000);
			nExIds = CPUInfo[0];
			for (i = 0x80000000; i <= nExIds; ++i)
			{
				__cpuid(CPUInfo, i);
				// Interpret CPU brand string
				if (i == 0x80000002)
					memcpy(CPUBrandString, CPUInfo, sizeof(CPUInfo));
				else if (i == 0x80000003)
					memcpy(CPUBrandString + 16, CPUInfo, sizeof(CPUInfo));
				else if (i == 0x80000004)
					memcpy(CPUBrandString + 32, CPUInfo, sizeof(CPUInfo));
			}
			//string includes manufacturer, model and clockspeed
			return CPUBrandString;
#else
			char CPUBrandString[0x40];
			unsigned int CPUInfo[4] = { 0,0,0,0 };

			__cpuid(0x80000000, CPUInfo[0], CPUInfo[1], CPUInfo[2], CPUInfo[3]);
			unsigned int nExIds = CPUInfo[0];

			memset(CPUBrandString, 0, sizeof(CPUBrandString));

			for (unsigned int i = 0x80000000; i <= nExIds; ++i)
			{
				__cpuid(i, CPUInfo[0], CPUInfo[1], CPUInfo[2], CPUInfo[3]);

				if (i == 0x80000002)
					memcpy(CPUBrandString, CPUInfo, sizeof(CPUInfo));
				else if (i == 0x80000003)
					memcpy(CPUBrandString + 16, CPUInfo, sizeof(CPUInfo));
				else if (i == 0x80000004)
					memcpy(CPUBrandString + 32, CPUInfo, sizeof(CPUInfo));
			}
			return CPUBrandString;
#endif
		}

		static int GetCPUNumberOfCores()
		{
#ifdef WIN32
			SYSTEM_INFO sysinfo;
			GetSystemInfo(&sysinfo);
			return sysinfo.dwNumberOfProcessors;
#elif MACOS
			int mib[4];
			int numCPU;
			std::size_t len = sizeof(numCPU);

			/* set the mib for hw.ncpu */
			mib[0] = CTL_HW;
			mib[1] = HW_AVAILCPU;  // alternatively, try HW_NCPU;

			/* get the number of CPUs from the system */
			sysctl(mib, 2, &numCPU, &len, NULL, 0);

			if (numCPU < 1)
			{
				mib[1] = HW_NCPU;
				sysctl(mib, 2, &numCPU, &len, NULL, 0);
				if (numCPU < 1)
				{
					numCPU = 1;
				}
			}

			return numCPU;
#else
			return sysconf(_SC_NPROCESSORS_ONLN);
#endif
		}

		static unsigned long long GetTotalRAM()
		{
#ifdef WIN32
			MEMORYSTATUSEX status;
			status.dwLength = sizeof(status);
			GlobalMemoryStatusEx(&status);
			return status.ullTotalPhys;
#elif MACOS
			int mib[2] = { CTL_HW, HW_MEMSIZE };
			u_int namelen = sizeof(mib) / sizeof(mib[0]);
			uint64_t size;
			size_t len = sizeof(size);

			if (sysctl(mib, namelen, &size, &len, NULL, 0) < 0)
			{
				return 0;
			}
			return size;
#else
			long pages = sysconf(_SC_PHYS_PAGES);
			long page_size = sysconf(_SC_PAGE_SIZE);
			return pages * page_size;
#endif
		}

		static std::string GetRendererAPI()
		{
			std::string glVersion = reinterpret_cast<char const*>(glGetString(GL_VERSION));
			return glVersion;
		}

		static std::string GetGPUModel()
		{
			std::string gpuModel = reinterpret_cast<char const*>(glGetString(GL_RENDERER));
			return gpuModel;
		}

		static std::string GetGPUVendor()
		{
			std::string gpuVendor = reinterpret_cast<char const*>(glGetString(GL_VENDOR));
			return gpuVendor;
		}
	};

}
