/*
This is my solution of the dynamic programming problem of finding if a set, with size n, of positive integers can be partitioned into 2 subsets 
such that the sum of elements in both subsets are equal. This idea can be applied to floating point numbers as well.
TC: 2^n?
SC: n (recursion stack).

PS: I did not use any DP techniques such as memoization or tabulation of the data. 
I might do these in the future but for a trivial problem like this, it is not necessary.
*/

class PartitionSet {
  public static boolean canPartition(int[] nums) {
    if (2 > nums.length || nums == null) return false;
    
    int sum = 0;
    for (int i = 0; i < nums.length; ++i) sum += nums[i];
    if (sum % 2 != 0) return false;    
    return canPartRec(sum/2 - nums[0], nums, 1); 
  }

  private static boolean canPartRec(int rem, int[] nums, int curr){
    if (rem < 0) return false;
    if (rem == 0) return true;
    else {      
      while (curr < nums.length) {
        if (canPartRec(rem - nums[curr], nums, ++curr))
          return true; 
      }
    }
    return false;
  }
  
/*  public canPartIter(int[] nums, int k) {
    int rem = 0;
    for (int i = 0; i < nums.length; ++i) sum += nums[i];
    if (sum % 2 != 0) return false;
    
    final int val = sum/2;
    int last;
    for (int i = 0; i < nums.length; ++i) {
      int rem = val - nums[i];
      if (rem < 0) continue;
      else if (rem == 0) return true;
      last = i; //use stack
      
      for (int j = i+1; j < nums.length; ++j) {
        int temp = rem - nums[j];
        if (temp < 0) {
          if (last != j-1) j = last;
          continue;
        }
        else if (temp == 0) return true;
        else rem = temp;
        last = j;
      }
    } //*/
}
