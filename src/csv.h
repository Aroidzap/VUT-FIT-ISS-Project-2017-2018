#pragma once
#include <fstream>
#include <vector>
#include <string>

template<class X, class Y>
class CSV {
	std::vector<X> data_x;
	std::vector<Y> data_y;
	bool index;
public:
	CSV(const std::vector<X> & x, const std::vector<Y> & y);
	CSV(const std::vector<X> & x, const std::vector<Y> & y, bool use_index);
	bool Save(const std::string filename);
	//CSV<X, Y> & Reduce(unsigned int reduction);
};

template<class X, class Y>
inline CSV<X, Y>::CSV(const std::vector<X>& x, const std::vector<Y>& y) : data_x(x), data_y(y), index(false) {}

template<class X, class Y>
inline CSV<X, Y>::CSV(const std::vector<X>& x, const std::vector<Y>& y, bool use_index) : data_x(x), data_y(y), index(use_index) {}

template<class X, class Y>
inline bool CSV<X, Y>::Save(const std::string filename)
{
	// Open/Create file
	std::fstream file(filename, std::fstream::out);
	if (file.bad()) { return false; }

	// Save CSV
	size_t max_size = data_x.size() > data_y.size() ? data_x.size() : data_y.size();
	int val = 0;

	if (index) {
		file << "index";
		val++;
	}
	if (val) { file << ','; }
	if (data_x.size()) {
		file << "X";
		val++;
	}
	if (val) { file << ','; }
	if (data_y.size()) {
		file << "Y";
		val++;
	}
	if (val) { file << '\n'; }

	for (unsigned int i = 0; i < max_size; i++) {
		val = 0;
		if (index) {
			file << i;
			val++;
		}
		if (i < data_x.size()) {
			if (val) { file << ','; }
			file << data_x[i];
			val++;
		}
		if (i < data_y.size()) {
			if (val) { file << ','; }
			file << data_y[i];
			val++;
		}
		if (val) { file << '\n'; }
	}
	
	return true;
}

/*template<class X, class Y>
inline CSV<X, Y> & CSV<X, Y>::Reduce(unsigned int reduction)
{
	if (reduction > 1) {
		unsigned cnt = 0;
		for (unsigned int i = 0; i < data_x.size(); i += reduction){
			for (unsigned int k = 1; k < reduction; k++) {
				data_x[i] = data_x[i] + data_x[i + k];
			}
			data_x[i] = data_x[i] / reduction;
			cnt++;
		}
		for (unsigned int i = 1; i < cnt; i++) {
			data_x[i] = data_x[i * reduction];
		}
		data_x.resize(cnt);
		cnt = 0;
		for (unsigned int i = 0; i < data_y.size(); i += reduction) {
			for (unsigned int k = 1; k < reduction; k++) {
				data_y[i] = data_y[i] + data_y[i + k];
			}
			data_y[i] = data_y[i] / reduction;
			cnt++;
		}
		for (unsigned int i = 1; i < cnt; i++) {
			data_y[i] = data_y[i * reduction];
		}
		data_y.resize(cnt);
	}
	return *this;
}
*/