#  Copyright: ©Ahnaf Shariar 2024
#
#  Stetch originally wrote 17 July 2024
#  by Md. Ahnaf Shariar
#
#  This example code is in the public domain.

print("Welcome to the ultimate calculator")
print("----------------------------------")
user_input = input("What type of calculation do you need?: ")
if user_input == "Length" or user_input == "length":
    user_input_length = input("Which unit of length do you want to enter?: ")
    if user_input_length == "Kilometer" or user_input_length == "kilometer" or user_input_length == "km":
        kilometer = float(input("Kilometer = "))
        millimeter = kilometer*1000000
        centimeter = kilometer*100000
        meter = kilometer*1000
        mile = kilometer*0.621371192
        nautical_mile = kilometer*0.539956803
        inch = kilometer*39370.07874
        feet = kilometer*3280.839895
        yard = kilometer*1093.613298
        micron = kilometer*1000000000
        print(f"Micron = {micron}")
        print(f"Millimeter = {millimeter}")
        print(f"Centimeter = {centimeter}")
        print(f"Meter = {meter}")
        print(f"Inch = {inch}")
        print(f"Feet = {feet}")
        print(f"Yard = {yard}")
        print(f"Mile = {mile}")
        print(f"Nautical mile = {nautical_mile}")
    if user_input_length == "Millimeter" or user_input_length == "millimeter" or user_input_length == "mm":
        millimeter = float(input("Millimeter = "))
        centimeter = millimeter/10
        kilometer = millimeter/1000000
        meter = millimeter/1000
        mile = kilometer*0.621371192
        nautical_mile = kilometer*0.539956803
        inch = centimeter/2.54
        feet = inch/12
        yard = feet/3
        micron = millimeter*1000
        print(f"Micron = {micron}")
        print(f"Centimeter = {centimeter}")
        print(f"Meter = {meter}")
        print(f"Kilometer = {kilometer}")
        print(f"Inch = {inch}")
        print(f"Feet = {feet}")
        print(f"Yard = {yard}")
        print(f"Mile = {mile}")
        print(f"Nautical mile = {nautical_mile}")
    if user_input_length == "Centimeter" or user_input_length == "centimeter" or user_input_length == "cm":
        centimeter = float(input("Centimeter = "))
        millimeter = centimeter*10
        meter = centimeter/100
        kilometer = meter/1000
        micron = centimeter*10000
        inch = centimeter/2.54
        feet = inch/12
        yard = feet/3
        mile = kilometer*0.621371192
        nautical_mile = kilometer*0.539956803
        print(f"Micron = {micron}")
        print(f"Millimeter = {millimeter}")
        print(f"Meter = {meter}")
        print(f"Kilometer = {kilometer}")
        print(f"Inch = {inch}")
        print(f"Feet = {feet}")
        print(f"Yard = {yard}")
        print(f"Mile = {mile}")
        print(f"Nautical mile = {nautical_mile}")
    if user_input_length == "Micron" or user_input_length == "micron":
        micron = float(input("Micron = "))
        millimeter = micron/1000
        centimeter = millimeter/10
        meter = centimeter/100
        kilometer = meter/1000
        inch = centimeter/2.54
        feet = inch/12
        yard = feet/3
        mile = kilometer*0.621371192
        nautical_mile = kilometer*0.539956803
        print(f"Millimeter = {millimeter}")
        print(f"Centimeter = {centimeter}")
        print(f"Meter = {meter}")
        print(f"Kilometer = {kilometer}")
        print(f"Inch = {inch}")
        print(f"Feet = {feet}")
        print(f"Yard = {yard}")
        print(f"Mile = {mile}")
        print(f"Nautical mile = {nautical_mile}")
    if user_input_length == "Meter" or user_input_length == "meter" or user_input_length == "m":
        meter = float(input("Meter = "))
        micron = meter*1000000
        millimeter = meter*1000
        centimeter = meter*100
        kilometer = meter/1000
        inch = centimeter/2.54
        feet = inch/12
        yard = feet/3
        mile = kilometer*0.621371192
        nautical_mile = kilometer*0.539956803
        print(f"Micron = {micron}")
        print(f"Millimeter = {millimeter}")
        print(f"Centimeter = {centimeter}")
        print(f"Kilometer = {kilometer}")
        print(f"Inch = {inch}")
        print(f"Feet = {feet}")
        print(f"Yard = {yard}")
        print(f"Mile = {mile}")
        print(f"Nautical mile = {nautical_mile}")
    if user_input_length == "Inch" or user_input_length == "inch" or user_input_length == "in":
        inch = float(input("Inch = "))
        centimeter = inch*2.54
        millimeter = centimeter*10
        micron = millimeter*1000
        meter = centimeter/100
        kilometer = meter/1000
        feet = inch/12
        yard = feet/3
        mile = kilometer*0.621371192
        nautical_mile = kilometer*0.539956803
        print(f"Micron = {micron}")
        print(f"Millimeter = {millimeter}")
        print(f"Centimeter = {centimeter}")
        print(f"Meter = {meter}")
        print(f"Kilometer = {kilometer}")
        print(f"Feet = {feet}")
        print(f"Yard = {yard}")
        print(f"Mile = {mile}")
        print(f"Nautical mile = {nautical_mile}")
    if user_input_length == "Feet" or user_input_length == "feet" or user_input_length == "ft":
        feet = float(input("Feet = "))
        inch = feet*12
        yard = feet/3
        centimeter = inch*2.54
        millimeter = centimeter*10
        micron = millimeter*1000
        meter = centimeter/100
        kilometer = meter/1000
        mile = kilometer*0.621371192
        nautical_mile = kilometer*0.539956803
        print(f"Micron = {micron}")
        print(f"Millimeter = {millimeter}")
        print(f"Centimeter = {centimeter}")
        print(f"Meter = {meter}")
        print(f"Kilometer = {kilometer}")
        print(f"Inch = {inch}")
        print(f"Yard = {yard}")
        print(f"Mile = {mile}")
        print(f"Nautical mile = {nautical_mile}")
    if user_input_length == "Yard" or user_input_length == "yard" or user_input_length == "yd":
        yard = float(input("Yard = "))
        feet = yard*3
        inch = feet*12
        centimeter = inch*2.54
        millimeter = centimeter*10
        micron = millimeter*1000
        meter = centimeter/100
        kilometer = meter/1000
        mile = kilometer*0.621371192
        nautical_mile = kilometer*0.539956803
        print(f"Micron = {micron}")
        print(f"Millimeter = {millimeter}")
        print(f"Centimeter = {centimeter}")
        print(f"Meter = {meter}")
        print(f"Kilometer = {kilometer}")
        print(f"Inch = {inch}")
        print(f"Feet = {feet}")
        print(f"Mile = {mile}")
        print(f"Nautical mile = {nautical_mile}")
    if user_input_length == "Mile" or user_input_length == "mile" or user_input_length == "mi":
        mile = float(input("Mile = "))
        kilometer = mile*1.609344
        nautical_mile = kilometer*0.539956803
        meter = kilometer*1000
        centimeter = meter*100
        millimeter = centimeter*10
        micron = millimeter*1000
        inch = centimeter/2.54
        feet = inch/12
        yard = feet/3
        print(f"Micron = {micron}")
        print(f"Millimeter = {millimeter}")
        print(f"Centimeter = {centimeter}")
        print(f"Meter = {meter}")
        print(f"Kilometer = {kilometer}")
        print(f"Inch = {inch}")
        print(f"Feet = {feet}")
        print(f"Yard = {yard}")
        print(f"Nautical mile = {nautical_mile}")
    if user_input_length == "Nautical mile" or user_input_length == "nautical mile" or user_input_length == "n.mi" or user_input_length == "n.mile":
        nautical_mile = float(input("Nautical mile = "))
        meter = nautical_mile*1852
        kilometer = meter/1000
        centimeter = meter*100
        millimeter = centimeter*10
        micron = millimeter*1000
        inch = centimeter/2.54
        feet = inch/12
        yard = feet/3
        mile = kilometer*0.621371192
        print(f"Micron = {micron}")
        print(f"Millimeter = {millimeter}")
        print(f"Centimeter = {centimeter}")
        print(f"Meter = {meter}")
        print(f"Kilometer = {kilometer}")
        print(f"Inch = {inch}")
        print(f"Feet = {feet}")
        print(f"Yard = {yard}")
        print(f"Mile = {mile}")
