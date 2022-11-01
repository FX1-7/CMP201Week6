// CMP201.2022 AX1.5 String Search,
// Author: William Kavanagh
// Partial Framework

#include <string>
#include <iostream>
#include <vector>

const int ALPHABET_SIZE = 256;		// characters.

/*
* INPUT: pattern as string, length of pattern as in, int array of size alphabet to be filled.
* values in array should be -1 (if not in the pattern) or the index position of a character in the pattern.
* PERFORMANCE: O(m+n) (this is a hint as to what is provided).
*/
void badCharHeur(std::string pattern, int length, int in_pattern[ALPHABET_SIZE])
{
	// Assessed [1]: Information is provided in lecture 7B
	for(int i = 0; i < ALPHABET_SIZE; i++) {
		in_pattern[i] = -1;
	}

	for(int i = 0; i < length; i++) {
		in_pattern[pattern[i]] = i;
	}
}

/*
* INPUT: A text to search through and a pattern to search for.
* Returns a structure with the indexes of the first character of each occurence of the pattern in the text. Empty if none.
* PERFORMANCE: Boyer-Moore-Horspool should run in O(mn) in the worst-case and should be sublinear in the average case.
*/
std::vector<int> BMH(std::string text, std::string pattern)
{
	// Assessed [2]: Information is provided in lecture 7B
	// complete TODO statements to finish implementation.

	int pattern_len = pattern.size();
	int text_len = text.size();
	int shift_position = 0;											// possible position for first char of pattern
	// TODO: Create results structure
	std::vector<int> ResultsStruct;	
	// TODO: Create bad character heuristic lookup structure
	int BadCharStruct[ALPHABET_SIZE];
	// TODO: Fill bad character heuristic lookup.
	badCharHeur(pattern, pattern_len, BadCharStruct);
	while (shift_position <= text_len - pattern_len)
	{
		// while we are still looking over the text
		int characters_unmatched = pattern_len - 1;									
		while (characters_unmatched > 0 && pattern[characters_unmatched] == text[shift_position + characters_unmatched])
		{
			// While the pattern matches the text (going backwards)
			// TODO: Reduce the number of characters still to be matched.
			characters_unmatched = characters_unmatched - 1;

		}
		// TODO: If the pattern has been matched
		if(characters_unmatched == 0) {
			ResultsStruct.push_back(shift_position);
			// TODO: Add shift position to results
			if (shift_position + pattern_len < text_len)
			{
				// TODO: Uncomment below once the bad character structure exists, you may need to change <badChar> if you use a different name.
				shift_position += pattern_len - BadCharStruct[text[shift_position + pattern_len]];
			}
			else {
				shift_position++;
			}
		}
		// TODO: Uncomment below when If statement above is implemented.
		else{
			// Pattern not matched, shift along by at least 1.
			// TODO: '
			shift_position += std::max(1, characters_unmatched - BadCharStruct[text[shift_position + characters_unmatched]]);
		}
	}
	// TODO: Return the results structure
	return ResultsStruct;	// TODO: Remove when implementation complete.
}

/*
* INPUT: pattern as string, length of pattern as in, pointer to array to be used as LPS structure.
* For each character in the pattern, fill the LPS structure with the length of the longest proper prefix-suffix,
*/
void computeLPS(std::string pat, int M, int* lps)
{
	// UNASSESSED: Information is provided in lecture 7C
	int len = 0;
	lps[0] = 0;
	int i = 1;
	while (i < M)
	{
		if (pat[i] == pat[len])
		{
			len++;
			lps[i] = len;
			i++;
		}
		else
		{
			if (len != 0) len = lps[len - 1];
			else
			{
				lps[i] = 0;
				i++;
			}
		}
	}
}

/*
* INPUT: A text to search through and a pattern to search for.
* Returns a structure with the indexes of the first character of each occurence of the pattern in the text. Empty if none.
* PERFORMANCE: O(m+h) in the worst case and similar in the average case.
*/
std::vector<int> KMP(std::string text, std::string pattern)
{
	// ASSESSED [2]: Information is provided in lecture 7C
	std::vector<int> ResultsStruct;
	int* lps = new int[pattern.size()];
	computeLPS(pattern, pattern.size(), lps);
	int i = 0;
	int j = 0;
	while (j < pattern.size() && i < text.size()) {
		if (text[i] == pattern[j]) {
			i++;
			j++;
			if (j == pattern.size()) {
				ResultsStruct.push_back(i-j);
				j = lps[j-1];
			}
		}
		else {
			if (j > 0) {
				j = lps[j-1];
			}
			else {
				i++;
			}
		}
	}
	return ResultsStruct;
}


