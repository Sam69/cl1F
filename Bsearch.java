import java.util.Arrays;
import java.util.Scanner;
class Bsearch
{
    int binarySearch(int arr[], int x)
    {
        int l = 0, r = arr.length - 1;
        while (l <= r)
        {
            int m = l + (r-l)/2;
 
            // Check if x is present at mid
            if (arr[m] == x)
                return m;
 
            // If x greater, ignore left half
            if (arr[m] < x)
                l = m + 1;
 
            // If x is smaller, ignore right half
            else
                r = m - 1;
        }
 
        // if we reach here, then element was not present
        return -1;
    }
 
    // Driver method to test above
    public static void main(String args[])
    {
        Bsearch ob = new Bsearch();
	Scanner sc = new Scanner(System.in);
	System.out.println("Enter no.of elements: ");
	int n = sc.nextInt();
        System.out.println("Enter array elements: ");
	int arr[] = new int[n];
	for(int i=0; i<n; i++)
	{
		arr[i] = sc.nextInt();
	}
	Arrays.sort(arr);
	System.out.println("Enter element to be searched for:");
	int x = sc.nextInt();
        int result = ob.binarySearch(arr, x);
        if (result == -1)
            System.out.println("Element not present");
        else
            System.out.println("Element found at index "+result+" in sorted array.");
    }
}
