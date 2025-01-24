//Jake Baartman
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <ctime>
#include <cstdlib>

using namespace std;

//Is Sorted Check
bool isSorted(const vector<int>& arr) {
  //Loop through the array starting from index 1
  for(int i = 1; i < arr.size(); i++) {
    if(arr[i] < arr[i - 1]) {
      return false; //if element is smaller than previous
    }
  }
  
  return true; //if no element
}

//Bubble Sort
void bubbleSort(vector<int>& arr) {
  int n = arr.size(); //get size of array
  //outer loop for each pass 
  for(int i = 0; i < n-1; i++) {
    //inner loop to compare elements
    for(int j = 0; j < n-i-1; j++) {
      //swap elements in wrong order
      if(arr[j] > arr[j+1]) {
        int temp = arr[j]; //swap
        arr[j] = arr[j+1];
        arr[j+1] = temp;
      }
    }
  }
}

//Insertion Sort
void insertionSort(vector<int>& arr) {
  int n = arr.size();
  for(int i = 1; i < n; i++) {
    int key = arr[i]; //current element to be inserted
    int j = i - 1; //previous element
    //shift elements > key
    while(j >= 0 && arr[j] > key) {
      arr[j+1] = arr[j];
      j--;
    }
    arr[j+1] = key; //place key in correct position
  }
}

//Selection Sort
void selectionSort(vector<int>& arr) {
  int n = arr.size(); //get size 
  //outer loop for each element
  for(int i = 0; i < n - 1; i++) {
    int min = i; //assume current is smallest
    //find min
    for(int j = i + 1; j < n; j++) {
      if(arr[j] < arr[min]) {
        min = j;
      }
    }
    //swap min
    int temp = arr[i];
    arr[i] = arr[min];
    arr[min] = temp;
  }
}

//Quicksort
int partition(vector<int>& arr, int low, int high) {
  int pivot = arr[high]; //select the last element
  int n = low - 1; //smaller index

  //reorder based on pivot
  for(int i = low; i < high; i++) {
    //if current is smaller or equal to pivot
    if(arr[i] <= pivot) {
      n++; //incrememnt the index of smaller element
      //swap to move smaller elements left
      int temp = arr[n];
      arr[n] = arr[i];
      arr[i] = temp;
    }
  }
  //swap pivot element with element at n+1
  int temp = arr[n + 1];
  arr[n + 1] = arr[high];
  arr[high] = temp;
  return n + 1;
}

//Quicksort
void quickSort(vector<int>& arr, int low, int high) {
  //sort only if array contains more than 1
  if(low < high) {
    //get pivot index
    int p = partition(arr, low, high);
    //recursive sort
    quickSort(arr, low, p - 1); //sort left half
    //recursive sort
    quickSort(arr, p + 1, high); //sort right half
  }
}

//Quicksort (overloaded to call without parameters)
void quickSort(vector<int>& arr) {
  quickSort(arr, 0, arr.size() - 1); //call with full array range
}

//useful code snippets
//calculate mean of a vector of doubles
double getMean(const vector<double>& v) {
  double sum = 0;
  for (int i = 0; i < v.size(); i++) {
    sum += v[i];
  }
  return sum / v.size();
}

//useful code snippets
//Utility function to calculate standard deviation
double sampleSD(const vector<double>& v) {
  double mean = getMean(v);
  double sd = 0;

  for (int i = 0; i < v.size(); i++) {
      sd += (v[i] - mean) * (v[i] - mean);
  }
  sd = sd / (v.size() - 1);
  return sqrt(sd);
}

//useful code snippets
//Generate random vector
vector<int> randomVector(int size, int low, int high) {
  vector<int> v(size, 0);

  for (int i = 0; i < size; i++) {
    v[i] = rand() % (high - low + 1) + low;
  }
  return v;
}

//function to generate a sorted vector
vector<int> generateBestCase(int size) {
  vector<int> v(size); //initialize vector
                       
  //loop to assign increasing values to the vector
  for (int i = 0; i < size; i++) {
    v[i] = i;
  }
  return v;
}

//function to generate a reverse sorted vector
vector<int> generateWorstCase(int size) {
  vector<int> v(size); //initialize vector

  //loop to assign decreasing values to the vector
  for (int i = 0; i < size; i++) {
      v[i] = size - i;
  }
  return v;
}

//function to find min value in a vector of times
double getMinTime(const vector<double>& v) {
  double min = v[0]; //assume first element is the min
                     
  //loop to find the min value
  for (int i = 1; i < v.size(); i++) {
      if (v[i] < min) {
          min = v[i];
      }
  }
  return min;
}

//function to find the maximum value in a vector of times
double getMaxTime(const vector<double>& v) {
  double max = v[0]; //assume first element is the max

  //loop to find max value
  for (int i = 1; i < v.size(); i++) {
      if (v[i] > max) {
          max = v[i];
      }
  }
  return max;
}


