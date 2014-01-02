#!/bin/bash





echo "Testing array {-1,3,-5,4,6,-1,2,-7,13,-3} Result should be 17"
echo "Testing using kadane"
      ./kadane 10 -1 3 -5 4 6 -1 2 -7 13 -3
echo "Testing using bentley"
      ./bentley 10 -1 3 -5 4 6 -1 2 -7 13 -3
echo "Testing array {5,5,5,5,5} Result should be 25"
echo "Testing using kadane"
      ./kadane 5 5 5 5 5 5
echo "Testing using bentley"
      ./bentley 5 5 5 5 5 5
