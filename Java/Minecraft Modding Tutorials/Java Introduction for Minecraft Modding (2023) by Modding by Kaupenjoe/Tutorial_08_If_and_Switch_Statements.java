import java.util.Scanner;

public class Tutorial_08_If_and_Switch_Statements{
	public static void main(String[] args){

		Scanner scanner = new Scanner(System.in);


		// If, else and else if
		System.out.print("How much Health do you have? > ");
		int health = scanner.nextInt();
		boolean isAlive = health > 0;
		if(isAlive){
			System.out.println("You are still alive!");
		}else{
			System.out.println("You are dead!");
		}


		System.out.print("How many points do you have? > ");
		int points = scanner.nextInt();
		if(points >= 100){
			System.out.println("You passed with HONORS!");
		}else if(points >= 50){
			System.out.println("You passed!");
		}else{
			System.out.println("You failed!");
		}



		// Switch
		int x = 3;

		switch(x){
			case 0: System.out.println("X is 0"); break;
			case 1: System.out.println("X is 1"); break;
			case 2: System.out.println("X is 2"); break;
			case 3: System.out.println("X is lucky"); break;
			default: System.out.println("X is undefined!"); break;
		}


		scanner.close();
	}
}