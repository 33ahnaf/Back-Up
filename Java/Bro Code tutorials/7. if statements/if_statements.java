import java.util.Scanner;

public class if_statements {
    public static void main(String[] args) {
        
        // if statement -> performs a block of code if its condition is true

        Scanner scanner = new Scanner(System.in);

        int age = 25;
        String name;
        boolean isStudent;

        System.out.print("Enter your name: ");
        name = scanner.nextLine();
        System.out.print("Enter your age: ");
        age = scanner.nextInt();
        System.out.print("Are you a student? (true/false): ");
        isStudent = scanner.nextBoolean();

        // GROUP 1
        if(name.isEmpty()){ // same as name == ""
            System.out.println("You didn't enter your name!");
        }else{
            System.out.println("Hello, " + name + "!");
        }

        // GROUP 2
        if(age <= 0){
            System.out.println("You haven't been born yet.");
        }else if(age <= 17){
            System.out.println("You are a child!");
        }else{
            System.out.println("You are an adult!");
        }

        // GROUP 3
        if(isStudent){
            System.out.println("You are a student.");
        }else{
            System.out.println("You are NOT a student.");
        }

        scanner.close();
    }
}