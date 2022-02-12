import sort.*;

public class Test {
	public static void main(String[] args) {
		Integer[] test = {7, 1, 2, 3, 2, 9, 4, 9, 7, 7};

		int[] copy = CountSort.sort(test, 1, test.length, 9);

		for(int i = 0; i < test.length; i++){
			//System.out.print(copy[i] + " ");
			test[i] = (int) copy[i];
		}

		for (int t : test) System.out.print( t + " ");
		System.out.println();
	}
}