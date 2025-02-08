#include "compression.h"

using namespace std;

vector<pair<uint8_t, uint8_t>> compressGrayscale(array<array<uint8_t, width>, height>& bitmap)
{
	vector<pair<uint8_t, uint8_t>> compressedBitmap;
	
	for (const auto row : bitmap)
	{
		auto column_it = row.begin();
		uint8_t last_value = 256;
		short int counter = 0;

		while (column_it < row.end())
		{			
			if (*column_it == last_value || column_it == row.begin())
			{
				counter++;
				if (column_it == row.end() - 1)
				{
					compressedBitmap.emplace_back(last_value, static_cast<uint8_t>(counter));
				}
			}
			if (*column_it != last_value && column_it != row.begin())
			{
				compressedBitmap.emplace_back(last_value, static_cast<uint8_t>(counter));
				counter = 1;
				if (column_it == row.end() - 1)
					compressedBitmap.emplace_back(*column_it, static_cast<uint8_t>(1));
			}
			last_value = *column_it;
			column_it++;
		}
	}		

	return compressedBitmap;
}

array<array<uint8_t, width>, height> decompressGrayscale(vector<pair<uint8_t, uint8_t>>& compressedBitmap)
{
	array<array<uint8_t, width>, height> output;

	int row = 0;
	int column = 0;
	for (auto it : compressedBitmap)
	{
		if (row < height)
		{
			for (int k = 0; k < it.second; k++)
			{
				if (column < width)
				{
					output.at(row).at(column) = it.first;
					column++;
				}
				if (column == width)
				{
					column = 0;
					row++;
				}
			}
		}
	}

	return output;
}