if user_input == "Volume" or user_input == "volume":
    user_input_volume = input("Which unit of volume do you want to enter?: ")
    if user_input_volume == "Liter" or user_input_volume == "liter" or user_input_volume == "l":
        liter = float(input("Liter = "))
        milliliter = liter*1000
        kiloliter = liter/1000
        cubic_centimeter = milliliter
        cubic_meter = kiloliter
        cubic_inch = cubic_centimeter/16.387064
        cubic_feet = cubic_inch/1728
        cubic_yard = cubic_feet/27
        gallon_us = liter*0.264172037
        gallon_uk = liter*0.219969248
        print(f"Milliliter = {milliliter}")
        print(f"Kiloliter = {kiloliter}")
        print(f"Cubic centimeter = {cubic_centimeter}")
        print(f"Cubic meter = {cubic_meter}")
        print(f"Cubic inch = {cubic_inch}")
        print(f"Cubic feet = {cubic_feet}")
        print(f"Cubic yard = {cubic_yard}")
        print(f"Gallon(US) = {gallon_us}")
        print(f"Gallon(UK) = {gallon_uk}")
    if user_input_volume == "Milliliter" or user_input_volume == "milliliter" or user_input_volume == "ml":
        milliliter = float(input("Milliliter = "))
        liter = milliliter/1000
        kiloliter = liter/1000
        cubic_centimeter = milliliter
        cubic_meter = kiloliter
        cubic_inch = cubic_centimeter/16.387064
        cubic_feet = cubic_inch/1728
        cubic_yard = cubic_feet/27
        gallon_us = liter*0.264172037
        gallon_uk = liter*0.219969248
        print(f"Liter = {liter}")
        print(f"Kiloliter = {kiloliter}")
        print(f"Cubic centimeter = {cubic_centimeter}")
        print(f"Cubic meter = {cubic_meter}")
        print(f"Cubic inch = {cubic_inch}")
        print(f"Cubic feet = {cubic_feet}")
        print(f"Cubic yard = {cubic_yard}")
        print(f"Gallon(US) = {gallon_us}")
        print(f"Gallon(UK) = {gallon_uk}")
    if user_input_volume == "Kiloliter" or user_input_volume == "kiloliter" or user_input_volume == "kl":
        kiloliter = float(input("Kiloliter = "))
        liter = kiloliter*1000
        milliliter = liter*1000
        cubic_centimeter = milliliter
        cubic_meter = kiloliter
        cubic_inch = cubic_centimeter/16.387064
        cubic_feet = cubic_inch/1728
        cubic_yard = cubic_feet/27
        gallon_us = liter*0.264172037
        gallon_uk = liter*0.219969248
        print(f"Milliliter = {milliliter}")
        print(f"Liter = {liter}")
        print(f"Cubic centimeter = {cubic_centimeter}")
        print(f"Cubic meter = {cubic_meter}")
        print(f"Cubic inch = {cubic_inch}")
        print(f"Cubic feet = {cubic_feet}")
        print(f"Cubic yard = {cubic_yard}")
        print(f"Gallon(US) = {gallon_us}")
        print(f"Gallon(UK) = {gallon_uk}")
    if user_input_volume == "Cubic centimeter" or user_input_volume == "cubic centimeter" or user_input_volume == "c.cm":
        cubic_centimeter = float(input("Cubic centimeter = "))
        milliliter = cubic_centimeter
        liter = milliliter/1000
        kiloliter = liter/1000
        cubic_meter = kiloliter
        cubic_inch = cubic_centimeter/16.387064
        cubic_feet = cubic_inch/1728
        cubic_yard = cubic_feet/27
        gallon_us = liter*0.264172037
        gallon_uk = liter*0.219969248
        print(f"Milliliter = {milliliter}")
        print(f"Liter = {liter}")
        print(f"Kiloliter = {kiloliter}")
        print(f"Cubic meter = {cubic_meter}")
        print(f"Cubic inch = {cubic_inch}")
        print(f"Cubic feet = {cubic_feet}")
        print(f"Cubic yard = {cubic_yard}")
        print(f"Gallon(US) = {gallon_us}")
        print(f"Gallon(UK) = {gallon_uk}")
    if user_input_volume == "Cubic meter" or user_input_volume == "cubic meter" or user_input_volume == "c.m":
        cubic_meter = float(input("Cubic meter = "))
        kiloliter = cubic_meter
        liter = kiloliter*1000
        milliliter = liter*1000
        cubic_centimeter = milliliter
        cubic_inch = cubic_centimeter/16.387064
        cubic_feet = cubic_inch/1728
        cubic_yard = cubic_feet/27
        gallon_us = liter*0.264172037
        gallon_uk = liter*0.219969248
        print(f"Milliliter = {milliliter}")
        print(f"Liter = {liter}")
        print(f"Kiloliter = {kiloliter}")
        print(f"Cubic centimeter = {cubic_centimeter}")
        print(f"Cubic inch = {cubic_inch}")
        print(f"Cubic feet = {cubic_feet}")
        print(f"Cubic yard = {cubic_yard}")
        print(f"Gallon(US) = {gallon_us}")
        print(f"Gallon(UK) = {gallon_uk}")
    if user_input_volume == "Cubic inch" or user_input_volume == "cubic inch" or user_input_volume == "c.in":
        cubic_inch = float(input("Cubic inch = "))
        cubic_centimeter = cubic_inch*16.387064
        milliliter = cubic_centimeter
        liter = milliliter/1000
        kiloliter = liter/1000
        cubic_meter = kiloliter
        cubic_feet = cubic_inch/1728
        cubic_yard = cubic_feet/27
        gallon_us = liter*0.264172037
        gallon_uk = liter*0.219969248
        print(f"Milliliter = {milliliter}")
        print(f"Liter = {liter}")
        print(f"Kiloliter = {kiloliter}")
        print(f"Cubic centimeter = {cubic_centimeter}")
        print(f"Cubic meter = {cubic_meter}")
        print(f"Cubic feet = {cubic_feet}")
        print(f"Cubic yard = {cubic_yard}")
        print(f"Gallon(US) = {gallon_us}")
        print(f"Gallon(UK) = {gallon_uk}")
    if user_input_volume == "Cubic feet" or user_input_volume == "cubic feet" or user_input_volume == "c.ft":
        cubic_feet = float(input("Cubic feet = "))
        cubic_inch = cubic_feet*1728
        cubic_yard = cubic_feet/27
        cubic_centimeter = cubic_inch*16.387064
        milliliter = cubic_centimeter
        liter = milliliter/1000
        kiloliter = liter/1000
        cubic_meter = kiloliter
        gallon_us = liter*0.264172037
        gallon_uk = liter*0.219969248
        print(f"Milliliter = {milliliter}")
        print(f"Liter = {liter}")
        print(f"Kiloliter = {kiloliter}")
        print(f"Cubic centimeter = {cubic_centimeter}")
        print(f"Cubic meter = {cubic_meter}")
        print(f"Cubic inch = {cubic_inch}")
        print(f"Cubic yard = {cubic_yard}")
        print(f"Gallon(US) = {gallon_us}")
        print(f"Gallon(UK) = {gallon_uk}")
    if user_input_volume == "Cubic yard" or user_input_volume == "cubic yard" or user_input_volume == "c.yd":
        cubic_yard = float(input("Cubic yard = "))
        cubic_feet = cubic_yard*27
        cubic_inch = cubic_feet*1728
        cubic_centimeter = cubic_inch*16.387064
        milliliter = cubic_centimeter
        liter = milliliter/1000
        kiloliter = liter/1000
        cubic_meter = kiloliter
        gallon_us = liter*0.264172037
        gallon_uk = liter*0.219969248
        print(f"Milliliter = {milliliter}")
        print(f"Liter = {liter}")
        print(f"Kiloliter = {kiloliter}")
        print(f"Cubic centimeter = {cubic_centimeter}")
        print(f"Cubic meter = {cubic_meter}")
        print(f"Cubic inch = {cubic_inch}")
        print(f"Cubic feet = {cubic_feet}")
        print(f"Gallon(US) = {gallon_us}")
        print(f"Gallon(UK) = {gallon_uk}")
    if user_input_volume == "Gallon(US)" or user_input_volume == "gallon(US)" or user_input_volume == "gallon(us)":
        gallon_us = float(input("Gallon(US) = "))
        liter = gallon_us*3.785412
        kiloliter = liter/1000
        milliliter = liter*1000
        cubic_centimeter = milliliter
        cubic_meter = kiloliter
        cubic_inch = cubic_centimeter/16.387064
        cubic_feet = cubic_inch/1728
        cubic_yard = cubic_feet/27
        gallon_uk = liter*0.219969248
        print(f"Milliliter = {milliliter}")
        print(f"Liter = {liter}")
        print(f"Kiloliter = {kiloliter}")
        print(f"Cubic centimeter = {cubic_centimeter}")
        print(f"Cubic meter = {cubic_meter}")
        print(f"Cubic inch = {cubic_inch}")
        print(f"Cubic feet = {cubic_feet}")
        print(f"Cubic yard = {cubic_yard}")
        print(f"Gallon(UK) = {gallon_uk}")
    if user_input_volume == "Gallon(UK)" or user_input_volume == "gallon(UK)" or user_input_volume == "gallon(uk)":
        gallon_uk = float(input("Gallon(UK) = "))
        liter = gallon_uk*4.54609
        kiloliter = liter/1000
        milliliter = liter*1000
        cubic_centimeter = milliliter
        cubic_meter = kiloliter
        cubic_inch = cubic_centimeter/16.387064
        cubic_feet = cubic_inch/1728
        cubic_yard = cubic_feet/27
        gallon_us = liter*0.264172037
        print(f"Milliliter = {milliliter}")
        print(f"Liter = {liter}")
        print(f"Kiloliter = {kiloliter}")
        print(f"Cubic centimeter = {cubic_centimeter}")
        print(f"Cubic meter = {cubic_meter}")
        print(f"Cubic inch = {cubic_inch}")
        print(f"Cubic feet = {cubic_feet}")
        print(f"Cubic yard = {cubic_yard}")
        print(f"Gallon(US) = {gallon_us}")
