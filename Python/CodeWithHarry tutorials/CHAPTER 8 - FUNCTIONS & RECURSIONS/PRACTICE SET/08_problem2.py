def celsius_to_fahrenheit(celsius):
    fahrenheit = (celsius * 9.0/5.0) + 32.0
    return fahrenheit

celsius = float(input("Enter a number: "))

print(f"Fahrenheit = {round(celsius_to_fahrenheit(celsius), 2)} °F")