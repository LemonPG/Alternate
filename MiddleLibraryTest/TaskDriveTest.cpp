/*
 https://docs.microsoft.com/ja-jp/visualstudio/test/microsoft-visualstudio-testtools-cppunittestframework-api-reference?view=vs-2019#general_asserts
 Microsoft.VisualStudio.TestTools.CppUnitTestFramework API ƒŠƒtƒ@ƒŒƒ“ƒX
 */
#include "pch.h"
#include "TaskDrive.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace alt;

namespace alt
{
	class TestTask : public ITaskTemplate
	{
	public:
		TestTask() {};
		virtual ~TestTask() {};

		bool PreProcess()
		{
			Logger::WriteMessage("TestTask::PreProcess()\n");
			return true;
		};

		bool DoProcess()
		{
			Logger::WriteMessage("TestTask::DoProcess()\n");
			return true;
		};

		bool PostProcess()
		{
			Logger::WriteMessage("TestTask::PostProcess()\n");
			return true;
		}
	};
}

namespace MiddleLibraryTest
{
	TEST_CLASS(TaskDriveTest)
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

		TEST_METHOD(TaskDriveTest1)
		{
			Logger::WriteMessage("TaskTestDrive1\n");

			TestTask testTask;
			TaskDrive taskDrive(&testTask);

			bool ret1 = taskDrive.Action();
			Assert::IsTrue(ret1);
		}
	};
}
