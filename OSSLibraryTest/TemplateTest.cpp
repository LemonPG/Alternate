/*
 https://docs.microsoft.com/ja-jp/visualstudio/test/microsoft-visualstudio-testtools-cppunittestframework-api-reference?view=vs-2019#general_asserts
 Microsoft.VisualStudio.TestTools.CppUnitTestFramework API ƒŠƒtƒ@ƒŒƒ“ƒX
 */
#include "pch.h"
#include "OSSLibrary.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OSSLibraryTest
{
	TEST_CLASS(TemplateTest)
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

		TEST_METHOD(TemplateSampleTest)
		{
			Logger::WriteMessage("TemplateSampleTest.\n");

			Assert::AreEqual(123, 123, _T("This test is failed.\n"));
			OutputDebugString(_T("Output TemplateSampleTest.\n"));
		}
	};
}
