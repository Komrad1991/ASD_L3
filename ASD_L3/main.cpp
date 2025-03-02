#include "bdp.h"

int main()
{
	bdp<int> bdp1;
	bdp1.add(2);
	bdp1.add(1);
	bdp1.add(3);
	bdp1.add(5);
	bdp1.add(7);
	bdp1.add(-1);
	bdp1.add(-5);
	bdp1.add(6);
	bdp1.print_rtl();
	std::cout << std::endl;
	auto seven = bdp1.find(7);
	std::cout << seven->data << std::endl;
	std::cout << bdp1.min() << std::endl;
	std::cout << bdp1.max() << std::endl;
	bdp1.erase(7);
	bdp1.print_ltr();
	std::cout << std::endl;
	auto upper = bdp1.upper(4);
	auto lower = bdp1.lower(-4);
	if (upper) std::cout << upper->data << std::endl;
	if (lower) std::cout << lower->data << std::endl;
	bdp<int> eq1;
	eq1.add(5);
	eq1.add(3);
	eq1.add(7);
	eq1.add(4);
	eq1.add(8);
	eq1.add(6);
	bdp<int> eq2;
	eq2.add(5);
	eq2.add(3);
	eq2.add(7);
	eq2.add(4);
	eq2.add(8);
	eq2.add(6);
	std::cout << eq1.equal(eq2) << std::endl;
	bdp<int> eq3;
	eq3.add(5);
	eq3.add(1);
	eq3.add(7);
	eq3.add(4);
	eq3.add(8);
	eq3.add(6);
	std::cout << eq1.equal(eq3) << std::endl;
}