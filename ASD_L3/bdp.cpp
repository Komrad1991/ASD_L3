#include "bdp.h"
#include <vector>

void eratosphenMySet(int n)
{
	bdp<int> sieve;
	for (int i = n; i >= (n + 1) / 2; i--)
	{
		sieve.add(i);
	}
	for (int i = 2; i < (n + 1)/2; i++)
	{
		sieve.add(i);
	}

	for (int i = 2; i * i <= n+1; i++)
	{
		if (sieve.find(i))
		{
			for (int j = i * i; j <= n+1; j += i)
			{
				sieve.erase(j);
			}
		}
	}
	sieve.print_ltr();
	std::cout << std::endl;
}

void eratosphenVector(int n)
{
	std::vector<bool> sieve;
	for (int i = 0; i < n + 1; i++)
	{
		sieve.push_back(true);
	}

	for (int i = 2; i * i <= n; i++)
	{
		if (sieve[i])
		{
			for (int j = i * i; j <= n; j += i)
			{
				sieve[j] = false;
			}
		}
	}
	for (int i = 2; i < sieve.size(); i++)
	{
		if (sieve[i]) std::cout << i << " ";
	}
	std::cout << std::endl;
}