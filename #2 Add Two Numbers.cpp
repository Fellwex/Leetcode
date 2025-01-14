#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <vector>

// https://leetcode.com/problems/add-two-numbers/

// Definition for singly-linked list.
struct ListNode 
{
    int val;
    ListNode* next;

    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution 
{
public:
    using SumType = int;

    ListNode* addTwoNumbers(const ListNode* left_list, const ListNode* right_list) 
    {
        ListNode* head = nullptr;
        ListNode* tail = nullptr;
        bool is_additional_one = false;

        while (left_list != nullptr || right_list != nullptr || is_additional_one)
        {
            SumType sum = 0;
           
            if (left_list)
            {
                sum += left_list->val;
                left_list = left_list->next;
            }
            if (right_list)
            {
                sum += right_list->val;
                right_list = right_list->next;
            }
            if (is_additional_one)
            {
                ++sum;
            }

            is_additional_one = (sum >= 10) ? true : false;
            sum %= 10;

            if (!head)
            {
                head = new ListNode(sum);
                tail = head;
            }
            else
            {
                tail->next = new ListNode(sum);
                tail = tail->next;
            }
        }

        return head;
    }
};

struct TestItems
{
    std::vector<Solution::SumType> first_list;
    std::vector<Solution::SumType> second_list;
    std::vector<Solution::SumType> expected_result;
};

class AddTwoNumbersTest : public testing::TestWithParam<TestItems>
{
protected:
    ListNode* FromVectorToList(const std::vector<Solution::SumType>& values)
    {
        ListNode* head = nullptr;
        ListNode* tail = nullptr;

        for (const auto v : values)
        {
            if (!head)
            {
                head = new ListNode(v);
                tail = head;
            }
            else
            {
                tail->next = new ListNode(v);
                tail = tail->next;
            }
        }

        return head;
    }

    std::vector<Solution::SumType> FromListToVector(const ListNode* list)
    {
        std::vector<Solution::SumType> result;

        while (list)
        {
            result.push_back(list->val);
            list = list->next;
        }

        return result;
    }

    void DeleteList(const ListNode* list)
    {
        while (list)
        {
            const ListNode* temp = list;
            list = list->next;
            delete temp;
        }
    }
};

INSTANTIATE_TEST_SUITE_P(AddTwoNumbersTestInstance, AddTwoNumbersTest, testing::Values(
    TestItems{ {}, {}, {} },
    TestItems{ {1}, {}, {1} },
    TestItems{ {}, {2}, {2} },
    
    TestItems{ {1, 2, 3}, {4, 5, 6}, {5, 7, 9} },
    TestItems{ {1, 2, 3}, {},        {1, 2, 3} },
    TestItems{ {},        {4, 5, 6}, {4, 5, 6} },
    
    TestItems{ {9, 9}, {1, 1}, {0, 1, 1} },
    TestItems{ {9, 9}, {0, 5, 9}, {9, 4, 0, 1} },
    TestItems{ {9, 9, 1, 8, 9}, {0, 0, 9, 0, 1}, {9, 9, 0, 9, 0, 1} },
    TestItems{ {9, 9, 9, 9, 9}, {9, 9, 9}, {8, 9, 9, 0, 0, 1} }
    ));

TEST_P(AddTwoNumbersTest, Tests)
{
    ListNode* list1 = FromVectorToList(GetParam().first_list);
    ListNode* list2 = FromVectorToList(GetParam().second_list);

    Solution solution;
    ListNode* result = solution.addTwoNumbers(list1, list2);

    EXPECT_EQ(FromListToVector(result), GetParam().expected_result);

    for (const auto list : {list1, list2, result})
    {
        DeleteList(list);
    }
}

int main()
{
    testing::InitGoogleTest(); 
    return RUN_ALL_TESTS();
}