# Lookup Performance of Different Data Structures

Data structures tested are: unordered map, ordered map, vector, deque, unordered multimap. 

Summary of results: 
| Data structure     | Number of elements for lookup | Speed [ms] | Rate [MHz]  |
| ------------------ | ----------------------------- | ---------- | ----------- |
| Unordered map      | 100000                        | 12         | 8.33333     |
| std::map           | 100000                        | 48         | 2.08333     |
| Vector             | 100000                        | 1996       | 0.000501002 |
| unordered multimap | 100000                        | 19         | 5.26316     |
| deque              | 100000                        | 3280       | 0.000304878 |
