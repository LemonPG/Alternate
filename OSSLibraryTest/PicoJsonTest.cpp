/*
 https://docs.microsoft.com/ja-jp/visualstudio/test/microsoft-visualstudio-testtools-cppunittestframework-api-reference?view=vs-2019#general_asserts
 Microsoft.VisualStudio.TestTools.CppUnitTestFramework API リファレンス
 */
#include "pch.h"
#include "OSSLibrary.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace OSSLibraryTest
{
	TEST_CLASS(PicoJsonTest)
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

		TEST_METHOD(PicoJsonTest1)
		{
			Logger::WriteMessage("PicoJsonTest1.\n");

            std::ifstream ifs;
            ifs.open("test.json");
            if (ifs.fail())
            {
                std::cerr << "fail to read test.json" << std::endl;
                Assert::Fail(_T("test.jsonのオープンに失敗しました。"));
            }

            const std::string json(
                (std::istreambuf_iterator<char>(ifs)),
                std::istreambuf_iterator<char>());
            ifs.close();

            picojson::value val;
            const std::string error = picojson::parse(val, json);
            if (!error.empty())
            {
                std::cerr << error << std::endl;
                Assert::Fail(_T("picojson::parse()に失敗しました。"));
            }

            // @sa https://qiita.com/usagi/items/da3568d8fa61e4aafede
            /*
               picojson::valueの中身の可能性
               double           JSONの数値
               std::string      JSONの文字列
               picojson::array  JSONの配列
               picojson::object JSONのオブジェクト(=辞書)
               picojson::null   JSONのnull
             */

            try
            {
                picojson::object Root = val.get<picojson::object>();

                int Numeric = (int)Root["Numeric"].get<double>();
                std::cout << "Numeric:" << Numeric << std::endl;

                auto String = Root["String"].get<std::string>();
                std::cout << "String:" << String << std::endl;

                bool Boolean = Root["Boolean"].get<bool>();
                std::cout << "Boolean:" << std::boolalpha << Boolean << std::endl;

                std::cout << "Object:" << std::endl;
                picojson::object Object = Root["Object"].get<picojson::object>();

                double _Numeric = Object["numeric"].get<double>();
                std::cout << "  numeric:" << _Numeric << std::endl;

                auto _String = Object["string"].get<std::string>();
                std::cout << "  string:" << _String << std::endl;

                bool _Boolean = Object["boolean"].get<bool>();
                std::cout << "  boolean:" << std::boolalpha << _Boolean << std::endl;

                auto _Array1 = Object["Array1"].get<picojson::array>();
                std::cout << "  Array1:";
                for (auto item : _Array1)
                {
                    std::cout << item.get<double>() << ",";
                }
                std::cout << std::endl;

                auto _Array2 = Object["Array2"].get<picojson::array>();
                std::cout << "  Array2:";
                for (auto item : _Array2)
                {
                    std::cout << item.get<std::string>() << ",";
                }
                std::cout << std::endl;

                auto Array1 = Root["Array1"].get<picojson::array>();
                std::cout << "Array1:";
                for (auto item : Array1)
                {
                    std::cout << item.get<double>() << ",";
                }
                std::cout << std::endl;

                auto Array2 = Root["Array2"].get<picojson::array>();
                std::cout << "Array2:";
                for (auto item : Array2)
                {
                    std::cout << item.get<std::string>() << ",";

                }
                std::cout << std::endl;
            }
            catch (...)
            {
                std::cout << "catched anything." << std::endl;
                Assert::Fail(_T("JSON分析中に例外が発生しました。"));
            }
        }
	};
}
