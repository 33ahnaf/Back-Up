import os

def list_directory_contents(directory_path):
    try:
        # List the contents of the specified directory
        contents = os.listdir(directory_path)
        print(f"Contents of directory '{directory_path}':")
        for item in contents:
            print(item)
    except FileNotFoundError:
        print(f"Error: The directory '{directory_path}' does not exist.")
    except PermissionError:
        print(f"Error: You do not have permission to access '{directory_path}'.")
    except Exception as e:
        print(f"An unexpected error occurred: {e}")

# Specify the directory you want to list
directory_path = input("Enter the path of the directory to list: ")
list_directory_contents(directory_path)
