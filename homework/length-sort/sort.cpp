#include "sort.hpp"

using namespace std;

deque<string> lengthSort(forward_list<string>& input)
{
	deque<string> temp;
	for (auto element : input)
		temp.push_back(element);

	sort(temp.begin(), temp.end());
	sort(temp.begin(), temp.end(), [](const auto& a, const auto& b) {return a.length() < b.length(); });

	return temp;
}
