public class Tutorial_05_Integers_and_Math{
    public static void main(String[] args){
        /* INTEGERS & MATH */
        int a = 100;
        int b = 200;

        // ADDITION
        int sum = a + b;
        System.out.println("Sum: " + sum);

        // SUBTRACTION
        int sub = a - b;
        System.out.println("Substraction: " + sub);

        // MULTIPLICATION
        int multi = a*b;
        System.out.println(multi);

        // DIVISION
        int div = a/b;
        System.out.println("Division: " + div);

        div = b/a;
        System.out.println("Division: " + div);

        // NO DIVISION BY 0
        // div = b/0;
        // System.out.println("Division: " + div);

        // Remainder (MODULO)
        int remainder = 101 % 2;
        System.out.println("Remainder: " + remainder);

        


        // Some math methods
        System.out.println("Absolute: " + Math.abs(-100));
        System.out.println("Ceiling: " + Math.ceil(3.14));
        System.out.println("Round: " + Math.round(3.45));
        System.out.println("Round: " + Math.round(3.5));
        System.out.println("Floor: " + Math.floor(3.14));

        System.out.println("Minimum: " + Math.min(10, 20));
        System.out.println("Maximum: " + Math.max(10, 20));
    }
}