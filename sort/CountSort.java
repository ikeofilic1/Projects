package sort;

public class CountSort {

	/*public static Object[] sort(Object[] arr, Object base) {
		CompareClass integerComp = (a, b) -> (int)b - (int)a;
		return sort(arr, base, arr.length, arr.length, integerComp);		
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
	}*/

	public static Object[] sort(Integer[] arr, int keys) {
        return sort(arr, keys, b -> (int)b);      
    }

    public static Object[] sort(Object[] arr, int keys, MyInt func) {
        int[] mm = mm(arr, func);
        int min = mm[0], max = mm[1];

        int[] counts = new int[keys];
        Object[] temp = new Object[arr.length];

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