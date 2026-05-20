import os

def list_directory_contents(directory_path): # Cteate a function for the task.
    try:
        contents = os.listdir(directory_path)
        print(f"Contents of directory '{directory_path}':") # Prints the content(s)
        for item in contents:
            print(item)
    except FileNotFoundError:
        print(f"Error: The directory '{directory_path}' does not exist.") # Error handling
    except PermissionError:
        print(f"Error: You do not have permission to access '{directory_path}'.") # Error handling
    except Exception as e:
        print(f"An unexpected error occurred: {e}") # Error handling

directory_path = input("Enter the path of the directory to list: ") # Take the directory path from user
list_directory_contents(directory_path) # Calling function.
