#include "sort.h"

using namespace std;

auto lexiSort = [](const auto& word1, const auto& word2)
	{
		int length = (word1.length() < word2.length()) ? word1.length() : word2.length();

		for (int i = 0; i < length; i++)
			if (word1[i] != word2[i])
				return (int(word1[i]) < int(word2[i])) ? true : false;
	};

deque<string> lengthSort(forward_list<string>& input)
{
	deque<string> temp;
	for (auto element : input)
		temp.push_back(element);

	sort(temp.begin(), temp.end(), lexiSort);
	sort(temp.begin(), temp.end(), [](const auto& a, const auto& b) {return a.length() < b.length(); });

	return temp;
}
