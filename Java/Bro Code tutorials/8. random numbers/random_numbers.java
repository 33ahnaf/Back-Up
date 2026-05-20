import java.util.Random;

public class random_numbers {
    public static void main(String[] args) {
        
        Random random = new Random();

        int number1;
        double number2;
        boolean isHead;

        number1 = random.nextInt(1, 101); // generates a random int ranging between the range of int if paramiters aren't given.
                                                       // generates a random int from given range. Note: origin: inclusive, bound: exclusive.
        number2 = random.nextDouble(3, 20); // generates a random double ranging between 0 and 1 if paramiters aren't given.
                                                         // generates a random double from given range. Note: origin: inclusive, bound: exclusive.
        isHead = random.nextBoolean();

        System.out.println(number1);
        System.out.println(number2);
        System.out.println(isHead);
    }
}