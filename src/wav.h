#pragma once
#include <string>
#include <vector>

struct WAVHeader {
	char const_RIFF[4]; // "RIFF"
	uint32_t overallSize : 32;
	char const_WAVE[4]; // "WAVE"
	char const_fmt_[4]; // "fmt "
	uint32_t formatDataLength : 32; // 16
	uint16_t typeOfFormat : 16; // 1 == PCM
	uint16_t channels : 16; // 1
	uint32_t samplingFrequency : 32;
	uint32_t byteRate : 32; // samplingFrequency * bitsPerSample * channels / 8
	uint16_t blockAlign : 16; // bitsPerSample * channels / 8
	uint16_t bitsPerSample : 16; // 16
	char const_data[4]; // "data"
	uint32_t sizeOfData : 32;
};

class WAV {
private:
	WAVHeader header;
	unsigned int samples;
	std::vector<double> data;
public:
	WAV();
	WAV(const std::vector<double> & data);
	WAV(const std::vector<double> & data, const WAVHeader & header);
	const WAVHeader & GetHeader() const;
	bool Load(const std::string filename);
	bool Save(const std::string filename);
	operator std::vector<double>() const { return this->data; }
	double SamplingFrequency();
	int Samples();
};