/*
 *   VisionManager.h
 *
 *   Author: Wu Chih-En
 *
 */

#ifndef _VISION_MANGER_H_
#define _VISION_MANGER_H_

#include <list>
#include <fstream>
#include <iostream>
#include "Status.h"
#include "VisionModule.h"
#include "minIni.h"

#define OFFSET_SECTION "Offset"
#define INVALID_VALUE   -1024.0

namespace Robot
{
	class VisionManager
	{
	private:
		static VisionManager* m_UniqueInstance;
		std::list<VisionModule*> m_Modules;
		bool m_ProcessEnable;
		bool m_Enabled;

		bool m_IsRunning;
		bool m_IsThreadRunning;
		bool m_IsLogging;

		std::ofstream m_LogFileStream;

        VisionManager();

	protected:

	public:
		bool DEBUG_PRINT;

		~VisionManager();

		static VisionManager* GetInstance() { return m_UniqueInstance; }

		bool Initialize();
		bool Reinitialize();
        void Process();
		void SetEnable(bool enable);
		bool GetEnable()				{ return m_Enabled; }
		void AddModule(VisionModule *module);
		void RemoveModule(VisionModule *module);

		void StartLogging();
		void StopLogging();

        void LoadINISettings(minIni* ini);
        void LoadINISettings(minIni* ini, const std::string &section);
        void SaveINISettings(minIni* ini);
        void SaveINISettings(minIni* ini, const std::string &section);
	};
}

#endif
