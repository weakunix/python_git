import todos

def main():
    if menu():
        todos.display()
    else:
        schedule.display()

if __name__ == "__main__":
    main()