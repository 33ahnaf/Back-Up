import java.util.Scanner;

public class user_input {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter your name: ");
        // Note: .next() just takes user input without any space(like scanf), when .nextLine() takes user input with spaces(like fgets)
        String name = scanner.nextLine();

        System.out.print("Enter your age: ");
        int age = scanner.nextInt();

        System.out.print("Enter your GPA: ");
        double gpa = scanner.nextDouble();

        System.out.print("Are you a student? (true/false): ");
        boolean isStudent = scanner.nextBoolean();

        System.out.println("Hello, " + name + "!");
        System.out.println("You are " + age + " years old.");
        System.out.println("Your GPA: " + gpa);
        System.out.println("Student status: " + isStudent);


        // Common issue
        // System.out.print("Enter your age: ");
        // int age = scanner.nextInt();
        // scanner.nextLine();
        // // Note: when scanning int or float or double, a \n stays in the input buffer, and to get rid of that we have to clear the buffer using the above code.

        // System.out.print("Enter your favourite color: ");
        // String color = scanner.nextLine();

        // System.out.println("You are " + age + " years old.");
        // System.out.println("You like the color " + color);

        scanner.close();
    }
}