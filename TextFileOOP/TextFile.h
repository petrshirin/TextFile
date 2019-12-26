#pragma once

#include <fstream>
#include <iostream>
#include <vector>

class TextFile
{
	std::string file_indent;
	int type;
	std::ifstream in;
	std::ofstream out;
	void calculate_field();
	std::vector <int*> quicksort(std::vector <int*> mas, int first, int last, int field_to_sort);
public:
	TextFile();
	TextFile& operator=(const TextFile& right);
	std::vector <int*> data_arr;
	int count_fields;
	void write_file();
	void show_data();
	std::vector <int> conside_cols(TextFile& right, int col);
	void make_file(std::string new_path, TextFile& other, bool type_making);
	void copy_data(std::string file_path);
	TextFile(char* path, int type);
	TextFile(std::string path, int type);
	~TextFile();
	void sort(int field_to_sort, bool reverse=false);
	void get_data();
};

