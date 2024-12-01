// Jake Weber
// 9/14/24
// Arup Guha
// CIS 3362
// HW 3 Question 4

import java.util.*;

public class Playfair {
	public static void main (String[] args) {
		
		Scanner myScan = new Scanner(System.in);
		int n = myScan.nextInt(); // number of messages to encrypt (test cases)
		for (int i = 0; i < n; i++) {
			
			// Gather key and plaintext
			String keyTemp = myScan.next();
			ArrayList<Character> key = new ArrayList<Character>();
			String plaintextTemp = myScan.next();
			ArrayList<Character> plaintext = new ArrayList<Character>();
			for (int j = 0; j < keyTemp.length(); j++)
				key.add(keyTemp.charAt(j));
			for (int j = 0; j < plaintextTemp.length(); j++)
				plaintext.add(plaintextTemp.charAt(j));
			
			// Initialize grid
			ArrayList<Character> grid = new ArrayList<Character>();
			for (int j = 0; j < key.size(); j++) {
				if (!grid.contains(key.get(j))) {
					if (key.get(j) == 'i') {
						if(grid.contains('j'))
							continue;
						else
							grid.add('j');
					}
					else
						grid.add(key.get(j));
				}
			}
			for (int j = 97; j <= 122; j++) {
				if (!grid.contains((char) j))
					grid.add((char) j);
			}
			grid.remove((Character) 'i');
				
			// Pad plaintext
			for (int j = 0; j < plaintext.size(); ) {
				if (j + 1 >= plaintext.size() && plaintext.get(j) == 'x')
					plaintext.add('q');
				else if (j + 1 >= plaintext.size())
					plaintext.add('x');
				if (plaintext.get(j) == plaintext.get(j + 1)) {
					if (plaintext.get(j) == 'x')
						plaintext.add(j + 1, 'q');
					else
						plaintext.add(j + 1, 'x');
				}
				j += 2;
			}
			for (int j = 0; j < plaintext.size(); ) {
				if (plaintext.get(j) == 'i')
					plaintext.set(j, 'j'); 
				if (plaintext.get(j + 1) == 'i')
					plaintext.set(j + 1, 'j');
				j += 2;
			}
			
			// Encrypt
			ArrayList<Character> ciphertext = new ArrayList<Character>();
			for (int j = 0; j < plaintext.size(); ) {
				// Same row
				if (grid.indexOf(plaintext.get(j)) / 5 == grid.indexOf(plaintext.get(j + 1)) / 5) {
					if (grid.indexOf(plaintext.get(j)) % 5 == 4) {
						ciphertext.add(grid.get(grid.indexOf(plaintext.get(j)) - 4));
						ciphertext.add(grid.get(grid.indexOf(plaintext.get(j + 1)) + 1));
					} else if (grid.indexOf(plaintext.get(j + 1)) % 5 == 4) {
						ciphertext.add(grid.get(grid.indexOf(plaintext.get(j)) + 1));
						ciphertext.add(grid.get(grid.indexOf(plaintext.get(j + 1)) - 4));
					} else {
						ciphertext.add(grid.get(grid.indexOf(plaintext.get(j)) + 1));
						ciphertext.add(grid.get(grid.indexOf(plaintext.get(j + 1)) + 1));
					}
				}
				// Same column
				else if (grid.indexOf(plaintext.get(j)) % 5 == grid.indexOf(plaintext.get(j + 1)) % 5) {
					if (grid.indexOf(plaintext.get(j)) / 5 == 4) {
						ciphertext.add(grid.get(grid.indexOf(plaintext.get(j)) - 20));
						ciphertext.add(grid.get(grid.indexOf(plaintext.get(j + 1)) + 5));
					} else if (grid.indexOf(plaintext.get(j + 1)) / 5 == 4) {
						ciphertext.add(grid.get(grid.indexOf(plaintext.get(j)) + 5));
						ciphertext.add(grid.get(grid.indexOf(plaintext.get(j + 1)) - 20));
					} else {
						ciphertext.add(grid.get(grid.indexOf(plaintext.get(j)) + 5));
						ciphertext.add(grid.get(grid.indexOf(plaintext.get(j + 1)) + 5));
					}
				}
				// Different row different column
				else {
					int index = 5 * (grid.indexOf(plaintext.get(j)) / 5) + (grid.indexOf(plaintext.get(j + 1)) % 5);
					ciphertext.add(grid.get(index));
					index = 5 * (grid.indexOf(plaintext.get(j + 1)) / 5) + (grid.indexOf(plaintext.get(j)) % 5);
					ciphertext.add(grid.get(index));
				}
				j += 2;
			}
			
			// Output
			for (int j = 0; j < ciphertext.size(); j++)
				System.out.print(ciphertext.get(j));
			System.out.print("\n");
		}
	}
}