// Beep_Generator.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
using namespace std;
using namespace sounds_h;
int sounds[7][12] = {
	{ 33,35,37,39,41,44,46,49,52,55,58,62 },
	{ 65,69,73,78,82,87,92,98,104,110,117,123 },
	{ 131,139,147,156,165,175,185,196,208,220,233,247 },
	{ 262,277,294,311,329,349,370,392,415,440,466,494 },
	{ 523,554,587,622,659,698,740,784,831,880,932,988 },
	{ 1047,1109,1175,1245,1319,1397,1480,1568,1661,1760,1865,1976 },
	{ 2093,2217,2349,2489,2637,2794,2960,3135,3322,3520,3729,3951 }
};

int main(int argc, char *argv[])
{
	if (argc<2) {
		cout << "Error: No Input File! " << endl;
		system("pause>nul");
		return 0;
	}
	ifstream fin(argv[1]);
	string output_name;
	int fnote_length;
	fin >> output_name >> fnote_length;
	ofstream fout(output_name + ".txt");
	string note_type, sound_type;
	int height;
	while (fin >> note_type) {
		if (note_type.substr(0, 2) == "//") {
			continue;
		}
		fin >> sound_type;
		if (sound_type == "br") {
			fout << "Sleep(" << identify_and_get_sum(fnote_length, note_type) << ");" << endl;
			cout << "Identified break note! " << endl;
			continue;
		}
		fin >> height;
		int drmf = get_note_id(sound_type);
		if (drmf == -1) {
			cout << "Error: Invaild Note! " << endl;
			continue;
		}
		int sum = identify_and_get_sum(fnote_length, note_type);
		if (sum <= 0) {
			cout << "Error: Time Can't Be Negative! " << endl;
			continue;
		}
		fout << "Beep(" << sounds[height][drmf] << "," << sum << ");" << endl;
		cout << "Identified " << note_type << " note! " << endl;
	}
	cout << "Finish! " << endl;
	system("pause>nul");
	return 0;
}

