import java.util.Scanner;

public class mad_libs_game {
    public static void main(String[] args) {
        
        // MAD LIBS GAME

        Scanner scanner = new Scanner(System.in);

        String adjective1, noun1, adjective2, verb1, adjective3;

        System.out.print("Enter an adjective (description): ");
        adjective1 = scanner.nextLine();
        System.out.print("Enter a noun (a animal): ");
        noun1 = scanner.nextLine();
        System.out.print("Enter an adjective (description): ");
        adjective2 = scanner.nextLine();
        System.out.print("Enter a verb (action): ");
        verb1 = scanner.nextLine();
        System.out.print("Enter an adjective (description): ");
        adjective3 = scanner.nextLine();

        System.out.println("\n\nToday I went to a " + adjective1 + " zoo.");
        System.out.println("In an exhibit, I saw a/an " + noun1 + ".");
        System.out.println("The " + noun1 + " was " + adjective2 + " and " + verb1 + "!");
        System.out.println("I was " + adjective3 + "!");

        scanner.close();
    }
}