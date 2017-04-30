package pagereplacement;

import java.util.Random;
import java.util.Scanner;

import pagereplacement.algorithms.FirstInFirstOutReplacement;
import pagereplacement.algorithms.LeastRecentlyUsedReplacement;
import pagereplacement.algorithms.OptimalReplacement;

/**
 * CS4440 Spring 2017 - Project 2
 * @author Alvin Quach
 */
public class PageReplacement {
	
	@SuppressWarnings("resource")
	public static void main(String[] args) {
		
//		int[] refString = new int[] {7,2,3,1,2,5,3,4,6,7,7,1,0,5,4,6,2,3,0,1};
//		int[] refString = new int[] {1,2,3,2,1,5,2,1,6,2,5,6,3,1,3,6,1,2,4,3};
		
		System.out.println("CS4440 Spring 2017 - Project 2");
		System.out.println("Alvin Quach - 300793735");
		System.out.println("Enter 'exit' at anytime to exit.");
		System.out.println();
		
		Scanner reader = new Scanner(System.in);
		
		while (true) {
			
			String input;
			Integer stringLength;
			Integer frameCount;
			
			while (true) {
				System.out.println("Enter page reference string length: ");
				input = reader.nextLine();
				stringLength = parseInput(input);
				if (stringLength != null && stringLength > 0) {
					break;
				}
				System.out.println("Invalid Number");
			}
			
			while (true) {
				System.out.println("Enter page frame count (1-7): ");
				input = reader.nextLine();
				frameCount = parseInput(input);
				if (frameCount != null && frameCount > 0 && frameCount < 8) {
					break;
				}
				System.out.println("Invalid Number");
			}
			
			System.out.println();
			System.out.print("Page Reference String: ");
			
			int[] refString = new int[stringLength];
			for (int i = 0; i < refString.length; i++) {
				refString[i] = new Random().nextInt(10);
				if (i > 0) {
					System.out.print(", ");
				}
				System.out.print(refString[i]);
			}
			
			System.out.println();
			System.out.println("Page Frame Count: " + frameCount);
			System.out.println("LRU: " + new LeastRecentlyUsedReplacement().process(refString, frameCount));
			System.out.println("FIFO: " + new FirstInFirstOutReplacement().process(refString, frameCount));
			System.out.println("Optimal: " + new OptimalReplacement().process(refString, frameCount));
			System.out.println();
			
		}
		
	}
		
	private static Integer parseInput(String input) {
		if (input.equalsIgnoreCase("exit")) {
			System.exit(0);
		}
		try {
			return Integer.parseInt(input);
		}
		catch (NumberFormatException e) {
			return null;
		}
	}
	
}
