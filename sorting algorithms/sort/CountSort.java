package sort;

public class CountSort {

	/*public static <T extends Number> T[] sort(T[] arr) {
		T max = arr[0], min = max;
        for (int i = 1; i < arr.length; ++i) {
            if (arr[i] < min) min = arr[i];
            else if (arr[i] > max) max = arr[i];
        }
        int keys = (max-min+1).intValue();
        if (arr.length < keys) keys = arr.length;
		return sort(arr, min, keys);		
	}
    
    public static <T extends Comparable<? super T>> T[] sort(T[] arr) {
        T base = arr[0];
        for (int i = 1; i < arr.length; ++i)
            if (base.compareTo(arr[i]) > 0) base = arr[i];
        
        return sort(arr, base, arr.length);
    }

	private static T[] sort(T[] arr, T base, int keys) {
		if (arr == null) throw new NullPointerException(); 

		int[] counts = new int[keys];
		T[] temp = new T[size];

		for(int j = 0; j < keys; j++)
			counts[j] = 0;

		for(int t = 0; t < size; t++)
			++counts[base.compareTo(arr[t])];
		
		for(int j = 1; j < keys; j++) 
			counts[j] += counts[j-1];

		for(int t = size; t > 0; t--)
			temp[(--counts[base.compare(arr[t-1])])] = arr[t-1];

		return temp;
	}*/

	public static <T extends Object> T[] sort(T[] arr, int keys, MyInt func) {
        int[] mm = mm(arr, func);
        int min = mm[0], max = mm[1];

        int[] counts = new int[keys];
        T[] temp = new T[arr.length];

        for(int j = 0; j < keys; j++)
            counts[j] = 0;

        for(int t = 0; t < arr.length; t++){
            double index = (func.toInt(arr[t]) - min)*keys/(max - min + 1);
            ++counts[(int)index];
        }
        
        for(int j = 1; j < keys; j++) 
            counts[j] += counts[j-1];

        for(int t = arr.length; t > 0; t--){
            double index = (func.toInt(arr[t-1]) - min)*keys/(max - min + 1);
            temp[(--counts[(int)index])] = arr[t-1];
        }

        return temp;
    }

    private static int[] mm(Object[] arr, MyInt func) {
        int[] mm = {func.toInt(arr[0]), func.toInt(arr[0])};
        for (int i = 1; i < arr.length; ++i) {
            int test = func.toInt(arr[i]);
            if (test < mm[0])
                mm[0] = test;
            else if (test > mm[1])
                mm[1] = test;
        }

        return mm;
    }
}
