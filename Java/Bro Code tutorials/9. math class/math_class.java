public class math_class {
    public static void main(String[] args) {

        // System.out.println(Math.PI);
        // System.out.println(Math.E);

        double result = 0;

        result = Math.pow(19, 3); // same as 19^3
        result = Math.abs(-3); // returns the absolute value (distance from 0)
        result = Math.sqrt(9); // returns the square root of any given number
        result = Math.round(3.14); // returns the round figure of any given number
        result = Math.ceil(3.14); // returns the closest highest integer
        result = Math.floor(3.14); // returns the closest lowest integer
        result = Math.max(3, 19); // returns the maximum of two numbers
        result = Math.min(3, 19); // returns the minimum of two numbers

        System.out.println(result);
    }
}