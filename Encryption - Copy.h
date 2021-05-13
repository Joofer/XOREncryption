#pragma once
#include <iostream>
#include <cstring>
//#include <vector>
//#include <algorithm>

using namespace std;

const int MAXSB = 512;
const int MAXSBENC = 16;
const int MAXINSTR = MAXSB * MAXSBENC;
//const int RU_ru = 33;
//const int EN_en = 26;

class EncryptionObj {
private:
	char String[MAXSB];
	unsigned short EncString[MAXSB][MAXSBENC];
	char InEncString[MAXINSTR];
//	vector<char> Str;
//	vector<char>::iterator StrIter;
	char TempStr[MAXSB][MAXSBENC];
	char DecString[MAXSB];
	char Password[MAXSB];
	unsigned short EncPass[MAXSB][MAXSBENC];
//	char AlphabetRU[RU_ru][MAXSBENC];
//	char AlphabetEN[EN_en][MAXSBENC];
	int Temp[MAXSBENC];
	unsigned int WordCount;
public:
	EncryptionObj()
	{
		char TString[] = "T";
		char TPassword[] = "T";
		strcpy_s(String, TString);
		strcpy_s(Password, TPassword);
	}
	EncryptionObj(string S, string P)
	{
		strcpy_s(String, S.c_str());
		strcpy_s(Password, P.c_str());
	}
	void SetData(string S, string P)
	{
		strcpy_s(String, S.c_str());
		strcpy_s(Password, P.c_str());
	}
	int C_XOR(int Char1, int Char2)
	{
		if (Char1 == 0)
		{
			if (Char2 == 1) return 1;
			else return 0;
		}
		if (Char1 == 1)
		{
			if (Char2 == 0) return 1;
			else return 0;
		}
	}
	void GetBin(int N)
	{
		int i = 0;
		for (int i = 0; i < MAXSBENC; i++) Temp[i] = 0;
		while (N > 0)
		{
			Temp[i] = N % 2;
			N = N / 2;
			i++;
		}
		//
//		cout << "Temp: " << N << ": ";
//		for (int i = 0; i < MAXSBENC; i++)
//		{
//			cout << Temp[i];
//		}
//		cout << endl;
		//
	}
	int GetASCII(char S[MAXSBENC])
	{
		int N = (int)S;
		long dec = 0;
		long rem;
		long base = 1;
		//
		while (N > 0)
		{
			rem = N % 10;
			dec = dec + rem * base;
			base = base * 2;
			N = N / 10;
		}
		return dec;
	}
	void ConvertString()
	{
		int TempASCII;
		for (int i = 0; i < strlen(String); i++)
		{
			TempASCII = (int)String[i];
			//
//			cout << "TempASCII: " << TempASCII << endl;
			//
			if (String[i] != ' ')
			{
				GetBin(TempASCII);
				for (int j = 0; j < MAXSBENC; j++)
				{
					EncString[i][j] = Temp[j];
//					cout << EncString[i][j] << " <-> " << Temp[j] << endl;
				}
//				cout << "EncString[i]: " << EncString[i] << endl;
			}
			else
				for (int j = 0; j < MAXSBENC; j++)
					EncString[i][j] = 0;
		}
	}
	void ConvertPassword()
	{
		int TempASCII;
		for (int i = 0; i < strlen(Password); i++)
		{
			TempASCII = (int)Password[i];
			//
//			cout << "TempASCII: " << TempASCII << endl;
			//
			if (Password[i] != ' ')
			{
				GetBin(TempASCII);
				for (int j = 0; j < MAXSBENC; j++)
				{
					EncPass[i][j] = Temp[j];
					cout << EncPass[i][j];
//					cout << EncPass[i][j] << " <-> " << Temp[j] << endl;
				}
				cout << '\t';
//				cout << "EncPass[i]: " << EncPass[i] << endl;
			}
			else
			{
				for (int j = 0; j < MAXSBENC; j++)
				{
					EncPass[i][j] = 0;
					cout << EncPass[i][j];
				}
				cout << '\t';
			}
		}
		cout << endl;
	}
	void ConvertEncString()
	{
		int n = 0;
		WordCount = 0;
		// ...
		for (int i = 0; i < strlen(InEncString)/MAXSBENC; i++)
		{
			for (int j = 0; j < MAXSBENC; j++)
			{
				TempStr[i][j] = InEncString[n];
				n++;
			}
			if (n == strlen(InEncString)) break;
			WordCount++;
		}
		cout << endl;
	}
	int GetNumber(char C)
	{
		if (C == '0') return 0;
		else return 1;
	}
	void Encrypt()
	{
		this->ConvertString();
		this->ConvertPassword();
		int k = 0;
		cout << endl;
		for (int i = 0; i < strlen(String); i++)
		{
			for (int j = 0; j < MAXSBENC; j++)
			{
				cout << "EncString[i][j]: " << EncString[i][j] << "; EncPass[k][j]: " << EncPass[k][j] << "; Return: ";
				if (k < strlen(Password))
					EncString[i][j] = C_XOR(EncString[i][j], EncPass[k][j]);
				else
				{
					k = 0;
					EncString[i][j] = C_XOR(EncString[i][j], EncPass[k][j]);
				}
				cout << EncString[i][j] << endl;
			}
			k++;
		}
		cout << endl;
	}
	void Decrypt(string S, string P)
	{
		char TempNumber[MAXSBENC];
		int m = 0;
		int k = 0;
		int TempASCII;
		strcpy_s(InEncString, S.c_str());
		strcpy_s(Password, P.c_str());
		//
		this->ConvertEncString(); // From InEncString to TempStr
		this->ConvertPassword(); // From Password to EncPass
		//
		for (int i = 0; i < WordCount; i++)
		{
			for (int j = 0; j < MAXSBENC; j++)
			{
				EncString[i][j] = GetNumber(TempStr[i][j]);
				cout << EncString[i][j];
			}
			cout << endl;
			// Decode
			// Number
//			TempASCII = this->GetASCII(TempNumber);
			// Symbol
		}
		// Decoding string
		cout << endl;
		for (int i = 0; i < WordCount; i++)
		{
			for (int j = 0; j < MAXSBENC; j++)
			{
				if (k < strlen(Password))
					EncString[i][j] = C_XOR(EncString[i][j], EncPass[k][j]);
				else
				{
					k = 0;
					EncString[i][j] = C_XOR(EncString[i][j], EncPass[k][j]);
				}
				cout << EncString[i][j];
			}
			cout << '\t';
			k++;
		}
	}
	void GetEncString()
	{
		cout << "ENCRYPTED STRING: " << endl;
		for (int i = 0; i < strlen(String); i++)
		{
			for (int j = 0; j < MAXSBENC; j++)
			{
				cout << EncString[i][j];
			}
			cout << '\t';
		}
		cout << endl;
	}
	void GetDecString()
	{
		cout << "DECRYPTED STRING: " << String << endl;
	}
};