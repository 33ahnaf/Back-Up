#include <stdio.h>

int main(){
    char user_input[31], user_input_length[31], user_input_volume[31], user_input_mass[31], user_input_temperature[31], user_input_area[31], user_input_speed[31], user_input_time[31], user_input_power[31];
    float kilometer = 0, millimeter = 0, centimeter = 0, meter = 0, mile = 0, nautical_mile = 0, inch = 0, feet = 0, yard = 0, micron = 0, liter = 0, milliliter = 0, kiloliter = 0, cubic_centimeter = 0, cubic_meter = 0, cubic_inch = 0, cubic_feet = 0, cubic_yard = 0, gallon_us = 0, gallon_uk = 0, milligram = 0, gram = 0, kilogram = 0, tonn = 0, pound = 0, ounce = 0, celsius = 0, fahrenheit = 0, kelvin = 0, square_meter = 0, square_centimeter = 0, square_millimeter = 0, hectares = 0, square_kilometer = 0, square_inch = 0, square_feet = 0, square_yard = 0, square_mile = 0, kilometer_per_hour = 0, kilometer_per_second = 0, meter_per_second = 0, mach = 0, feet_per_second = 0, yard_per_second = 0, mile_per_hour = 0, knot = 0, microsecond = 0, millisecond = 0, second = 0, minute = 0, hour = 0, day = 0, week = 0, month = 0, year = 0, century = 0, watt = 0, kilowatt = 0, horsepower = 0;
    printf("Welcome to the ultimate calculator\n");
    printf("----------------------------------\n");
    printf("What type of calculation do you want to enter?: ");
    scanf("%30s", user_input);
    if (user_input == "Length" || user_input == "length")
    {
        printf("Which unit of length do you want to enter?: ");
        scanf("%30s", user_input_length);
        if (user_input_length == "Kilometer" || user_input_length == "kilometer" || user_input_length == "km")
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
        }
        if (user_input_length == "Millimeter" || user_input_length == "millimeter" || user_input_length == "mm")
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
        }
        if (user_input_length == "Centimeter" || user_input_length == "centimeter" || user_input_length == "cm")
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
        }
        if (user_input_length == "Micron" || user_input_length == "micron")
        {
            printf("Centimeter = ");
            scanf("%f", &centimeter);
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
        }
        if (user_input_length == "Meter" || user_input_length == "meter" || user_input_length == "m")
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
        }
        if (user_input_length == "Inch" || user_input_length == "inch" || user_input_length == "in")
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
        }
        if (user_input_length == "Feet" || user_input_length == "feet" || user_input_length == "ft")
        {
            printf("Inch = ");
            scanf("%f", &inch);
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
        }
        if (user_input_length == "Yard" || user_input_length == "yard" || user_input_length == "yd")
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
        }
        if (user_input_length == "Mile" || user_input_length == "mile" || user_input_length == "mi")
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
        }
        if (user_input_length == "Nautical mile" || user_input_length == "nautical mile" || user_input_length == "n.mi" || user_input_length == "n.mile")
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
        }
    }
    if (user_input == "Volume" || user_input == "volume")
    {
        printf("Which unit of volume do you want to enter?: ");
        scanf("%30s", user_input_volume);
        if (user_input_volume == "Liter" || user_input_volume == "liter" || user_input_volume == "l")
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
        }
        if (user_input_volume == "Milliliter" || user_input_volume == "milliliter" || user_input_volume == "ml")
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
        }
        if (user_input_volume == "Kiloliter" || user_input_volume == "kiloliter" || user_input_volume == "kl")
        {
            printf("Milliliter = ");
            scanf("%f", &milliliter);
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
        }
        if (user_input_volume == "Cubic centimeter" || user_input_volume == "cubic centimeter" || user_input_volume == "c.cm")
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
        }
        if (user_input_volume == "Cubic meter" || user_input_volume == "cubic meter" || user_input_volume == "c.m")
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
        }
        if (user_input_volume == "Cubic inch" || user_input_volume == "cubic inch" || user_input_volume == "c.in")
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
        }
        if (user_input_volume == "Cubic feet" || user_input_volume == "cubic feet" || user_input_volume == "c.ft")
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
        }
        if (user_input_volume == "Cubic yard" || user_input_volume == "cubic yard" || user_input_volume == "c.yd")
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
        }
        if (user_input_volume == "Gallon(US)" || user_input_volume == "gallon(US)" || user_input_volume == "gallon(us)")
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
        }
        if (user_input_volume == "Gallon(UK)" || user_input_volume == "gallon(UK)" || user_input_volume == "gallon(uk)")
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
        }
    }
    if (user_input == "Mass" || user_input == "mass")
    {
        printf("Which unit of mass do you want to enter?: ");
        scanf("%30s", &user_input_mass);
        if (user_input_mass == "Milligram" || user_input_mass == "milligram" || user_input_mass == "mg")
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
        }
        if (user_input_mass == "Gram" || user_input_mass == "gram" || user_input_mass == "g")
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
        }
        if (user_input_mass == "Kilogram" || user_input_mass == "kilogram" || user_input_mass == "kg")
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
        }
        if (user_input_mass == "Tonn" || user_input_mass == "tonn" || user_input_mass == "t")
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
        }
        if (user_input_mass == "Pound" || user_input_mass == "pound" || user_input_mass == "lb")
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
        }
        if (user_input_mass == "Ounce" || user_input_mass == "ounce" || user_input_mass == "oz")
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
        }
    }
    if (user_input == "Temperature" || user_input == "temperature")
    {
        printf("Which unit of temperature do you want to enter?: ");
        scanf("%30s", &user_input_temperature);
        if (user_input_temperature == "Celsius" || user_input_temperature == "celsius" || user_input_temperature == "C")
        {
            printf("Celsius = ");
            scanf("%f", &celsius);
            kelvin = celsius+273.15;
            fahrenheit = (1.8*celsius)+32;
            printf("Fahrenheit = %f\n", fahrenheit);
            printf("Kelvin = %f\n", kelvin);
        }
        if (user_input_temperature == "Fahrenheit" || user_input_temperature == "fahrenheit" || user_input_temperature == "F")
        {
            printf("Fahrenheit = ");
            scanf("%f", &fahrenheit);
            celsius = (fahrenheit-32)/1.8;
            kelvin = celsius+273.15;
            printf("Celsius = %f\n", celsius);
            printf("Kelvin = %f\n", kelvin);
        }
        if (user_input_temperature == "Kelvin" || user_input_temperature == "kelvin" || user_input_temperature == "K")
        {
            printf("Kelvin = ");
            scanf("%f", &kelvin);
            celsius = kelvin-273.15;
            fahrenheit = (celsius*1.8)+32;
            printf("Celsius = %f\n", celsius);
            printf("Fahrenheit = %f\n", fahrenheit);
        }
    }
    if (user_input == "Area" || user_input == "area")
    {
        printf("Which unit of area do you want to enter?: ");
        scanf("%30s", &user_input_area);
        if (user_input_area == "Square meter" || user_input_area == "square meter" || user_input_area == "s.m")
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
        }
        if (user_input_area == "Square millimeter" || user_input_area == "square millimeter" || user_input_area == "s.mm")
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
        }
        if (user_input_area == "Square centimeter" || user_input_area == "square centimeter" || user_input_area == "s.cm")
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
        }
        if (user_input_area == "Square kilometer" || user_input_area == "square kilometer" || user_input_area == "s.km")
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
        }
        if (user_input_area == "Hectares" || user_input_area == "hectares" || user_input_area == "ht")
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
        }
        if (user_input_area == "Square inch" || user_input_area == "square inch" || user_input_area == "s.in")
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
        }
        if (user_input_area == "Square feet" || user_input_area == "square feet" || user_input_area == "s.ft")
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
        }
        if (user_input_area == "Square yard" || user_input_area == "square yard" || user_input_area == "s.yd")
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
        }
        if (user_input_area == "Square mile" || user_input_area == "square mile" || user_input_area == "s.mi")
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
        }
    }
    return 0;
}