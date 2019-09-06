#include <time.h>
#include <iomanip>
#include <chrono>
#include <unistd.h>
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct Node{
    int key;
    struct Node *left, *right;
};

struct Node *newNode(int item){
    struct Node *temp = new Node;
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

struct bucket{
    int count;
    int* value;
};

int compareIntegers(const void* first, const void* second){
    int x = ((int)first), y =  ((int)second);
    if (x == y){
        return 0;
    }
    else if (x < y){
        return -1;
    }
    else{
        return 1;
    }
}

void storeSorted(Node *root, int arr[], int &i){
    if (root != NULL)    {
        storeSorted(root->left, arr, i);
        arr[i++] = root->key;
        storeSorted(root->right, arr, i);
    }
}

Node* insert(Node* node, int key){
    if (node == NULL) return newNode(key);
    if (key < node->key)
        node->left  = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    return node;
}

int getMax(int arr[], int n){
    int mx = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > mx)
            mx = arr[i];
    return mx;
}

void swap(int *xp, int *yp){
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void heapify(int arr[], int n, int i){
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest])
        largest = l;

    if (r < n && arr[r] > arr[largest])
        largest = r;

    if (largest != i) {
        swap(arr[i], arr[largest]);

        heapify(arr, n, largest);
    }
}

void merge(int *a, int low, int high, int mid){
  int i, j, k, temp[high - low + 1];
  i = low;
  k = 0;
  j = mid + 1;

  while(i <= mid && j <= high){
    if(a[i] < a[j]){
      temp[k] = a[i];
      k++;
      i++;
    } else {
      temp[k] = a[j];
      k++;
      j++;
    }
  }

  while(i <= mid){
    temp[k] = a[i];
    k++;
    i++;
  }

  while(j <= high){
    temp[k] = a[j];
    k++;
    j++;
  }

  for (i = low; i <= high; i++){
    a[i] = temp[i-low];
  }

}

void mergeSort(int *a, int low, int high){
  int mid;
	if (low < high)	{
		mid=(low+high)/2;
		mergeSort(a, low, mid);
		mergeSort(a, mid+1, high);

		merge(a, low, high, mid);
	}
  // https://www.geeksforgeeks.org/merge-sort/
}

