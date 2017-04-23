package pagereplacement.algorithms;

import java.util.ArrayList;
import java.util.List;

public class LeastRecentlyUsedReplacement implements IReplacmentAlgorithm {

	/** 
	 * Applies the least recently used (LRU) replacement algorithm to the page-reference string 
	 * and returns the number of page faults incurred by the algorithm. 
	 */ 
	@Override
	public int process(int[] refString, int frameCount) {
		List<Frame> frames = new ArrayList<>(frameCount);
		int faultCount = 0;
		for (int i = 0; i < refString.length; i++) {
			int pageRef = refString[i];
			if (updateFrame(findByPageRef(frames, pageRef), pageRef, i)) {
				continue;
			}
			if (frames.size() == frameCount) {
				updateFrame(findLeastRecentlyUsed(frames), pageRef, i);
			}
			else {
				frames.add(new Frame(pageRef, i));
			}
			faultCount++;
		}
		return faultCount;
	}
	
	private boolean updateFrame(Frame frame, int pageRef, int useIndex) {
		if (frame == null) {
			return false;
		}
		frame.setPageRef(pageRef);
		frame.setLastUse(useIndex);
		return true;
	}
	
	private Frame findByPageRef(List<Frame> frames, int pageRef) {
		for (Frame frame : frames) {
			if (frame.getPageRef() == pageRef) {
				return frame;
			}
		}
		return null;
	}
	
	private Frame findLeastRecentlyUsed(List<Frame> frames) {
		int minIndex = 0;
		for (int i = 0; i < frames.size(); i++) {
			if (frames.get(i).getLastUse() < frames.get(minIndex).getLastUse()) {
				minIndex = i;
			}
		}
		return frames.get(minIndex);
	}
	
	private class Frame {
		
		private int pageRef;
		private int lastUse;
		
		public Frame(int pageRef, int lastUse) {
			this.pageRef = pageRef;
			this.lastUse = lastUse;
		}
		
		public int getPageRef() {
			return pageRef;
		}
		
		public void setPageRef(int pageRef) {
			this.pageRef = pageRef;
		}
		
		public int getLastUse() {
			return lastUse;
		}
		
		public void setLastUse(int lastUse) {
			this.lastUse = lastUse;
		}
		
	}

}
