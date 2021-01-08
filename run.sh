echo "-----------your program---------------"
gcc test.s -no-pie -o test-out
./test-out
rm -f test-out
echo "\n----------standard program------------"
gcc std-output/test.s -no-pie -o std-output/test-out
std-output/test-out
rm -f std-output/test-out