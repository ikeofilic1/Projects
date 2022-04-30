import sort.*;

public class TestSort {
	public static void main(String[] args) {
		Integer[] test = {7, 1, 2, 3, 2, 9, 4, 9, 7, 7};

		Object[] copy = CountSort.sort(test, 6);

		for(int i = 0; i < test.length; i++){
			test[i] = (int) copy[i];
		}

		for (int t : test) System.out.print( t + " ");
		System.out.println();
	}
}