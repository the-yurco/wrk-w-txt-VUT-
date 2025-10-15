#!/bin/bash
#
# Tests for 1. IZP project [2023, 2025]
# Author: _ramb0_
# Forked and currently maintained by: Toaster
# Usage:
#     1.) In the project folder run this: wget https://gist.githubusercontent.com/Toaster192/2a4fc166dd8ee334cbabe3e9e571cc6c/raw/test_keyfilter.sh
#     2.) Then (for adding permission): chmod u+x test_keyfilter.sh 
#     3.) finally: ./test_keyfilter.sh


# Color codes
RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m' # No Color

# Compile the program
gcc -std=c11 -Wall -Wextra -Werror keyfilter.c -o keyfilter

run_test() {
	input_file=$1
	test_arg=$2
	expected_output=$3

	echo -n "Running test with input from $input_file and argument ${test_arg:0:10}... "

		actual_output=$(cat "$input_file" | ./keyfilter "$test_arg")
		# changed this to dump to stdin instead of redirecting to perhaps catch some people who use rewind and other bullshit
		if [[ "$actual_output" == "$expected_output" ]]; then
			echo -e "${GREEN}PASSED${NC}"
		else
			echo -e "${RED}FAILED${NC}"
			echo "Expected: $expected_output"
			echo "Got:      $actual_output"
		fi
	}

# Test cases
echo -e "Praha\nBrno\nBruntal\nBratislava" > test_01.txt

run_test "test_01.txt" "" "Enable: BP"

run_test "test_01.txt" "b" "Enable: R"
run_test "test_01.txt" "B" "Enable: R"

run_test "test_01.txt" "br" "Enable: ANU"
run_test "test_01.txt" "BR" "Enable: ANU"

run_test "test_01.txt" "brn" "Found: BRNO"
run_test "test_01.txt" "BRN" "Found: BRNO"

run_test "test_01.txt" "be" "Not found"
run_test "test_01.txt" "BE" "Not found"

# More complex file
echo -e "Praha\nBrno\nBruntal\nBratislava\nBerlin\nBudapest\nPrague\nBrunswick\nBritain\nBrazil\nBremen" > test_02.txt

run_test "test_02.txt" "" "Enable: BP"

run_test "test_02.txt" "b" "Enable: ERU"

run_test "test_02.txt" "br" "Enable: AEINU"
run_test "test_02.txt" "BR" "Enable: AEINU"

run_test "test_02.txt" "bru" "Enable: N"
run_test "test_02.txt" "BRU" "Enable: N"

run_test "test_02.txt" "brun" "Enable: ST"

run_test "test_02.txt" "brunt" "Found: BRUNTAL"

run_test "test_02.txt" "be" "Found: BERLIN"

run_test "test_02.txt" "ber" "Found: BERLIN"

run_test "test_02.txt" "berl" "Found: BERLIN"

run_test "test_02.txt" "bremen" "Found: BREMEN"

run_test "test_02.txt" "p" "Enable: R"

echo -e "TohleJeTestNaStoCharakteruDlouhejRadekJestliNahodouJsiTamNeudelalChybickuFrajereJustAskingYouKnowHeh" > test_03.txt

run_test "test_03.txt" "to" "Found: TOHLEJETESTNASTOCHARAKTERUDLOUHEJRADEKJESTLINAHODOUJSITAMNEUDELALCHYBICKUFRAJEREJUSTASKINGYOUKNOWHEH"

# Test special characters
echo -e " \n1\n2\n3\n!\n:\n_\n;\n~\nA\nB\nc" > test_04.txt

run_test "test_04.txt" "" "Enable:  !123:;ABC_~"

#white spaces
echo -e "\nBratislava\nBrno hl.n.\nBrno hl.aut.n\nBrno\nBruntal" > test_05.txt

run_test "test_05.txt" "brno h" "Enable: L"
run_test "test_05.txt" "brno hl." "Enable: AN"

# Empty line
echo -e "Praha\nBrno\n\n" > test_06.txt

# Commenting as I'm not sure how this one should work, since the line is "" and we're searching for "" this could be a "Found: " I guess
# run_test "test_06.txt" "" "Enable: BP"

# Found + Enable
echo -e "Brno\nBrnovice\n" > test_07.txt

run_test "test_07.txt" "brno" 'Found: BRNO
Enable: V' # I hate this but it works

rm test_07.txt
rm test_06.txt
rm test_05.txt
rm test_04.txt
rm test_03.txt
rm test_02.txt
rm test_01.txt