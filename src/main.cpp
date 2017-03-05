#include <iostream>
#include <map>

#include "string_bst.hpp"
#include "max_heap.hpp"
#include "text_item.hpp"
#include "util.hpp"

using namespace std;

//--- PART 1A: Implementation and testing of heap insert
void heap_insert_tests(max_heap &hp) {
	text_item temp;
	std::string word = "item";
	int random_num;
	long int seed = long(time(0));    // seed for random number generator
	srand(seed);
	
	//--- Testing insert functionality
	std::cout << "*** TESTING INSERT ***" << std::endl;
	//--- This adds 5 items to the heap with random numbers
	//    and prints out the top, but it does not fully 
	//    test the correctness of the insert function.
	for (int i = 0 ; i < 5; i++) {
		random_num = rand() % 100;
		string text = word;
		text += std::to_string(i+1);
		std::cout << "adding " << text << ",  with number " << random_num << " to heap" << std::endl;
		hp.insert(text_item{text, random_num});	
		temp = hp.top();
		std::cout << "Top of heap is: " << temp << std::endl;		
	}
	
	//--- Specific insert functionality that should be tested:
	
	// insert without any swap_ups needed
    string text1 = "noswaptest";
    int num1 = 0;
    hp.insert(text_item{text1,num1});
    temp = hp.bottom();
    std::cout << "Last item in the heap is (noswaptest,0): " << temp << std::endl;
    
    
	// insert with a swap_up / multiple swap_ups
    string text2 = "multiswaptest";
    int num2 = 101;
    hp.insert(text_item{text2,num2});
    temp = hp.top();
    std::cout << "Top of heap is (multiswaptest, 101): " << temp << std::endl;
}

//--- PART 1B: Implementation and testing of heap delete
void heap_delete_tests(max_heap &hp) {
	text_item temp;
	
	//--- Testing deleteMax functionality
	std::cout << "*** TESTING DELETEMAX ***" << std::endl;
	//--- This does not fully test delete_max functionality.
    
	if (hp.size() > 1) {
		temp = hp.delete_max();
		std::cout << "Item returned from heap delete (multiswaptest,101): "<< temp << std::endl;
		temp = hp.top();
		std::cout << "Top of heap is now: " << temp << std::endl;	
	}
    
    // starting with a max heap with 6 items
    hp.insert(text_item{"testitem0", 10});
    hp.insert(text_item{"testitem1", 130});
    hp.insert(text_item{"testitem2", 120});
    hp.insert(text_item{"testitem3", 110});
    hp.insert(text_item{"testitem4", 100});
    hp.insert(text_item{"testitem5", 125});
    temp = hp.top();
    std::cout << "Top of heap is now (testitem1,130): " << temp << std::endl;
    
	//--- Specific delete functionality that should be tested:
    
	// remove_max works when swap_down with right child
    temp = hp.delete_max();
    std::cout << "Item returned from heap delete (testitem1, 130): "<< temp << std::endl;
    temp = hp.top();
    std::cout << "Top of heap is now the right child (testitem5, 125): " << temp << std::endl;
		
	// remove_max works when swap_down with left child
    temp = hp.delete_max();
    std::cout << "Item returned from heap delete (testitem5, 125): "<< temp << std::endl;
    temp = hp.top();
    std::cout << "Top of heap is now the left child (testitem5, 120): " << temp << std::endl;
		
    for(int i = hp.size(); i > 0; i--)
        hp.delete_max();
    
	// remove_max on an empty heap (should throw exception similar to top())
    try {
        std::cout << "Deleting item from an empty heap. Size: "<< hp.size() << std::endl;
        hp.delete_max();
    } catch (std::logic_error e) {
        std::cout << e.what() << std::endl;
    }
		
}

