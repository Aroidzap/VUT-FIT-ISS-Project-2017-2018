#include "wav.h"
#include <fstream>
#include <iostream>

WAV::WAV() : header{ { 'R','I','F','F' }, 36, { 'W','A','V','E' }, { 'f','m','t',' ' }, 16, 1, 1, 16000, 32000, 2, 16, { 'd','a','t','a' }, 0 } {}
WAV::WAV(const std::vector<float> & data) : data(data), header{ { 'R','I','F','F' }, 36,{ 'W','A','V','E' },{ 'f','m','t',' ' }, 16, 1, 1, 16000, 32000, 2, 16,{ 'd','a','t','a' }, 0 } {
	this->header.sizeOfData = data.size();
	this->header.overallSize += this->header.sizeOfData;
}

bool CheckHeader(WAVHeader &h) 
{
	if (h.const_RIFF[0] != 'R' || h.const_WAVE[0] != 'W' ||
		h.const_RIFF[1] != 'I' || h.const_WAVE[1] != 'A' ||
		h.const_RIFF[2] != 'F' || h.const_WAVE[2] != 'V' ||
		h.const_RIFF[3] != 'F' || h.const_WAVE[3] != 'E' ||
		h.const_fmt_[0] != 'f' || h.const_data[0] != 'd' ||
		h.const_fmt_[1] != 'm' || h.const_data[1] != 'a' ||
		h.const_fmt_[2] != 't' || h.const_data[2] != 't' ||
		h.const_fmt_[3] != ' ' || h.const_data[3] != 'a' ||
		h.formatDataLength != 16 || h.overallSize != (h.sizeOfData + 36)) {
		std::cerr << "Invalid WAV file!"; return false;
	}
	if (h.typeOfFormat != 1 /* PCM */) {
		std::cerr << "Only PCM WAV files are supported!"; return false;
	}
	if (h.channels != 1) {
		std::cerr << "Only one channel is supported!"; return false;
	}
	if (h.bitsPerSample != 16) {
		std::cerr << "Only 16 bits per sample are supported!"; return false;
	}
	if (h.sizeOfData % (h.channels * h.bitsPerSample / 8) != 0) {
		std::cerr << "WAV data are corrupted!"; return false; 
	}
	return true;
};

bool WAV::Load(const std::string filename)
{
	// Open file
	std::fstream file(filename, std::fstream::in | std::fstream::binary);
	
	// Load header
	if (sizeof(this->header) != 44) { std::cerr << "Implementation error!"; return false; }
	file.read(reinterpret_cast<char *>(&this->header), sizeof(this->header));

	// Check header
	if (!CheckHeader(this->header)) { return false; }

	// Load data
	this->samples = this->header.sizeOfData / sizeof(int16_t);
	int16_t *raw_data = new int16_t[this->samples];
	file.read(reinterpret_cast<char *>(raw_data), this->header.sizeOfData);

	this->data.reserve(this->samples);
	for (unsigned int i = 0; i < this->samples; i++) {
		this->data.push_back(static_cast<float>(raw_data[i]) / 32768.0f);
	}

	delete[] raw_data;
	return true;
}

bool WAV::Save(const std::string filename)
{
	// Open/Create file
	std::fstream file(filename, std::fstream::out | std::fstream::binary);

	// Update header
	this->samples = static_cast<unsigned int>(this->data.size());
	this->header.sizeOfData = samples * sizeof(int16_t);
	this->header.overallSize = this->header.sizeOfData + 36;

	// Check header
	if (!CheckHeader(this->header)) { return false; }

	// Write header
	if (sizeof(this->header) != 44) { std::cerr << "Implementation error!"; return false; }
	file.write(reinterpret_cast<char *>(&this->header), sizeof(this->header));

	// Save data
	int16_t *raw_data = new int16_t[this->samples];
	for (unsigned int i = 0; i < this->samples; i++) {
		// NOTE: denormalizing by lower value compared to value used for normalizing when loading WAV file to avoid overflow;
		raw_data[i] = static_cast<int16_t>(data[i] * 32767.0f);
	}
	file.write(reinterpret_cast<char *>(raw_data), this->header.sizeOfData);

	delete[] raw_data;
	return false;
}

std::vector<float>& WAV::Data()
{
	return this->data;
}

float WAV::SamplingFrequency()
{
	return static_cast<float>(this->header.samplingFrequency);
}

int WAV::Samples() {
	this->samples = static_cast<unsigned int>(this->data.size());
	return this->samples;
}
