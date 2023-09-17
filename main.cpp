#include <iostream>
#include <fstream>
#include <thread>

using namespace std;

int inv_hex(int num) {
	if (num<0) num += 256;
	return (num%16*16+num/16);
}

void crypt(const char *filename, int *pos, int length, ifstream* file) {
	
	char* buffer = new char[length];
	
	file->read(buffer, length);
	
	char* res = new char[length];

	for (*pos=0; *pos<length; *pos = *pos + 1) res[*pos] = inv_hex(buffer[*pos]);
	
	ofstream outfile (filename, ios::binary);
	outfile.write(res, length);	
}

int main(int argc, char* argv[]) {

	ifstream file (argv[1], ios::binary);
	
	if (!file.is_open()) cout<<"INPUT FILE INVALID";

	file.seekg(0, file.end);
    int length = file.tellg();
    if (length>2147483647) {
		cout<<"FILE TOO BIG "<<length<<" B EXCEDES THE 2147483647 B LIMIT";
		return 0;
	}
	file.seekg(0, file.beg);
	
	int pos = 0;
	
	thread th1(crypt, argv[1], &pos, length, &file);
	while (pos<length) cout<<"\r"<<(float)pos/length*100<<"          ";
	cout<<"\r"<<(float)pos/length*100<<"          ";
	th1.join();
}