if user_input == "Mass" or user_input == "mass":
    user_input_mass = input("Which unit of mass do you want to enter?: ")
    if user_input_mass == "Milligram" or user_input_mass == "milligram" or user_input_mass == "mg":
        milligram = float(input("Milligram = "))
        gram = milligram/1000
        kilogram = gram/1000
        tonn = kilogram/1000
        pound = kilogram*2.204622476
        ounce = gram/28.34952
        print(f"Gram = {gram}")
        print(f"Kilogram = {kilogram}")
        print(f"Tonn = {tonn}")
        print(f"Pound = {pound}")
        print(f"Ounce = {ounce}")
    if user_input_mass == "Gram" or user_input_mass == "gram" or user_input_mass == "g":
        gram = float(input("Gram = "))
        milligram = gram*1000
        kilogram = gram/1000
        tonn = kilogram/1000
        pound = kilogram*2.204622476
        ounce = gram/28.34952
        print(f"Milligram = {milligram}")
        print(f"Kilogram = {kilogram}")
        print(f"Tonn = {tonn}")
        print(f"Pound = {pound}")
        print(f"Ounce = {ounce}")
    if user_input_mass == "Kilogram" or user_input_mass == "kilogram" or user_input_mass == "kg":
        kilogram = float(input("Kilogram = "))
        gram = kilogram*1000
        milligram = gram*1000
        tonn = kilogram/1000
        pound = kilogram*2.204622476
        ounce = gram/28.34952
        print(f"Milligram = {milligram}")
        print(f"Gram = {gram}")
        print(f"Tonn = {tonn}")
        print(f"Pound = {pound}")
        print(f"Ounce = {ounce}")
    if user_input_mass == "Tonn" or user_input_mass == "tonn" or user_input_mass == "t":
        tonn = float(input("Tonn = "))
        kilogram = tonn*1000
        gram = kilogram*1000
        milligram = gram*1000
        pound = kilogram*2.204622476
        ounce = gram/28.34952
        print(f"Milligram = {milligram}")
        print(f"Gram = {gram}")
        print(f"Kilogram = {kilogram}")
        print(f"Pound = {pound}")
        print(f"Ounce = {ounce}")
    if user_input_mass == "Pound" or user_input_mass == "pound" or user_input_mass == "lb":
        pound = float(input("Pound = "))
        kilogram = pound/2.204622476
        gram = kilogram*1000
        milligram = gram*1000
        tonn = kilogram/1000
        ounce = gram/28.34952
        print(f"Milligram = {milligram}")
        print(f"Gram = {gram}")
        print(f"Kilogram = {kilogram}")
        print(f"Tonn = {tonn}")
        print(f"Ounce = {ounce}")
    if user_input_mass == "Ounce" or user_input_mass == "ounce" or user_input_mass == "oz":
        ounce = float(input("Ounce = "))
        gram = ounce*28.34952
        milligram = gram*1000
        kilogram = gram/1000
        tonn = kilogram/1000
        pound = kilogram*2.204622476
        print(f"Milligram = {milligram}")
        print(f"Gram = {gram}")
        print(f"Kilogram = {kilogram}")
        print(f"Tonn = {tonn}")
        print(f"Pound = {pound}")
