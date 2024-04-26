#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sys/stat.h>
#include <unistd.h>
using namespace std;

void cp()
{
	cout << endl;
	cout << "Enter the name of the file to be copied \n > ";
	string filename;
	cin >> filename;

	cout << "Enter the name of the file copy: \n > ";
	string newFilename;
	cin >> newFilename;
	//ошибка
	if (filename == newFilename) {
		cout << "There is an error in the name of the copy. The name of the copy must not match the original" << endl;
		return;
	}
	ifstream fin;
	size_t bufsize = 4;
	char* buf = new char[bufsize];
	fin.open(filename, ios::binary);
	if (fin.is_open()) {
		ofstream fout;
		fout.open(newFilename, ios::binary);
		while (!fin.eof()) {
			fin.read(buf, bufsize);
			if (fin.gcount()) fout.write(buf, fin.gcount());
		}
		cout << " > The copying was successful!" << endl;
		delete[] buf;
		fin.close();
		fout.close();
	}
	else {
		cout << "Copying failed" << endl;
		return;
	}
}

void moveFile() {
	cout << endl;
	cout << "Enter the first path: \n > ";
	string st_original;
	cin >> st_original;

	cout << "Enter the second path: \n > ";
	string st_duplicate;
	cin >> st_duplicate;

	if (rename(st_original.c_str(), st_duplicate.c_str()) != 0) {
		cerr << "Error moving file." << endl;
	}
	else {
		cout << "File moved successfully." << endl;
	}
}

//010100111
//000100000
//000000000
string Permssions(mode_t mode) {

	string message = "User_";

	if (mode & S_IRUSR)
		message += "r";
	else
		message += "_";
	if (mode & S_IWUSR)
		message += "w";
	else
		message += "_";
	if (mode & S_IXUSR)
		message += "x";
	else
		message += "_";

	message += "_Group_";

	if (mode & S_IRGRP)
		message += "r";
	else
		message += "_";
	if (mode & S_IWGRP)
		message += "w";
	else
		message += "_";
	if (mode & S_IXGRP)
		message += "x";
	else
		message += "_";
	message += "_Other_";
	if (mode & S_IROTH)
		message += "r";
	else
		message += "_";
	if (mode & S_IWOTH)
		message += "w";
	else
		message += "_";
	if (mode & S_IXOTH)
		message += "x";
	else
		message += "_";

	return message;
}

void fileInfo() {
	cout << "Enter the file name: \n > ";
	string st_original;
	cin >> st_original;

	struct stat fileStat;
	if (stat(st_original.c_str(), &fileStat) == 0) {
		cout << "File permissions: " << Permssions(fileStat.st_mode) << endl;
		cout << "File size: " << fileStat.st_size << " bytes" << endl;
		cout << "Last modification time: " << ctime(&fileStat.st_mtime);
	}
	else {
		cerr << "Error getting file info.\n";
	}
}

void changePermissions() {
	cout << endl;
	cout << "Enter the file name: \n > ";
	string st_original;
	cin >> st_original;

	cout << "Enter the access right \n > ";
	string str_mod;
	cin >> str_mod;

	mode_t mod;
	int index = -1;

	vector<string> mods = { "x", "w", "wx", "r", "rx", "rw", "rwx" };
	for (int i = 0; i < mods.size(); i++) {
		if (str_mod == mods[i]) {
			index = i;
			break;
		}
		else {
			index = -1;
		}
	}


	switch (index) {
	case (0): //x
		mod = S_IXUSR;
		break;

	case (1): //w
		mod = S_IWUSR;
		break;

	case (2): //wx
		mod = S_IWUSR | S_IXUSR;
		break;

	case (3): //r
		mod = S_IRUSR;
		break;

	case (4): //rx
		mod = S_IRUSR | S_IXUSR;
		break;

	case (5): //rw
		mod = S_IRUSR | S_IWUSR;
		break;

	case (6): //rwx
		mod = S_IRWXU;
		break;

	}

	if (chmod(st_original.c_str(), mod) != 0) {
		cerr << "Error changing file permissions.\n";
	}
	else {
		cout << "File permissions changed successfully.\n";
	}
}

void helpscreen() {
	cout << "============================================" << endl;	
	cout << "Actions:" <<endl;
	cout << "============================================" << endl;
	cout << "copy\n"
	<< "move\n"
	<< "info\n"
	<< "chmod" << endl;
	cout << "============================================" << endl;
}

int main(int i_argc, char* ch_arr_argv[])
{
	int index = -1;
	vector<string> key = { "help","info","copy", "move", "chmod" };

	for (int i = 0; i < key.size(); i++) {
		if (ch_arr_argv[1] == key[i]) {
			index = i;
			break;
		}
		else {
			index = -1;
		}
	}
	switch (index) {

	case (-1):
		cout << "Mistake. Invalid key" << endl;
		break;

	case (0):
		helpscreen();
		break;

	case (1):
		fileInfo();
		break;

	case (2):
		cp();
		break;

	case (3):
		moveFile();
		break;

	case (4):
		changePermissions();
		break;
	}

	return 0;

}