//--- PART 2: Implementation and testing of BST word_frequency
void tree_tester(string_bst const &tree) {
	std::cout << std::endl << "BEGINNING TESTS FOR PART 2" << std::endl;
	
	//--- Testing word_frequency functionality
	//--- This does not fully test word_frequency functionality.
	if (tree.size() > 1) {
		string to_find = "is";
		int num_times = tree.word_frequency(to_find);
		std::cout << "Found: "<< to_find << 
			" in the input file " << num_times 
			<< " time(s)." << std::endl;
	}
	
	//--- Specific word_frequency functionality that should be tested:

    // The map includes words that are in the sample file as well as words that are not
    // therefore taking care of all test cases.
    map<string, int> test_map = {
        {"index", 1},
        {"of", 2},
        {"words", 2},
        {"is", 3},
        {"difficult", 1},
        {"to", 4},
        {"calculate", 2},
        {"alphabetically", 2},
        {"if", 1},
        {"not", 2},
        {"careful", 1},
        {"and", 2},
        {"when", 3},
        {"attention", 1},
        {"detail", 1},
        {"each", 1},
        {"word", 2},
        {"considered", 1},
        {"carefully", 1},
        {"because", 1},
        {"a", 4},
        {"and", 1},
        {"taken", 1},
        {"one", 1},
        {"letter", 1},
        {"at", 1},
        {"time", 1},
        {"deciding", 1},
        {"how", 1},
        {"sort", 1},
        {"implement", 1},
        {"bst", 1},
        {"writing", 1},
        {"function", 1},
        {"ruishen", 0},
        {"computer", 0},
        {"123", 0}
    };
    
    int numPassedWords = 0;
    
    for(auto const& word : test_map){
        cout << "Testing word frequency of *"<< word.first << "* in sample1.txt. " << endl;
        int freq = tree.word_frequency(word.first);
        cout << "Expected word frequency: " << word.second << " Returned word frequency: "<< freq << endl;
        if(word.second == freq )
            cout << "Frequency match confirmed. Test Passed for "<< word.first << endl;
        else{
            cout << "TEST FAILED." << endl;
            break;
        }
        numPassedWords++;
    }
    if(numPassedWords == test_map.size())
        cout << "ALL TESTS PASSED!!!!!" << endl;
}

//--- PART 3: Implementation and testing of word frequency analysis
void overall_most_freq(max_heap hp) {

    for(int i = 0; i < 5; i++){
        try {
            // deleting the maximum word in the heap and printing it
            cout << hp.delete_max() << endl;
        } catch (std::logic_error e) {
            break;
        }
    }
}

void at_least_length(max_heap hp, size_t num_letters) {
	cout << "*** Top 5 most frequent words with at least " 
		<< num_letters << " letters ***" << std::endl;
		
	//--- Add code to print out the 5 most common
	//--- words of length at least <num_letters>
    int heap_size = hp.size();
    max_heap* new_hp = new max_heap(heap_size);
    
    for(int i=0; i < heap_size; i++){
        try {
            text_item top = hp.delete_max();
            if(top.word.length() >= num_letters)
                (*new_hp).insert(top);
        } catch (std::logic_error e) {
            std::cout << e.what() << std::endl;
        }
    }

    overall_most_freq(*new_hp);
}

void starts_with(max_heap hp, char starts_with_letter) {
	cout << "*** Top 5 most frequent words that begin with " 
		<< starts_with_letter << " ***" << std::endl;
		
	//--- Add code to print out the 5 most common words
	//--- that start with the letter <starts_with_letter>

    int heap_size = hp.size();
    max_heap* new_heap = new max_heap(heap_size);
    
    for(int i=0; i < heap_size; i++){
        try {
            text_item top = hp.delete_max();
            if(top.word.at(0) == starts_with_letter)
                (*new_heap).insert(top);
        } catch (std::logic_error e){
            std::cout << e.what() << std::endl;
        }
    }
	overall_most_freq(*new_heap);
}

void heap_tester() {	
	text_item temp;
	int heap_size = 20; //feel free to create heaps of other sizes when testing
	//cout << "How many items should be added to heap? ";
	//cin >> heap_size;
	max_heap hp(heap_size);
	std::cout << "Created heap of size " << heap_size << std::endl;
		
	//--- Testing heap size and top
	std::cout << "Current number of items in heap is: " << hp.size() << std::endl;
	try {
		temp = hp.top(); //should throw and exception without items in heap
		std::cout << "Top of heap is: " << temp << std::endl;	
	} catch (std::logic_error e) {
		std::cout << e.what() << std::endl;
	}
	// PART 1A:
	std::cout << std::endl << "BEGINNING TESTS FOR PART 1A" << std::endl;
	heap_insert_tests(hp);
	// PART 1B:
	std::cout << std::endl << "BEGINNING TESTS FOR PART 1B" << std::endl;
	heap_delete_tests(hp);
}

void text_analysis_tester(string_bst &tree) {
	std::cout << std::endl << "BEGINNING TESTS FOR PART 3" << std::endl;
    std::cout << "*** Top 5 most frequent words: ***" << std::endl;
	overall_most_freq(copy_to_heap(tree));
	std::cout << std::endl;
	at_least_length(copy_to_heap(tree), 8); // change the 8 to test other string-lengths
	std::cout << std::endl;
	starts_with(copy_to_heap(tree), 'c'); // change the 'c' to test words that starts_with_letter
											// with different characters
}

int main(int argc, char* argv[]) {
	
	//--- Part 1: max_heap implementation
	heap_tester();
    
	//--- Part 2: string_bst implementation
	string_bst tree;
	load_bst("/Users/WilliamChoi/Desktop/cs221/project2/word-frequency/src/sample1.txt", tree); // create a bst from an input file.
	tree_tester(tree);			//sample2.txt contains a much bigger file
	
	//--- Part 3: word frequency analysis of text files
	text_analysis_tester(tree);

}
