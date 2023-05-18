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
std::vector<int> generate_complete_graph(int N)
{
    std::vector<int> links;
    for (int i = 0; i < N; i++)
    {
        for (int j = i + 1; j < N; j++)
        {
            add_link(links, i, j);
        }
    }
    return links;
}

// Determine if vector contains element
bool contains(std::vector<int> &vec, int target)
{
    for (auto element : vec)
    {
        if (target == element)
            return true;
    }
    return false;
}

std::vector<int> BA(std::mt19937 &mt, int N, int m)
{
    // Initialize a graph
    int N0 = 5;
    std::vector<int> links = generate_complete_graph(N0);

    // For N-N0 steps, add a node with m links
    // Labels of new nodoes: N0,...,N-1
    // Choose targets of m links by preferential attachment
    std::uniform_real_distribution<double> uni(0.0, 1.0);
    for (int new_node = N0; new_node < N; new_node++)
    {
        int L = links.size();
        std::vector<int> targets;
        while (targets.size() < m)
        {
            int index = int(uni(mt) * L);
            int new_target = links[index];
            // Avoid multi-links
            if (contains(targets, new_target))
                continue;
            add_link(links, new_node, new_target);
            targets.push_back(new_target);
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
    std::string out_file = out_dir + "ba.csv";

    int seed = 1;
    std::mt19937 mt(seed);

    int N = 1e6;
    int m = 3; // 新規参入するノードのリンク数
    std::vector<int> links = BA(mt, N, m);

    output_links(links, out_file);

    return 0;
}