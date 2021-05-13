#define _CRT_SECURE_NO_WARNINGS

#include "Encryption21.h"

int main()
{
	char* S = new char[MAX_SYMBOLS];
	char* P = new char[MAX_SYMBOLS];

	cin.getline(S, MAX_SYMBOLS);
	cin >> P;

	cout << "RESULT: " << EncryptionObj::ENCRYPT(S, P) << endl;

	cin >> S;
	cin >> P;

	cout << "RESULT: " << EncryptionObj::DECRYPT(S, P) << endl;

	delete[] S;
	delete[] P;
}
