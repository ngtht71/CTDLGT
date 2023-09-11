#include <iostream>

using namespace std;

void print_array (int a[], int n)
{
    for (int i = 0; i < n; i++)
        cout << a[i] << ' ';
    cout << endl;
}

//selection sort
int findMin (int a[], int index, int n)
{
    int min_index = index;
    for (int i = index + 1; i < n; i++)
        if (a[i] < a[min_index]) min_index = i;
    return min_index;
}

void selection_sort (int a[], int n)
{
    for (int i = 0; i < n-1; i++)
    {
        int min_index = findMin(a, i, n);
        swap (a[min_index], a[i]);
        cout << "Step " << i+1 << ": ";
        print_array (a, n);
    }
}

//insertion sort
void insert (int a[], int index)
{
    int key = a[index];
    int j = index -1;
    while (j >= 0 && a[j] > key){
        a[j+1] = a[j];
        j--;
    }
    a[j+1] = key;
}

void insertion_sort (int a[], int n)
{
    for (int i = 1; i < n; i++)
    {
        insert(a, i);
        cout << "Step " << i << ": ";
        print_array(a, n);
    }
}

void buble_sort (int a[], int n)
{
    for (int i = 0; i < n-1; i++){
        for (int j = 0; j < n-1-i; j++)
        {
        if (a[j] > a[j+1]) swap (a[j], a[j+1]);
        cout << "Step " << i+1 << "." << j+1 << ": ";
        print_array(a, n);
        }
        cout << "Step " << i+1 << ": ";
        print_array (a, n);
    }
}

void merge_array (int a[], int low, int mid, int high)
{
    // size = 9 -> high = 8, low = 0, mid = 4 --> m = 5, n = 4
    // size = 8 -> high = 7, low = 0, mid = 3 --> m = 4, n = 4
    int m = mid - low + 1;
    int n = high - mid;

    int left[m], right[n];
    for (int i = 0; i < m; i++) left[i] = a[low+i]; // vi dung de quy
    for (int i = 0; i < m; i++) right[i] = a[mid+1+i]; // vi dung de quy

    //print_array (left, m);
    //print_array (right, n);

    int i = 0, j = 0, k = low;
    while (i < m || j < n) {
        if (j >= n || (i < m && left[i] <= right[j]))
            a[k++] = left[i++];
        else
            a[k++] = right[j++];
    }
    while (i < m)
        a[k++] = left[i++];
    while (j < n)
        a[k++] = right[j++];
}

void merge_sort (int a[], int low, int high)
{
    if (low < high){
        int mid = low + (high - low)/2;
        //de quy- recursion - sort nua trc, nua sau
        merge_sort (a, low, mid);
        merge_sort (a, mid+1, high);

        //noi 2 mang
        merge_array (a, low, mid, high);
        cout << "Step: ";
        print_array (a, high);
    }
}


// Partition the array using the last element as the pivot
int partition(int arr[], int low, int high)
{
    // Choosing the pivot
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        // If current element is smaller than the pivot
        if (arr[j] < pivot) {
            // Increment index of smaller element
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quick_sort(int arr[], int low, int high)
{
    if (low < high) {
        // pi is partitioning index, arr[p] is now at right place
        int pi = partition(arr, low, high);

        // Separately sort elements before partition and after partition
        quick_sort(arr, low, pi - 1);
        print_array(arr, high+1);
        quick_sort(arr, pi + 1, high);
        print_array(arr, high+1);
    }
}

void heap_sort(){
}

void radix_sort(){}

int main (){
    int a[] = {3, 4, 5, 6, 7, 8, 9, 10, 1, 2};
    int b[] = {3, 4, 5, 6, 7, 8, 9, 10, 1, 2};
    int c[] = {3, 4, 5, 6, 7, 8, 9, 10, 1, 2};
    int d[] = {3, 4, 5, 6, 7, 8, 9, 10, 1, 2};
    int e[] = {3, 4, 5, 6, 7, 8, 9, 10, 1, 2};

    int n = sizeof (a) / sizeof (a[0]);

    cout << "Unsorted Array: ";
    print_array(a, n);

    cout << "Selection sort Method\n";
    selection_sort (a, n);
    cout << "Selection Sorted Array: ";
    print_array (a, n);

    cout << "Insert sort Method\n";
    insertion_sort (b, n);
    cout << "Insertion Sorted Array: ";
    print_array (b, n);

    cout << "Buble sort Method\n";
    buble_sort (c, n);
    cout << "Buble Sorted Array: ";
    print_array (c, n);

    cout << "Merge sort Method\n";
    merge_sort (d, 0, n-1);
    cout << "Merge Sorted Array: ";
    print_array (d, n);

    cout << "Quick sort Method\n";
    quick_sort (e, 0, n-1);
    cout << "Quick Sorted Array: ";
    print_array (e, n);



    return 0;
}
