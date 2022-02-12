package sort;

public class CountSort {

	public static Object[] sort(Object[] arr, Object base, int size, int keys) {

		CompareClass integerComp = (Object a, Object b) -> { return (int)b - (int)a; };

		return sort(arr, base, size, keys, integerComp);		
	}

	public static Object[] sort(Object[] arr, Object base, int size, int keys, CompareClass func) {
		if (base == null) throw new NullPointerException(); 

		int[] counts = new int[keys];
		Object[] temp = new Object[size];

		for(int j = 0; j < keys; j++)
			counts[j] = 0;

		for(int t = 0; t < size; t++)
			++counts[func.compare(base, arr[t])];
		
		for(int j = 1; j < keys; j++) 
			counts[j] += counts[j-1];

		for(int t = size; t > 0; t--)
			temp[(--counts[func.compare(base, arr[t-1])])] = arr[t-1];

		return temp;
	}
}