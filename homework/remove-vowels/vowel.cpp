#include "vowel.hpp"

void removeVowels(std::vector<std::string>& input)
{
	std::string vowels = "aeiouyAEIOUY";
	
	for (auto &word : input)
	{
		for (int letter_in_word = 0; letter_in_word < word.length(); letter_in_word++)
			for (auto vowel : vowels)
				if (word[letter_in_word] == vowel)
				{
					word.erase(word.begin() + letter_in_word);
					letter_in_word--;
					break;
				}
	}
	input.shrink_to_fit();
}
