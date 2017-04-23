package pagereplacement.algorithms;

import java.util.ArrayList;
import java.util.List;

public class OptimalReplacement implements IReplacmentAlgorithm {

	@Override
	public int process(int[] refString, int frameCount) {
		List<Integer> frames = new ArrayList<>(frameCount);
		int faultCount = 0;
		for (int i = 0; i < refString.length; i++) {
			int pageRef = refString[i];
			if (frames.contains(pageRef)) {
				continue;
			}
			if (frames.size() == frameCount) {
				int farthestIndex = -1;
				int farthestPageRef = frames.get(0);
				for (int frame : frames) {
					int nextIndex = findNextOccurance(refString, frame, i + 1);
					if (nextIndex > farthestIndex) {
						farthestIndex = nextIndex;
						farthestPageRef = frame;
					}
				}
				int frameIndex = frames.indexOf(farthestPageRef);
				frames.remove(frameIndex);
				frames.add(frameIndex, pageRef);
			}
			else {
				frames.add(pageRef);
			}
			faultCount++;
		}
		return faultCount;
	}
	
	private int findNextOccurance(int[] refString, int pageRef, int startIndex) {
		for (int i = startIndex; i < refString.length; i++) {
			if (refString[i] == pageRef) {
				return i;
			}
		}
		return Integer.MAX_VALUE;
	}

}
