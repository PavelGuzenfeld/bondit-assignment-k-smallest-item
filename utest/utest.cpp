#include <iostream> //cout()
#include <vector>
#include <iterator> // adcance()
#include <algorithm>
#include <initializer_list>
#include <functional>
#include <utility>
#include <stdlib.h>
#include <time.h>



auto get_element(auto const& a_pair, auto a_offset = 0)
{
    return a_pair.first[a_pair.second - a_offset];
}

auto min(auto const& a_numbers)
{
    using namespace std;
    auto comp = [](auto const& a_lhs, auto const& a_rhs)
        {
            return get_element(a_lhs, 0) < get_element(a_rhs, 0);
        };
    return min_element(a_numbers.begin(), a_numbers.end(), comp);
}

auto next_min(auto& last_min, auto& a_numbers)
{
    // find maximum element samller then a_min
    using namespace std;
    auto ret_val = begin(a_numbers);
    for(auto itr = begin(a_numbers) + 1; itr != end(a_numbers); ++itr)
    {
        std::cout <<"itr - " << get_element(*itr ,0) << "," ;
        if(get_element(*itr, 0) <= get_element(last_min ,0) && get_element(*itr, 0) >= get_element(*ret_val, 0))
        {
            ret_val = itr;
            std::cout  << "\n"  <<"new min - " << get_element(*ret_val ,0) ;
        }
        else
        {
            --(itr->second);
        }
    }
    return *ret_val;
}

// auto next_min(auto& a_min, auto const& a_numbers)
// {
//     using namespace std;
//     auto comp = [a_min](auto const& a_lhs, auto const& a_rhs)
//         {
//             return get_element(a_lhs, 0) > get_element(a_rhs, 0) && get_element(a_lhs, 0) <= get_element(a_min, 0);
//         };
//     return min_element(a_numbers.begin(), a_numbers.end(), comp);
// }

auto make_pairs(auto a_num,auto const& a_vectors)
{
    using Pair = std::pair<std::vector<int>,int>;
    auto pairs = std::vector<Pair>{};
    pairs.reserve(a_vectors.size());
    for(auto vector: a_vectors)
    {
        pairs.emplace_back(Pair{std::move(vector), a_num});
    }
    return pairs;
}

void advance(auto& a_vectors)
{
   for(auto& e: a_vectors)
   {
       --e.second;
   }
}

auto count_smaller(auto const& a_min, auto const& vectors)
{
    auto count = 0;
    for(auto vector: vectors)
    {
        if(get_element(vector, 1) <= get_element(a_min, 0))
        {
            count += vector.second;
        }
    }

    // for(auto vector: vectors)
    // {
    //     if(get_element(vector, 0) <= get_element(a_min, 0))
    //     {
    //         count += 1;
    //     }
    // }
    return count;
}

int smallest_k(auto a_k,auto const& a_vectors)
{
    using namespace std;
    auto vectors = make_pairs(a_k, a_vectors);
    auto m = *min(vectors);
    auto ref_m = reference_wrapper{m};
    advance(vectors);
    // cout << get_element(ref_m.get(), 0) << "\n";
    // cout << vectors[0].second << "\n";
    // cout << ref_m.get().second << "\n";
    while(true)
    {
        auto smaller_elements = count_smaller(ref_m.get(), vectors);
        cout << "min: " << get_element(ref_m.get(), 0) << "\n";
        cout <<"smaller elements: " <<  smaller_elements << "\n";
        if(smaller_elements <= a_k)
        {
            break;
        }
        auto next_m = next_min(ref_m.get(), vectors);
        ref_m = next_m;
        cout <<"\n-----------\n";
    }
    return get_element(ref_m.get(), 0);
}

int main()
{
    using namespace std;

    //test:
    auto first = vector{1,5,9,10,11,19,21,29};
    auto second = vector{-5,0,9,13,14,17};
    auto third = vector{1,8,10,11,12,20};

    auto r = smallest_k(4, vector{first, second, third});
    cout <<"result is: " << r << "\n";
    if(r == 5)
        std::cout << " smallest_k pass\n";
    else
        std::cout << "smallest_k fail\n";

    return 0;
}