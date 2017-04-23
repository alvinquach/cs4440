package pagereplacement;

import pagereplacement.algorithm.FirstInFirstOutReplacement;
import pagereplacement.algorithm.LeastRecentlyUsedReplacement;
import pagereplacement.algorithm.OptimalReplacement;

public class Application {
	
	public static void main(String[] args) {
		
//		int[] refString = new int[] {7,2,3,1,2,5,3,4,6,7,7,1,0,5,4,6,2,3,0,1};
		int[] refString = new int[] {1,2,3,2,1,5,2,1,6,2,5,6,3,1,3,6,1,2,4,3};
		
		int frameCount = 3;
		
		System.out.println("LRU: " + new LeastRecentlyUsedReplacement().process(refString, frameCount));
		
		System.out.println("FIFO: " + new FirstInFirstOutReplacement().process(refString, frameCount));
		
		System.out.println("Optimal: " + new OptimalReplacement().process(refString, frameCount));

		
	}
	
}
