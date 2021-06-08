#include <string>
#include "drawData.h"
#include "polyFit.h"


int main(int argc, char *argv[])
{
    std::cout << "This is a demo of problem 3 of MTCP\n";
    std::string filename;
    std::ifstream fs;
    Eigen::MatrixXd scatter_mat, line_mat, coefs_mat;
    double x_span[2];
    int estimate_size;
    while (true)
    {
        std::cout << "Please type the filename of input data(type .quit to quit this program):\n";
        std::cin >> filename;
        if (filename == ".quit")
            break;
        fs.open(filename);
        if (!fs)
        {
            std::cout << "fail to open file: " << filename << std::endl;
            continue;
        }
        scatter_mat = loadData(fs);
        fs.close();

        std::cout << "Please type the fitting type here: (linear or parabolic):\n";
        std::cin >> filename;
        if (filename == "linear")
            coefs_mat = polyFit(scatter_mat, true);
        else if (filename == "parabolic")
            coefs_mat = polyFit(scatter_mat, false);

        std::cout << "Now type in the lower and upper bounds:\n";
        std::cin >> x_span[0] >> x_span[1];

        std::cout << "Type in the number of steps:\n";
        std::cin >> estimate_size;
        if (filename == "linear")
            line_mat = Estimate(coefs_mat, x_span[0], x_span[1], estimate_size, true);
        else if (filename == "parabolic")
            line_mat = Estimate(coefs_mat, x_span[0], x_span[1], estimate_size, false);
        drawData(argc, argv, scatter_mat, line_mat);
    }
    return 0;
}

