#pragma once

#include <nlohmann/json.hpp>

#include <fstream>
#include <iostream>
#include <string>

using json = nlohmann::json;

using namespace std;

class Save {

public:
	Save(string file_path = "");
	void load_data();
	int operator()(string setting_dir, string setting_name);
	void set(string setting_dir, string setting_name, int numb);

private:
	string file_path = "save.json";
	json config;

};
