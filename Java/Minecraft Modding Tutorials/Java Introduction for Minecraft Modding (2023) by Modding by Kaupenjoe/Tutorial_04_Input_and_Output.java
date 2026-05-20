import java.util.Scanner; // for Inputting

public class Tutorial_04_Input_and_Output{
    public static void main(String[] args){
        /* INPUT & OUTPUT */


        /* OUTPUT */
        
        // Outputting a String
        System.out.println("Hello, I am Ahnaf, Afrina's bestu");

        int life = 42;
        System.out.println(life);

        int grade = 80;
        System.out.println("Your grade is " + grade);


        /* INPUT */
        Scanner scanner = new Scanner(System.in);
        int number = scanner.nextInt();
        System.out.println("You just typed " + number);

        scanner.nextLine();
        String input = scanner.nextLine();
        System.out.println("You now just typed (String): " + input);
        scanner.close();
    }
}