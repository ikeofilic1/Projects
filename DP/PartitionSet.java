/*
This is my solution of the dynamic programming problem of finding if a set of positive numbers can be partitioned into two such that the sum of elements in both subsets are equal.
TC: 2^n.
SC: n.

PS: I did not use any DP techniques such as memoization or tabulation of the data. I might do these in the future but for a trivial problem like this, it is not necessary.
*/

class PartitionSet {
  public static boolean canPartition(int[] nums) {
    int sum = 0;
    for (int i = 0; i < nums.length; ++i) sum += nums[i];
    if (sum % 2 != 0) return false;
    
    return canPartRec(sum/2 - num[0], nums, 1); 
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
}