if user_input == "Temperature" or user_input == "temperature":
    user_input_temperature = input("Which unit of temperature do you want to enter?: ")
    if user_input_temperature == "Celsius" or user_input_temperature == "celsius" or user_input_temperature == "C":
        celsius = float(input("Celsius = "))
        kelvin = celsius+273.15
        fahrenheit = (1.8*celsius)+32
        print(f"Fahrenheit = {fahrenheit}")
        print(f"Kelvin = {kelvin}")
    if user_input_temperature == "Fahrenheit" or user_input_temperature == "fahrenheit" or user_input_temperature == "F":
        fahrenheit = float(input("Fahrenheit = "))
        celsius = (fahrenheit-32)/1.8
        kelvin = celsius+273.15
        print(f"Celsius = {celsius}")
        print(f"Kelvin = {kelvin}")
    if user_input_temperature == "Kelvin" or user_input_temperature == "kelvin" or user_input_temperature == "K":
        kelvin = float(input("Kelvin = "))
        celsius = kelvin-273.15
        fahrenheit = (celsius*1.8)+32
        print(f"Celsius = {celsius}")
        print(f"Fahrenheit = {fahrenheit}")
if user_input == "Area" or user_input == "area":
    user_input_area = input("Which unit of area do you want to enter?: ")
    if user_input_area == "Square meter" or user_input_area == "square meter" or user_input_area == "s.m":
        square_meter = float(input("Square meter = "))
        square_centimeter = square_meter*10000
        square_millimeter = square_centimeter*100
        hectares = square_meter/10000
        square_kilometer = square_meter/1000000
        square_inch = square_centimeter/6.4516
        square_feet = square_inch/144
        square_yard = square_feet/9
        square_mile = square_kilometer/2.5921000000000003
        print(f"Square millimeter = {square_millimeter}")
        print(f"Square centimeter = {square_centimeter}")
        print(f"Hectares = {hectares}")
        print(f"Square kilometer = {square_kilometer}")
        print(f"Square inch = {square_inch}")
        print(f"Square feet = {square_feet}")
        print(f"Square yard = {square_yard}")
        print(f"Square mile = {square_mile}")
    if user_input_area == "Square millimeter" or user_input_area == "square millimeter" or user_input_area == "s.mm":
        square_millimeter = float(input("Square millimeter = "))
        square_centimeter = square_millimeter/100
        square_meter = square_centimeter/10000
        square_kilometer = square_meter/1000000
        hectares = square_meter/10000
        square_inch = square_centimeter/6.4516
        square_feet = square_inch/144
        square_yard = square_feet/9
        square_mile = square_kilometer/2.5921000000000003
        print(f"Square centimeter = {square_centimeter}")
        print(f"Square meter = {square_meter}")
        print(f"Hectares = {hectares}")
        print(f"Square kilometer = {square_kilometer}")
        print(f"Square inch = {square_inch}")
        print(f"Square feet = {square_feet}")
        print(f"Square yard = {square_yard}")
        print(f"Square mile = {square_mile}")
    if user_input_area == "Square centimeter" or user_input_area == "square centimeter" or user_input_area == "s.cm":
        square_centimeter = float(input("Square centimeter = "))
        square_millimeter = square_centimeter*100
        square_meter = square_centimeter/10000
        square_kilometer = square_meter/1000000
        hectares = square_meter/10000
        square_inch = square_centimeter/6.4516
        square_feet = square_inch/144
        square_yard = square_feet/9
        square_mile = square_kilometer/2.5921000000000003
        print(f"Square millimeter = {square_millimeter}")
        print(f"Square meter = {square_meter}")
        print(f"Hectares = {hectares}")
        print(f"Square kilometer = {square_kilometer}")
        print(f"Square inch = {square_inch}")
        print(f"Square feet = {square_feet}")
        print(f"Square yard = {square_yard}")
        print(f"Square mile = {square_mile}")
    if user_input_area == "Square kilometer" or user_input_area == "square kilometer" or user_input_area == "s.km":
        square_kilometer = float(input("Square kilometer = "))
        square_meter = square_kilometer*1000000
        square_centimeter = square_meter*10000
        square_millimeter = square_centimeter*100
        hectares = square_meter/10000
        square_inch = square_centimeter/6.4516
        square_feet = square_inch/144
        square_yard = square_feet/9
        square_mile = square_kilometer/2.5921000000000003
        print(f"Square millimeter = {square_millimeter}")
        print(f"Square centimeter = {square_centimeter}")
        print(f"Square meter = {square_meter}")
        print(f"Hectares = {hectares}")
        print(f"Square inch = {square_inch}")
        print(f"Square feet = {square_feet}")
        print(f"Square yard = {square_yard}")
        print(f"Square mile = {square_mile}")
    if user_input_area == "Hectares" or user_input_area == "hectares" or user_input_area == "ht":
        hectares = float(input("Hectares = "))
        square_meter = hectares*10000
        square_kilometer = square_meter/1000000
        square_centimeter = square_meter*10000
        square_millimeter = square_centimeter*100
        square_inch = square_centimeter/6.4516
        square_feet = square_inch/144
        square_yard = square_feet/9
        square_mile = square_kilometer/2.5921000000000003
        print(f"Square millimeter = {square_millimeter}")
        print(f"Square centimeter = {square_centimeter}")
        print(f"Square meter = {square_meter}")
        print(f"Square kilometer = {square_kilometer}")
        print(f"Square inch = {square_inch}")
        print(f"Square feet = {square_feet}")
        print(f"Square yard = {square_yard}")
        print(f"Square mile = {square_mile}")
    if user_input_area == "Square inch" or user_input_area == "square inch" or user_input_area == "s.in":
        square_inch = float(input("Square inch = "))
        square_centimeter = square_inch*6.4516
        square_millimeter = square_centimeter*100
        square_meter = square_centimeter/10000
        square_kilometer = square_meter/1000000
        hectares = square_meter/10000
        square_feet = square_inch/144
        square_yard = square_feet/9
        square_mile = square_kilometer/2.5921000000000003
        print(f"Square millimeter = {square_millimeter}")
        print(f"Square centimeter = {square_centimeter}")
        print(f"Square meter = {square_meter}")
        print(f"Hectares = {hectares}")
        print(f"Square kilometer = {square_kilometer}")
        print(f"Square feet = {square_feet}")
        print(f"Square yard = {square_yard}")
        print(f"Square mile = {square_mile}")
    if user_input_area == "Square feet" or user_input_area == "square feet" or user_input_area == "s.ft":
        square_feet = float(input("Square feet = "))
        square_inch = square_feet*144
        square_centimeter = square_inch*6.4516
        square_millimeter = square_centimeter*100
        square_meter = square_centimeter/10000
        square_kilometer = square_meter/1000000
        hectares = square_meter/10000
        square_yard = square_feet/9
        square_mile = square_kilometer/2.5921000000000003
        print(f"Square millimeter = {square_millimeter}")
        print(f"Square centimeter = {square_centimeter}")
        print(f"Square meter = {square_meter}")
        print(f"Hectares = {hectares}")
        print(f"Square kilometer = {square_kilometer}")
        print(f"Square inch = {square_inch}")
        print(f"Square yard = {square_yard}")
        print(f"Square mile = {square_mile}")
    if user_input_area == "Square yard" or user_input_area == "square yard" or user_input_area == "s.yd":
        square_yard = float(input("Square yard = "))
        square_feet = square_yard*9
        square_inch = square_feet*144
        square_centimeter = square_inch*6.4516
        square_millimeter = square_centimeter*100
        square_meter = square_centimeter/10000
        square_kilometer = square_meter/1000000
        hectares = square_meter/10000
        square_mile = square_kilometer/2.5921000000000003
        print(f"Square millimeter = {square_millimeter}")
        print(f"Square centimeter = {square_centimeter}")
        print(f"Square meter = {square_meter}")
        print(f"Hectares = {hectares}")
        print(f"Square kilometer = {square_kilometer}")
        print(f"Square inch = {square_inch}")
        print(f"Square feet = {square_feet}")
        print(f"Square mile = {square_mile}")
    if user_input_area == "Square mile" or user_input_area == "square mile" or user_input_area == "s.mi":
        square_mile = float(input("Square mile = "))
        square_kilometer = square_mile*2.5921000000000003
        square_meter = square_kilometer*1000000
        square_centimeter = square_meter*10000
        square_millimeter = square_centimeter*100
        hectares = square_meter/10000
        square_inch = square_centimeter/6.4516
        square_feet = square_inch/144
        square_yard = square_feet/9
        print(f"Square millimeter = {square_millimeter}")
        print(f"Square centimeter = {square_centimeter}")
        print(f"Square meter = {square_meter}")
        print(f"Hectares = {hectares}")
        print(f"Square kilometer = {square_kilometer}")
        print(f"Square inch = {square_inch}")
        print(f"Square feet = {square_feet}")
        print(f"Square yard = {square_yard}")
