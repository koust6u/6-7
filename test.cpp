//testind.cc - TextindexedFile 사용 실습
#include "textind.h"
#include "buffile.h"
#include "recordng.h"
#include "indfile.h"
#include "student.h"
ostream& operator<<(ostream& stream, Student& s) {
	stream << "Label: " << s.Label << endl;
	stream << "ID: " << s.idNum << endl;
	stream << "Name: " << s.Name << endl;
	stream << "Identifier: " << s.Identifier << endl;
	stream << "Address: " << s.Address << endl;
	stream << "Age: " << s.Age << endl;
	stream << "Weight: " << s.Weight << endl;
	return stream;
}

istream& operator>>(istream& stream, Student& s) {

	cout << "Enter Label: ";
	stream.getline(s.Label, 29);
	cout << "Enter ID: ";
	stream.getline(s.idNum, 29);
	cout << "Enter Name: ";
	stream.getline(s.Name, 29);
	cout << "Enter Identifer: ";
	stream.getline(s.Identifier, 29);
	cout << "Address: ";
	stream.getline(s.Address, 29);
	cout << "Age: ";
	stream.getline(s.Age, 29);
	cout << "Weight: ";
	stream.getline(s.Weight, 29);

	return stream;
}
int main(void)
{// first argument is the file name for the data file
	int result;

	TextIndex RecIndex(10);
	DelimFieldBuffer Buffer; // create a buffer
	TextIndexedFile<Student> IndFile(Buffer, 12, 10);
	//TextIndexedFile<RecType>::TextIndexedFile(IOBuffer & buffer, int keySize, int maxKeys)
	result = IndFile.Create("indfile", ios::out);
	if (!result)
	{
		cout << "Unable to open indfile " << result << endl;
		return 0;
	}
	int recaddr;
	//write records
	Student* stable[10], foundRecord;
	Student s;
	cout << "----------------입력란--------------" << endl;;
	for (int i = 0; i < 3; i++) {
		cout << "------------------------------" << endl;
		cin >> s;
		stable[i] = new Student(s);


	}
	/*R[0] = new Recording("LON", "2312", "Romeo and Juliet", "Prokofiev", "Maazel");
	R[1] = new Recording("RCA", "2626", "Quartet in C Sharp Minor", "Beethoven", "Julliard");
	R[2] = new Recording("WAR", "23699", "Touchstone", "Corea", "Corea");
	R[3] = new Recording("ANG", "3795", "Symphony No. 9", "Beethoven", "Giulini");
	R[4] = new Recording("COL", "38358", "Nebraska", "Springsteen", "Springsteen");
	R[5] = new Recording("DG", "18807", "Symphony No. 9", "Beethoven", "Karajan");
	R[6] = new Recording("MER", "75016", "Coq d'or Suite", "Rimsky-Korsakov", "Leinsdorf");
	R[7] = new Recording("COL", "31809", "Symphony No. 9", "Dvorak", "Bernstein");
	R[8] = new Recording("DG", "139201", "Violin Concerto", "Beethoven", "Ferras");
	R[9] = new Recording("FF", "245", "Good News", "Sweet Honey in the Rock", "Sweet Honey in the Rock");*/
	for (int i = 0; i < 3; i++)
	{
		recaddr = IndFile.Append(*stable[i]);
		cout << "IndFile R[" << i << "] at recaddr " << recaddr << endl;
	}
	cout << "----------------출력란----------------" << endl;
	cout << "print Record" << endl;
	for (int i = 0; i < 3; i++) {
		cout << "---------------------------------" << endl;
		cout << *(stable[i]);
	}
	;
	cout << "Enter find Label: ";
	char findLabel[10];
	cin >> findLabel;
	cout << "Enter find key: ";
	char findKey[10];
	cin >> findKey;
	for (int j = 0; j < 3; j++) {
		if (!(strcmp((*stable[j]).Label, findLabel))) {
			if (!(strcmp((*stable[j]).idNum, findKey))) {
				cout << "----------키 값으로 찾은 내용---------" << endl;
				cout << *stable[j];
				break;
			}
			cout << "키의 내용이 없습니다.";
		}
		
	}
	//const char* searchKey = "DG139201";
		//IndFile.Read(searchKey, foundRecord);
		//foundRecord.Print(cout);
		//IndFile.Close();
		//system("pause");
	return 1;
}


