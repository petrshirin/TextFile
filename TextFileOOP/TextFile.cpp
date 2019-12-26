#include "pch.h"
#include "TextFile.h"
#include <string>

TextFile::TextFile()
{

}

bool compare_arrs(int* arr1, int* arr2, int len1, int len2) {
	int len;
	bool is_same = true;
	if (len1 < len2)
		len = len1;
	else
		len = len2;
	for (int i = 0; i < len; i++) {
		if (arr1[i] != arr2[i])
			return !is_same;
	}
	return is_same;
}

TextFile::TextFile(std::string path, int _type)
{
	file_indent = path;
	type = _type;
	if (type == 0) {
		in.open(path);
		calculate_field();
	}
	else
		out.open(path);
}

TextFile::TextFile(char* path, int _type)
{	
	file_indent = path;
	type = _type;
	if (type == 1) {
		in.open(path);
		calculate_field();
	}
	else
		out.open(path);
}

void TextFile::calculate_field() {
	std::string row;
	std::getline(in, row, '\n');
	int count = 1;
	for (int i = 0; i < row.length(); i++) {
		if ((row[i] == ' ') || (row[i] == '\t'))
			count += 1;
	}
	count_fields = count;
	in.seekg(0, std::ios::beg);
}

void TextFile::get_data() {
	int* row;
	while (true)
	{
		row = new int[count_fields];
		for (int i = 0; i < count_fields; i++)
			in >> row[i];
		if (!in.eof())
			data_arr.push_back(row);
		else
			return;
	}
}

void TextFile::sort(int field_to_sort, bool reverse) {
	std::vector <int*> *data_ptr = new std::vector <int*>(data_arr.size());
	if (!reverse)
		quicksort(data_arr, 0, data_arr.size() - 1, field_to_sort);
	else
		quicksort(data_arr, data_arr.size() - 1, 0, field_to_sort);

}

std::vector <int*> TextFile::quicksort(std::vector <int*> mas, int first, int last, int field_to_sort)
{
	int mid;
	std::vector <int*> count;
	count.push_back(data_arr[0]);
	count[0] = new int[count_fields];
	int f = first, l = last;
	mid = mas[(f + l) / 2][field_to_sort];
	do
	{
		while (mas[f][field_to_sort] < mid)
			f++;
		while (mas[l][field_to_sort] > mid)
			l--;
		if (f <= l)
		{
			count[0] = mas[f];
			mas[f] = mas[l];
			mas[l] = count[0];
			f++;
			l--;
		}
	} while (f < l);
	if (first < l) 
		mas = quicksort(mas, first, l, field_to_sort);
	if (f < last) 
		mas = quicksort(mas, f, last, field_to_sort);
	data_arr = mas;
	return mas;
}

void TextFile::show_data() {
	for (int i = 0; i < data_arr.size(); i++) {
		for (int j = 0; j < count_fields; j++) {
			std::cout << data_arr[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void TextFile::write_file() {
	if (type == 0)
		throw "Error file open on read";
	for (int i = 0; i < data_arr.size(); i++) {
		for (int j = 0; j < count_fields; j++) {
			out << data_arr[i][j] << "\t";
		}
		out << "\n";
	}
}

TextFile& TextFile::operator=(const TextFile& right) {
	data_arr = right.data_arr;
	count_fields = right.count_fields;
	return *this;
}

std::vector <int> TextFile::conside_cols(TextFile& right, int col) {
	int len;
	std::vector <int> vect;
	if (right.count_fields > count_fields)
		len = data_arr.size();
	else
		len = right.data_arr.size();
	for (int i = 0; i < len; i++) {
		vect.push_back(data_arr[i][col] + right.data_arr[i][col]);
	}
	return vect;
}

void TextFile::make_file(std::string new_path, TextFile& other, bool unic) {
	TextFile new_file(new_path, 1);
	new_file.count_fields = count_fields;
	sort(0);
	other.sort(0);
	new_file.data_arr = data_arr;
	for (int i = 0; i < other.data_arr.size(); i++)
		new_file.data_arr.push_back(other.data_arr[i]);
	new_file.sort(0);
	int j = 1;
	int i = 0;
	bool is_same;
	while (i != new_file.data_arr.size() - 2){
		j = 1;
		is_same = false;
		if (i + j == new_file.data_arr.size())
			break;
		while (compare_arrs(new_file.data_arr[i], new_file.data_arr[i + j],
			count_fields, count_fields)) {
			j++;
			is_same = true;
			if (i + j == new_file.data_arr.size()) {
				j--;
				break;
			}
				

		}

		if ((unic) && (is_same)) {
			for (j; j > 0; j--) {
				new_file.data_arr.erase(new_file.data_arr.begin() + i);
			}
		}
		else
			if (j == 1) {
				new_file.data_arr.erase(new_file.data_arr.begin() + i);
			}
		i++;
	}
	new_file.sort(0);
	new_file.write_file();
	//bool unic_row = true;
	//for (int i = 0; i < data_arr.size(); i++) {
	//	for (int j = 0; j < other.data_arr.size(); j++) {
	//		if (data_arr[i][0] <= other.data_arr[j][0]) {
	//			if (compare_arrs(data_arr[i], data_arr[j], count_fields, other.count_fields)) {
	//				unic_row = false;
	//				break;
	//			}
	//				

	//		}
	//		else
	//			break;
	//	}
	//	if (unic) {
	//		if (unic_row)
	//			new_file.data_arr.push_back(data_arr[i]);
	//	}
	//	else
	//		if (!unic_row)
	//			new_file.data_arr.push_back(data_arr[i]);
	//}
}

void TextFile::copy_data(std::string file_path_to) {
	std::ofstream out_tmp(file_path_to, std::ios::app);
	for (int i = 0; i < data_arr.size(); i++) {
		for (int j = 0; j < count_fields; j++) {
			out_tmp << data_arr[i][j] << "\t";
		}
		out_tmp << "\n";
	}
	out_tmp << "\0";
	out_tmp.close();
}

TextFile::~TextFile()
{
	if (type != 0) {
		out << "\0";
		out.close();
	}
	else
		in.close();
}
