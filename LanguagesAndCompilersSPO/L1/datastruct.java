import java.util.Scanner;  // Import the Scanner class

public class datastruct{
	public static void main(String[] args) {
		// Scanner myObj = new Scanner(System.in);  // Create a Scanner object
    // System.out.println("Enter a calculation: \n");

    // String input = myObj.nextLine();  // Read user input
		String input = "2 + 1 * 2 + 2 * 4";
		String[] arr = input.split(" ");
		CheckInput(arr);
	}

	static void CheckInput(String[] arr){
		char[] symbols = "*+".toCharArray();
		char[] arr2 = "2 + 1 * 2 + 2 * 4".trim().toCharArray();
		for (char symbol : symbols) {
			for (int i = 0; i < arr2.length; i++) {
				if(Character.compare(symbol, arr2[i]) == 0){
					int res = GiveResult(symbol, Character.getNumericValue(arr2[i-1]), 
																			 Character.getNumericValue(arr2[i+1]));
					//arr2[i-1] = 'z';
				}
			}
		}
		for (char string : arr2) {
			System.out.println(string);
		}
/*
		for (int i = 0; i < arr.length; i++){
			if(arr[i].equals("*")){
				int res = GiveResult("*", Integer.parseInt(arr[i-1]), Integer.parseInt(arr[i+1]));
			  arr[i-1] = Integer.toString(res);
				arr = RemoveFromStringArr(arr, i, i+1);
			}
		}
		for (int i = 0; i < arr.length; i++){
			if(arr[i].equals("+")){
				int res = GiveResult("+", Integer.parseInt(arr[i-1]), Integer.parseInt(arr[i+1]));
			  arr[i-1] = Integer.toString(res);
				arr = RemoveFromStringArr(arr, i, i+1);
			}
		}
		if(arr.length != 1) CheckInput(arr);
		else{
			for (String string : arr) {
				System.out.println(string);
			}
		}*/
	}

	static String[] RemoveFromStringArr(String[] arr, int i1, int i2){
		String[] arr2 = new String[arr.length - 2];

		int buffer = 0;
		for (int j = 0; j < arr.length; j++){
			if(j==i1 || j==i2){
				buffer++;
				continue;
			}
			arr2[j - buffer] = arr[j];
		}
		return arr2;
	}

	static int GiveResult(String symbol, int a, int b){
		switch(symbol){
			case "*": return a * b;
			case "+": return a + b;
			default: return 0;
		}
	}

	static int GiveResult(char symbol, int a, int b){
		switch(symbol){
			case '*': return a * b;
			case '+': return a + b;
			default: return 0;
		}
	}

}
