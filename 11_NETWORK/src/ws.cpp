#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>


void add_link(std::vector<int> &links, int source, int target)
{
    // add source->target link
    links.push_back(source);
    links.push_back(target);
}


std::vector<int> generate_regular_ring_lattice(int N, int k)
{
	std::vector<int> links;
	for (int i = 0; i < N; i++)
	{
		for (int d = 1; d <= k/2; d++)
		{
			add_link(links, i, i + d);
		}
	}
	return links;
}


// Assume undirected graph
// Node labels: 0,...,N-1
// k: adjacent edges of regular ring lattice
// p: rewiring probability
std::vector<int> WS(std::mt19937 &mt, int N, int k, double p)
{
	// Choose targets of m links by preferential attachment
	std::uniform_real_distribution<double> uni(0.0, 1.0);
    
	std::vector<int> links = generate_regular_ring_lattice(N, k);
    for (int i = 0; i < links.size() / 2; i++)
    {
		if (uni(mt) > p) continue;
		int source = links[2 * i];
		// Rewiring: randomly choose node excepting k+1 nodes (source node and its neighbors)
		int index = int(uni(mt) * (N-(k+1)));
		int new_target = (source + k/2 + 1 + index) % N;
		links[2 * i + 1] = new_target;
    }
    return links;
}


void output_links(std::vector<int> &links, std::string path = "")
{
    if (path == "")
    {
        for (int i = 0; i < links.size() / 2; i++)
            std::cout << links[2 * i] << "," << links[2 * i + 1] << std::endl;
        return;
    }
    std::ofstream ofs(path);
    for (int i = 0; i < links.size() / 2; i++)
        ofs << links[2 * i] << "," << links[2 * i + 1] << std::endl;
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
    std::string out_file = out_dir + "ws.csv";

    int seed = 1;
    std::mt19937 mt(seed);

    int N = 1e4;
	int k = 4; // 正則リング格子の次数
	double p = 0.4; // 最配線確率
	std::vector<int> links = WS(mt, N, k, p);

    output_links(links, out_file);

    return 0;
}
