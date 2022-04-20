// F.12 fixlen.cpp Code for class FixedLengthBuffer

#include "fixlen.h"
#include "length.h"
#include <string.h>
#include <iostream>
using namespace std;
//class FixedLengthBuffer

// public members

FixedLengthBuffer::FixedLengthBuffer(int recordSize)
// construct with a maximum of maxFields
	: IOBuffer(recordSize)
{
	Init(recordSize);
}

void FixedLengthBuffer::Clear()
// clear fields from buffer
{
	IOBuffer::Clear();
	Buffer[0] = 0;
	Packing = TRUE;
}

int FixedLengthBuffer::Read(istream& stream)
// write the number of bytes in the buffer field definitions
{
	int recaddr = stream.tellg(); stream.clear();
	Clear();
	Packing = FALSE;
	stream.read(Buffer, BufferSize);
	if (!stream.good()) { stream.clear(); return recaddr; }
	return recaddr;
}


int FixedLengthBuffer::Write(ostream& stream) const
// read the number of bytes in the buffer field definitions
// return the location of the record in the file
{
	int recaddr = stream.tellp();
	stream.write(Buffer, BufferSize);
	if (!stream.good()) return -1;
	return recaddr;
}

static const char* headerStr = "Fixed";
static const int headerStrSize = strlen(headerStr);

int FixedLengthBuffer::ReadHeader(istream& stream)
// read the header and check for consistency
// see WriteHeader for header record structure
{
	//char str[headerStrSize+1];//visual studio 지원하지 않음
	char str[6];
	int recordSize;
	int result;
	// read the IOBuffer header
	result = IOBuffer::ReadHeader(stream);
	if (result < 0) return -1;
	// read the string "Fixed"
	stream.read(str, headerStrSize);
	if (!stream.good()) return -1;
	if (strncmp(str, headerStr, headerStrSize) != 0) return -1;
	stream.read((char*)&recordSize, sizeof(recordSize));
	if (Initialized) // check header for consistency
	{
		if (recordSize != BufferSize) return -1;
	}
	// else initialize the buffer from the header
	ChangeRecordSize(recordSize);
	return stream.tellg();
}

int FixedLengthBuffer::WriteHeader(ostream& stream) const
// write a buffer header to the beginning of the stream
// A header consists of the 
//	IOBUFFER header	
//	FIXED			5 bytes
//	record size		2 bytes
{
	int result;
	if (!Initialized) return -1; // cannot write unitialized buffer
	// write the parent (IOBuffer) header
	result = IOBuffer::WriteHeader(stream);
	if (!result) return -1;
	// write the string "Fixed"
	stream.write(headerStr, headerStrSize);
	if (!stream.good()) return -1;
	// write the record size
	stream.write((char*)&BufferSize, sizeof(BufferSize));
	if (!stream.good()) return -1;
	return stream.tellp();
}

void FixedLengthBuffer::Print(ostream& stream) const
{
	IOBuffer::Print(stream);
	stream << "  FixedLengthBuffer :: Print()::Fixed ";
}

int FixedLengthBuffer::Init(int recordSize)
// construct with a maximum of maxFields
{
	Clear();
	BufferSize = recordSize;
	return 1;
}

int FixedLengthBuffer::ChangeRecordSize(int recordSize)
// construct with a maximum of maxFields
{
	BufferSize = recordSize;
	return 1;
}
