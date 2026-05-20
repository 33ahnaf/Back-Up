import java.util.Scanner;

public class shopping_cart_program {
    public static void main(String[] args) {
        
        // SHOPPING CART PROGRAM

        Scanner scanner = new Scanner(System.in);

        String item;
        double priceEach, totalPrice;
        int quantity;

        System.out.print("What item would you like to buy?: ");
        item = scanner.nextLine();

        System.out.print("What is the price for each?: ");
        priceEach = scanner.nextDouble();

        System.out.print("How many would you like?: ");
        quantity = scanner.nextInt();

        totalPrice = priceEach * quantity;

        System.out.println("\nYou have bought " + quantity + " " + item + "(s)");
        System.out.println("Your total is $" + totalPrice);

        scanner.close();
    }
}