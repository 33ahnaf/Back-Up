public class Variables {
    public static void main(String[] args) {

        // Primitive data types
        int age = 14;
        int year = 2025;
        // int quantity = 1;
        System.out.println("The year is " + year);

        double price = 15.99;
        // double gpa = 4.84;
        // double temperature = -273.15;
        System.out.println("$" + price);

        char grade = 'A';
        // char symbol = '!';
        // char currency = '$';
        System.out.println(grade);

        // boolean isStudent = true;
        // boolean forSale = false;
        boolean isOnline = false;
        System.out.println(isOnline);

        float Pi = 3.14f;
        System.out.println(Pi);

        // Reference data types
        String name = "Ahnaf Shariar";
        String friend = "Mst. Afrina Rahman Meghna";
        String sport = "Formula One AND Cricket";
        String car = "Nissan GT R";
        System.out.println("Hello, " + name);
        System.out.println("Hello, " + friend);
        System.out.println("My favourite car is " + car);



        System.out.println("\n\nHello, " + name + "!");
        System.out.println("You are " + age + " years old.");
        System.out.println("Your friend's name is " + friend + ".");
        System.out.println("Your favourite car is " + car + " and sport is " + sport + ".");
    }
}