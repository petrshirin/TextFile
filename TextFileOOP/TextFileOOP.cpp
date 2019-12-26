// TextFileOOP.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include "TextFile.h"

int main() {

	TextFile file("C:/Users/Admin/source/repos/TextFileOOP/file.txt", 0);
	TextFile file1("C:/Users/Admin/source/repos/TextFileOOP/file1.txt", 0);
	file.get_data();
	file1.get_data();
	file.sort(0);
	file1.show_data();
	std::cout << std::endl; 
	file.show_data();
	std::cout << std::endl;
	file.copy_data("C:/Users/Admin/source/repos/TextFileOOP/copyfile.txt");
	std::vector <int> cons_vect = file.conside_cols(file1, 2);
	file.make_file("C:/Users/Admin/source/repos/TextFileOOP/unicfile.txt", file1, true);
	file.make_file("C:/Users/Admin/source/repos/TextFileOOP/nonunicfile.txt", file1, false);
	
}