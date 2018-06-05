/* Implementation of the recursive algorithm finding max subarray 
from "Introduction to algorithms" T.H.Cormen, C.E.Leiserson, R.L.Rivest, C.Stein */

#include<iostream>
#include<tuple>
using std::tuple;
#include<vector>
using std::vector;

typedef vector<int> vec;
typedef tuple<int, int, int> mytuple;

mytuple findMaxCrossingSub(const vec &v, int low, int mid, int high)
{
	int left_sum = INT16_MIN,                   //just some big enough limiter      
		sum = 0,
		max_left = 0,
	 right_sum = INT16_MIN,
		max_right = 0;
	for (int i = mid; i >= low; i--)
	{
		sum = sum + v[i];
		if (sum > left_sum)
		{
			left_sum = sum;
			max_left = i;
		}
	}
		sum = 0;
		for (int j = mid + 1; j <= high; j++)
		{
			sum = sum + v[j];
			if (sum > right_sum)
			{
				right_sum = sum;
				max_right = j;
			}
		}
	return std::make_tuple(max_left, max_right, left_sum + right_sum);
}

mytuple findMax_Subarray(const vec &v, int low, int high)
{
	if (high == low)
		return std::make_tuple(low, high, v[low]);
	else
	{
		int mid = (low + high) / 2;
		mytuple lefttuple = findMax_Subarray(v, low, mid);          //find max subarray in left part of array
		mytuple righttuple = findMax_Subarray(v, mid + 1, high);    //find max subarray in right part of array
		mytuple crosstuple = findMaxCrossingSub(v, low, mid, high); //find max subarray begins in left part and ends
																	// in right part of array	
		if (std::get<2>(lefttuple) >= std::get<2>(righttuple) && std::get<2>(lefttuple) >= std::get<2>(crosstuple))
			return lefttuple;
		else if (std::get<2>(righttuple) >= std::get<2>(lefttuple) && std::get<2>(righttuple) >= std::get<2>(crosstuple))
			return righttuple;
		else
			return crosstuple;
	}
}

int main()
{
	vec arr{ 13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7 };
	//vec arr{ -13, -3, -25, -20, -3, -16, -23, -18, -20, -7, -12, -5, -22, -15, -4, -7 };
	mytuple answer = findMax_Subarray(arr, 0, arr.size() - 1);
	std::cout << "The maximum arrange of array with " << std::get<0>(answer) << " element to " <<
		std::get<1>(answer) << " element. Sum is " << std::get<2>(answer) << std::endl;
}
