#pragma once
#include <iostream>
#include <cmath>

using namespace std;

const int MAX_SYMBOLS = 512;
const int MAX_CHAR = 8;
const int MAX_OBJ = 1024;

class EncryptionObj
{
private:
	char* STRING;
	char* PASSWORD;
	char BIN_STRING[MAX_SYMBOLS][MAX_CHAR];
	char BIN_PASSWORD[MAX_SYMBOLS][MAX_CHAR];
	char ENCRYPTED_STRING[MAX_SYMBOLS][MAX_CHAR];
	char ENC[MAX_SYMBOLS * MAX_CHAR];
	int COUNT;
	int COUNT_PASS;
	static EncryptionObj* OBJ_ARRAY[];
	static int OBJ_COUNT;
public:
	EncryptionObj()
	{
		STRING = new char[MAX_SYMBOLS];
		PASSWORD = new char[MAX_SYMBOLS];
		for (int i = 0; i < MAX_SYMBOLS; i++)
		{
			STRING[i] = NULL;
			PASSWORD[i] = NULL;
		}
		for (int i = 0; i < MAX_SYMBOLS; i++)
		{
			for (int j = 0; j < MAX_CHAR; j++)
			{
				BIN_STRING[i][j] = NULL;
				BIN_PASSWORD[i][j] = NULL;
			}
		}
		COUNT = 0;
		COUNT_PASS = 0;
	}
	~EncryptionObj()
	{
		// ...
	}
	static char* ENCRYPT(char* S, char* P);
	static char* DECRYPT(char* S, char* P);
	virtual void CLEAR_DATA()
	{
		STRING = new char[MAX_SYMBOLS];
		PASSWORD = new char[MAX_SYMBOLS];
		for (int i = 0; i < MAX_SYMBOLS; i++)
		{
			STRING[i] = NULL;
			PASSWORD[i] = NULL;
		}
		for (int i = 0; i < MAX_SYMBOLS; i++)
		{
			for (int j = 0; j < MAX_CHAR; j++)
			{
				BIN_STRING[i][j] = NULL;
				BIN_PASSWORD[i][j] = NULL;
			}
		}
		COUNT = 0;
		COUNT_PASS = 0;
	}
	virtual void SET_DATA(char* S, char* P)
	{
		CLEAR_DATA();
		//
		STRING = S;
		PASSWORD = P;
	}
	virtual void SET_DEC_DATA(char* S, char* P)
	{
		CLEAR_DATA();
		//
		for (int i = 0; i < MAX_SYMBOLS * MAX_CHAR; i++)
		{
			ENC[i] = S[i];
		}
		cout << ENC << endl;
		PASSWORD = P;
	}
	virtual void SET_ENCRYPTED()
	{
		int N = 0;
		for (int i = 0; i < strlen(ENC) / MAX_CHAR; i++)
		{
			for (int j = 0; j < MAX_CHAR; j++)
			{
				ENCRYPTED_STRING[i][j] = ENC[N];
				N++;
			}
			cout << ENCRYPTED_STRING[i] << endl;
		}
	}
	virtual long long DATA_BIN(char ARG)
	{
		// convert string and password to binary variables
		int ASCII = (int)ARG;
		long long binaryNumber = 0;
		int remainder, i = 1, step = 1;
		int Counter = 0;

		while (ASCII != 0)
		{
			remainder = ASCII % 2;
//			cout << "Step " << step++ << ": " << ASCII << "/2, Remainder = " << remainder << ", Quotient = " << ASCII / 2 << endl;
			ASCII /= 2;
			binaryNumber += remainder * i;
			i *= 10;
			Counter++;
		}
		return binaryNumber;
	}
	virtual int CONVERT_DECRYPTED(char* L)
	{
		// Convert decrypted array to string
		int N = 0;
		long long binaryNumber = 0;
		char CHAR;

		while (N != MAX_CHAR)
		{
			if (L[N] == '0') N++;
			else
			{
				binaryNumber += (L[N] - '0') * pow(10, MAX_CHAR - N - 1);
				N++;
			}
		}
		cout << "Binary: " << binaryNumber << endl;

		int decimalNumber = 0, i = 0, remainder;
		while (binaryNumber != 0)
		{
			remainder = binaryNumber % 10;
			binaryNumber /= 10;
			decimalNumber += remainder * pow(2, i);
			i++;
		}
		cout << "Decimal: " << decimalNumber << endl;
		return decimalNumber;
	}
	virtual void STRING_BIN(long long ARGN)
	{
		int TEMP;
		int N = MAX_CHAR - 1;

		// if a number call function BIN_NUMBER(int ARG, &BIN_STRING)
		while (ARGN != 0)
		{
			TEMP = ARGN % 10;
			BIN_STRING[COUNT][N] = TEMP + '0';
			N--;
			ARGN /= 10;
		}
		for (int i = 0; i < MAX_CHAR; i++)
			if (BIN_STRING[COUNT][i] == NULL) BIN_STRING[COUNT][i] = '0';
		cout << STRING[COUNT] << " AFTER CONVERTION " << BIN_STRING[COUNT] << endl;
	}
	virtual void PASSWORD_BIN(long long ARGN)
	{
		int TEMP;
		int N = MAX_CHAR - 1;

		// if a number call function BIN_NUMBER(int ARG, &BIN_PASSWORD)
		while (ARGN != 0)
		{
			TEMP = ARGN % 10;
			BIN_PASSWORD[COUNT_PASS][N] = TEMP + '0';
			N--;
			ARGN /= 10;
		}
		for (int i = 0; i < MAX_CHAR; i++)
			if (BIN_PASSWORD[COUNT_PASS][i] == NULL) BIN_PASSWORD[COUNT_PASS][i] = '0';
		cout << PASSWORD[COUNT_PASS] << " AFTER CONVERTION " << BIN_PASSWORD[COUNT_PASS] << endl;
	}
	virtual void BIN_NUMBER(int N)
	{
		// ...
	}
	virtual void CONVERT_DATA()
	{
		for (int i = 0; i < strlen(STRING); i++)
		{
			if (STRING[i] == ' ') STRING[i] = '_';
			STRING_BIN(DATA_BIN(STRING[i]));
			COUNT++;
		}
		for (int i = 0; i < strlen(PASSWORD); i++)
		{
			PASSWORD_BIN(DATA_BIN(PASSWORD[i]));
			COUNT_PASS++;
		}
	}
	virtual void CONVERT_PASSWORD()
	{
		for (int i = 0; i < strlen(PASSWORD); i++)
		{
			PASSWORD_BIN(DATA_BIN(PASSWORD[i]));
			COUNT_PASS++;
		}
	}
	virtual char RETURN_XOR(char ARGS, char ARGP)
	{
		if (ARGS == '0' && ARGP == '1') return '1';
		else if (ARGS == '0' && ARGP == '0') return '0';
		else if (ARGS == '1' && ARGP == '1') return '0';
		else return '1';
	}
	virtual void XOR()
	{
		// XOR
		int N;
		N = 0;
		cout << endl;
		for (int i = 0; i < strlen(STRING); i++)
		{
			for (int j = 0; j < MAX_CHAR; j++)
			{
				ENCRYPTED_STRING[i][j] = RETURN_XOR(BIN_STRING[i][j], BIN_PASSWORD[N][j]);
				cout << RETURN_XOR(BIN_STRING[i][j], BIN_PASSWORD[N][j]) << '\t';
			}
			N++;
			if (N == strlen(PASSWORD)) N = 0;
			cout << endl;
			cout << ENCRYPTED_STRING[i] << endl;
		}
	}
	virtual void DEXOR()
	{
		int N;
		N = 0;

		for (int i = 0; i < strlen(ENC) / MAX_CHAR; i++)
		{
			for (int j = 0; j < MAX_CHAR; j++)
			{
				BIN_STRING[i][j] = RETURN_XOR(ENCRYPTED_STRING[i][j], BIN_PASSWORD[N][j]);
			}
			N++;
			if (N == strlen(PASSWORD)) N = 0;
			cout << BIN_STRING[i] << '\t';
		}
		cout << endl;
	}
	virtual bool CHECK_SIZE(char *ARG)
	{
		if (strlen(ARG) > 0) return 1;
		else return false;
	}
	virtual void CHECK_DATA()
	{
		if (!CHECK_SIZE(STRING) || !CHECK_SIZE(PASSWORD))
		{
			cout << "EXCEPTION CAUGHT. NO DATA PICKED. PLEASE, USE SET_DATA(*S, *P) FUNCTION TO SET DATA." << endl;
			exit(10); // code for data failure
		}
	}
	virtual char* OBJ_ENCRYPT(char* S, char* P)
	{
		// ...
		SET_DATA(S, P);
		CHECK_DATA(); // check if data is set
		CONVERT_DATA(); // convert data from characters to bin;
		cout << endl;
		XOR();

//		cout << endl;
/*		for (int i = 0; i < strlen(STRING); i++)
		{
			for (int j = 0; j < MAX_CHAR; j++)
				cout << ENCRYPTED_STRING[i][j];
			cout << '\t';
		}
		cout << endl; */

		return *ENCRYPTED_STRING;
	}
	virtual char* OBJ_DECRYPT(char* S, char* P)
	{
		// ...
		SET_DEC_DATA(S, P);
		SET_ENCRYPTED();
		CONVERT_PASSWORD();
		DEXOR();

//		cout << endl;
		for (int i = 0; i < strlen(ENC) / MAX_CHAR; i++)
		{
			STRING[i] = CONVERT_DECRYPTED(BIN_STRING[i]);
			if (STRING[i] == '_') STRING[i] = ' ';
//			cout << STRING[i] << endl;
		}

		return STRING;
	}
};

int EncryptionObj::OBJ_COUNT;
EncryptionObj* EncryptionObj::OBJ_ARRAY[MAX_OBJ];

char* EncryptionObj::ENCRYPT(char* S, char* P)
{
	OBJ_ARRAY[OBJ_COUNT] = new EncryptionObj;
	OBJ_COUNT++;
	return OBJ_ARRAY[OBJ_COUNT-1]->OBJ_ENCRYPT(S, P);
}
char* EncryptionObj::DECRYPT(char* S, char* P)
{
	OBJ_ARRAY[OBJ_COUNT] = new EncryptionObj;
	OBJ_COUNT++;
	return OBJ_ARRAY[OBJ_COUNT-1]->OBJ_DECRYPT(S, P);
}