if user_input == "Speed" or user_input == "speed":
    user_input_speed = input("Which unit of speed do you want to enter?: ")
    if user_input_speed == "Kilometer per hour" or user_input_speed == "kilometer per hour" or user_input_speed == "km/h" or user_input_speed == "kmph":
        kilometer_per_hour = float(input("Kilometer per hour = "))
        kilometer_per_second = kilometer_per_hour/3600
        meter_per_second = kilometer_per_hour/3.6
        mach = kilometer_per_hour/1234.8
        feet_per_second = kilometer_per_hour*0.911344415
        yard_per_second = feet_per_second/3
        mile_per_hour = kilometer_per_hour*0.621371192
        knot = kilometer_per_hour*0.539956803
        print(f"Kilometer per second = {kilometer_per_second}")
        print(f"Meter per second = {meter_per_second}")
        print(f"Mach = {mach}")
        print(f"Feet per second = {feet_per_second}")
        print(f"Yard per second = {yard_per_second}")
        print(f"Mile per hour = {mile_per_hour}")
        print(f"Knot = {knot}")
    if user_input_speed == "Kilometer per second" or user_input_speed == "kilometer per second" or user_input_speed == "km/s" or user_input_speed == "kmps":
        kilometer_per_second = float(input("Kilometer per second = "))
        kilometer_per_hour = kilometer_per_second*3600
        meter_per_second = kilometer_per_second*1000
        mach = kilometer_per_hour/1234.8
        feet_per_second = kilometer_per_hour*0.911344415
        yard_per_second = feet_per_second/3
        mile_per_hour = kilometer_per_hour*0.621371192
        knot = kilometer_per_hour*0.539956803
        print(f"Kilometer per hour = {kilometer_per_hour}")
        print(f"Meter per second = {meter_per_second}")
        print(f"Mach = {mach}")
        print(f"Feet per second = {feet_per_second}")
        print(f"Yard per second = {yard_per_second}")
        print(f"Mile per hour = {mile_per_hour}")
        print(f"Knot = {knot}")
    if user_input_speed == "Meter per second" or user_input_speed == "meter per second" or user_input_speed == "m/s":
        meter_per_second = float(input("Meter per second = "))
        kilometer_per_hour = meter_per_second*3.6
        kilometer_per_second = kilometer_per_hour/3600
        mach = kilometer_per_hour/1234.8
        feet_per_second = kilometer_per_hour*0.911344415
        yard_per_second = feet_per_second/3
        mile_per_hour = kilometer_per_hour*0.621371192
        knot = kilometer_per_hour*0.539956803
        print(f"Kilometer per hour = {kilometer_per_hour}")
        print(f"Kilometer per second = {kilometer_per_second}")
        print(f"Mach = {mach}")
        print(f"Feet per second = {feet_per_second}")
        print(f"Yard per second = {yard_per_second}")
        print(f"Mile per hour = {mile_per_hour}")
        print(f"Knot = {knot}")
    if user_input_speed == "Mach" or user_input_speed == "mach":
        mach = float(input("Mach = "))
        kilometer_per_hour = mach*1234.8
        kilometer_per_second = kilometer_per_hour/3600
        meter_per_second = kilometer_per_hour/3.6
        feet_per_second = kilometer_per_hour*0.911344415
        yard_per_second = feet_per_second/3
        mile_per_hour = kilometer_per_hour*0.621371192
        knot = kilometer_per_hour*0.539956803
        print(f"Kilometer per hour = {kilometer_per_hour}")
        print(f"Kilometer per second = {kilometer_per_second}")
        print(f"Meter per second = {meter_per_second}")
        print(f"Feet per second = {feet_per_second}")
        print(f"Yard per second = {yard_per_second}")
        print(f"Mile per hour = {mile_per_hour}")
        print(f"Knot = {knot}")
    if user_input_speed == "Feet per second" or user_input_speed == "feet per second" or user_input_speed == "ft/s":
        feet_per_second = float(input("Feet per second = "))
        yard_per_second = feet_per_second/3
        meter_per_second = yard_per_second/1.093613298
        kilometer_per_hour = meter_per_second*3.6
        kilometer_per_second = kilometer_per_hour/3600
        mach = kilometer_per_hour/1234.8
        mile_per_hour = kilometer_per_hour*0.621371192
        knot = kilometer_per_hour*0.539956803
        print(f"Kilometer per hour = {kilometer_per_hour}")
        print(f"Kilometer per second = {kilometer_per_second}")
        print(f"Meter per second = {meter_per_second}")
        print(f"Mach = {mach}")
        print(f"Yard per second = {yard_per_second}")
        print(f"Mile per hour = {mile_per_hour}")
        print(f"Knot = {knot}")
    if user_input_speed == "Yard per second" or user_input_speed == "yard per second" or user_input_speed == "yd/s":
        yard_per_second = float(input("Yard per second = "))
        meter_per_second = yard_per_second/1.093613298
        kilometer_per_hour = meter_per_second*3.6
        kilometer_per_second = kilometer_per_hour/3600
        mach = kilometer_per_hour/1234.8
        feet_per_second = yard_per_second*3
        mile_per_hour = kilometer_per_hour*0.621371192
        knot = kilometer_per_hour*0.539956803
        print(f"Kilometer per hour = {kilometer_per_hour}")
        print(f"Kilometer per second = {kilometer_per_second}")
        print(f"Meter per second = {meter_per_second}")
        print(f"Mach = {mach}")
        print(f"Feet per second = {feet_per_second}")
        print(f"Mile per hour = {mile_per_hour}")
        print(f"Knot = {knot}")
    if user_input_speed == "Mile per hour" or user_input_speed == "mile per hour" or user_input_speed == "mph":
        mile_per_hour = float(input("Mile per hour = "))
        kilometer_per_hour = mile_per_hour*1.609344
        kilometer_per_second = kilometer_per_hour/3600
        meter_per_second = kilometer_per_second*1000
        mach = kilometer_per_hour/1234.8
        feet_per_second = kilometer_per_hour*0.911344415
        yard_per_second = feet_per_second/3
        knot = kilometer_per_hour*0.539956803
        print(f"Kilometer per hour = {kilometer_per_hour}")
        print(f"Kilometer per second = {kilometer_per_second}")
        print(f"Meter per second = {meter_per_second}")
        print(f"Mach = {mach}")
        print(f"Feet per second = {feet_per_second}")
        print(f"Yard per second = {yard_per_second}")
        print(f"Knot = {knot}")
    if user_input_speed == "Knot" or user_input_speed == "knot":
        knot = float(input("Knot = "))
        kilometer_per_hour = knot/0.539956803
        kilometer_per_second = kilometer_per_hour/3600
        meter_per_second = kilometer_per_second*1000
        mach = kilometer_per_hour/1234.8
        feet_per_second = kilometer_per_hour*0.911344415
        yard_per_second = feet_per_second/3
        mile_per_hour = kilometer_per_hour*0.621371192
        print(f"Kilometer per hour = {kilometer_per_hour}")
        print(f"Kilometer per second = {kilometer_per_second}")
        print(f"Meter per second = {meter_per_second}")
        print(f"Mach = {mach}")
        print(f"Feet per second = {feet_per_second}")
        print(f"Yard per second = {yard_per_second}")
        print(f"Mile per hour = {mile_per_hour}")
