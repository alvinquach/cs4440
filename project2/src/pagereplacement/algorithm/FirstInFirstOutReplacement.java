package pagereplacement.algorithm;

import java.util.LinkedList;
import java.util.Queue;

public class FirstInFirstOutReplacement implements IReplacmentAlgorithm {

	/** 
	 * Applies the first in, first out (FIFO) replacement algorithm to the page-reference string 
	 * and returns the number of page faults incurred by the algorithm. 
	 */ 
	@Override
	public int process(int[] refString, int frameCount) {
		Queue<Integer> frames = new LinkedList<>();
		int faultCount = 0;
		for (int pageRef : refString) {
			if (frames.contains(pageRef)) {
				continue;
			}
			if (frames.size() == frameCount) {
				frames.poll();
			}
			frames.add(pageRef);
			faultCount++;
		}
		return faultCount;
	}

}
