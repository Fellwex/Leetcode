#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <vector>

// https://leetcode.com/problems/two-sum/description/

class Solution 
{
public:
    std::vector<int> twoSum(const std::vector<int>& nums, int target)
    {
        if (nums.size() < 2)
        {
            return {};
        }

        for (size_t i = 0; i < nums.size() - 1; ++i)
        {
            for (size_t j = i + 1; j < nums.size(); ++j)
            {
                if (nums[i] + nums[j] == target)
                {
                    return { static_cast<int>(i), static_cast<int>(j) };
                }
            }
        }

        return {};
    }
};

TEST(TestTwoSum, Tests) 
{
    Solution solution;

    EXPECT_THAT(solution.twoSum({ 2,7,11,15 }, 9), testing::ElementsAre(0,1));
    EXPECT_THAT(solution.twoSum({ 3,2,4 }, 6), testing::ElementsAre(1, 2));
    EXPECT_THAT(solution.twoSum({ 3,3 }, 6), testing::ElementsAre(0, 1));

    EXPECT_THAT(solution.twoSum({ 0,0,1 }, 1), testing::ElementsAre(0, 2));
    EXPECT_THAT(solution.twoSum({ 0,0 }, 0), testing::ElementsAre(0, 1));
}

int main()
{
    testing::InitGoogleTest(); 
    return RUN_ALL_TESTS();
}