if user_input == "Time" or user_input == "time":
    user_input_time = input("Which unit of time do you want to enter?: ")
    if user_input_time == "Microsecond" or user_input_time == "microsecond":
        microsecond = float(input("Microsecond = "))
        millisecond = microsecond/1000
        second = millisecond/1000
        minute = second/60
        hour = minute/60
        day = hour/24
        week = day/7
        month = day/30
        year = day/365
        century = year/100
        print(f"Millisecond = {millisecond}")
        print(f"Second = {second}")
        print(f"Minute = {minute}")
        print(f"Hour = {hour}")
        print(f"Day = {day}")
        print(f"Week = {week}")
        print(f"Month = {month}")
        print(f"Year = {year}")
        print(f"Century = {century}")
    if user_input_time == "Millisecond" or user_input_time == "millisecond" or user_input_time == "ms":
        millisecond = float(input("Millisecond = "))
        microsecond = millisecond*1000
        second = millisecond/1000
        minute = second/60
        hour = minute/60
        day = hour/24
        week = day/7
        month = day/30
        year = day/365
        century = year/100
        print(f"Microsecond = {microsecond}")
        print(f"Second = {second}")
        print(f"Minute = {minute}")
        print(f"Hour = {hour}")
        print(f"Day = {day}")
        print(f"Week = {week}")
        print(f"Month = {month}")
        print(f"Year = {year}")
        print(f"Century = {century}")
    if  user_input_time == "Second" or user_input_time == "second" or user_input_time == "s":
        second = float(input("Second = "))
        millisecond = second*1000
        microsecond = millisecond*1000
        minute = second/60
        hour = minute/60
        day = hour/24
        week = day/7
        month = day/30
        year = day/365
        century = year/100
        print(f"Microsecond = {microsecond}")
        print(f"Millisecond = {millisecond}")
        print(f"Minute = {minute}")
        print(f"Hour = {hour}")
        print(f"Day = {day}")
        print(f"Week = {week}")
        print(f"Month = {month}")
        print(f"Year = {year}")
        print(f"Century = {century}")
    if user_input_time == "Minute" or user_input_time == "minute" or user_input_time == "m":
        minute = float(input("Minute = "))
        second = minute*60
        millisecond = second*1000
        microsecond = millisecond*1000
        hour = minute/60
        day = hour/24
        week = day/7
        month = day/30
        year = day/365
        century = year/100
        print(f"Microsecond = {microsecond}")
        print(f"Millisecond = {millisecond}")
        print(f"Second = {second}")
        print(f"Hour = {hour}")
        print(f"Day = {day}")
        print(f"Week = {week}")
        print(f"Month = {month}")
        print(f"Year = {year}")
        print(f"Century = {century}")
    if user_input_time == "Hour" or user_input_time == "hour" or user_input_time == "h":
        hour = float(input("Hour = "))
        minute = hour*60
        second = minute*60
        millisecond = second*1000
        microsecond = millisecond*1000
        day = hour/24
        week = day/7
        month = day/30
        year = day/365
        century = year/100
        print(f"Microsecond = {microsecond}")
        print(f"Millisecond = {millisecond}")
        print(f"Second = {second}")
        print(f"Minute = {minute}")
        print(f"Day = {day}")
        print(f"Week = {week}")
        print(f"Month = {month}")
        print(f"Year = {year}")
        print(f"Century = {century}")
    if user_input_time == "Day" or user_input_time == "day" or user_input_time == "d" or user_input_time == "dd":
        day = float(input("Day = "))
        hour = day*24
        minute = hour*60
        second = minute*60
        millisecond = second*1000
        microsecond = millisecond*1000
        week = day/7
        month = day/30
        year = day/365
        century = year/100
        print(f"Microsecond = {microsecond}")
        print(f"Millisecond = {millisecond}")
        print(f"Second = {second}")
        print(f"Minute = {minute}")
        print(f"Hour = {hour}")
        print(f"Week = {week}")
        print(f"Month = {month}")
        print(f"Year = {year}")
        print(f"Century = {century}")
    if user_input_time == "Week" or user_input_time == "week" or user_input_time == "w":
        week = float(input("Week = "))
        day = week*7
        hour = day*24
        minute = hour*60
        second = minute*60
        millisecond = second*1000
        microsecond = millisecond*1000
        month = day/30
        year = day/365
        century = year/100
        print(f"Microsecond = {microsecond}")
        print(f"Millisecond = {millisecond}")
        print(f"Second = {second}")
        print(f"Minute = {minute}")
        print(f"Hour = {hour}")
        print(f"Day = {day}")
        print(f"Month = {month}")
        print(f"Year = {year}")
        print(f"Century = {century}")
    if user_input_time == "Month" or user_input_time == "month" or user_input_time == "mm":
        month = float(input("Month = "))
        day = month*30
        hour = day*24
        minute = hour*60
        second = minute*60
        millisecond = second*1000
        microsecond = millisecond*1000
        year = day/365
        century = year/100
        week = day/7
        print(f"Microsecond = {microsecond}")
        print(f"Millisecond = {millisecond}")
        print(f"Second = {second}")
        print(f"Minute = {minute}")
        print(f"Hour = {hour}")
        print(f"Day = {day}")
        print(f"Week = {week}")
        print(f"Year = {year}")
        print(f"Century = {century}")
    if user_input_time == "Year" or user_input_time == "year" or user_input_time == "y" or user_input_time == "yy":
        year = float(input("Year = "))
        day = year*365
        hour = day*24
        minute = hour*60
        second = minute*60
        millisecond = second*1000
        microsecond = millisecond*1000
        week = day/7
        month = day/30
        century = year/100
        print(f"Microsecond = {microsecond}")
        print(f"Millisecond = {millisecond}")
        print(f"Second = {second}")
        print(f"Minute = {minute}")
        print(f"Hour = {hour}")
        print(f"Day = {day}")
        print(f"Week = {week}")
        print(f"Month = {month}")
        print(f"Century = {century}")
    if user_input_time == "Century" or user_input_time == "century" or user_input_time == "cen":
        century = float(input("Century = "))
        year = century*100
        day = year*365
        hour = day*24
        minute = hour*60
        second = minute*60
        millisecond = second*1000
        microsecond = millisecond*1000
        week = day/7
        month = year*12
        print(f"Microsecond = {microsecond}")
        print(f"Millisecond = {millisecond}")
        print(f"Second = {second}")
        print(f"Minute = {minute}")
        print(f"Hour = {hour}")
        print(f"Day = {day}")
        print(f"Week = {week}")
        print(f"Month = {month}")
        print(f"Year = {year}")
