#include "student.h"
Student::Student() {
	Label[0] = 0;
	idNum[0] = 0;
	Name[0] = 0;
	Identifier[0] = 0;
	Address[0] = 0;
	Age[0] = 0;
	Weight[0] = 0;
}

Student::Student(const char* label, const char* idNum,
	const char* name, const char* identifier, const char* address, const char* age, const char* weight) {
	strcpy_s(Label, label);
	strcpy_s(this->idNum, idNum);
	strcpy_s(Name, name);
	strcpy_s(Identifier, identifier);
	strcpy_s(Address, address);
	strcpy_s(Age, age);
	strcpy_s(Weight, weight);
}
Student::Student(Student& s) {

	strcpy_s(Label, s.Label);
	strcpy_s(this->idNum, s.idNum);
	strcpy_s(Name, s.Name);
	strcpy_s(Identifier, s.Identifier);
	strcpy_s(Address, s.Address);
	strcpy_s(Age, s.Age);
	strcpy_s(Weight, s.Weight);
}

Student::Student(Student&& s) {
	cout << "dd" << endl;

}

char* Student::Key()const {
	ostrstream key;
	key << Label << idNum << endl;
	return key.str();
}

int Student::Pack(IOBuffer& Buffer) const {
	int numBytes;
	Buffer.Clear();
	numBytes = Buffer.Pack(idNum);
	if (numBytes == -1) return FALSE;
	numBytes = Buffer.Pack(Label);
	if (numBytes == -1) return FALSE;
	numBytes = Buffer.Pack(Name);
	if (numBytes == -1) return FALSE;
	numBytes = Buffer.Pack(Identifier);
	if (numBytes == -1) return FALSE;
	numBytes = Buffer.Pack(Address);
	if (numBytes == -1) return FALSE;
	numBytes = Buffer.Pack(Age);
	if (numBytes == -1) return FALSE;
	numBytes = Buffer.Pack(Weight);
	if (numBytes == -1) return FALSE;

}

Student& Student::operator=(const Student& s)
{
	strcpy_s(Label, s.Label);
	strcpy_s(this->idNum, s.idNum);
	strcpy_s(Name, s.Name);
	strcpy_s(Identifier, s.Identifier);
	strcpy_s(Address, s.Address);
	strcpy_s(Age, s.Age);
	strcpy_s(Weight, s.Weight);
	// TODO: 여기에 return 문을 삽입합니다.
	return *this;
}

int Student::Unpack(IOBuffer& Buffer)
{// unpack with maximum size, and add null termination to strings
	int numBytes;
	numBytes = Buffer.Unpack(idNum, 29);
	if (numBytes == -1) return FALSE;
	idNum[numBytes] = 0;
	numBytes = Buffer.Unpack(Name, 29);
	if (numBytes == -1) return FALSE;
	Name[numBytes] = 0;
	numBytes = Buffer.Unpack(Identifier, 29);
	if (numBytes == -1) return FALSE;
	Identifier[numBytes] = 0;
	numBytes = Buffer.Unpack(Address, 29);
	if (numBytes == -1) return FALSE;
	Address[numBytes] = 0;
	numBytes = Buffer.Unpack(Label,29);
	if (numBytes == -1) return FALSE;
	Label[numBytes] = 0;
	return TRUE;
}

void Student::Print(ostream& stream, char* label) const
{
	stream << Label << '|' << idNum << '|' << Name << '|'
		<< Identifier << '|' << Address << '|' << Age << '|' << Weight;

}

//
//int Student::InitBuffer(FixedFieldBuffer& Buffer)
//// initialize a FixedFieldBuffer to be used for Persons
//{
//	int result;
//	result = Buffer.AddField(10); // IdNum[7]
//	result = result && Buffer.AddField(15); // Title[30]
//	result = result && Buffer.AddField(10); // Composer[30]
//	result = result && Buffer.AddField(5); // Artist[30]
//	result = result && Buffer.AddField(5); // Label[7]
//	result = result && Buffer.AddField(10);
//	result = result && Buffer.AddField(10);
//	return result;
//}
////char IdNum[7]; char Title[30]; char Composer[30];char Artist[30]; char Label[7];
//int Student::InitBuffer(DelimFieldBuffer& Buffer)
//// initialize a DelimFieldBuffer to be used for Persons
//{
//	return TRUE;
//}
//
//int Student::InitBuffer(LengthFieldBuffer& Buffer)
//// initialize a LengthFieldBuffer to be used for Persons
//{
//	return TRUE;
//}

