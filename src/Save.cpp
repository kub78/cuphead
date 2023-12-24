#include "Save.h"

Save::Save(string file_path) {
	if (!file_path.empty()) {
		this->file_path = file_path;
	}
	load_data();
}

void Save::load_data() {
	ifstream file_stream(file_path);
	file_stream >> config;
	file_stream.close();
}

int Save::operator()(string setting_dir, string setting_name) {
	load_data();
	return config[setting_dir][setting_name];
}


void Save::set(string setting_dir, string setting_name, int numb) {
	ofstream file_stream(file_path);
	config[setting_dir][setting_name] = numb;
	file_stream << config;
	file_stream.close();
}