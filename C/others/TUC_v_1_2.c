#include <stdio.h>
#include <string.h>

void remove_newline(char *input){
    if (strlen(input) > 0 && input[strlen(input) - 1] == '\n'){
        input[strlen(input) - 1] = '\0';
    }
}

int main(){
    char user_input[31];
    printf("Welcome to the ultimate calculator\n");
    printf("----------------------------------\n");
    printf("What type of calculation do you want to enter?: ");
    fgets(user_input, sizeof(user_input), stdin);
    remove_newline(user_input);
    if (strcasecmp(user_input, "Length") == 0)
    {
        char user_input_length[31];
        float kilometer, millimeter, centimeter, meter, mile, nautical_mile, inch, feet, yard, micron;
        printf("Which unit of length do you want to enter?: ");
        fgets(user_input_length, sizeof(user_input_length), stdin);
        remove_newline(user_input_length);
        if (strcasecmp(user_input_length, "Kilometer") == 0 || strcasecmp(user_input_length, "km") == 0)
        {
            printf("Kilometer = ");
            scanf("%f", &kilometer);
            millimeter = kilometer*1000000;
            centimeter = kilometer*100000;
            meter = kilometer*1000;
            mile = kilometer*0.621371192;
            nautical_mile = kilometer*0.539956803;
            inch = kilometer*39370.07874;
            feet = kilometer*3280.839895;
            yard = kilometer*1093.613298;
            micron = kilometer*1000000000;
            printf("Micron = %f\n", micron);
            printf("Millimeter = %f\n", millimeter);
            printf("Centimeter = %f\n", centimeter);
            printf("Meter = %f\n", meter);
            printf("Inch = %f\n", inch);
            printf("Feet = %f\n", feet);
            printf("Yard = %f\n", yard);
            printf("Mile = %f\n", mile);
            printf("Nautical mile = %f\n", nautical_mile);
        }else if (strcasecmp(user_input_length, "Millimeter") == 0 || strcasecmp(user_input_length, "mm") == 0)
        {
            printf("Millimeter = ");
            scanf("%f", &millimeter);
            centimeter = millimeter/10;
            kilometer = millimeter/1000000;
            meter = millimeter/1000;
            mile = kilometer*0.621371192;
            nautical_mile = kilometer*0.539956803;
            inch = centimeter/2.54;
            feet = inch/12;
            yard = feet/3;
            micron = millimeter*1000;
            printf("Micron = %f\n", micron);
            printf("Centimeter = %f\n", centimeter);
            printf("Meter = %f\n", meter);
            printf("Kilometer = %f\n", kilometer);
            printf("Inch = %f\n", inch);
            printf("Feet = %f\n", feet);
            printf("Yard = %f\n", yard);
            printf("Mile = %f\n", mile);
            printf("Nautical mile = %f\n", nautical_mile);
        }else if (strcasecmp(user_input_length, "Centimeter") == 0 || strcasecmp(user_input_length, "cm") == 0)
        {
            printf("Centimeter = ");
            scanf("%f", &centimeter);
            millimeter = centimeter*10;
            meter = centimeter/100;
            kilometer = meter/1000;
            micron = centimeter*10000;
            inch = centimeter/2.54;
            feet = inch/12;
            yard = feet/3;
            mile = kilometer*0.621371192;
            nautical_mile = kilometer*0.539956803;
            printf("Micron = %f\n", micron);
            printf("Millimeter = %f\n", millimeter);
            printf("Meter = %f\n", meter);
            printf("Kilometer = %f\n", kilometer);
            printf("Inch = %f\n", inch);
            printf("Feet = %f\n", feet);
            printf("Yard = %f\n", yard);
            printf("Mile = %f\n", mile);
            printf("Nautical mile = %f\n", nautical_mile);
        }else if (strcasecmp(user_input_length, "Micron") == 0 || strcasecmp(user_input_length, "Micrometer") == 0)
        {
            printf("Micron = ");
            scanf("%f", &micron);
            millimeter = micron/1000;
            centimeter = millimeter/10;
            meter = centimeter/100;
            kilometer = meter/1000;
            inch = centimeter/2.54;
            feet = inch/12;
            yard = feet/3;
            mile = kilometer*0.621371192;
            nautical_mile = kilometer*0.539956803;
            printf("Millimeter = %f\n", millimeter);
            printf("Centimeter = %f\n", centimeter);
            printf("Meter = %f\n", meter);
            printf("Kilometer = %f\n", kilometer);
            printf("Inch = %f\n", inch);
            printf("Feet = %f\n", feet);
            printf("Yard = %f\n", yard);
            printf("Mile = %f\n", mile);
            printf("Nautical mile = %f\n", nautical_mile);
        }else if (strcasecmp(user_input_length, "Meter") == 0 || strcasecmp(user_input_length, "m") == 0)
        {
            printf("Meter = ");
            scanf("%f", &meter);
            micron = meter*1000000;
            millimeter = meter*1000;
            centimeter = meter*100;
            kilometer = meter/1000;
            inch = centimeter/2.54;
            feet = inch/12;
            yard = feet/3;
            mile = kilometer*0.621371192;
            nautical_mile = kilometer*0.539956803;
            printf("Micron = %f\n", micron);
            printf("Millimeter = %f\n", millimeter);
            printf("Centimeter = %f\n", centimeter);
            printf("Kilometer = %f\n", kilometer);
            printf("Inch = %f\n", inch);
            printf("Feet = %f\n", feet);
            printf("Yard = %f\n", yard);
            printf("Mile = %f\n", mile);
            printf("Nautical mile = %f\n", nautical_mile);
        }else if (strcasecmp(user_input_length, "Inch") == 0 || strcasecmp(user_input_length, "in") == 0)
        {
            printf("Inch = ");
            scanf("%f", &inch);
            centimeter = inch*2.54;
            millimeter = centimeter*10;
            micron = millimeter*1000;
            meter = centimeter/100;
            kilometer = meter/1000;
            feet = inch/12;
            yard = feet/3;
            mile = kilometer*0.621371192;
            nautical_mile = kilometer*0.539956803;
            printf("Micron = %f\n", micron);
            printf("Millimeter = %f\n", millimeter);
            printf("Centimeter = %f\n", centimeter);
            printf("Meter = %f\n", meter);
            printf("Kilometer = %f\n", kilometer);
            printf("Feet = %f\n", feet);
            printf("Yard = %f\n", yard);
            printf("Mile = %f\n", mile);
            printf("Nautical mile = %f\n", nautical_mile);
        }else if (strcasecmp(user_input_length, "Feet") == 0 || strcasecmp(user_input_length, "ft") == 0)
        {
            printf("Feet = ");
            scanf("%f", &feet);
            inch = feet*12;
            yard = feet/3;
            centimeter = inch*2.54;
            millimeter = centimeter*10;
            micron = millimeter*1000;
            meter = centimeter/100;
            kilometer = meter/1000;
            mile = kilometer*0.621371192;
            nautical_mile = kilometer*0.539956803;
            printf("Micron = %f\n", micron);
            printf("Millimeter = %f\n", millimeter);
            printf("Centimeter = %f\n", centimeter);
            printf("Meter = %f\n", meter);
            printf("Kilometer = %f\n", kilometer);
            printf("Inch = %f\n", inch);
            printf("Yard = %f\n", yard);
            printf("Mile = %f\n", mile);
            printf("Nautical mile = %f\n", nautical_mile);
        }else if (strcasecmp(user_input_length, "Yard") == 0 || strcasecmp(user_input_length, "yd") == 0)
        {
            printf("Yard = ");
            scanf("%f", &yard);
            feet = yard*3;
            inch = feet*12;
            centimeter = inch*2.54;
            millimeter = centimeter*10;
            micron = millimeter*1000;
            meter = centimeter/100;
            kilometer = meter/1000;
            mile = kilometer*0.621371192;
            nautical_mile = kilometer*0.539956803;
            printf("Micron = %f\n", micron);
            printf("Millimeter = %f\n", millimeter);
            printf("Centimeter = %f\n", centimeter);
            printf("Meter = %f\n", meter);
            printf("Kilometer = %f\n", kilometer);
            printf("Inch = %f\n", inch);
            printf("Feet = %f\n", feet);
            printf("Mile = %f\n", mile);
            printf("Nautical mile = %f\n", nautical_mile);
        }else if (strcasecmp(user_input_length, "Mile") == 0 || strcasecmp(user_input_length, "mi") == 0)
        {
            printf("Mile = ");
            scanf("%f", &mile);
            kilometer = mile*1.609344;
            nautical_mile = kilometer*0.539956803;
            meter = kilometer*1000;
            centimeter = meter*100;
            millimeter = centimeter*10;
            micron = millimeter*1000;
            inch = centimeter/2.54;
            feet = inch/12;
            yard = feet/3;
            printf("Micron = %f\n", micron);
            printf("Millimeter = %f\n", millimeter);
            printf("Centimeter = %f\n", centimeter);
            printf("Meter = %f\n", meter);
            printf("Kilometer = %f\n", kilometer);
            printf("Inch = %f\n", inch);
            printf("Feet = %f\n", feet);
            printf("Yard = %f\n", yard);
            printf("Nautical mile = %f\n", nautical_mile);
        }else if (strcasecmp(user_input_length, "Nautical mile") == 0 || strcasecmp(user_input_length, "n.mi") == 0 || strcasecmp(user_input_length, "n.mile") == 0)
        {
            printf("Nautical mile = ");
            scanf("%f", &nautical_mile);
            meter = nautical_mile*1852;
            kilometer = meter/1000;
            centimeter = meter*100;
            millimeter = centimeter*10;
            micron = millimeter*1000;
            inch = centimeter/2.54;
            feet = inch/12;
            yard = feet/3;
            mile = kilometer*0.621371192;
            printf("Micron = %f\n", micron);
            printf("Millimeter = %f\n", millimeter);
            printf("Centimeter = %f\n", centimeter);
            printf("Meter = %f\n", meter);
            printf("Kilometer = %f\n", kilometer);
            printf("Inch = %f\n", inch);
            printf("Feet = %f\n", feet);
            printf("Yard = %f\n", yard);
            printf("Mile = %f\n", mile);
        }else{
            printf("Invalid option!");
            return 1;
        }
    }else if (strcasecmp(user_input, "Volume") == 0)
    {
        char user_input_volume[31];
        float liter, milliliter, kiloliter, cubic_centimeter, cubic_meter, cubic_inch, cubic_feet, cubic_yard, gallon_us, gallon_uk;
        printf("Which unit of volume do you want to enter?: ");
        fgets(user_input_volume, sizeof(user_input_volume), stdin);
        remove_newline(user_input_volume);
        if (strcasecmp(user_input_volume, "Liter") == 0 || strcasecmp(user_input_volume, "l") == 0)
        {
            printf("Liter = ");
            scanf("%f", &liter);
            milliliter = liter*1000;
            kiloliter = liter/1000;
            cubic_centimeter = milliliter;
            cubic_meter = kiloliter;
            cubic_inch = cubic_centimeter/16.387064;
            cubic_feet = cubic_inch/1728;
            cubic_yard = cubic_feet/27;
            gallon_us = liter*0.264172037;
            gallon_uk = liter*0.219969248;
            printf("Milliliter = %f\n", milliliter);
            printf("Kiloliter = %f\n", kiloliter);
            printf("Cubic centimeter = %f\n", cubic_centimeter);
            printf("Cubic meter = %f\n", cubic_meter);
            printf("Cubic inch = %f\n", cubic_inch);
            printf("Cubic feet = %f\n", cubic_feet);
            printf("Cubic yard = %f\n", cubic_yard);
            printf("Gallon(US) = %f\n", gallon_us);
            printf("Gallon(UK) = %f\n", gallon_uk);
        }else if (strcasecmp(user_input_volume, "Milliliter") == 0 || strcasecmp(user_input_volume, "ml") == 0)
        {
            printf("Milliliter = ");
            scanf("%f", &milliliter);
            liter = milliliter/1000;
            kiloliter = liter/1000;
            cubic_centimeter = milliliter;
            cubic_meter = kiloliter;
            cubic_inch = cubic_centimeter/16.387064;
            cubic_feet = cubic_inch/1728;
            cubic_yard = cubic_feet/27;
            gallon_us = liter*0.264172037;
            gallon_uk = liter*0.219969248;
            printf("Liter = %f\n", liter);
            printf("Kiloliter = %f\n", kiloliter);
            printf("Cubic centimeter = %f\n", cubic_centimeter);
            printf("Cubic meter = %f\n", cubic_meter);
            printf("Cubic inch = %f\n", cubic_inch);
            printf("Cubic feet = %f\n", cubic_feet);
            printf("Cubic yard = %f\n", cubic_yard);
            printf("Gallon(US) = %f\n", gallon_us);
            printf("Gallon(UK) = %f\n", gallon_uk);
        }else if (strcasecmp(user_input_volume, "Kiloliter") == 0 || strcasecmp(user_input_volume, "kl") == 0)
        {
            printf("Kiloliter = ");
            scanf("%f", &kiloliter);
            liter = kiloliter*1000;
            milliliter = liter*1000;
            cubic_centimeter = milliliter;
            cubic_meter = kiloliter;
            cubic_inch = cubic_centimeter/16.387064;
            cubic_feet = cubic_inch/1728;
            cubic_yard = cubic_feet/27;
            gallon_us = liter*0.264172037;
            gallon_uk = liter*0.219969248;
            printf("Milliliter = %f\n", milliliter);
            printf("Liter = %f\n", liter);
            printf("Cubic centimeter = %f\n", cubic_centimeter);
            printf("Cubic meter = %f\n", cubic_meter);
            printf("Cubic inch = %f\n", cubic_inch);
            printf("Cubic feet = %f\n", cubic_feet);
            printf("Cubic yard = %f\n", cubic_yard);
            printf("Gallon(US) = %f\n", gallon_us);
            printf("Gallon(UK) = %f\n", gallon_uk);
        }else if (strcasecmp(user_input_volume, "Cubic centimeter") == 0 || strcasecmp(user_input_volume, "c.cm") == 0)
        {
            printf("Cubic centimeter = ");
            scanf("%f", &cubic_centimeter);
            milliliter = cubic_centimeter;
            liter = milliliter/1000;
            kiloliter = liter/1000;
            cubic_meter = kiloliter;
            cubic_inch = cubic_centimeter/16.387064;
            cubic_feet = cubic_inch/1728;
            cubic_yard = cubic_feet/27;
            gallon_us = liter*0.264172037;
            gallon_uk = liter*0.219969248;
            printf("Milliliter = %f\n", milliliter);
            printf("Liter = %f\n", liter);
            printf("Kiloliter = %f\n", kiloliter);
            printf("Cubic meter = %f\n", cubic_meter);
            printf("Cubic inch = %f\n", cubic_inch);
            printf("Cubic feet = %f\n", cubic_feet);
            printf("Cubic yard = %f\n", cubic_yard);
            printf("Gallon(US) = %f\n", gallon_us);
            printf("Gallon(UK) = %f\n", gallon_uk);
        }else if (strcasecmp(user_input_volume, "Cubic meter") == 0 || strcasecmp(user_input_volume, "c.m") == 0)
        {
            printf("Cubic meter = ");
            scanf("%f", &cubic_meter);
            kiloliter = cubic_meter;
            liter = kiloliter*1000;
            milliliter = liter*1000;
            cubic_centimeter = milliliter;
            cubic_inch = cubic_centimeter/16.387064;
            cubic_feet = cubic_inch/1728;
            cubic_yard = cubic_feet/27;
            gallon_us = liter*0.264172037;
            gallon_uk = liter*0.219969248;
            printf("Milliliter = %f\n", milliliter);
            printf("Liter = %f\n", liter);
            printf("Kiloliter = %f\n", kiloliter);
            printf("Cubic centimeter = %f\n", cubic_centimeter);
            printf("Cubic inch = %f\n", cubic_inch);
            printf("Cubic feet = %f\n", cubic_feet);
            printf("Cubic yard = %f\n", cubic_yard);
            printf("Gallon(US) = %f\n", gallon_us);
            printf("Gallon(UK) = %f\n", gallon_uk);
        }else if (strcasecmp(user_input_volume, "Cubic inch") == 0 || strcasecmp(user_input_volume, "c.in") == 0)
        {
            printf("Cubic inch = ");
            scanf("%f", &cubic_inch);
            cubic_centimeter = cubic_inch*16.387064;
            milliliter = cubic_centimeter;
            liter = milliliter/1000;
            kiloliter = liter/1000;
            cubic_meter = kiloliter;
            cubic_feet = cubic_inch/1728;
            cubic_yard = cubic_feet/27;
            gallon_us = liter*0.264172037;
            gallon_uk = liter*0.219969248;
            printf("Milliliter = %f\n", milliliter);
            printf("Liter = %f\n", liter);
            printf("Kiloliter = %f\n", kiloliter);
            printf("Cubic centimeter = %f\n", cubic_centimeter);
            printf("Cubic meter = %f\n", cubic_meter);
            printf("Cubic feet = %f\n", cubic_feet);
            printf("Cubic yard = %f\n", cubic_yard);
            printf("Gallon(US) = %f\n", gallon_us);
            printf("Gallon(UK) = %f\n", gallon_uk);
        }else if (strcasecmp(user_input_volume, "Cubic feet") == 0 || strcasecmp(user_input_volume, "c.ft") == 0)
        {
            printf("Cubic feet = ");
            scanf("%f", &cubic_feet);
            cubic_inch = cubic_feet*1728;
            cubic_yard = cubic_feet/27;
            cubic_centimeter = cubic_inch*16.387064;
            milliliter = cubic_centimeter;
            liter = milliliter/1000;
            kiloliter = liter/1000;
            cubic_meter = kiloliter;
            gallon_us = liter*0.264172037;
            gallon_uk = liter*0.219969248;
            printf("Milliliter = %f\n", milliliter);
            printf("Liter = %f\n", liter);
            printf("Kiloliter = %f\n", kiloliter);
            printf("Cubic centimeter = %f\n", cubic_centimeter);
            printf("Cubic meter = %f\n", cubic_meter);
            printf("Cubic inch = %f\n", cubic_inch);
            printf("Cubic yard = %f\n", cubic_yard);
            printf("Gallon(US) = %f\n", gallon_us);
            printf("Gallon(UK) = %f\n", gallon_uk);
        }else if (strcasecmp(user_input_volume, "Cubic yard") == 0 || strcasecmp(user_input_volume, "c.yd") == 0)
        {
            printf("Cubic yard = ");
            scanf("%f", &cubic_yard);
            cubic_feet = cubic_yard*27;
            cubic_inch = cubic_feet*1728;
            cubic_centimeter = cubic_inch*16.387064;
            milliliter = cubic_centimeter;
            liter = milliliter/1000;
            kiloliter = liter/1000;
            cubic_meter = kiloliter;
            gallon_us = liter*0.264172037;
            gallon_uk = liter*0.219969248;
            printf("Milliliter = %f\n", milliliter);
            printf("Liter = %f\n", liter);
            printf("Kiloliter = %f\n", kiloliter);
            printf("Cubic centimeter = %f\n", cubic_centimeter);
            printf("Cubic meter = %f\n", cubic_meter);
            printf("Cubic inch = %f\n", cubic_inch);
            printf("Cubic feet = %f\n", cubic_feet);
            printf("Gallon(US) = %f\n", gallon_us);
            printf("Gallon(UK) = %f\n", gallon_uk);
        }else if (strcasecmp(user_input_volume, "Gallon(US)") == 0 || strcasecmp(user_input_volume, "g.us"))
        {
            printf("Gallon(US) = ");
            scanf("%f", &gallon_us);
            liter = gallon_us*3.785412;
            kiloliter = liter/1000;
            milliliter = liter*1000;
            cubic_centimeter = milliliter;
            cubic_meter = kiloliter;
            cubic_inch = cubic_centimeter/16.387064;
            cubic_feet = cubic_inch/1728;
            cubic_yard = cubic_feet/27;
            gallon_uk = liter*0.219969248;
            printf("Milliliter = %f\n", milliliter);
            printf("Liter = %f\n", liter);
            printf("Kiloliter = %f\n", kiloliter);
            printf("Cubic centimeter = %f\n", cubic_centimeter);
            printf("Cubic meter = %f\n", cubic_meter);
            printf("Cubic inch = %f\n", cubic_inch);
            printf("Cubic feet = %f\n", cubic_feet);
            printf("Cubic yard = %f\n", cubic_yard);
            printf("Gallon(UK) = %f\n", gallon_uk);
        }else if (strcasecmp(user_input_volume, "Gallon(UK)") == 0 || strcasecmp(user_input_volume, "g.uk"))
        {
            printf("Gallon(UK) = ");
            scanf("%f", &gallon_uk);
            liter = gallon_uk*4.54609;
            kiloliter = liter/1000;
            milliliter = liter*1000;
            cubic_centimeter = milliliter;
            cubic_meter = kiloliter;
            cubic_inch = cubic_centimeter/16.387064;
            cubic_feet = cubic_inch/1728;
            cubic_yard = cubic_feet/27;
            gallon_us = liter*0.264172037;
            printf("Milliliter = %f\n", milliliter);
            printf("Liter = %f\n", liter);
            printf("Kiloliter = %f\n", kiloliter);
            printf("Cubic centimeter = %f\n", cubic_centimeter);
            printf("Cubic meter = %f\n", cubic_meter);
            printf("Cubic inch = %f\n", cubic_inch);
            printf("Cubic feet = %f\n", cubic_feet);
            printf("Cubic yard = %f\n", cubic_yard);
            printf("Gallon(US) = %f\n", gallon_us);
        }else{
            printf("Invalid option!");
            return 1;
        }
    }else if (strcasecmp(user_input, "Mass") == 0)
    {
        char user_input_mass[31];
        float milligram, gram, kilogram, tonn, pound, ounce;
        printf("Which unit of mass do you want to enter?: ");
        fgets(user_input_mass, sizeof(user_input_mass), stdin);
        remove_newline(user_input_mass);
        if (strcasecmp(user_input_mass, "Milligram") == 0 || strcasecmp(user_input_mass, "mg") == 0)
        {
            printf("Milligram = ");
            scanf("%f", &milligram);
            gram = milligram/1000;
            kilogram = gram/1000;
            tonn = kilogram/1000;
            pound = kilogram*2.204622476;
            ounce = gram/28.34952;
            printf("Gram = %f\n", gram);
            printf("Kilogram = %f\n", kilogram);
            printf("Tonn = %f\n", tonn);
            printf("Pound = %f\n", pound);
            printf("Ounce = %f\n", ounce);
        }else if (strcasecmp(user_input_mass, "Gram") == 0 || strcasecmp(user_input_mass, "g") == 0)
        {
            printf("Gram = ");
            scanf("%f", &gram);
            milligram = gram*1000;
            kilogram = gram/1000;
            tonn = kilogram/1000;
            pound = kilogram*2.204622476;
            ounce = gram/28.34952;
            printf("Milligram = %f\n", milligram);
            printf("Kilogram = %f\n", kilogram);
            printf("Tonn = %f\n", tonn);
            printf("Pound = %f\n", pound);
            printf("Ounce = %f\n", ounce);
        }else if (strcasecmp(user_input_mass, "Kilogram") == 0 || strcasecmp(user_input_mass, "kg") == 0)
        {
            printf("Kilogram = ");
            scanf("%f", &kilogram);
            gram = kilogram*1000;
            milligram = gram*1000;
            tonn = kilogram/1000;
            pound = kilogram*2.204622476;
            ounce = gram/28.34952;
            printf("Milligram = %f\n", milligram);
            printf("Gram = %f\n", gram);
            printf("Tonn = %f\n", tonn);
            printf("Pound = %f\n", pound);
            printf("Ounce = %f\n", ounce);
        }else if (strcasecmp(user_input_mass, "Tonn") == 0 || strcasecmp(user_input_mass, "t") == 0)
        {
            printf("Tonn = ");
            scanf("%f", &tonn);
            kilogram = tonn*1000;
            gram = kilogram*1000;
            milligram = gram*1000;
            pound = kilogram*2.204622476;
            ounce = gram/28.34952;
            printf("Milligram = %f\n", milligram);
            printf("Gram = %f\n", gram);
            printf("Kilogram = %f\n", kilogram);
            printf("Pound = %f\n", pound);
            printf("Ounce = %f\n", ounce);
        }else if (strcasecmp(user_input_mass, "Pound") == 0 || strcasecmp(user_input_mass, "lb") == 0)
        {
            printf("Pound = ");
            scanf("%f", &pound);
            kilogram = pound/2.204622476;
            gram = kilogram*1000;
            milligram = gram*1000;
            tonn = kilogram/1000;
            ounce = gram/28.34952;
            printf("Milligram = %f\n", milligram);
            printf("Gram = %f\n", gram);
            printf("Kilogram = %f\n", kilogram);
            printf("Tonn = %f\n", tonn);
            printf("Ounce = %f\n", ounce);
        }else if (strcasecmp(user_input_mass, "Ounce") == 0 || strcasecmp(user_input_mass, "oz") == 0)
        {
            printf("Ounce = ");
            scanf("%f", &ounce);
            gram = ounce*28.34952;
            milligram = gram*1000;
            kilogram = gram/1000;
            tonn = kilogram/1000;
            pound = kilogram*2.204622476;
            printf("Milligram = %f\n", milligram);
            printf("Gram = %f\n", gram);
            printf("Kilogram = %f\n", kilogram);
            printf("Tonn = %f\n", tonn);
            printf("Pound = %f\n", pound);
        }else{
            printf("Invalid option!");
            return 1;
        }
    }else if (strcasecmp(user_input, "Temperature") == 0)
    {
        char user_input_temperature[31];
        float celsius, fahrenheit, kelvin;
        printf("Which unit of temperature do you want to enter?: ");
        fgets(user_input_temperature, sizeof(user_input_temperature), stdin);
        remove_newline(user_input_temperature);
        if (strcasecmp(user_input_temperature, "Celsius") == 0 || strcasecmp(user_input_temperature, "C") == 0)
        {
            printf("Celsius = ");
            scanf("%f", &celsius);
            kelvin = celsius+273.15;
            fahrenheit = (1.8*celsius)+32;
            printf("Fahrenheit = %f\n", fahrenheit);
            printf("Kelvin = %f\n", kelvin);
        }else if (strcasecmp(user_input_temperature, "Fahrenheit") == 0 || strcasecmp(user_input_temperature, "F") == 0)
        {
            printf("Fahrenheit = ");
            scanf("%f", &fahrenheit);
            celsius = (fahrenheit-32)/1.8;
            kelvin = celsius+273.15;
            printf("Celsius = %f\n", celsius);
            printf("Kelvin = %f\n", kelvin);
        }else if (strcasecmp(user_input_temperature, "Kelvin") == 0 || strcasecmp(user_input_temperature, "K") == 0)
        {
            printf("Kelvin = ");
            scanf("%f", &kelvin);
            celsius = kelvin-273.15;
            fahrenheit = (celsius*1.8)+32;
            printf("Celsius = %f\n", celsius);
            printf("Fahrenheit = %f\n", fahrenheit);
        }else{
            printf("Invalid option!");
            return 1;
        }
    }else if (strcasecmp(user_input, "Area") == 0)
    {
        char user_input_area[31];
        float square_meter, square_centimeter, square_millimeter, hectares, square_kilometer, square_inch, square_feet, square_yard, square_mile;
        printf("Which unit of area do you want to enter?: ");
        fgets(user_input_area, sizeof(user_input_area), stdin);
        remove_newline(user_input_area);
        if (strcasecmp(user_input_area, "Square meter") == 0 || strcasecmp(user_input_area, "s.m") == 0)
        {
            printf("Square meter = ");
            scanf("%f", &square_meter);
            square_centimeter = square_meter*10000;
            square_millimeter = square_centimeter*100;
            hectares = square_meter/10000;
            square_kilometer = square_meter/1000000;
            square_inch = square_centimeter/6.4516;
            square_feet = square_inch/144;
            square_yard = square_feet/9;
            square_mile = square_kilometer/2.5921000000000003;
            printf("Square millimeter = %f", square_millimeter);
            printf("Square centimeter = %f", square_centimeter);
            printf("Hectares = %f", hectares);
            printf("Square kilometer = %f", square_kilometer);
            printf("Square inch = %f", square_inch);
            printf("Square feet = %f", square_feet);
            printf("Square yard = %f", square_yard);
            printf("Square mile = %f", square_mile);
        }else if (strcasecmp(user_input_area, "Square millimeter") == 0 || strcasecmp(user_input_area, "s.mm") == 0)
        {
            printf("Square millimeter = ");
            scanf("%f", &square_millimeter);
            square_centimeter = square_millimeter/100;
            square_meter = square_centimeter/10000;
            square_kilometer = square_meter/1000000;
            hectares = square_meter/10000;
            square_inch = square_centimeter/6.4516;
            square_feet = square_inch/144;
            square_yard = square_feet/9;
            square_mile = square_kilometer/2.5921000000000003;
            printf("Square centimeter = %f", square_centimeter);
            printf("Square meter = %f", square_meter);
            printf("Hectares = %f", hectares);
            printf("Square kilometer = %f", square_kilometer);
            printf("Square inch = %f", square_inch);
            printf("Square feet = %f", square_feet);
            printf("Square yard = %f", square_yard);
            printf("Square mile = %f", square_mile);
        }else if (strcasecmp(user_input_area, "Square centimeter") == 0 || strcasecmp(user_input_area, "s.cm") == 0)
        {
            printf("Square centimeter = ");
            scanf("%f", &square_centimeter);
            square_millimeter = square_centimeter*100;
            square_meter = square_centimeter/10000;
            square_kilometer = square_meter/1000000;
            hectares = square_meter/10000;
            square_inch = square_centimeter/6.4516;
            square_feet = square_inch/144;
            square_yard = square_feet/9;
            square_mile = square_kilometer/2.5921000000000003;
            printf("Square millimeter = %f", square_millimeter);
            printf("Square meter = %f", square_meter);
            printf("Hectares = %f", hectares);
            printf("Square kilometer = %f", square_kilometer);
            printf("Square inch = %f", square_inch);
            printf("Square feet = %f", square_feet);
            printf("Square yard = %f", square_yard);
            printf("Square mile = %f", square_mile);
        }else if (strcasecmp(user_input_area, "Square kilometer") == 0 || strcasecmp(user_input_area, "s.km") == 0)
        {
            printf("Square kilometer = ");
            scanf("%f", &square_kilometer);
            square_meter = square_kilometer*1000000;
            square_centimeter = square_meter*10000;
            square_millimeter = square_centimeter*100;
            hectares = square_meter/10000;
            square_inch = square_centimeter/6.4516;
            square_feet = square_inch/144;
            square_yard = square_feet/9;
            square_mile = square_kilometer/2.5921000000000003;
            printf("Square millimeter = %f", square_millimeter);
            printf("Square centimeter = %f", square_centimeter);
            printf("Square meter = %f", square_meter);
            printf("Hectares = %f", hectares);
            printf("Square inch = %f", square_inch);
            printf("Square feet = %f", square_feet);
            printf("Square yard = %f", square_yard);
            printf("Square mile = %f", square_mile);
        }else if (strcasecmp(user_input_area, "Hectares") == 0 || strcasecmp(user_input_area, "Hectare") == 0 || strcasecmp(user_input_area, "ht") == 0)
        {
            printf("Hectares = ");
            scanf("%f", &hectares);
            square_meter = hectares*10000;
            square_kilometer = square_meter/1000000;
            square_centimeter = square_meter*10000;
            square_millimeter = square_centimeter*100;
            square_inch = square_centimeter/6.4516;
            square_feet = square_inch/144;
            square_yard = square_feet/9;
            square_mile = square_kilometer/2.5921000000000003;
            printf("Square millimeter = %f", square_millimeter);
            printf("Square centimeter = %f", square_centimeter);
            printf("Square meter = %f", square_meter);
            printf("Square kilometer = %f", square_kilometer);
            printf("Square inch = %f", square_inch);
            printf("Square feet = %f", square_feet);
            printf("Square yard = %f", square_yard);
            printf("Square mile = %f", square_mile);
        }else if (strcasecmp(user_input_area, "Square inch") == 0 || strcasecmp(user_input_area, "s.in") == 0)
        {
            printf("Square inch = ");
            scanf("%f", &square_inch);
            square_centimeter = square_inch*6.4516;
            square_millimeter = square_centimeter*100;
            square_meter = square_centimeter/10000;
            square_kilometer = square_meter/1000000;
            hectares = square_meter/10000;
            square_feet = square_inch/144;
            square_yard = square_feet/9;
            square_mile = square_kilometer/2.5921000000000003;
            printf("Square millimeter = %f", square_millimeter);
            printf("Square centimeter = %f", square_centimeter);
            printf("Square meter = %f", square_meter);
            printf("Hectares = %f", hectares);
            printf("Square kilometer = %f", square_kilometer);
            printf("Square feet = %f", square_feet);
            printf("Square yard = %f", square_yard);
            printf("Square mile = %f", square_mile);
        }else if (strcasecmp(user_input_area, "Square feet") == 0 || strcasecmp(user_input_area, "s.ft") == 0)
        {
            printf("Square feet = ");
            scanf("%f", &square_feet);
            square_inch = square_feet*144;
            square_centimeter = square_inch*6.4516;
            square_millimeter = square_centimeter*100;
            square_meter = square_centimeter/10000;
            square_kilometer = square_meter/1000000;
            hectares = square_meter/10000;
            square_yard = square_feet/9;
            square_mile = square_kilometer/2.5921000000000003;
            printf("Square millimeter = %f", square_millimeter);
            printf("Square centimeter = %f", square_centimeter);
            printf("Square meter = %f", square_meter);
            printf("Hectares = %f", hectares);
            printf("Square kilometer = %f", square_kilometer);
            printf("Square inch = %f", square_inch);
            printf("Square yard = %f", square_yard);
            printf("Square mile = %f", square_mile);
        }else if (strcasecmp(user_input_area, "Square yard") == 0 || strcasecmp(user_input_area, "s.yd") == 0)
        {
            printf("Square yard = ");
            scanf("%f", &square_yard);
            square_feet = square_yard*9;
            square_inch = square_feet*144;
            square_centimeter = square_inch*6.4516;
            square_millimeter = square_centimeter*100;
            square_meter = square_centimeter/10000;
            square_kilometer = square_meter/1000000;
            hectares = square_meter/10000;
            square_mile = square_kilometer/2.5921000000000003;
            printf("Square millimeter = %f", square_millimeter);
            printf("Square centimeter = %f", square_centimeter);
            printf("Square meter = %f", square_meter);
            printf("Hectares = %f", hectares);
            printf("Square kilometer = %f", square_kilometer);
            printf("Square inch = %f", square_inch);
            printf("Square feet = %f", square_feet);
            printf("Square mile = %f", square_mile);
        }else if (strcasecmp(user_input_area, "Square mile") == 0 || strcasecmp(user_input_area, "s.mi") == 0)
        {
            printf("Square mile = ");
            scanf("%f", &square_mile);
            square_kilometer = square_mile*2.5921000000000003;
            square_meter = square_kilometer*1000000;
            square_centimeter = square_meter*10000;
            square_millimeter = square_centimeter*100;
            hectares = square_meter/10000;
            square_inch = square_centimeter/6.4516;
            square_feet = square_inch/144;
            square_yard = square_feet/9;
            printf("Square millimeter = %f", square_millimeter);
            printf("Square centimeter = %f", square_centimeter);
            printf("Square meter = %f", square_meter);
            printf("Hectares = %f", hectares);
            printf("Square kilometer = %f", square_kilometer);
            printf("Square inch = %f", square_inch);
            printf("Square feet = %f", square_feet);
            printf("Square yard = %f", square_yard);
        }else{
            printf("Invalid option!");
            return 1;
        }
    }else if (strcasecmp(user_input, "Speed") == 0)
    {
        char user_input_speed[31];
        float kilometer_per_hour, kilometer_per_second, meter_per_second, mach, feet_per_second, yard_per_second, mile_per_hour, knot;
        printf("Which unit of speed do you want to enter?: ");
        fgets(user_input_speed, sizeof(user_input_speed), stdin);
        remove_newline(user_input_speed);
        if (strcasecmp(user_input_speed, "Kilometer per hour") == 0 || strcasecmp(user_input_speed, "km/h") == 0)
        {
            printf("Kilometer per hour = ");
            scanf("%f", &kilometer_per_hour);
            kilometer_per_second = kilometer_per_hour/3600;
            meter_per_second = kilometer_per_hour/3.6;
            mach = kilometer_per_hour/1234.8;
            feet_per_second = kilometer_per_hour*0.911344415;
            yard_per_second = feet_per_second/3;
            mile_per_hour = kilometer_per_hour*0.621371192;
            knot = kilometer_per_hour*0.539956803;
            printf("Kilometer per second = %f", kilometer_per_second);
            printf("Meter per second = %f", meter_per_second);
            printf("Mach = %f", mach);
            printf("Feet per second = %f", feet_per_second);
            printf("Yard per second = %f", yard_per_second);
            printf("Mile per hour = %f", mile_per_hour);
            printf("Knot = %f", knot);
        }else if (strcasecmp(user_input_speed, "Kilometer per second") == 0 || strcasecmp(user_input_speed, "km/s") == 0)
        {
            printf("Kilometer per second = ");
            scanf("%f", &kilometer_per_second);
            kilometer_per_hour = kilometer_per_second*3600;
            meter_per_second = kilometer_per_second*1000;
            mach = kilometer_per_hour/1234.8;
            feet_per_second = kilometer_per_hour*0.911344415;
            yard_per_second = feet_per_second/3;
            mile_per_hour = kilometer_per_hour*0.621371192;
            knot = kilometer_per_hour*0.539956803;
            printf("Kilometer per hour = %f", kilometer_per_hour);
            printf("Meter per second = %f", meter_per_second);
            printf("Mach = %f", mach);
            printf("Feet per second = %f", feet_per_second);
            printf("Yard per second = %f", yard_per_second);
            printf("Mile per hour = %f", mile_per_hour);
            printf("Knot = %f", knot);
        }else if (strcasecmp(user_input_speed, "Meter per second") == 0 || strcasecmp(user_input_speed, "m/s") == 0)
        {
            printf("Meter per second = ");
            scanf("%f", &meter_per_second);
            kilometer_per_hour = meter_per_second*3.6;
            kilometer_per_second = kilometer_per_hour/3600;
            mach = kilometer_per_hour/1234.8;
            feet_per_second = kilometer_per_hour*0.911344415;
            yard_per_second = feet_per_second/3;
            mile_per_hour = kilometer_per_hour*0.621371192;
            knot = kilometer_per_hour*0.539956803;
            printf("Kilometer per hour = %f", kilometer_per_hour);
            printf("Kilometer per second = %f", kilometer_per_second);
            printf("Mach = %f", mach);
            printf("Feet per second = %f", feet_per_second);
            printf("Yard per second = %f", yard_per_second);
            printf("Mile per hour = %f", mile_per_hour);
            printf("Knot = %f", knot);
        }else if (strcasecmp(user_input_speed, "Mach") == 0)
        {
            printf("Mach = ");
            scanf("%f", &mach);
            kilometer_per_hour = mach*1234.8;
            kilometer_per_second = kilometer_per_hour/3600;
            meter_per_second = kilometer_per_hour/3.6;
            feet_per_second = kilometer_per_hour*0.911344415;
            yard_per_second = feet_per_second/3;
            mile_per_hour = kilometer_per_hour*0.621371192;
            knot = kilometer_per_hour*0.539956803;
            printf("Kilometer per hour = %f", kilometer_per_hour);
            printf("Kilometer per second = %f", kilometer_per_second);
            printf("Meter per second = %f", meter_per_second);
            printf("Feet per second = %f", feet_per_second);
            printf("Yard per second = %f", yard_per_second);
            printf("Mile per hour = %f", mile_per_hour);
            printf("Knot = %f", knot);
        }else if (strcasecmp(user_input_speed, "Feet per second") == 0 || strcasecmp(user_input_speed, "ft/s") == 0)
        {
            printf("Feet per second = ");
            scanf("%f", &feet_per_second);
            yard_per_second = feet_per_second/3;
            meter_per_second = yard_per_second/1.093613298;
            kilometer_per_hour = meter_per_second*3.6;
            kilometer_per_second = kilometer_per_hour/3600;
            mach = kilometer_per_hour/1234.8;
            mile_per_hour = kilometer_per_hour*0.621371192;
            knot = kilometer_per_hour*0.539956803;
            printf("Kilometer per hour = %f", kilometer_per_hour);
            printf("Kilometer per second = %f", kilometer_per_second);
            printf("Meter per second = %f", meter_per_second);
            printf("Mach = %f", mach);
            printf("Yard per second = %f", yard_per_second);
            printf("Mile per hour = %f", mile_per_hour);
            printf("Knot = %f", knot);
        }else if (strcasecmp(user_input_speed, "Yard per second") == 0 || strcasecmp(user_input_speed, "yd/s") == 0)
        {
            printf("Yard per second = ");
            scanf("%f", &yard_per_second);
            meter_per_second = yard_per_second/1.093613298;
            kilometer_per_hour = meter_per_second*3.6;
            kilometer_per_second = kilometer_per_hour/3600;
            mach = kilometer_per_hour/1234.8;
            feet_per_second = yard_per_second*3;
            mile_per_hour = kilometer_per_hour*0.621371192;
            knot = kilometer_per_hour*0.539956803;
            printf("Kilometer per hour = %f", kilometer_per_hour);
            printf("Kilometer per second = %f", kilometer_per_second);
            printf("Meter per second = %f", meter_per_second);
            printf("Mach = %f", mach);
            printf("Feet per second = %f", feet_per_second);
            printf("Mile per hour = %f", mile_per_hour);
            printf("Knot = %f", knot);
        }else if (strcasecmp(user_input_speed, "Mile per hour") == 0 || strcasecmp(user_input_speed, "mph") == 0)
        {
            printf("Mile per hour = ");
            scanf("%f", &mile_per_hour);
            kilometer_per_hour = mile_per_hour*1.609344;
            kilometer_per_second = kilometer_per_hour/3600;
            meter_per_second = kilometer_per_second*1000;
            mach = kilometer_per_hour/1234.8;
            feet_per_second = kilometer_per_hour*0.911344415;
            yard_per_second = feet_per_second/3;
            knot = kilometer_per_hour*0.539956803;
            printf("Kilometer per hour = %f", kilometer_per_hour);
            printf("Kilometer per second = %f", kilometer_per_second);
            printf("Meter per second = %f", meter_per_second);
            printf("Mach = %f", mach);
            printf("Feet per second = %f", feet_per_second);
            printf("Yard per second = %f", yard_per_second);
            printf("Knot = %f", knot);
        }else if (strcasecmp(user_input_speed, "Knot") == 0)
        {
            printf("Knot = ");
            scanf("%f", &knot);
            kilometer_per_hour = knot/0.539956803;
            kilometer_per_second = kilometer_per_hour/3600;
            meter_per_second = kilometer_per_second*1000;
            mach = kilometer_per_hour/1234.8;
            feet_per_second = kilometer_per_hour*0.911344415;
            yard_per_second = feet_per_second/3;
            mile_per_hour = kilometer_per_hour*0.621371192;
            printf("Kilometer per hour = %f", kilometer_per_hour);
            printf("Kilometer per second = %f", kilometer_per_second);
            printf("Meter per second = %f", meter_per_second);
            printf("Mach = %f", mach);
            printf("Feet per second = %f", feet_per_second);
            printf("Yard per second = %f", yard_per_second);
            printf("Mile per hour = %f", mile_per_hour);
        }else{
            printf("Invalid option!");
            return 1;
        }
    }else if (strcasecmp(user_input, "Time") == 0)
    {
        char user_input_time[31];
        float microsecond, millisecond, second, minute, hour, day, week, month, year, century;
        printf("Which unit of time do you want to enter?: ");
        fgets(user_input_time, sizeof(user_input_time), stdin);
        remove_newline(user_input_time);
        if (strcasecmp(user_input_time, "Microsecond") == 0 || strcasecmp(user_input_time, "micro.s") == 0)
        {
            printf("Microsecond = ");
            scanf("%f", &microsecond);
            millisecond = microsecond/1000;
            second = millisecond/1000;
            minute = second/60;
            hour = minute/60;
            day = hour/24;
            week = day/7;
            month = day/30;
            year = day/365;
            century = year/100;
            printf("Millisecond = %f", millisecond);
            printf("Second = %f", second);
            printf("Minute = %f", minute);
            printf("Hour = %f", hour);
            printf("Day = %f", day);
            printf("Week = %f", week);
            printf("Month = %f", month);
            printf("Year = %f", year);
            printf("Century = %f", century);
        }else if (strcasecmp(user_input_time, "Millisecond") == 0 || strcasecmp(user_input_time, "ms") == 0)
        {
            printf("Millisecond = ");
            scanf("%f", &millisecond);
            microsecond = millisecond*1000;
            second = millisecond/1000;
            minute = second/60;
            hour = minute/60;
            day = hour/24;
            week = day/7;
            month = day/30;
            year = day/365;
            century = year/100;
            printf("Microseconds = %f", microsecond);
            printf("Second = %f", second);
            printf("Minute = %f", minute);
            printf("Hour = %f", hour);
            printf("Day = %f", day);
            printf("Week = %f", week);
            printf("Month = %f", month);
            printf("Year = %f", year);
            printf("Century = %f", century);
        }else if (strcasecmp(user_input_time, "Second") == 0 || strcasecmp(user_input_time, "s") == 0)
        {
            printf("Second = ");
            scanf("%f", &second);
            millisecond = second*1000;
            microsecond = millisecond*1000;
            minute = second/60;
            hour = minute/60;
            day = hour/24;
            week = day/7;
            month = day/30;
            year = day/365;
            century = year/100;
            printf("Microseconds = %f", microsecond);
            printf("Milliseconds = %f", millisecond);
            printf("Minute = %f", minute);
            printf("Hour = %f", hour);
            printf("Day = %f", day);
            printf("Week = %f", week);
            printf("Month = %f", month);
            printf("Year = %f", year);
            printf("Century = %f", century);
        }else if (strcasecmp(user_input_time, "Minute") == 0 || strcasecmp(user_input_time, "m") == 0)
        {
            printf("Minute = ");
            scanf("%f", &minute);
            second = minute*60;
            millisecond = second*1000;
            microsecond = millisecond*1000;
            hour = minute/60;
            day = hour/24;
            week = day/7;
            month = day/30;
            year = day/365;
            century = year/100;
            printf("Microseconds = %f", microsecond);
            printf("Milliseconds = %f", millisecond);
            printf("Second = %f", second);
            printf("Hour = %f", hour);
            printf("Day = %f", day);
            printf("Week = %f", week);
            printf("Month = %f", month);
            printf("Year = %f", year);
            printf("Century = %f", century);
        }else if (strcasecmp(user_input_time, "Hour") == 0 || strcasecmp(user_input_time, "h") == 0)
        {
            printf("Hour = ");
            scanf("%f", &hour);
            minute = hour*60;
            second = minute*60;
            millisecond = second*1000;
            microsecond = millisecond*1000;
            day = hour/24;
            week = day/7;
            month = day/30;
            year = day/365;
            century = year/100;
            printf("Microseconds = %f", microsecond);
            printf("Milliseconds = %f", millisecond);
            printf("Second = %f", second);
            printf("Minute = %f", minute);
            printf("Day = %f", day);
            printf("Week = %f", week);
            printf("Month = %f", month);
            printf("Year = %f", year);
            printf("Century = %f", century);
        }else if (strcasecmp(user_input_time, "Day") == 0 || strcasecmp(user_input_time, "dd") == 0)
        {
            printf("Day = ");
            scanf("%f", &day);
            hour = day*24;
            minute = hour*60;
            second = minute*60;
            millisecond = second*1000;
            microsecond = millisecond*1000;
            week = day/7;
            month = day/30;
            year = day/365;
            century = year/100;
            printf("Microseconds = %f", microsecond);
            printf("Milliseconds = %f", millisecond);
            printf("Second = %f", second);
            printf("Minute = %f", minute);
            printf("Hour = %f", hour);
            printf("Week = %f", week);
            printf("Month = %f", month);
            printf("Year = %f", year);
            printf("Century = %f", century);
        }else if (strcasecmp(user_input_time, "Week") == 0 || strcasecmp(user_input_time, "w") == 0)
        {
            printf("Week = ");
            scanf("%f", &week);
            day = week*7;
            hour = day*24;
            minute = hour*60;
            second = minute*60;
            millisecond = second*1000;
            microsecond = millisecond*1000;
            month = day/30;
            year = day/365;
            century = year/100;
            printf("Microseconds = %f", microsecond);
            printf("Milliseconds = %f", millisecond);
            printf("Second = %f", second);
            printf("Minute = %f", minute);
            printf("Hour = %f", hour);
            printf("Day = %f", day);
            printf("Month = %f", month);
            printf("Year = %f", year);
            printf("Century = %f", century);
        }else if (strcasecmp(user_input_time, "Month") == 0 || strcasecmp(user_input_time, "mm") == 0)
        {
            printf("Month = ");
            scanf("%f", &month);
            day = month*30;
            hour = day*24;
            minute = hour*60;
            second = minute*60;
            millisecond = second*1000;
            microsecond = millisecond*1000;
            year = day/365;
            century = year/100;
            week = day/7;
            printf("Microseconds = %f", microsecond);
            printf("Milliseconds = %f", millisecond);
            printf("Second = %f", second);
            printf("Minute = %f", minute);
            printf("Hour = %f", hour);
            printf("Day = %f", day);
            printf("Week = %f", week);
            printf("Year = %f", year);
            printf("Century = %f", century);
        }else if (strcasecmp(user_input_time, "Year") == 0 || strcasecmp(user_input_time, "yy") == 0)
        {
            printf("Year = ");
            scanf("%f", &year);
            day = year*365;
            hour = day*24;
            minute = hour*60;
            second = minute*60;
            millisecond = second*1000;
            microsecond = millisecond*1000;
            week = day/7;
            month = day/30;
            century = year/100;
            printf("Microseconds = %f", microsecond);
            printf("Milliseconds = %f", millisecond);
            printf("Second = %f", second);
            printf("Minute = %f", minute);
            printf("Hour = %f", hour);
            printf("Day = %f", day);
            printf("Week = %f", week);
            printf("Month = %f", month);
            printf("Century = %f", century);
        }else if (strcasecmp(user_input_time, "Century") == 0 || strcasecmp(user_input_time, "C.") == 0)
        {
            printf("Century = ");
            scanf("%f", &century);
            year = century*100;
            day = year*365;
            hour = day*24;
            minute = hour*60;
            second = minute*60;
            millisecond = second*1000;
            microsecond = millisecond*1000;
            week = day/7;
            month = year*12;
            printf("Microseconds = %f", microsecond);
            printf("Milliseconds = %f", millisecond);
            printf("Second = %f", second);
            printf("Minute = %f", minute);
            printf("Hour = %f", hour);
            printf("Day = %f", day);
            printf("Week = %f", week);
            printf("Month = %f", month);
            printf("Year = %f", year);
        }else{
            printf("Invalid option!");
            return 1;
        }
    }else if (strcasecmp(user_input, "Power") == 0)
    {
        char user_input_power[31];
        float watt, kilowatt, horsepower;
        printf("Which unit of power do you want to enter?: ");
        fgets(user_input_power, sizeof(user_input_power), stdin);
        remove_newline(user_input_power);
        if (strcasecmp(user_input_power, "Watt") == 0 || strcasecmp(user_input_power, "w") == 0)
        {
            printf("Watt = ");
            scanf("%f", &watt);
            kilowatt = watt/1000;
            horsepower = kilowatt*1.341021859;
            printf("Kilowatt = %f", kilowatt);
            printf("Horsepower = %f", horsepower);
        }else if (strcasecmp(user_input_power, "Kilowatt") == 0 || strcasecmp(user_input_power, "kw") == 0)
        {
            printf("Kilowatt = ");
            scanf("%f", &kilowatt);
            watt = kilowatt*1000;
            horsepower = kilowatt*1.341021859;
            printf("Watt = %f", watt);
            printf("Horsepower = %f", horsepower);
        }else if (strcasecmp(user_input_power, "Horsepower") == 0 || strcasecmp(user_input_power, "hp") == 0)
        {
            printf("Horsepower = ");
            scanf("%f", &horsepower);
            kilowatt = horsepower/1.341021859;
            watt = kilowatt*1000;
            printf("Watt = %f", watt);
            printf("Kilowatt = %f",kilowatt);
        }else{
            printf("Invalid option!");
            return 1;
        }
    }else if (strcasecmp(user_input, "Electronics") == 0)
    {
        char user_input_electronics[31];
        float volt, amphare, watt;
        printf("Which unit do you want to calculate?: ");
        fgets(user_input_electronics, sizeof(user_input_electronics), stdin);
        remove_newline(user_input_electronics);
        if (strcasecmp(user_input_electronics, "Watt") == 0 || strcasecmp(user_input_electronics, "w") == 0)
        {
            printf("Volt = ");
            scanf("%f", &volt);
            printf("Amphare = ");
            scanf("%f", &amphare);
            watt = volt*amphare;
            printf("Watt = %f", watt);
        }else if (strcasecmp(user_input_electronics, "Volt") == 0 || strcasecmp(user_input_electronics, "V") == 0)
        {
            printf("Watt = ");
            scanf("%f", &watt);
            printf("Amphare = ");
            scanf("%f", &amphare);
            volt = watt/amphare;
            printf("Volt = %f", volt);
        }else if (strcasecmp(user_input_electronics, "Amphare") == 0 || strcasecmp(user_input_electronics, "A") == 0 || strcasecmp(user_input_electronics, "I") == 0 || strcasecmp(user_input_electronics, "Amp") == 0)
        {
            printf("Watt = ");
            scanf("%f", &watt);
            printf("Volt = ");
            scanf("%f", &volt);
            amphare = watt/volt;
            printf("Amphare = %f", amphare);
        }else{
            printf("Invalid option!");
            return 1;
        }
    }else{
        printf("Invalid option!");
        return 1;
    }
    return 0;
}