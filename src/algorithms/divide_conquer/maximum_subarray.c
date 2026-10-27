#include "divide_conquer.h"

static MaxSubarrayResult max_crossing_subarray(
    const double values[],
    int left,
    int middle,
    int right
)
{
    double sum = 0.0;
    double best_left_sum = values[middle];
    int best_left = middle;

    for (int i = middle; i >= left; i--)
    {
        sum += values[i];

        if (sum > best_left_sum)
        {
            best_left_sum = sum;
            best_left = i;
        }
    }

    sum = 0.0;

    double best_right_sum = values[middle + 1];
    int best_right = middle + 1;

    for (int i = middle + 1; i <= right; i++)
    {
        sum += values[i];

        if (sum > best_right_sum)
        {
            best_right_sum = sum;
            best_right = i;
        }
    }

    MaxSubarrayResult result = {
        best_left,
        best_right,
        best_left_sum + best_right_sum
    };

    return result;
}


static MaxSubarrayResult maximum_subarray_recursive(
    const double values[],
    int left,
    int right
)
{
    if (left == right)
    {
        MaxSubarrayResult result = {
            left,
            right,
            values[left]
        };

        return result;
    }

    int middle = left + (right - left) / 2;

    MaxSubarrayResult left_result =
        maximum_subarray_recursive(values, left, middle);

    MaxSubarrayResult right_result =
        maximum_subarray_recursive(values, middle + 1, right);

    MaxSubarrayResult crossing_result =
        max_crossing_subarray(values, left, middle, right);

    if (left_result.sum >= right_result.sum &&
        left_result.sum >= crossing_result.sum)
    {
        return left_result;
    }

    if (right_result.sum >= left_result.sum &&
        right_result.sum >= crossing_result.sum)
    {
        return right_result;
    }

    return crossing_result;
}


MaxSubarrayResult maximum_subarray(
    const double values[],
    int count
)
{
    if (values == 0 || count <= 0)
    {
        MaxSubarrayResult invalid = {-1, -1, 0.0};
        return invalid;
    }

    return maximum_subarray_recursive(
        values,
        0,
        count - 1
    );
}