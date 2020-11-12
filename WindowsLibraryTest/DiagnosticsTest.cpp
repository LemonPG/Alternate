/*
 https://docs.microsoft.com/ja-jp/visualstudio/test/microsoft-visualstudio-testtools-cppunittestframework-api-reference?view=vs-2019#general_asserts
 Microsoft.VisualStudio.TestTools.CppUnitTestFramework API ���t�@�����X
 */
#include "pch.h"
#include "Diagnostics.h"
#include "File.h"
#include "FileUtility.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#define TEST_FILE _T(".\\DiskIOTest.txt")

namespace WindowsLibraryTest
{
	TEST_CLASS(DiagnosticsTest)
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

		void MemoryStatusPrint(PROCESS_MEMORY_COUNTERS& pmc)
		{
			TCHAR tszBuf[MAX_PATH];

			Logger::WriteMessage(_T("\n---------------------------------------------------------------\n"));

			_stprintf_s(tszBuf, _T("�ő像�[�L���O�Z�b�g(�������g�p��)__________________ %10llu\n"), pmc.PeakWorkingSetSize);
			Logger::WriteMessage(tszBuf);

			_stprintf_s(tszBuf, _T("���݃��[�L���O�Z�b�g(�ő僁�����g�p��)______________ %10llu\n"), pmc.WorkingSetSize);
			Logger::WriteMessage(tszBuf);

			_stprintf_s(tszBuf, _T("�ő�y�[�W�v�[���̎g�p�T�C�Y(�y�[�W�v�[��)__________ %10llu\n"), pmc.QuotaPeakPagedPoolUsage);
			Logger::WriteMessage(tszBuf);

			_stprintf_s(tszBuf, _T("�ő��y�[�W�v�[���̎g�p�T�C�Y(��y�[�W�v�[��)______ %10llu\n"), pmc.QuotaPeakNonPagedPoolUsage);
			Logger::WriteMessage(tszBuf);

			_stprintf_s(tszBuf, _T("���݃y�[�W���O�t�@�C���̎g�p�T�C�Y(���z�������T�C�Y) %10llu\n"), pmc.PagefileUsage);
			Logger::WriteMessage(tszBuf);

			_stprintf_s(tszBuf, _T("�y�[�W�E�t�H�[���g��________________________________ %10u\n"), pmc.PageFaultCount);
			Logger::WriteMessage(tszBuf);
		}

		//
		// @sa https://ameblo.jp/sgl00044/entry-12463939983.html
		//
		TEST_METHOD(MemoryDiagnosticsTest)
		{
			Logger::WriteMessage("MemoryDiagnosticsTest\n");

			alt::Diagnostics diag;
			BOOL ret;

			PROCESS_MEMORY_COUNTERS pmc;
			ret = diag.GetProcessMemory(pmc);
			Assert::IsTrue(ret);
			MemoryStatusPrint(pmc);

			BYTE* pbyBuf = new BYTE[1024 * 1024 * 1024]; // 1GB
			ret = diag.GetProcessMemory(pmc);
			Assert::IsTrue(ret);
			MemoryStatusPrint(pmc);

			ZeroMemory(pbyBuf, 1024 * 1024 * 1024);
			ret = diag.GetProcessMemory(pmc);
			Assert::IsTrue(ret);
			MemoryStatusPrint(pmc);

			delete[] pbyBuf;
			ret = diag.GetProcessMemory(pmc);
			Assert::IsTrue(ret);
			MemoryStatusPrint(pmc);
		}

		TEST_METHOD(DiskDiagnosticsTest)
		{
			Logger::WriteMessage("DiskDiagnosticsTest\n");

			alt::Diagnostics diag;
			IO_COUNTERS ioCounters;
			BOOL ret;

			ret = diag.GetProcessIO(ioCounters);
			Assert::IsTrue(ret);
			DiskStatusPrint(ioCounters);

			alt::File* pFile = new alt::File();
			ret = pFile->Create(TEST_FILE, GENERIC_ALL, FILE_SHARE_READ, CREATE_ALWAYS);
			Assert::IsTrue(ret);

			BYTE byTest[1024];
			ZeroMemory(byTest, 1024);
			pFile->Write(byTest, 1024);

			ret = diag.GetProcessIO(ioCounters);
			Assert::IsTrue(ret);
			DiskStatusPrint(ioCounters);

			pFile->SetPointer(FILE_BEGIN);
			pFile->Read(byTest, 1024);

			ret = diag.GetProcessIO(ioCounters);
			Assert::IsTrue(ret);
			DiskStatusPrint(ioCounters);

			pFile->Close();

			delete pFile;

			alt::FileUtility::Delete(TEST_FILE);
		}

		void DiskStatusPrint(IO_COUNTERS& ioCounters)
		{
			TCHAR tszBuf[MAX_PATH];

			Logger::WriteMessage(_T("\n---------------------------------------------------------------\n"));

			_stprintf_s(tszBuf, _T("I/O�ǂݎ��________ %10llu\n"), ioCounters.ReadOperationCount);
			Logger::WriteMessage(tszBuf);

			_stprintf_s(tszBuf, _T("I/O��������________ %10llu\n"), ioCounters.WriteOperationCount);
			Logger::WriteMessage(tszBuf);

			_stprintf_s(tszBuf, _T("I/O���̑�__________ %10llu\n"), ioCounters.OtherOperationCount);
			Logger::WriteMessage(tszBuf);

			_stprintf_s(tszBuf, _T("I/O�ǂݎ��o�C�g�� %10llu\n"), ioCounters.ReadTransferCount);
			Logger::WriteMessage(tszBuf);

			_stprintf_s(tszBuf, _T("I/O�������݃o�C�g�� %10llu\n"), ioCounters.WriteTransferCount);
			Logger::WriteMessage(tszBuf);

			_stprintf_s(tszBuf, _T("I/O���̑��o�C�g��__ %10llu\n"), ioCounters.OtherTransferCount);
			Logger::WriteMessage(tszBuf);
		}