int partition (int arr[], int low, int high){
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++){
        if (arr[j] < pivot){
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void bubbleSort(int array[], int n){
  for(int i = 0; i < n - 1; i++){
    for(int j = 0; j < n - i - 1; j++){
      if(array[j] > array[j+1]){
        int temp = array[j];
        array[j] = array[j+1];
        array[j+1] = temp;
      }
    }
  }
  //obtenido de mis códigos realizados en otra clase
}

void cocktailSort(int a[], int n){
  bool swapped = true;
  int start = 0;
  int end = n - 1;

  while (swapped) {
    swapped = false;
    for (int i = start; i < end; ++i) {
      if (a[i] > a[i + 1]) {
        swap(a[i], a[i + 1]);
        swapped = true;
      }
    }

    if (!swapped)
      break;
    swapped = false;
    --end;
    for (int i = end - 1; i >= start; --i) {
      if (a[i] > a[i + 1]) {
        swap(a[i], a[i + 1]);
        swapped = true;
      }
    }

    ++start;
    }
    // https://www.geeksforgeeks.org/cpp-program-for-cocktail-sort/
}

void insertionSort(int array[], int n){
  for (int i = 1; i < n; i ++){
    int temp = array[i];
    for(int j = i - 1; j>= 0 && array[j] > temp; j--){
      array[j + 1]= array[j];
      array[j] = temp;
    }
  }
  //https://www.geeksforgeeks.org/insertion-sort/
}

void bucketSort(int array[],int n){
    struct bucket buckets[3];
    int i, j, k;
    for (i = 0; i < 3; i++){
        buckets[i].count = 0;
        buckets[i].value = (int*)malloc(sizeof(int) * n);
    }

    for (i = 0; i < n; i++){
        if (array[i] < 0){
            buckets[0].value[buckets[0].count++] = array[i];
        }
        else if (array[i] > 10){
            buckets[2].value[buckets[2].count++] = array[i];
        }
        else{
            buckets[1].value[buckets[1].count++] = array[i];
        }
    }
    for (k = 0, i = 0; i < 3; i++){
        qsort(buckets[i].value, buckets[i].count, sizeof(int), &compareIntegers);
        for (j = 0; j < buckets[i].count; j++){
            array[k + j] = buckets[i].value[j];
        }
        k += buckets[i].count;
        free(buckets[i].value);
    }
    //https://www.geeksforgeeks.org/bucket-sort-2/
}

void countingSort(vector <int>& arr){
    int max = *max_element(arr.begin(), arr.end());
    int min = *min_element(arr.begin(), arr.end());
    int range = max - min + 1;

    vector<int> count(range), output(arr.size());
    for(int i = 0; i < arr.size(); i++)
        count[arr[i]-min]++;

    for(int i = 1; i < count.size(); i++)
           count[i] += count[i-1];

    for(int i = arr.size()-1; i >= 0; i--)
    {
         output[ count[arr[i]-min] -1 ] = arr[i];
              count[arr[i]-min]--;
    }

    for(int i=0; i < arr.size(); i++)
            arr[i] = output[i];

  //https://www.geeksforgeeks.org/counting-sort/
}

void binaryTreeSort(int arr[], int n){
    struct Node *root = NULL;
    root = insert(root, arr[0]);
    for (int i=1; i<n; i++)
        insert(root, arr[i]);
    int i = 0;
    storeSorted(root, arr, i);
    //https://www.geeksforgeeks.org/tree-sort/
}

void countSort(int arr[], int n, int exp){
    int output[n];
    int i, count[10] = {0};

    for (i = 0; i < n; i++)
        count[ (arr[i]/exp)%10 ]++;

    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (i = n - 1; i >= 0; i--) {
        output[count[ (arr[i]/exp)%10 ] - 1] = arr[i];
        count[ (arr[i]/exp)%10 ]--;
    }

    for (i = 0; i < n; i++)
        arr[i] = output[i];
}

void radixSort(int arr[], int n){
  int m = getMax(arr, n);

  for (int exp = 1; m/exp > 0; exp *= 10)
      countSort(arr, n, exp);

  //https://www.geeksforgeeks.org/radix-sort/
}

void shellSort(int arr[], int n){
  for (int gap = n/2; gap > 0; gap /= 2) {
      for (int i = gap; i < n; i += 1){
          int temp = arr[i];
          int j;
          for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
              arr[j] = arr[j - gap];
          arr[j] = temp;
      }
  }
  //https://www.geeksforgeeks.org/shellsort/
}

void selectionSort(int arr[], int n){
  int i, j, min_idx;

  for (i = 0; i < n-1; i++)  {
      min_idx = i;
      for (j = i+1; j < n; j++)
      if (arr[j] < arr[min_idx])
          min_idx = j;

      swap(&arr[min_idx], &arr[i]);
  }

  //obtenido de mis códigos realizados en clases anteriores
}

void heapSort(int arr[], int n){
  for (int i = n / 2 - 1; i >= 0; i--)
      heapify(arr, n, i);

  for (int i = n - 1; i >= 0; i--) {
      swap(arr[0], arr[i]);
      heapify(arr, i, 0);
  }

  //https://www.geeksforgeeks.org/cpp-program-for-heap-sort/
}

void quickSort(int arr[], int low, int high){
  if (low < high)  {
      int pi = partition(arr, low, high);
      quickSort(arr, low, pi - 1);
      quickSort(arr, pi + 1, high);
  }
  //https://www.geeksforgeeks.org/quick-sort/
}

int main(){
  int size = 0;
  int algorithm = 12;

  cout << "Type in the size of your array. Choose from the following list: " << endl;
  cout << "1. 10\n2. 100\n3. 1 000\n4. 10 000\n5. 100 000\n6. 200 000\n";
    cin >> size;

  //creating the array with random numbers
  int array[size+1];
  for(int i = 0; i < size; i++){
    array[i] = rand() % 200 + 1;
  }

  cout << "\nSORTING ALGORITHM\t  ELAPSED TIME (ms)\n" << "____________________________________________" << endl;
  for(int i = 1; i <= algorithm; i++){
    //creating a copy of they original array
    int arrayCopy[size+1];
    for(int i = 0; i < size; i++){
      arrayCopy[i] = array[i];
    }
    switch(i){
      case 1: //BubbleSort
      {
        auto start = chrono::steady_clock::now();
        bubbleSort(array, size);
        auto end = chrono::steady_clock::now();
        cout << "\nBubble Sort\t\t\t" << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms\n" << endl;
      }
      break;
      case 2: //CocktailSort
      {
        auto start = chrono::steady_clock::now();
        cocktailSort(array, size);
        auto end = chrono::steady_clock::now();
        cout << "Cocktail Sort\t\t\t" << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms\n" << endl;
      }
      break;
      case 3://Insertion Sort
      {
        auto start = chrono::steady_clock::now();
        insertionSort(array, size);
        auto end = chrono::steady_clock::now();
        cout << "Insertion Sort\t\t\t" << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms\n" << endl;
      }
      break;
      case 4: //Bucket Sort
      {
        auto start = chrono::steady_clock::now();
        bucketSort(array, size);
        auto end = chrono::steady_clock::now();
        cout << "Bucket Sort\t\t\t" << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms\n" << endl;
      }
      break;
      case 5: //Counting Sort
      {
        //array into vector
        vector<int> vec;

        for(int i = 0; i < size; ++i){
          vec.push_back(array[i]);
        }

        auto start = chrono::steady_clock::now();
        countingSort(vec);
        auto end = chrono::steady_clock::now();
        cout << "Counting Sort\t\t\t" << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms\n" << endl;
      }
      break;
      case 6: //Merge sort
      {
        auto start = chrono::steady_clock::now();
        mergeSort(array, 0, size-1);
        auto end = chrono::steady_clock::now();
        cout << "Merge Sort\t\t\t" << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms\n" << endl;
      }
      break;
      case 7: //Binary Tree sort
      {
        auto start = chrono::steady_clock::now();
        binaryTreeSort(array, size);
        auto end = chrono::steady_clock::now();
        cout << "Binary Tree Sort\t\t" << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms\n" << endl;
      }
      break;
      case 8: //Radix sort
      {
        auto start = chrono::steady_clock::now();
        radixSort(array, size);
        auto end = chrono::steady_clock::now();
        cout << "Radix Sort\t\t\t" << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms\n" << endl;
      }
      break;
      case 9: //Shell sort
      {
        auto start = chrono::steady_clock::now();
        shellSort(array, size);
        auto end = chrono::steady_clock::now();
        cout << "Shell Sort\t\t\t" << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms\n" << endl;
      }
      break;
      case 10: //Selection Sort
      {
        auto start = chrono::steady_clock::now();
        selectionSort(array, size);
        auto end = chrono::steady_clock::now();
        cout << "Selection Sort\t\t\t" << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms\n" << endl;
      }
      break;
      case 11: //Heap sort
      {
        auto start = chrono::steady_clock::now();
        heapSort(array, size);
        auto end = chrono::steady_clock::now();
        cout << "Heap Sort\t\t\t" << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms\n" << endl;
      }
      break;
      case 12: //Quick sort
      {
        auto start = chrono::steady_clock::now();
        quickSort(array, 0, size - 1);
        auto end = chrono::steady_clock::now();
        cout << "Quick Sort\t\t\t" << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms\n" << endl;
      }
      break;
    }
  }
  return 0;
}