// Function to run simple benchmark
void runSimpleBenchmark(const string& name, void (*sortFunc)(vector<int>&)) {
  const int NUM_TESTS = 10; //number of test cases
  const int VECTOR_SIZE = 100; //size of vectors
  vector<double> times; //store runtimes
  
  //print header
  cout << "************************\n";
  cout << name << " sort on " << NUM_TESTS << " vectors of length " << VECTOR_SIZE << "\n";
    
  bool success = true; //flag check
  for(int i = 0; i < NUM_TESTS; i++) {
    //generate random vector for each test
    vector<int> vec = randomVector(VECTOR_SIZE, 1, 1000);
 
    //record start time
    clock_t start = clock();
    //run sorting function
    sortFunc(vec);
    //record end time
    clock_t end = clock();

    //check if sorted correctly
    for (int j = 1; j < vec.size(); j++) {
      if (vec[j] < vec[j-1]) {
        success = false; //sorting
        break;
      }
    }
    
    //duration calculation
    double duration = double(end - start) / CLOCKS_PER_SEC;
    times.push_back(duration); 
  }
    
  //get min time from list of recorded times
  double min_time = getMinTime(times);
  //get max time
  double max_time = getMaxTime(times);
  //calculate mean 
  double mean = getMean(times);
  //calculate standard deviation
  double std_dev = sampleSD(times); 
  
  //print results
  cout << "Sorting " << (success ? "successful" : "failed") << "\n";
  //set precision for floating-point output
  cout.precision(6);
  //set formatting for output
  cout.setf(ios::fixed, ios::floatfield);
  //print min, mean, sd, and max
  cout << "Minimum: " << min_time << " sec; "
       << "Mean: " << mean << " sec; "
       << "Standard deviation: " << std_dev << " sec; "
       << "Maximum: " << max_time << " sec\n";
  cout << "************************\n";
}

//stores sorting algroithm details
struct SortingAlgorithm {
  string name;
  void (*func)(vector<int>&); //sorting function pointer

  //constructor to intialize the struct with alg name and function
  SortingAlgorithm(const string& algoName, void (*sortFunc)(vector<int>&)) {
    name = algoName;
    func = sortFunc;
  }
};

// Function to run comprehensive benchmark
void runComprehensiveBenchmark() {
  vector<int> sizes; //vector to store different input sizes
  sizes.push_back(10);
  sizes.push_back(100);
  sizes.push_back(1000);
  sizes.push_back(5000);
  sizes.push_back(10000);
    
  const int REPEATS = 50; //number of times each test will be repeated
  
  //output csv
  ofstream best_case("best_case_times.csv");
  ofstream avg_case("average_case_times.csv");
  ofstream worst_case("worst_case_times.csv");
  
  //define a vector of sorting algorithms
  vector<SortingAlgorithm> algorithms;
  algorithms.push_back(SortingAlgorithm("bubble", bubbleSort));
  algorithms.push_back(SortingAlgorithm("insertion", insertionSort));
  algorithms.push_back(SortingAlgorithm("selection", selectionSort));
  algorithms.push_back(SortingAlgorithm("quick", quickSort));
    
  cout << "Running comprehensive benchmark\n";
  
  //loop over all sorting algorithms
  for (int j = 0; j < algorithms.size(); j++) {
    //get algorithm
    string name = algorithms[j].name;
    //get sorting function
    void (*func)(vector<int>&) = algorithms[j].func;
    
    //loop over all input sizes
    for (int i = 0; i < sizes.size(); i++) {
      int size = sizes[i]; //current vector size
      cout << "Testing " << name << " sort with size " << size << "...\n";
        
      //repeat test multiple times
      for (int rep = 0; rep < REPEATS; rep++) {
        // Best case
        {
          vector<int> vec = generateBestCase(size); //generate best case
          clock_t start = clock(); //start timer
          func(vec); //run sorting function
          clock_t end = clock(); //stop timer
          //time calculation(seconds)
          double duration = double(end - start) / CLOCKS_PER_SEC;
          //scientific to convert to scientific notation
          best_case << name << "," << size << "," << scientific << duration << "\n";
        }
          
        // Average case
        {
          vector<int> vec = randomVector(size, 1, 1000); //generate random input
          clock_t start = clock();
          func(vec);
          clock_t end = clock();
          double duration = double(end - start) / CLOCKS_PER_SEC;
          avg_case << name << "," << size << "," << scientific << duration << "\n";
        }
          
        // Worst case
        {
          vector<int> vec = generateWorstCase(size); //generate worst case
          clock_t start = clock();
          func(vec);
          clock_t end = clock();
          double duration = double(end - start) / CLOCKS_PER_SEC;
          worst_case << name << "," << size << "," << scientific << duration << "\n";
        }
      }
    }
  }
 
  //notify the user
  cout << "Benchmark complete. Results written to CSV files.\n";
}

int main() {
  // Run simple benchmarks first
  cout << "Running Simple Benchmarks\n\n";
  runSimpleBenchmark("Bubble", bubbleSort);
  runSimpleBenchmark("Selection", selectionSort);
  runSimpleBenchmark("Insertion", insertionSort);
  runSimpleBenchmark("Quick", quickSort);
  
  //run comprehensive benchmark on all algorithms
  cout << "\nStarting comprehensive benchmark\n";
  runComprehensiveBenchmark();
    
  return 0;
}
