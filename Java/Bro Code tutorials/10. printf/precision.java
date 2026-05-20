public class precision {
    public static void main(String[] args){

        // + -> output a plus if positive
        // , -> comma grouping seperator
        // ( -> negative numbers are enclosed in ()
        // space -> display a minus if negative, space if positive

        double price1 = 9.99;
        double price2 = 10.15;
        double price3 = -54.01;

        System.out.printf("%+.2f\n", price1);
        System.out.printf("%+.2f\n", price2);
        System.out.printf("%+.2f\n", price3);

        System.out.printf("%,.2f\n", price1);
        System.out.printf("%,.2f\n", price2);
        System.out.printf("%,.2f\n", price3);

        System.out.printf("%(.2f\n", price1);
        System.out.printf("%(.2f\n", price2);
        System.out.printf("%(.2f\n", price3);

        System.out.printf("% .2f\n", price1);
        System.out.printf("% .2f\n", price2);
        System.out.printf("% .2f\n", price3);
    }   
}