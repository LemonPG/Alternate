/*
 https://docs.microsoft.com/ja-jp/visualstudio/test/microsoft-visualstudio-testtools-cppunittestframework-api-reference?view=vs-2019#general_asserts
 Microsoft.VisualStudio.TestTools.CppUnitTestFramework API リファレンス
 */
#include "pch.h"
#include "TaskTemplate.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace alt;

namespace MiddleLibraryTest
{
	TEST_CLASS(TaskTemplateTest)
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

		TEST_METHOD(SimpleCallTest)
		{
			Logger::WriteMessage("SimpleCallTest\n");

			Function functions[3];
			functions[0] = []()
			{
				Logger::WriteMessage("functions[0]() called.\n");
				return true;
			};
			functions[1] = []()
			{
				Logger::WriteMessage("functions[1]() called.\n");
				return true;
			};
			functions[2] = []()
			{
				Logger::WriteMessage("functions[2]() called.\n");
				return true;
			};

			TaskTemplate taskTemplate;
			bool ret = taskTemplate.DoAction(functions);
			Assert::IsTrue(ret);
		}

		TEST_METHOD(PreProcessFailedTest)
		{
			Logger::WriteMessage("SimpleCallTest\n");

			Function functions[3];
			functions[0] = []()
			{
				Logger::WriteMessage("functions[0]() called.\n");
				return false;
			};
			functions[1] = []()
			{
				Logger::WriteMessage("functions[1]() called.\n");
				return true;
			};
			functions[2] = []()
			{
				Logger::WriteMessage("functions[2]() called.\n");
				return true;
			};

			TaskTemplate taskTemplate;
			bool ret = taskTemplate.DoAction(functions);
			Assert::IsFalse(ret);
			Assert::IsTrue(TaskStatus::preProcess == taskTemplate.GetStatus());
		}

		TEST_METHOD(DoProcessExceptionTest)
		{
			Logger::WriteMessage("SimpleCallTest\n");

			Function functions[3];
			functions[0] = []()
			{
				Logger::WriteMessage("functions[0]() called.\n");
				return true;
			};
			functions[1] = []()
			{
				Logger::WriteMessage("functions[1]() called.\n");

				throw _T("functions[1]() exception rized.");

				return true;
			};
			functions[2] = []()
			{
				Logger::WriteMessage("functions[2]() called.\n");
				return true;
			};

			TaskTemplate taskTemplate;
			auto exceptionTest = [&] { taskTemplate.DoAction(functions); };
			Assert::ExpectException<LPTSTR>(exceptionTest, _T("PTSTR例外が正しく発生しませんでした。"));
			Assert::IsTrue(TaskStatus::doProcess == taskTemplate.GetStatus());
		}
	};
}
