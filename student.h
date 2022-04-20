#include <iostream>
#include "iobuffer.h"
#include "strstream"
using namespace std;

class Student {
public:
	Student();
	Student(const char* Label, const char* idNum,
		const char* name, const char* identifier, const char* address,const char* age,  const char* wieght);
	Student(Student&);
	Student(Student&&);
	char* Key()const;
	int Unpack(IOBuffer&);
	int Pack(IOBuffer&)const;
	Student& operator =(const Student&);
	void Print(ostream&, char* label = 0)const;
	//static int InitBuffer(DelimFieldBuffer&);
	//static int InitBuffer(FixedFieldBuffer&);
	//static int InitBuffer(LengthFieldBuffer&);
	
	char Name[30]; char Identifier[30]; char idNum[30]; char Label[30]; char Age[30];
	char Weight[30]; char Address[30];

};