if user_input == "Power" or user_input == "power":
    user_input_power = input("Which unit of power do you want to enter?: ")
    if user_input_power == "Watt" or user_input_power == "watt" or user_input_power == "w":
        watt = float(input("Watt = "))
        kilowatt = watt/1000
        horsepower = kilowatt*1.341021859
        print(f"Kilowatt = {kilowatt}")
        print(f"Horsepower = {horsepower}")
    if user_input_power == "Kilowatt" or user_input_power == "kilowatt" or user_input_power == "kw":
        kilowatt = float(input("Kilowatt = "))
        watt = kilowatt*1000
        horsepower = kilowatt*1.341021859
        print(f"Watt = {watt}")
        print(f"Horsepower = {horsepower}")
    if user_input_power == "Horsepower" or user_input_power == "horsepower" or user_input_power == "hp":
        horsepower = float(input("Horsepower = "))
        kilowatt = horsepower/1.341021859
        watt = kilowatt*1000
        print(f"Watt = {watt}")
        print(f"Kilowatt = {kilowatt}")
if user_input == "Electronics" or user_input == "electronics":
    user_input_electronics = input("Which unit do you want calculate?: ")
    if user_input_electronics == "Watt" or user_input_electronics == "watt":
        volt = float(input("Volt = "))
        amphare = float(input("Amphare = "))
        watt = volt*amphare
        print(f"Watt = {watt}")
    if user_input_electronics == "Volt" or user_input_electronics == "volt":
        watt = float(input("Watt = "))
        amphare = float(input("Amphare = "))
        volt = watt/amphare
        print(f"Volt = {volt}")
    if user_input_electronics == "Amphare" or user_input_electronics == "amphare":
        watt = float(input("Watt = "))
        volt = float(input("Volt = "))
        amphare = watt/volt
        print(f"Amphare = {amphare}")
input("Press enter to exit: ")
