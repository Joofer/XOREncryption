#define _CRT_SECURE_NO_WARNINGS

//#include "Encryption.h"
#include "Encryption21.h"

int main()
{
	char* S = new char[MAX_SYMBOLS];
	char* P = new char[MAX_SYMBOLS];

	cin.getline(S, MAX_SYMBOLS);
//	strcpy(S, "HELLO ITS ME");
//	cin >> S;
	cin >> P;

//	Obj.SET_DATA(S, P);
	cout << "RESULT: " << EncryptionObj::ENCRYPT(S, P) << endl;

//	Obj.~EncryptionObj();

	// 00011010000001110000000000010010000000110000011100000001000110100001110100010100

	cin >> S;
	cin >> P;

//	Obj.SET_DEC_DATA(S, P);
	cout << "RESULT: " << EncryptionObj::DECRYPT(S, P) << endl;

	delete[] S;
	delete[] P;
//    EncryptionObj EncObj; 
//    EncObj.SetData("Test String", "Pass");
//    EncObj.Encrypt();
//    EncObj.GetEncString();
//    EncObj.Decrypt("00101010000000001010011000000000110011100000000000101110000000000000000000000000110010100000000000101110000000000100111000000000100101100000000001110110000000001110011000000000", "Pass");
//    EncObj.GetDecString();
}
