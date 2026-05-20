import java.util.Scanner;

public class calculate_area {
    public static void main(String[] args) {
        double length = 0, width = 0;
        
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter the length: ");
        length = scanner.nextDouble();
        System.out.print("Enter the width: ");
        width = scanner.nextDouble();
        System.out.println("Area = " + length * width + " unit²");

        scanner.close();
    }
}