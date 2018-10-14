import java.util.Scanner;
import java.util.Random;

public class Lottery{
	public static void main(String[] args){
		lottery();
	}
	
	private static void lottery(){
		var random = new Random();
		var randomNumber = random.nextInt(89) + 10;
		var secondRN = randomNumber % 10;
		var firstRN = (randomNumber - secondRN) / 10;
		
		System.out.println("Please input a number which between 10 and 99(includint 10 and 99):");
		Scanner scanner = new Scanner(System.in);
		var numberFromUser = scanner.nextInt();
		var secondNumberFromUser = numberFromUser % 10;
		var firstNumberFromUser = (numberFromUser - secondNumberFromUser) / 10;
		
		var result1 = firstRN == firstNumberFromUser;
		var result2 = secondRN == secondNumberFromUser;
		var result3 = firstRN == secondNumberFromUser;
		var result4 = secondRN == firstNumberFromUser;
		if(result1 && result2){
			System.out.println("Congratulations! You will get 10000 dollars!!");
		}else if(result3 && result4){
			System.out.println("Congratulations! You will get 3000 dollars!!");
		}else if(result1 || result2 || result3 || result4){
			System.out.println("Congratulations! You will get 1000 dollars!!");
		}else {
			System.out.println("Oh, I'm sorry for that you would get no dollars!!");
		}
		System.out.println("The lottery number is " + randomNumber);
	}
	
	private static void test(){
		var c = 1;
		var d = 2;
		var b = c == d;
		System.out.println(b);
	}
}