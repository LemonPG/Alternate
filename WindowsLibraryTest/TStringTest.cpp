/*
 https://docs.microsoft.com/ja-jp/visualstudio/test/microsoft-visualstudio-testtools-cppunittestframework-api-reference?view=vs-2019#general_asserts
 Microsoft.VisualStudio.TestTools.CppUnitTestFramework API ���t�@�����X
 */
#include "pch.h"
#include "TString.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace WindowsLibraryTest
{
	TEST_CLASS(TStringTest)
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

		TEST_METHOD(ConstractorTest1)
		{
			alt::TString string1;
			Assert::IsNull(string1.Ctr());
			Assert::IsNull(string1.Ptr());

			alt::TString string2(_T("ABCDE"));
			Assert::AreEqual(_T("ABCDE"), string2.Ctr());
			Assert::AreEqual(_T("ABCDE"), string2.Ptr());

			alt::TString string3(string1);
			Assert::IsNull(string3.Ctr());
			Assert::IsNull(string3.Ptr());

			alt::TString string4(string2);
			Assert::AreEqual(_T("ABCDE"), string4.Ctr());
			Assert::AreEqual(_T("ABCDE"), string4.Ptr());

			alt::TString string5(10 + sizeof(TCHAR));
			lstrcpy(string5.Ptr(), _T("1234567890"));
			Assert::AreEqual(_T("1234567890"), string5.Ctr());
			Assert::AreEqual(_T("1234567890"), string5.Ptr());
		}

		TEST_METHOD(ConstractorTest2)
		{
			alt::TString* string1 = new alt::TString();
			Assert::IsNull(string1->Ctr());
			Assert::IsNull(string1->Ptr());

			alt::TString* string2 = new alt::TString(_T("ABCDE"));
			Assert::AreEqual(_T("ABCDE"), string2->Ctr());
			Assert::AreEqual(_T("ABCDE"), string2->Ptr());

			alt::TString* string3 = new alt::TString(*string1);
			Assert::IsNull(string3->Ctr());
			Assert::IsNull(string3->Ptr());

			alt::TString* string4 = new alt::TString(*string2);
			Assert::AreEqual(_T("ABCDE"), string4->Ctr());
			Assert::AreEqual(_T("ABCDE"), string4->Ptr());

			alt::TString* string5 = new alt::TString(10 + sizeof(TCHAR));
			lstrcpy(string5->Ptr(), _T("1234567890"));
			Assert::AreEqual(_T("1234567890"), string5->Ctr());
			Assert::AreEqual(_T("1234567890"), string5->Ptr());
		}

		TEST_METHOD(SizeTest)
		{
			alt::TString string1(_T("ABCDE"));
			Assert::AreEqual(lstrlen(_T("ABCDE")), string1.Len());
			Assert::AreEqual<int>((lstrlen(_T("ABCDE")) * sizeof(TCHAR)), string1.Byte());

			alt::TString string2(MAX_PATH);
			Assert::AreEqual(0, string2.Len());
			Assert::AreEqual(0, string2.Byte());

			alt::TString string3;
			Assert::AreEqual(0, string2.Len());
			Assert::AreEqual(0, string2.Byte());
		}

		TEST_METHOD(OperatorTest1)
		{
			alt::TString string1(_T("ABCDE"));
			alt::TString string2(_T("ABCDE"));
			Assert::IsTrue(string1 == string2);
			Assert::IsTrue(string1 == _T("ABCDE"));

			alt::TString string3(_T("ABCDE"));
			alt::TString string4(_T("abcde"));
			Assert::IsTrue(string3 != string4);
			Assert::IsTrue(string4 != _T("ABCDE"));
		}

		TEST_METHOD(OperatorTest2)
		{
			alt::TString string1(_T("ABCDE"));
			alt::TString string2;

			string2 = string1;
			Assert::AreEqual(_T("ABCDE"), string2.Ctr());

			string2 = _T("12345");
			Assert::AreEqual(_T("12345"), string2.Ctr());
		}

		TEST_METHOD(OperatorTest3)
		{
			alt::TString string1;

			string1 << _T("123") << _T("ABC");
			Assert::AreEqual(_T("123ABC"), string1.Ctr());

			alt::TString stringA(_T("ABC"));
			alt::TString stringB(_T("123"));
			alt::TString string2;

			string2 << stringA << stringB;
			Assert::AreEqual(_T("ABC123"), string2.Ctr());

			alt::TString string3;
			string3 << 123 << 456;
			Assert::AreEqual(_T("123456"), string3.Ctr());
		}

		TEST_METHOD(OperatorTest4)
		{
			alt::TString string0(_T("123"));
			alt::TString string00 = string0 + _T("ABC");
			Assert::AreEqual(_T("123ABC"), string00.Ctr());
			Assert::AreEqual(_T("123"), string0.Ctr());

			alt::TString string1;
			alt::TString string11;

			string11 = string1 + _T("123") + _T("ABC");
			Assert::AreEqual(_T("123ABC"), string11.Ctr());
			Assert::AreEqual(nullptr, string1.Ctr());

			alt::TString string2(_T("XYZ"));
			alt::TString string22;

			string22 = string2 + _T("123") + _T("ABC");
			Assert::AreEqual(_T("XYZ123ABC"), string22.Ctr());
			Assert::AreEqual(_T("XYZ"), string2.Ctr());

			alt::TString stringA(_T("ABC"));
			alt::TString stringB(_T("123"));
			alt::TString string3;
			alt::TString string33;

			string33 = string3 + stringA + stringB;
			Assert::AreEqual(_T("ABC123"), string33.Ctr());
			Assert::AreEqual(_T("ABC"), stringA.Ctr());
			Assert::AreEqual(_T("123"), stringB.Ctr());
			Assert::AreEqual(nullptr, string3.Ctr());

			alt::TString string4(_T("XYZ"));
			alt::TString string44;

			string44 = string4 + stringA + stringB;
			Assert::AreEqual(_T("XYZABC123"), string44.Ctr());
			Assert::AreEqual(_T("XYZ"), string4.Ctr());
			Assert::AreEqual(_T("ABC"), stringA.Ctr());
			Assert::AreEqual(_T("123"), stringB.Ctr());

		}

		TEST_METHOD(OperatorTest5)
		{
			alt::TString string1;
			alt::TString string2(_T("ABC"));
			alt::TString string3(_T("123"));

			string1 += string2;
			Assert::AreEqual(_T("ABC"), string1.Ctr());

			string3 += string2;
			Assert::AreEqual(_T("123ABC"), string3.Ctr());

			alt::TString string4;
			string4 += _T("ABC");
			Assert::AreEqual(_T("ABC"), string4.Ctr());

			alt::TString string5(_T("123"));
			string5 += _T("ABC");
			Assert::AreEqual(_T("123ABC"), string5.Ptr());
		}

		TEST_METHOD(ArrayOperatorTest)
		{
			alt::TString string = _T("ABC123");
			TCHAR c1 = string[1]; // B
			TCHAR c3 = string[3]; // 1
			TCHAR c5 = string[5]; // 3
			TCHAR c7 = string[7]; // \0

			Assert::IsTrue('B' == c1);
			Assert::IsTrue('1' == c3);
			Assert::IsTrue('3' == c5);
			Assert::IsTrue('\0' == c7);
		}

		TEST_METHOD(TrimLeftTest)
		{
			Logger::WriteMessage("TrimLeft\n");

			alt::TString string = _T("    1234    5678    ");
			string.TrimLeft();
			Assert::AreEqual(_T("1234    5678    "), string.Ptr());
		}

		TEST_METHOD(TrimRightTest)
		{
			Logger::WriteMessage("TrimRight\n");

			alt::TString string = _T("    1234    5678    ");
			string.TrimRight();
			Assert::AreEqual(_T("    1234    5678"), string.Ptr());
		}

		TEST_METHOD(TrimTest1)
		{
			Logger::WriteMessage("Trim1\n");

			alt::TString string = _T("    1234    5678    ");
			string.Trim();
			Assert::AreEqual(_T("1234    5678"), string.Ptr());
		}

		TEST_METHOD(TrimTest2)
		{
			Logger::WriteMessage("Trim2\n");

			alt::TString string = _T("    1234    5678    ");
			string.TrimLeft().TrimRight();
			Assert::AreEqual(_T("1234    5678"), string.Ptr());
		}

		TEST_METHOD(SubstringTest)
		{
			Logger::WriteMessage("SubstringTest\n");

			//                        01234567890123456789012345
			alt::TString string = _T("ABCDEFGHIJKLMNOPQRSTUVWXYZ");

			alt::TString str1 = string.Substring(0, 3);
			Assert::IsTrue(_T("ABCDEFGHIJKLMNOPQRSTUVWXYZ"), string.Ptr());
			Assert::IsTrue(alt::TString(_T("ABC")) == str1, str1.Ctr());

			alt::TString str2 = string.Substring(5, 3);
			Assert::IsTrue(_T("ABCDEFGHIJKLMNOPQRSTUVWXYZ"), string.Ptr());
			Assert::IsTrue(alt::TString(_T("FGH")) == str2, str2.Ctr());

			alt::TString str3 = string.Substring(23, 3);
			Assert::IsTrue(_T("ABCDEFGHIJKLMNOPQRSTUVWXYZ"), string.Ptr());
			Assert::IsTrue(alt::TString(_T("XYZ")) == str3, str3.Ctr());

			alt::TString str4 = string.Substring(24, 3);
			Assert::IsTrue(_T("ABCDEFGHIJKLMNOPQRSTUVWXYZ"), string.Ptr());
			Assert::IsTrue(alt::TString() == str4, str4.Ctr());

			alt::TString str5 = string.Substring(25);
			Assert::IsTrue(_T("ABCDEFGHIJKLMNOPQRSTUVWXYZ"), string.Ptr());
			Assert::AreEqual(_T("Z"), str5.Ptr());

			alt::TString str6 = string.Substring(23);
			Assert::IsTrue(_T("ABCDEFGHIJKLMNOPQRSTUVWXYZ"), string.Ptr());
			Assert::AreEqual(_T("XYZ"), str6.Ptr());

			alt::TString str7 = string.Substring(0, 0);
			Assert::AreEqual(nullptr, str7.Ctr());
		}

		TEST_METHOD(SplitTest1)
		{
			Logger::WriteMessage("SplitTest1\n");

			alt::TString string = _T("123/456;789,abc/def");
			alt::skeleton::Array<alt::TString> response = string.Split(_T(",;/"));

			Assert::AreEqual(_T("123"), response[0]->Ptr());
			Assert::AreEqual(_T("456"), response[1]->Ptr());
			Assert::AreEqual(_T("789"), response[2]->Ptr());
			Assert::AreEqual(_T("abc"), response[3]->Ptr());
			Assert::AreEqual(_T("def"), response[4]->Ptr());
			Assert::IsTrue(response[5] == nullptr);
		}

		TEST_METHOD(FindTest1)
		{
			Logger::WriteMessage("FindTest1\n");

			//                        01234567890123456
			alt::TString string = _T("1234567890ABCDEFG");

			int t1 = string.Find(_T("5678"));
			Assert::AreEqual(4, t1);

			int t2 = string.Find(_T("1"));
			Assert::AreEqual(0, t2);

			int t3 = string.Find(_T("123"));
			Assert::AreEqual(0, t3);

			int t4 = string.Find(_T("G"));
			Assert::AreEqual(16, t4);

			int t5 = string.Find(_T("ABCD"));
			Assert::AreEqual(10, t5);
		}

		TEST_METHOD(FindTest2)
		{
			Logger::WriteMessage("FindTest2\n");

			//                        01234567890123456
			alt::TString string = _T("ABABCBCABABCBCABC");

			int t1 = string.Find(_T("ABCD"));
			Assert::AreEqual(-1, t1);

			int t2 = string.Find(_T("ABC"));
			Assert::AreEqual(2, t2);

			int t3 = string.Find(_T("ABC"), 2);
			Assert::AreEqual(2, t3);

			int t4 = string.Find(_T("ABC"), 3);
			Assert::AreEqual(9, t4);

			int t5 = string.Find(_T("ABCD"), 7);
			Assert::AreEqual(-1, t5);
		}

		TEST_METHOD(FindTest3)
		{
			Logger::WriteMessage("FindTest3\n");

			//                        0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9
			alt::TString string = _T("���Q�l�ܘZ�������b��������ȍM�h�p�");

			int t1 = string.Find(_T("������"));
			Assert::AreEqual(6, t1);

			int t2 = string.Find(_T("�b������"));
			Assert::AreEqual(10, t2);

			int t3 = string.Find(_T("����"));
			Assert::AreEqual(-1, t3);
		}

		TEST_METHOD(FormatTest)
		{
			Logger::WriteMessage("FormatTest\n");

			alt::TString formatString;

			formatString.Format(_T(" TEST %d/%d "), 1, 2).Trim();

			Assert::AreEqual(_T("TEST 1/2"), formatString.Ctr());
		}

		TEST_METHOD(ReplaceTest1)
		{
			Logger::WriteMessage("ReplaceTest1\n");

			alt::TString baseString(_T("This text is sample."));

			alt::TString replaceBefore(_T("text"));
			alt::TString replaceAfter(_T("contents"));

			alt::TString replaced = baseString.Replace(replaceBefore, replaceAfter);

			Assert::AreEqual(_T("This contents is sample."), replaced.Ctr());
		}

		TEST_METHOD(ReplaceTest2)
		{
			Logger::WriteMessage("ReplaceTest2\n");

			alt::TString baseString(_T("This text is sample."));

			alt::TString replaceBefore(_T("This"));
			alt::TString replaceAfter(_T("That"));

			alt::TString replaced = baseString.Replace(replaceBefore, replaceAfter);

			Assert::AreEqual(_T("That text is sample."), replaced.Ctr());
		}

		TEST_METHOD(ReplaceTest3)
		{
			Logger::WriteMessage("ReplaceTest3\n");

			alt::TString baseString(_T("This text is sample.\r\n"));

			alt::TString replaceBefore(_T("\r\n"));
			alt::TString replaceAfter(_T(""));

			alt::TString replaced = baseString.Replace(replaceBefore, replaceAfter);

			Assert::AreEqual(_T("This text is sample."), replaced.Ctr());
		}

		TEST_METHOD(ReplaceAllTest)
		{
			Logger::WriteMessage("ReplaceAllTest\n");

			alt::TString baseString(_T("ABC 0ABC0 1ABCD1 2ABC"));

			alt::TString replaceBefore(_T("ABC"));
			alt::TString replaceAfter(_T("x"));

			alt::TString replaced = baseString.ReplaceAll(replaceBefore, replaceAfter);

			Assert::AreEqual(_T("x 0x0 1xD1 2x"), replaced.Ctr());
		}

		TEST_METHOD(FromSJISTest)
		{
			Logger::WriteMessage("FromSJISTest\n");

			LPCSTR lpcszSJIS = "�����SJIS�ō쐬���ꂽ������ł��B\n���Q�l�ܘZ�������\n";

			alt::TString convert;
			Assert::IsTrue(convert.FromSJIS(lpcszSJIS));
			Assert::AreEqual(31, convert.Len());
			Assert::AreEqual(62, convert.Byte());
			Logger::WriteMessage(convert.Ctr());
		}

		TEST_METHOD(ToSJISTest)
		{
			Logger::WriteMessage("ToSJISTest\n");

			LPCWSTR lpcwszUnicode = L"�����Unicode�ō쐬���ꂽ������ł��B\n���Q�l�ܘZ�������\n";

			alt::TString output(lpcwszUnicode);
			DWORD dwLen = output.Byte() + sizeof(TCHAR);
			LPSTR lpszBuf = new CHAR[dwLen];
			int ret = output.ToSJIS(lpszBuf, dwLen);
			Assert::IsTrue(ret > 0);
			Logger::WriteMessage(lpszBuf);
			delete[] lpszBuf;
		}
	};
}
