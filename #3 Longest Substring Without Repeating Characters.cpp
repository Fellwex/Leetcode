#include <gtest/gtest.h>

#include <string>
#include <unordered_set>
#include <algorithm>

// https://leetcode.com/problems/longest-substring-without-repeating-characters/

class Solution
{
public:
    int lengthOfLongestSubstring(const std::string& str)
    {
        int max_length = 0;
        std::unordered_set<char> unique_letters(str.size());

        for (size_t current_letter_index = 0; current_letter_index < str.size(); ++current_letter_index)
        {
            for (size_t next_letter_index = current_letter_index; next_letter_index < str.size(); ++next_letter_index)
            {
                char letter = str[next_letter_index];
                if (unique_letters.count(letter) == 0)
                {
                    unique_letters.insert(letter);
                }
                else
                {
                    break;
                }
            }

            max_length = std::max(max_length, static_cast<int>(unique_letters.size()));
            unique_letters.clear();
        }

        return max_length;
    }
};

class LengthOfLongestSubstringTest : public testing::TestWithParam<std::pair<std::string, int>>
{
};

INSTANTIATE_TEST_SUITE_P(LengthOfLongestSubstringTestInstance, LengthOfLongestSubstringTest,
    testing::Values(std::make_pair("abcabcbb", 3), std::make_pair("bbbb", 1), std::make_pair("babacabb", 3),
    std::make_pair("abc", 3), std::make_pair("pwwkew", 3), std::make_pair("baabbcdacbda", 4),
    std::make_pair("abcccca", 3), std::make_pair("vvaabacbd", 4), std::make_pair("va", 2),
    std::make_pair("1 23 456", 6), std::make_pair("456 23 1", 6)));

TEST_P(LengthOfLongestSubstringTest, Tests)
{
    Solution solution;
    const auto str = GetParam().first;
    const auto expected_result = GetParam().second;

    EXPECT_EQ(solution.lengthOfLongestSubstring(str), expected_result);
}

int main()
{
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
