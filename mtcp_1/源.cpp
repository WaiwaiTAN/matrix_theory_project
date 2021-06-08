#include "JordanForm.h"
#include "uSimilar.h"
#include <string>


void presse_demo(project_base & proj)
{
	std::string cmd;
	std::cout << "intput command to run a demo.\ncommand 'std' means input in std stream.\ncommand 'rand' means run a random demo\ncommand 'quit' means quit\n";
	while (true)
	{
		std::cout << ">> ";
		std::cin >> cmd;
		if (cmd == "std")
		{
			proj.std_demo();
			continue;
		}

		if (cmd == "rand")
		{
			proj.rand_demo();
			continue;
		}

		if (cmd == "quit")
		{
			break;
		}
	}
}

int main()
{
	std::cout << "chooose problem number(1 or 2):\n";
	int cmd;
	std::cin >> cmd;
	if (cmd == 1)
	{
		JordanForm js;
		presse_demo(js);
	}
	else
	{
		uSimilar us;
		presse_demo(us);
	}

	return 0;
}
