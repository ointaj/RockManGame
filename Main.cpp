#include  "Start.h"
int32_t main()
{
	auto systemStart = std::make_unique<SystemStart>();
	systemStart->Start();
}