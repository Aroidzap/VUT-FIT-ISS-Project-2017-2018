#pragma once
#include <fstream>
#include <vector>
#include <string>
#include <tuple>

template<class T>
class CSV {
	const char horizontal_delimiter = ',';
	const char vertical_delimiter = '\n';
	std::vector<std::tuple<std::string, std::vector<T>>> data;
	bool index;
public:
	CSV(const std::vector<std::tuple<std::string, std::vector<T>>> & data);
	bool Save(const std::string filename);
};

template<class T>
inline CSV<T>::CSV(const std::vector<std::tuple<std::string, std::vector<T>>>& data) : data(data) {}

template<class T>
inline bool CSV<T>::Save(const std::string filename)
{
	// Open/Create file
	std::fstream file(filename, std::fstream::out);
	if (file.bad()) { return false; }

	// Save CSV
	size_t max_size = 0;
	size_t columns = data.size();
	for (auto &it : data) {
		size_t v = std::get<1>(it).size();
		if (v > max_size) {
			max_size = v;
		}
	}
	for (size_t j = 0; j < columns; j++) {
		if (j != 0) { file << horizontal_delimiter;}
		file << std::get<0>(data[j]); // Names
	}
	file << vertical_delimiter;
	for (size_t i = 0; i < max_size; i++) {
		for (size_t j = 0; j < columns; j++) {
			if (j != 0) { file << horizontal_delimiter; }
			if (i < std::get<1>(data[j]).size()) {
				file << std::get<1>(data[j])[i]; // Values
			}
		}
		file << vertical_delimiter;
	}	
	return true;
}