		TEST_METHOD(NetworkDiagnosticsTest)
		{
			Logger::WriteMessage("NetworkDiagnosticsTest\n");

			alt::Diagnostics diag;
			MIB_IPSTATS mibIPStats;
			BOOL ret;

			ret = diag.GetIpStatistics(mibIPStats);
			Assert::IsTrue(ret);
			NetworkStatusPrint(mibIPStats);
		}

		void NetworkStatusPrint(MIB_IPSTATS& mibIPStats)
		{
			TCHAR tszBuf[MAX_PATH];

			Logger::WriteMessage(_T("\n---------------------------------------------------------------\n"));

			_stprintf_s(tszBuf, _T("dwForwarding :     %ld\n"), mibIPStats.dwForwarding);
			Logger::WriteMessage(tszBuf);
			_stprintf_s(tszBuf, _T("dwDefaultTTL:      %ld\n"), mibIPStats.dwDefaultTTL);
			Logger::WriteMessage(tszBuf);
			_stprintf_s(tszBuf, _T("dwInReceives:      %ld\n"), mibIPStats.dwInReceives);
			Logger::WriteMessage(tszBuf);
			_stprintf_s(tszBuf, _T("dwInHdrErrors:     %ld\n"), mibIPStats.dwInHdrErrors);
			Logger::WriteMessage(tszBuf);
			_stprintf_s(tszBuf, _T("dwInAddrErrors:    %ld\n"), mibIPStats.dwInAddrErrors);
			Logger::WriteMessage(tszBuf);
			_stprintf_s(tszBuf, _T("dwForwDatagrams:   %ld\n"), mibIPStats.dwForwDatagrams);
			Logger::WriteMessage(tszBuf);
			_stprintf_s(tszBuf, _T("dwInUnknownProtos: %ld\n"), mibIPStats.dwInUnknownProtos);
			Logger::WriteMessage(tszBuf);
			_stprintf_s(tszBuf, _T("dwInDiscards:      %ld\n"), mibIPStats.dwInDiscards);
			Logger::WriteMessage(tszBuf);
			_stprintf_s(tszBuf, _T("dwInDelivers:      %ld\n"), mibIPStats.dwInDelivers);
			Logger::WriteMessage(tszBuf);
			_stprintf_s(tszBuf, _T("dwOutRequests:     %ld\n"), mibIPStats.dwOutRequests);
			Logger::WriteMessage(tszBuf);
			_stprintf_s(tszBuf, _T("dwRoutingDiscards: %ld\n"), mibIPStats.dwRoutingDiscards);
			Logger::WriteMessage(tszBuf);
			_stprintf_s(tszBuf, _T("dwOutDiscards:     %ld\n"), mibIPStats.dwOutDiscards);
			Logger::WriteMessage(tszBuf);
			_stprintf_s(tszBuf, _T("dwOutNoRoutes:     %ld\n"), mibIPStats.dwOutNoRoutes);
			Logger::WriteMessage(tszBuf);
			_stprintf_s(tszBuf, _T("dwReasmTimeout:    %ld\n"), mibIPStats.dwReasmTimeout);
			Logger::WriteMessage(tszBuf);
			_stprintf_s(tszBuf, _T("dwReasmReqds:      %ld\n"), mibIPStats.dwReasmReqds);
			Logger::WriteMessage(tszBuf);
			_stprintf_s(tszBuf, _T("dwReasmOks:        %ld\n"), mibIPStats.dwReasmOks);
			Logger::WriteMessage(tszBuf);
			_stprintf_s(tszBuf, _T("dwReasmFails:      %ld\n"), mibIPStats.dwReasmFails);
			Logger::WriteMessage(tszBuf);
			_stprintf_s(tszBuf, _T("dwFragOks:         %ld\n"), mibIPStats.dwFragOks);
			Logger::WriteMessage(tszBuf);
			_stprintf_s(tszBuf, _T("dwFragFails:       %ld\n"), mibIPStats.dwFragFails);
			Logger::WriteMessage(tszBuf);
			_stprintf_s(tszBuf, _T("dwFragCreates:     %ld\n"), mibIPStats.dwFragCreates);
			Logger::WriteMessage(tszBuf);
			_stprintf_s(tszBuf, _T("dwNumIf:           %ld\n"), mibIPStats.dwNumIf);
			Logger::WriteMessage(tszBuf);
			_stprintf_s(tszBuf, _T("dwNumAddr:         %ld\n"), mibIPStats.dwNumAddr);
			Logger::WriteMessage(tszBuf);
			_stprintf_s(tszBuf, _T("dwNumRoutes:       %ld\n"), mibIPStats.dwNumRoutes);
			Logger::WriteMessage(tszBuf);
		}
	};
}
