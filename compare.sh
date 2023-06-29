#!/bin/bash
./ft_containers > ft_test
./std_containers > std_test
diff --text --color=always ft_test std_test
echo "Comparison done"