#include <iostream>
#include <vector>
#include <omp.h>
#include <climits>
#include<chrono>
#include<iomanip>

using namespace std;
using namespace std::chrono;

void min_reduction(int arr[], int n) {
  auto start=high_resolution_clock::now();
  int min_value = INT_MAX;
  #pragma omp parallel for reduction(min: min_value)
  for (int i = 0; i < n; i++) {
	if (arr[i] < min_value) {
  	min_value = arr[i];
	}
  }
  cout << "Minimum value: " << min_value << endl;
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<nanoseconds>(stop - start).count() / 1e9;
  cout << "\nParallel MIN_REDUCTION Execution Time: " << fixed << setprecision(10) << duration << " seconds" << endl;
}

void max_reduction(int arr[], int n) {
  auto start=high_resolution_clock::now();
  int max_value = INT_MIN;
  #pragma omp parallel for reduction(max: max_value)
  for (int i = 0; i < n; i++) {
	if (arr[i] > max_value) {
  	max_value = arr[i];
	}
  }
  cout << "Maximum value: " << max_value << endl;
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<nanoseconds>(stop - start).count() / 1e9;
  cout << "\nParallel MAX_REDUCTION Execution Time: " << fixed << setprecision(10) << duration << " seconds" << endl;
}


void sum_reduction(int arr[], int n) {
  auto start=high_resolution_clock::now();
  int sum = 0;
   #pragma omp parallel for reduction(+: sum)
   for (int i = 0; i < n; i++) {
	sum += arr[i];
  }
  cout << "Sum: " << sum << endl;
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<nanoseconds>(stop - start).count() / 1e9;
  cout << "\nParallel SUM_REDUCTION Execution Time: " << fixed << setprecision(10) << duration << " seconds" << endl;
}

void average_reduction(int arr[], int n) {
  auto start=high_resolution_clock::now();
  int sum = 0;
  #pragma omp parallel for reduction(+: sum)
  for (int i = 0; i < n; i++) {
	sum += arr[i];
  }
  cout << "Average: " << (double)sum / (n) << endl;
  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<nanoseconds>(stop - start).count() / 1e9;
  cout << "\nParallel AVERAGE_REDUCTION Execution Time: " << fixed << setprecision(10) << duration << " seconds" << endl;
}

int main() {
    int *arr,n;
    cout<<"\n enter total no of elements=>";
    cin>>n;
    arr=new int[n];
    cout<<"\n enter elements=>";
    for(int i=0;i<n;i++)
    {
   	 cin>>arr[i];
    }
  min_reduction(arr, n);
  max_reduction(arr, n);
  sum_reduction(arr, n);
  average_reduction(arr, n);
}