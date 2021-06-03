#include "JordanForm.h"
#include "uSimilar.h"
#include <string>

#define test_1
int main()
{
	std::string cmd;
	std::cout << "intput command to run a demo.\ncommand 'std' means input in std stream.\ncommand 'rand' means run a random demo\ncommand 'quit' means quit\n";
#ifdef test_1
	JordanForm js;
	while (true)
	{
		std::cin >> cmd;
		if (cmd == "std")
		{
			js.std_demo();
			continue;
		}

		if (cmd == "rand")
		{
			js.rand_demo();
			continue;
		}

		if (cmd == "quit")
		{
			break;
		}
	}
#else
	uSimilar us;
	while (true)
	{
		std::cin >> cmd;
		if (cmd == "std")
		{
			us.std_demo();
			continue;
		}

		if (cmd == "rand")
		{
			us.rand_demo();
			continue;
		}

		if (cmd == "quit")
		{
			break;
		}
	}
#endif // test_1

	return 0;
}