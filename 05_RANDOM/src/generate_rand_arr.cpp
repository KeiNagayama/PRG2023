#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <vector>
#include <cmath>

// ===== Ex.1 =====
// U(0,1), precisely, support = [0,1)
std::vector<double> generate_uniform_rand_arr(std::mt19937 &mt, int N)
{
	std::uniform_real_distribution<double> uni(0.0, 1.0);
	std::vector<double> rand_arr;
	for (int i = 0; i < N; i++)
		rand_arr.push_back(uni(mt));
	return rand_arr;
}

// ===== Ex.2 =====
// N(mu,sigma^2) by box-muller method
// Assume that N is odd
std::vector<double> generate_normal_rand_arr(std::mt19937 &mt, int N, double mu = 0, double sigma = 1)
{
	double pi = 3.1415926535;
	std::uniform_real_distribution<double> uni(0.0, 1.0);
	std::vector<double> rand_arr;

	for (int i = 0; i < N / 2; i++)
	{
		// Generate N(0,1)
		double u0, u1, r, z0, z1;
		u0 = uni(mt);
		u1 = uni(mt);
		r = std::sqrt(-2 * std::log(u0));
		z0 = r * std::cos(2 * pi * u1);
		z1 = r * std::sin(2 * pi * u1);
		// Convert to N(mu,sigma) by x = mu + z*sigma
		rand_arr.push_back(mu + z0 * sigma);
		rand_arr.push_back(mu + z1 * sigma);
	}
	return rand_arr;
}

// ===== Ex.3 =====
// Exp(mu) by inverse function method
// CDF   : F(x) := P(>x) = e^{-x/mu}    ; For x > 0
// InvCDF: x = F^{-1}(u) = - mu * log(u); For u in (0,1]
std::vector<double> generate_exp_rand_arr(std::mt19937 &mt, int N, double mu = 1)
{
	std::uniform_real_distribution<double> uni(0.0, 1.0);
	std::vector<double> rand_arr;
	auto inv_exp = [&mu](double u)
	{ return -mu * std::log(u); };
	for (int i = 0; i < N; i++)
	{
		// uni(mt)   \in [0,1)
		// 1-uni(mt) \in (0,1]
		rand_arr.push_back(inv_exp(1 - uni(mt)));
	}
	return rand_arr;
}

template <typename T>
void output_vector(std::vector<T> &v, std::string path = "")
{
	if (path == "")
	{
		for (auto x : v)
			std::cout << x << std::endl;
		return;
	}
	std::ofstream ofs(path);
	for (auto x : v)
		ofs << x << std::endl;
}

int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		std::cout << "Required an output directory." << std::endl;
		std::cout << "Usage: <bin> <out_dir>" << std::endl;
		return 0;
	}
	// 乱数列の出力ファイル
	// std::string out_dir = "../result/";
	std::string out_dir = argv[1];
	std::string out_uni = out_dir + "uni";
	std::string out_norm = out_dir + "norm";
	std::string out_exp = out_dir + "exp";

	// 乱数生成器
	int seed = 1;
	std::mt19937 mt(seed);

	// 乱数列
	int N = 1e6;
	std::vector<double> rand_arr;
	double mu, sigma;

	// U(0,1)
	rand_arr = generate_uniform_rand_arr(mt, N);
	output_vector(rand_arr, out_uni);

	// N(0,1)
	mu = 0;
	sigma = 1;
	rand_arr = generate_normal_rand_arr(mt, N, mu, sigma);
	output_vector(rand_arr, out_norm);

	// Exp(1)
	mu = 1;
	rand_arr = generate_exp_rand_arr(mt, N, mu);
	output_vector(rand_arr, out_exp);

	return 0;
}
