import java.util.Scanner;

public class circle_calculations {
    public static void main(String[] args) {

        // circumference = 2πr
        // area = πr²
        // volume = (4/3)πr³

        Scanner scanner = new Scanner(System.in);

        double radius, circumference, area, volume;

        System.out.print("Enter radius: ");
        radius = scanner.nextDouble();

        circumference = 2 * Math.PI * radius;
        area = Math.PI * Math.pow(radius, 2);
        volume = (4.0 / 3.0) * Math.PI * Math.pow(radius, 3);

        System.out.printf("Circumference: %.2f unit\n", circumference);
        System.out.printf("Area: %.2f unit²\n", area);
        System.out.printf("Volume: %.2f unit^3\n", volume);

        scanner.close();
    }   
}