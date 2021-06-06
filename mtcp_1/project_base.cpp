#include "project_base.h"

void project_base::std_intput()
{
	int dim;
	std::cout << "please type the dimension of your linear operator here: \n";
	std::cin >> dim;
	Eigen::MatrixXd mat_std(dim, dim);
	for (int i = 0; i < dim; i++)
	{
		for (int j = 0; j < dim; j++)
		{
			std::cin >> mat_std(i, j);
		}
	}
	mat_in = mat_std;
}

void project_base::rand_input()
{
	mat_in = Eigen::MatrixXd::Random(4, 4);
}

void project_base::rand_demo()
{
	rand_input();
	std::cout << "Here is a matrix: \n" << mat_in << std::endl;
	process();
	std::cout << "After process\n";
	print_ans();
}

void project_base::std_demo()
{
	std_intput();
	std::cout << "The matrix you input: \n" << mat_in << std::endl;
	process();
	std::cout << "After process\n";
	print_ans();
}
