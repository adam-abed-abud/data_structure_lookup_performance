#include <unordered_map>
#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <map>

// Dummy structure to use as value in map
struct ConnectionID
{
    std::string a;
    std::string b;
    int c;
};

// Get a random string of length `length` to use as a map key
std::string random_string(int length)
{
    static std::default_random_engine engine(12345);
    static std::uniform_int_distribution<char> uniform_dist('a', 'z');

    std::string ret;
    for(int i=0; i<length; ++i){
        ret+=uniform_dist(engine);
    }
    return ret;
}


int main(int /* argc */, char** /* argv */)
{
    // The number of entries in the map
    const int n_values = 1000;
    // The length of each string key in the map  
    const int key_length = 100;
    // The number of map lookups to do in the benchmarking step
    const int n_lookups = 1000'000;

    std::vector<std::string> keys;
    std::map<std::string, ConnectionID> hashmap;

    std::default_random_engine engine(123456);
    std::uniform_int_distribution<int> uniform_dist(0, n_values-1);

    // Insert random values into the map
    for(int i=0; i<n_values; ++i){
        std::string key=random_string(key_length);
        keys.push_back(key);
        hashmap[key]=ConnectionID{random_string(3), random_string(4), uniform_dist(engine)};
    }

    
    // Sum up the integer members of the looked-up values in the map
    // to make sure the optimizer doesn't turn the loop into a no-op
    int total = 0;

    // Pick a random array of indexes to look up
    std::vector<int> key_indexes_for_lookup;
    std::uniform_int_distribution<int> uniform_dist2(0, n_values-1);
    for(int idx=0; idx < n_lookups; ++idx){
        int which_key = uniform_dist2(engine);
        key_indexes_for_lookup.push_back(which_key);
    }
    
    
    // Do the actual lookups
    auto start = std::chrono::steady_clock::now();
    for(int i=0; i<n_lookups; ++i){
        const std::string& key = keys[ key_indexes_for_lookup[i] ];
        const ConnectionID& conn_id = hashmap[key];
        total += conn_id.c;
    }
    
    auto end = std::chrono::steady_clock::now();
    std::cout << total << std::endl;
    auto const ms = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
    float MHz = 1e-3*n_lookups/ms;
    std::cout << "Did " << n_lookups << " lookups in " << ms << "ms. " << MHz << "MHz" << std::endl;
    
}