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


// Assume undirected graph
// Node labels: 0,...,N-1
// Average degree = (N-1)p
std::vector<int> ER(std::mt19937 &mt, int N, double p)
{
	// Choose targets of m links by preferential attachment
	std::uniform_real_distribution<double> uni(0.0, 1.0);
    
	std::vector<int> links;
    for (int i = 0; i < N; i++)
    {
        for (int j = i + 1; j < N; j++)
        {
			if (uni(mt) < p)
            	add_link(links, i, j);
        }
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
    std::string out_file = out_dir + "er.csv";

    int seed = 1;
    std::mt19937 mt(seed);

    int N = 1e4;
	double p = 10.0 / N; // リンク接続確率(平均次数は2)
	std::vector<int> links = ER(mt, N, p);

    output_links(links, out_file);

    return 0;
}
