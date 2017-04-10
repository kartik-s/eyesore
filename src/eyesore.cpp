#include "eyesore.h"

using namespace eyesore;

int main(void)
{
	Engine e;

	e.makeWindow(400, 300, "eyesore", false);
	e.run();

	return 0;
}

