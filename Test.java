import sort.*;

public class Test {
	public static void main(String[] args) {
		Integer[] test = {7, 1, 2, 3, 2, 9, 4, 9, 7, 7};

		test = CountSort.sort(test, 1, test.length, 9);

		for (int t : test) System.out.print( t + " ");
		System.out.println();
	}
}
