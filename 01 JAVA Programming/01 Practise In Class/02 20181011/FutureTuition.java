public class FutureTuition{
	public static void main(String[] args){
	var temp = 1.07f;
	var count = 1;
	while(temp < 2){temp *= 1.07;count++;}
	System.out.println(count);
	System.out.println(temp);
	}
	
}