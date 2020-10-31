/*
 https://docs.microsoft.com/ja-jp/visualstudio/test/microsoft-visualstudio-testtools-cppunittestframework-api-reference?view=vs-2019#general_asserts
 Microsoft.VisualStudio.TestTools.CppUnitTestFramework API ���t�@�����X
 */
#include "pch.h"
#include "PipelineFactoryMethod.h"
#include "TString.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace alt;

using namespace alt::FactoryMethod;

namespace MiddleLibraryTest
{
	TEST_CLASS(PipelineFactoryMethodTest)
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

		TEST_METHOD(PipelineFactoryMethodTest1)
		{
			Logger::WriteMessage("PipelineFactoryMethodTest1 Started.\n");

			PipelineFactoryMethod* factory = new PipelineFactoryMethod();

			ProductManager* manager = (ProductManager*)factory->Buildup();

			Config* config = new Config();
			bool ret = config->Load(_T(".\\Config.ini"));
			Assert::IsTrue(ret, _T("Config�t�@�C���̓ǂݍ��݂Ɏ��s���܂����B"));

			manager->Init(config);

			for (int i = 0; i < 1; i++)
			{
				manager->Start();

				Sleep(30000); // 30�b

				manager->Finish();
			}

			manager->Exit();

			Sleep(10000); // 10�b

			Logger::WriteMessage("PipelineFactoryMethodTest1 Finished.\n");
		}
	};
}
