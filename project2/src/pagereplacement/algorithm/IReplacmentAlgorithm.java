package pagereplacement.algorithm;

public interface IReplacmentAlgorithm {
	
	/**
	 * Applies the algorithm to the page-reference string and returns the number of page faults incurred by the algorithm. 
	 * @param refString The page-reference string.
	 * @param frameCount The number of page frames.
	 * @return The number of page faults incurred by the algorithm.
	 */
	public int process(int[] refString, int frameCount);

}
