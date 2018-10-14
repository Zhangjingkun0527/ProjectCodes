import java.util.Scanner;
public class GuessBirthday{
	public static void main(String[] args){
		guessBirthday();
	}
	
	private static void guessBirthday(){
		System.out.println("Does your birthday exist in these 5 groups of numbers?");
		System.out.println("For each group, if yes please enter 1, or enter 0, then enter the key of Enter on the keyboard, and then judge the next one.");
		
		var numbers = new int[5][16];
		var counter = new int[]{0,0,0,0,0};
		//create the original number sets.
		for(int i = 1; i < 32; i++){
			var temp1 = i;
			for(int j = 0; j < 5; j++){
				var temp2 = temp1 ^ 1;
				if(temp2 % 2 == 0){
					numbers[j][counter[j]] = i;
					counter[j]++;
				}
				
				temp1 >>= 1;
				if(temp1 == 0) break;
			}
		}
		
		//print the numbers
		var scanner = new Scanner(System.in);
		var result = 0;
		for(int i = 0; i < 5; i++){
			System.out.println("Does your birthday exist in here?");
			for(int j = 0; j < 16; j++){
				if(j != 0 && j % 4 == 0){
					System.out.println("");
				}
				System.out.print(numbers[i][j] + " ");
			}
			System.out.println("");
			var temp = scanner.nextInt();
			if(temp == 1) result += Math.pow(2, i);
			System.out.println("");
		}
		
		System.out.println("your birthday is " + result);
	}
}