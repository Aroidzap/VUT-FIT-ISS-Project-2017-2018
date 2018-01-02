#include <iostream>
#include "constants.h"
#include "complex.h"
#include "DFT.h"
#include "DTF.h"
#include "correlation.h"
#include "Filter.h"
#include "wav.h"
#include "csv.h"

int main(int argc, char *argv[]) 
{
	if (argc < 2) { 
		std::cerr << "No file for analysis provided!"; 
		return 1;
	}

	// Load signal
	WAV signal;
	signal.Load(argv[1]);
	std::cout << "Analyzing signal: " << argv[1] << std::endl << std::endl;
	
	// Extract information
	std::cout << "Sampling frequency: " << signal.SamplingFrequency() << "[Hz]" << std::endl;
	std::cout << "Length: " << static_cast<double>(signal.Samples()) / signal.SamplingFrequency() << "[s], ";
	std::cout << signal.Samples() << "[samples]" << std::endl << std::endl;
	
	// Perform DFT
	std::cout << "Computing DFT..." << std::endl;
	std::vector<complex> dft = DFT(signal);

	// Compute modulus
	std::vector<double> dft_modulus, freq;
	for (unsigned int k = 0; k < dft.size(); k++) {
		dft_modulus.push_back(dft[k].modulus());
		freq.push_back(0.5*signal.SamplingFrequency()*k / dft.size());
	}

	// Find max DFT modulus frequency
	double max_dft_modulus = dft_modulus[0];
	unsigned int max_dft_modulus_idx;
	for (unsigned int k = 1; k < dft_modulus.size(); k++) {
		if (dft_modulus[k] > max_dft_modulus) {
			max_dft_modulus = dft_modulus[k];
			max_dft_modulus_idx = k;
		}
	}
	double perc1 = static_cast<double>(max_dft_modulus_idx) / static_cast<double>(dft_modulus.size());
	double max_dft_modulus_freq = perc1 * signal.SamplingFrequency() / 2.0;

	std::cout << "Max of DFT modulus is at frequency: " << max_dft_modulus_freq << "[Hz]" << std::endl;

	// Export DFT modulus to file
	const char* dft_m_file = "dft_modulus_original.csv";
	CSV<double>({ {"Sampling frequency [Hz]", freq}, {"|DFT(x[n])|", dft_modulus} }).Save(dft_m_file);
	std::cout << "DFT modulus is exported to '" << dft_m_file << "'" << std::endl << std::endl;
	

	// Create Discrete Transfer Function H(e^jw) of IIR filter
	std::cout << "Computing H(e^jw)..." << std::endl;
	double b0 = 0.2324, b1 = -0.4112, b2 = 0.2324, a1 = 0.2289, a2 = 0.4662;
	complex n0, n1, p0, p1;

	DTF H(b0, b1, b2, a1, a2);

	H.GetZeroesPoles(n0, n1, p0, p1);

	// Export poles and zeroes
	std::vector<complex> zeroes({ n0, n1 }), poles({ p0, p1 }), unit_circle;
	for (double i = 0.0; i < 1.0; i += 0.002) {
		unit_circle.push_back(e_to_j(PI * 2.0 * i));
	}
	const char* h_zp_file = "h_zeroes_poles.csv";
	CSV<double>({	{ "Unit Circle [Re]", Re(unit_circle) },
					{ "Unit Circle [Im]", Im(unit_circle) },
					{ "zero [Re]", Re(zeroes) },
					{ "zero [Im]", Im(zeroes) },
					{ "pole [Re]", Re(poles) },
					{ "pole [Im]", Im(poles) }	}).Save(h_zp_file);

	std::cout << "Zeroes and poles of H(e^jw) of IIR filter are exported to '" << h_zp_file << "'" << std::endl;

	// Export modulus of H(e^jw) of IIR filter to file
	std::vector<double> iir_dtf_modulus, iir_dtf_freq;
	for (double i = 0.0; i < 0.5; i += 0.002) {
		iir_dtf_modulus.push_back(H(e_to_j(PI * 2.0 * i)).modulus());
		iir_dtf_freq.push_back(i * signal.SamplingFrequency());
	}

	const char* iir_dtf_file = "iir_h_function_modulus.csv";
	CSV<double>({ { "Sampling frequency [Hz]", iir_dtf_freq }, { "|H(e^jw)|", iir_dtf_modulus } }).Save(iir_dtf_file);
	std::cout << "Modulus of H(e^jw) of IIR filter is exported to '" << iir_dtf_file << "'" << std::endl << std::endl;


	// Filter signal with IIR filter
	std::cout << "Filtering signal using IIR filter..." << std::endl;
	Filter iir({ b0, b1, b2 }, { a1, a2 });
	std::vector<double> filtered_signal = iir.Convolve(signal);

	// Export IIR filtered signal
	WAV iir_filtered_signal(filtered_signal, signal.GetHeader());

	const char* iir_filtered_file = "iir_filtered_signal.wav";
	iir_filtered_signal.Save(iir_filtered_file);
	std::cout << "IIR filtered signal is exported to '" << iir_filtered_file << "'" << std::endl << std::endl;

	// Perform DFT over IIR filtered signal
	std::cout << "Computing DFT of IIR filtered signal..." << std::endl;
	std::vector<complex> dft_filtered = DFT(filtered_signal);

	// Compute modulus
	std::vector<double> dft_modulus_filtered, freq_filtered;
	for (unsigned int k = 0; k < dft_filtered.size(); k++) {
		dft_modulus_filtered.push_back(dft_filtered[k].modulus());
		freq_filtered.push_back(0.5*signal.SamplingFrequency()*k / dft_filtered.size());
	}

	// Find max DFT modulus frequency of IIR filtered signal
	double max_dft_modulus_iir_filtered = dft_modulus_filtered[0];
	unsigned int max_dft_modulus_filtered_idx;
	for (unsigned int k = 1; k < dft_modulus_filtered.size(); k++) {
		if (dft_modulus_filtered[k] > max_dft_modulus_iir_filtered) {
			max_dft_modulus_iir_filtered = dft_modulus_filtered[k];
			max_dft_modulus_filtered_idx = k;
		}
	}
	double perc2 = static_cast<double>(max_dft_modulus_filtered_idx) / static_cast<double>(dft_modulus_filtered.size());
	double max_dft_modulus_filtered_freq = perc2 * signal.SamplingFrequency() / 2.0;

	std::cout << "Max of DFT modulus of IIR filtered signal is at frequency: " << max_dft_modulus_filtered_freq << "[Hz]" << std::endl;

	// Export DFT modulus of IIR filtered signal to file
	const char* dft_m_iir_file = "dft_modulus_iir_filtered.csv";
	CSV<double>({ { "Sampling frequency [Hz]", freq_filtered },{ "|DFT(x[n])|", dft_modulus_filtered } }).Save(dft_m_iir_file);
	std::cout << "DFT modulus of IIR filtered signal is exported to '" << dft_m_iir_file << "'" << std::endl << std::endl;
	

	// Find 20ms of 4kHz, 50% duty cycle signal
	// Create FIR filter
	std::cout << "Filtering signal using FIR filter..." << std::endl;

	double fir_frequency = 4000.0; // 4kHz
	double fir_time = 0.020; // 20ms

	std::vector<double> fir_coefs;
	size_t fir_period_count = static_cast<size_t>(signal.SamplingFrequency() / fir_frequency);
	size_t fir_coef_count = static_cast<size_t>(fir_time * static_cast<double>(signal.SamplingFrequency()));
	fir_coefs.resize(fir_coef_count);
	for (size_t i = 0; i < fir_coef_count; i++) {
		if (i % fir_period_count < fir_period_count / 2) {
			fir_coefs[i] = 1.0 / static_cast<double>(fir_coef_count);
		}
		else {
			fir_coefs[i] = - 1.0 / static_cast<double>(fir_coef_count);
		}
	}
	Filter fir({ fir_coefs });

	// Filter signal with FIR filter
	std::vector<double> filtered_fir_signal = fir.Convolve(signal);

	// Export FIR filtered signal
	WAV fir_filtered_signal(filtered_fir_signal, signal.GetHeader());

	const char* fir_filtered_file = "fir_filtered_signal.wav";
	fir_filtered_signal.Save(fir_filtered_file);
	std::cout << "FIR filtered signal is exported to '" << fir_filtered_file << "'" << std::endl;

	// Find position of maximal absolute value of fir filtered signal
	double max_abs_val = filtered_fir_signal[0];
	unsigned int max_abs_val_sample;
	for (unsigned int n = 1; n < filtered_fir_signal.size(); n++) {
		double abs = filtered_fir_signal[n];
		abs = abs < 0 ? -abs : abs;
		if ( abs > max_abs_val) {
			max_abs_val = abs;
			max_abs_val_sample = n;
		}
	}

	double sqr_signal_time = static_cast<double>(max_abs_val_sample) / static_cast<double>(filtered_fir_signal.size());
	std::cout << "4kHz square signal found at: " << sqr_signal_time << "[s], " << max_abs_val_sample << "[samples]" << std::endl << std::endl;
	
	// Compute biased auto-correlation coefficients from -50 to 50
	std::cout << "Computing auto-correlation..." << std::endl;
	std::vector<double>R = BiasedAutoCorrelation(signal, -50, 50);
	std::vector<double>k_axis;
	for (int k = -50; k <= 50; k++) {
		k_axis.push_back(static_cast<double>(k));
	}

	std::cout << "Value of auto-correlation coefficient R[10] is: " << R[50 + 10] << std::endl;

	const char* r_file = "auto_correlation.csv";
	CSV<double>({ { "k", k_axis },{ "R[k]", R } }).Save(r_file);
	std::cout << "Auto-correlation coefficients are exported to '" << r_file << "'" << std::endl << std::endl;

	// Compute joint probability density function p(x1, x2, 10)
	std::cout << "Computing joint probability density function..." << std::endl;
	double div_size = 1.0 / 64.0;
	double div_area = div_size * div_size;
	std::vector<std::vector<double>> jpdf = JointProbabilityDensity(signal, signal, 10, div_size);

	// Check joint probabiliry density by integration
	double integration = 0.0;
	for (int x2 = 0; x2 < jpdf.size(); x2++) {
		for (int x1 = 0; x1 < jpdf[x2].size(); x1++) {
			integration += jpdf[x2][x1] * div_area;
		}
	}
	std::cout << "Integration of joint probabiliry density is: " << integration << std::endl;

	// Compute R[10] from joint probabiliry density function
	double R10 = 0.0;

	double v_x2 = -1.0;
	for (int x2 = 0; x2 < jpdf.size(); x2++, v_x2 += div_size) {
		double v_x1 = -1.0;
		for (int x1 = 0; x1 < jpdf[x2].size(); x1++, v_x1 += div_size) {
			R10 += v_x1 * v_x2 * jpdf[x2][x1] * div_area;
		}
	}

	std::cout << "Value of R[10] computed from joint probability density is: " << R10 << std::endl;

	// Export joint probabiliry density
	std::vector<double> x1_axis, x2_axis, z_axis;

	double val_x2 = -1.0;
	for (int x2 = 0; x2 < jpdf.size(); x2++, val_x2 += div_size) {
		double val_x1 = -1.0;
		for (int x1 = 0; x1 < jpdf[x2].size(); x1++, val_x1 += div_size) {
			x1_axis.push_back(val_x1);
			x2_axis.push_back(val_x2);
			z_axis.push_back(jpdf[x2][x1]);
		}
	}

	const char* jpdf_file = "joint_probability_density.csv";
	CSV<double>({ { "x1", x1_axis },{ "x2", x2_axis },{ "density", z_axis } }).Save(jpdf_file);
	std::cout << "Joint probabiliry density function is exported to '" << jpdf_file << "'" << std::endl << std::endl;

	return 0;
}