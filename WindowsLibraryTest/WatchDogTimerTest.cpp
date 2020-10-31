/*
 https://docs.microsoft.com/ja-jp/visualstudio/test/microsoft-visualstudio-testtools-cppunittestframework-api-reference?view=vs-2019#general_asserts
 Microsoft.VisualStudio.TestTools.CppUnitTestFramework API ƒŠƒtƒ@ƒŒƒ“ƒX
 */
#include "pch.h"
#include "WatchDogTimer.h"
#include "Thread.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace WindowsLibraryTest
{
	const int count = 100;
	DWORD dwTime = 20;

	TEST_CLASS(WatchDogTimerTest)
	{
	public:
		TEST_CLASS_INITIALIZE(ClassInitialize)
		{
			Logger::WriteMessage("class initialize.\n");
		}

		TEST_CLASS_CLEANUP(ClassCleanup)
		{
			Logger::WriteMessage("class cleanup.\n");
		}

		TEST_METHOD_INITIALIZE(MethodInitialize)
		{
			Logger::WriteMessage("method initialize.\n");
		}

		TEST_METHOD_CLEANUP(MethodCleanup)
		{
			Logger::WriteMessage("method cleanup.\n");
		}

		TEST_METHOD(QueryPerformance1)
		{
			alt::QueryPerformance Q;
			TCHAR tszMsg[80];
			double dArray[count];

			for (int i = 0; i < count; i++)
			{
				Q.Start();
				Sleep(dwTime);
				Q.Stop();
				dArray[i] = Q.PastTime();
			}

			double sum = 0;
			double average = 0;
			double minValue = dwTime;
			double maxValue = dwTime;
			double sd = 0;

			for (int i = 0; i < count; i++)
			{
				sum += dArray[i];
				if (minValue > dArray[i]) minValue = dArray[i];
				if (maxValue < dArray[i]) maxValue = dArray[i];
			}
			average = sum / count;

			for (int i = 0; i < count; i++)
			{
				sd += pow(average - dArray[i], 2);
			}
			sd = pow(sd / count, 0.5);

			_stprintf_s(tszMsg, _T("interval=%d minValue=%.4f maxValue=%.4f average=%.4f sd=%.4f\n"), dwTime, minValue, maxValue, average, sd);
			Logger::WriteMessage(tszMsg);

			int outband = 0;
			for (int i = 0; i < count; i++)
			{
				double diff = dArray[i] - dwTime;
				if (-0.9 > diff || 0.9 < diff)
				{
					outband++;
					_stprintf_s(tszMsg, _T("i=%3d outband=%3d diff=%.4f\n"), i, outband, diff);
					Logger::WriteMessage(tszMsg);
				}
			}
		}

		class TimeupFunction : public alt::skeleton::ITimeup
		{
		public:
			TimeupFunction()
			{
				_dwPreviousTime = 0;
				ZeroMemory(_tszMsg, sizeof(_tszMsg));
			}

			void Timeup(LPVOID me, DWORD dwHiTime, DWORD dwLoTime)
			{
				_stprintf_s(_tszMsg, _T("--TimeupFunction::Timeup() dwHiTime=%u diff=%u\n"), dwHiTime, dwHiTime - _dwPreviousTime);
				Logger::WriteMessage(_tszMsg);
				_dwPreviousTime = dwHiTime;
			}

		private:
			DWORD _dwPreviousTime;
			TCHAR _tszMsg[80];
		};

		TEST_METHOD(WatchDogTimer1)
		{
			Logger::WriteMessage("WatchDogTimer1\n");

			timeBeginPeriod(1);

			TimeupFunction* function = new TimeupFunction();
			alt::WatchDogTimer* T = new alt::WatchDogTimer(function);

			BOOL ret1 = T->InitTimer(_T("WatchDogTimer1"));
			Assert::IsTrue(ret1);

			alt::QueryPerformance Q;

			TCHAR tszMsg[80];
			double dArray[count];
			ZeroMemory(dArray, sizeof(dArray));

			Logger::WriteMessage("Timer Start.\n");
			BOOL ret2 = T->StartTimer(dwTime);
			Assert::IsTrue(ret2);

			int iCounter = count - 1;
			while (true)
			{
				Q.Start();
				DWORD dwRet = T->WaitTimer();
				Q.Stop();

				if (dwRet == WAIT_OBJECT_0)
				{
					dArray[iCounter] = Q.PastTime();
					iCounter--;
					if (iCounter < 0) break;
				}
			}

			T->StopTimer();
			delete T;

			timeEndPeriod(1);

			double minValue = dwTime;
			double maxValue = dwTime;
			double sum = 0;
			double average = 0;
			double sd = 0;

			for (int i = 0; i < count; i++)
			{
				if (minValue > dArray[i]) minValue = dArray[i];
				if (maxValue < dArray[i]) maxValue = dArray[i];
				sum += dArray[i];
			}
			average = sum / count;

			for (int i = 0; i < count; i++)
			{
				sd += pow(average - dArray[i], 2);
			}
			sd = pow(sd / count, 0.5);

			_stprintf_s(tszMsg, _T("interval=%d minValue=%.4f maxValue=%.4f average=%.4f sd=%.4f\n"), dwTime, minValue, maxValue, average, sd);
			Logger::WriteMessage(tszMsg);

			int outband = 0;
			for (int i = 0; i < count; i++)
			{
				double diff = dArray[i] - dwTime;
				if (diff < -0.9 || 0.9 < diff)
				{
					outband++;
					_stprintf_s(tszMsg, _T("i=%3d outband=%3d diff=%.4f\n"), i, outband, diff);
					Logger::WriteMessage(tszMsg);
				}

			}

			Logger::WriteMessage("Timer Stopped.\n");
		}

		TEST_METHOD(WatchDogTimer2)
		{
			Logger::WriteMessage("WatchDogTimer2\n");

			timeBeginPeriod(1);

			alt::WatchDogTimer* T = new alt::WatchDogTimer();

			BOOL ret1 = T->InitTimer(_T("WatchDogTimer2"));
			Assert::IsTrue(ret1);

			alt::QueryPerformance Q;

			TCHAR tszMsg[80];
			double dArray[count];
			ZeroMemory(dArray, sizeof(dArray));

			Logger::WriteMessage("Timer Start.\n");
			BOOL ret2 = T->StartTimer(dwTime);
			Assert::IsTrue(ret2);

			int iCounter = count;
			while (iCounter--)
			{
				Q.Start();
				DWORD dwRet = T->WaitTimer();
				Q.Stop();

				if (dwRet == WAIT_OBJECT_0)
				{
					dArray[iCounter] = Q.PastTime();
				}
			}

			T->StopTimer();
			delete T;

			timeEndPeriod(1);

			double minValue = dwTime;
			double maxValue = dwTime;
			double sum = 0;
			double average = 0;
			double sd = 0;

			for (int i = 0; i < count; i++)
			{
				if (dArray[i] < minValue) minValue = dArray[i];
				if (dArray[i] > maxValue) maxValue = dArray[i];
				sum += dArray[i];
			}
			average = sum / count;

			for (int i = 0; i < count; i++)
			{
				sd += pow(average - dArray[i], 2);
			}
			sd = pow(sd / count, 0.5);

			_stprintf_s(tszMsg, _T("interval=%d minValue=%.4f maxValue=%.4f average=%.4f sd=%.4f\n"), dwTime, minValue, maxValue, average, sd);
			Logger::WriteMessage(tszMsg);

			int outband = 0;
			for (int i = 0; i < count; i++)
			{
				double diff = dArray[i] - dwTime;
				if (diff < -0.9 || 0.9 < diff)
				{
					outband++;
					_stprintf_s(tszMsg, _T("i=%3d outband=%3d diff=%.4f\n"), i, outband, diff);
					Logger::WriteMessage(tszMsg);
				}

			}

			Logger::WriteMessage("Timer Stopped.\n");
		}
	};
}