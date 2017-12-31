#include <iostream>
#include "wav.h"
#include "complex.h"
#include "DFT.h"
#include "csv.h"

int main(int argc, char *argv[]) 
{
	if (argc < 2) { 
		std::cerr << "No file to analyze defined!"; 
		return 1;
	}

	// Load signal
	WAV signal;
	signal.Load(argv[1]);
	std::cout << "Analyzing signal: " << argv[1] << std::endl << std::endl;

	// Extract information
	std::cout << "Sampling frequency: " << signal.SamplingFrequency() << "[Hz]" << std::endl;
	std::cout << "Length: " << static_cast<float>(signal.Samples()) / signal.SamplingFrequency() << "[s]" << std::endl;
	std::cout << "Length: " << signal.Samples() << "[samples]" << std::endl << std::endl;

	// Perform DFT
	std::vector<complex> dft = DFT(signal.Data());

	// Export DFT modulus to file
	std::vector<float> dft_modulus, freq;
	for (unsigned int k = 0; k < dft.size(); k++) {
		dft_modulus.push_back(dft[k].modulus());
		freq.push_back(0.5f*signal.SamplingFrequency()*k / dft.size());
	}

	const char* dft_m_file = "dft_modulus.csv";
	CSV<float, float>(freq, dft_modulus).Save(dft_m_file);
	std::cout << "DFT modulus is exported to " << dft_m_file << std::endl;

	// Find max DFT modulus frequency
	float max_dft_modulus = dft_modulus[0];
	unsigned int max_dft_modulus_idx;
	for (unsigned int k = 1; k < dft_modulus.size(); k++) {
		if (dft_modulus[k] > max_dft_modulus) {
			max_dft_modulus = dft_modulus[k];
			max_dft_modulus_idx = k;
		}
	}
	float p = static_cast<float>(max_dft_modulus_idx) / static_cast<float>(dft_modulus.size());
	float max_dft_modulus_freq = p * signal.SamplingFrequency() / 2.0f;

	std::cout << "Max of DFT modulus is at frequency: " << max_dft_modulus_freq << "[Hz]" << std::endl;

	return 0;
}