import java.util.Arrays;
import java.util.Collections;

class MyLong {
    
    public long smallestNumber(long num) {
        boolean neg = false;
        
        if (num < 0){
            num *= -1;
            neg = true;
        }
        
        String s = Long.toString(num); 
        Integer[] digits = new Integer[s.length()];
        
        for (int i = 0; i < s.length(); i++) {
            digits[i] = s.charAt(i) - '0';
        }     
        
        if (neg)
            Arrays.sort(digits, Collections.reverseOrder());
        else 
            Arrays.sort(digits);
        
        int j = 0;        
        while (j < digits.length && digits[j] == 0)  
            j++;
        
        if (digits[0] == 0 && j < digits.length){
            int temp = digits[0];
            digits[0] = digits[j];
            digits[j] = temp;
        }
                
        long ans = 0;
        for (j = 0; j < digits.length; j++){
            ans = 10 * ans + digits[j];
        }  
        if (neg) ans *= -1;
        
        return ans;
    }
}
